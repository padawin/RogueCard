#include "ObjectAction.hpp"
#include "../ObjectCard.hpp"
#include "../game/globals.hpp"
#include "../sdl2/TextureManager.hpp"

const int POSITION_X = 32;
const int POSITION_Y = 32;
const int MARGIN_X = 16;
const int MARGIN_Y = 16;
const int TEXT_POS_X = POSITION_X + MARGIN_X;
const int TEXT_POS_Y = POSITION_Y + MARGIN_Y;
const int MENU_WIDTH = SCREEN_WIDTH - POSITION_X * 2;
const int TEXT_MAX_WIDTH = MENU_WIDTH - MARGIN_X * 2;

ObjectAction::ObjectAction(std::shared_ptr<SDL2Renderer> renderer) :
	m_renderer(renderer)
{
	m_itemTexts[USE].first = Text();
	m_itemTexts[USE].first.setText("Use");
	m_itemTexts[USE].second = FLAG_USABLE;

	m_itemTexts[INFO].first = Text();
	m_itemTexts[INFO].first.setText("Info");
	m_itemTexts[INFO].second = 0;

	m_itemTexts[DISCARD].first = Text();
	m_itemTexts[DISCARD].first.setText("Discard");
	m_itemTexts[DISCARD].second = 0;

	m_itemTexts[ACTIONBAR].first = Text();
	m_itemTexts[ACTIONBAR].first.setText("ActionBar");
	m_itemTexts[ACTIONBAR].second = FLAG_USABLE;

	m_itemTexts[BACK].first = Text();
	m_itemTexts[BACK].first.setText("Back");
	m_itemTexts[BACK].second = 0;
}

void ObjectAction::open(std::shared_ptr<ObjectCard> card, bool inActionBar) {
	_reset();
	m_card = card;
	for (int i = 0; i < NB_ITEMS; ++i) {
		if (m_card->hasFlags(m_itemTexts[i].second)) {
			++m_iNbVisibleItems;
		}
	}
	if (m_card->hasFlags(m_itemTexts[ACTIONBAR].second)) {
		m_itemTexts[ACTIONBAR].first.setText(
			inActionBar ? "Remove from ActionBar" : "Add to ActionBar"
		);
	}
	_setSelectedAction();
	_setCursorPosition();
}

bool ObjectAction::isOpen() const {
	return m_card != nullptr;
}

void ObjectAction::close() {
	_reset();
}

void ObjectAction::_reset() {
	m_card = nullptr;
	m_iNbVisibleItems = 0;
	m_iSelectedItemIndex = 0;
	_setCursorPosition();
}

void ObjectAction::selectPrevious() {
	m_iSelectedItemIndex = (m_iNbVisibleItems + m_iSelectedItemIndex - 1) % m_iNbVisibleItems;
	_setSelectedAction();
	_setCursorPosition();
}

void ObjectAction::selectNext() {
	m_iSelectedItemIndex = (m_iSelectedItemIndex + 1) % m_iNbVisibleItems;
	_setSelectedAction();
	_setCursorPosition();
}

E_ObjectActionMenuItem ObjectAction::getSelectedAction() const {
	return m_selectedAction;
}

void ObjectAction::_setSelectedAction() {
	for (int renderIndex = 0, itemIndex = 0; itemIndex < NB_ITEMS; ++itemIndex) {
		if (m_card->hasFlags(m_itemTexts[itemIndex].second)) {
			if (renderIndex == m_iSelectedItemIndex) {
				m_selectedAction = (E_ObjectActionMenuItem) itemIndex;
				break;
			}
			++renderIndex;
		}
	}
}

void ObjectAction::_setCursorPosition() {
	m_iCursorPosition = TEXT_POS_Y + m_iSelectedItemIndex * 16;
}

void ObjectAction::render() {
	_renderItems();
	_renderCursor();
}

void ObjectAction::_renderItems() {
	_renderBackground(0, POSITION_Y);
	for (int renderIndex = 0, itemIndex = 0; itemIndex < NB_ITEMS; ++itemIndex) {
		if (m_card->hasFlags(m_itemTexts[itemIndex].second)) {
			_renderBackground(1, TEXT_POS_Y + renderIndex * 16);
			_renderItem(itemIndex, renderIndex);
			if (renderIndex == m_iSelectedItemIndex) {
				_renderCursor();
			}
			++renderIndex;
		}
	}
	_renderBackground(2, TEXT_POS_Y + m_iNbVisibleItems * 16);
}

void ObjectAction::_renderBackground(int spriteIndex, int y) {
	TextureManager::Instance()->drawFrame(
		"menu-background",
		POSITION_X,
		y,
		MENU_WIDTH,
		16,
		0, spriteIndex,
		m_renderer->getRenderer()
	);
}

void ObjectAction::_renderCursor() {
	TextureManager::Instance()->drawFrame(
		"menu-background",
		POSITION_X,
		m_iCursorPosition,
		MENU_WIDTH,
		16,
		0, 3,
		m_renderer->getRenderer()
	);
}

void ObjectAction::_renderItem(int itemIndex, int visibleIndex) {
	const int x = TEXT_POS_X + (TEXT_MAX_WIDTH - m_itemTexts[itemIndex].first.getLength()) / 2;
	const int y = TEXT_POS_Y + visibleIndex * 16;
	m_itemTexts[itemIndex].first.render(m_renderer->getRenderer(), x, y);
}
