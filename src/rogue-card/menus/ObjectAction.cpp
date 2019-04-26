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
	m_itemTexts[USE].text = Text();
	m_itemTexts[USE].text.setText("Use");
	m_itemTexts[USE].objectFlags = FLAG_USABLE | FLAG_APPLY_ON_SELF;
	m_itemTexts[USE].valid = false;

	m_itemTexts[INFO].text = Text();
	m_itemTexts[INFO].text.setText("Info");
	m_itemTexts[INFO].objectFlags = 0;
	m_itemTexts[INFO].valid = false;

	m_itemTexts[DISCARD].text = Text();
	m_itemTexts[DISCARD].text.setText("Discard");
	m_itemTexts[DISCARD].objectFlags = 0;
	m_itemTexts[DISCARD].valid = false;

	m_itemTexts[SORT].text = Text();
	m_itemTexts[SORT].text.setText("Sort");
	m_itemTexts[SORT].objectFlags = 0;
	m_itemTexts[SORT].valid = false;

	m_itemTexts[ACTIONBAR].text = Text();
	m_itemTexts[ACTIONBAR].text.setText("ActionBar");
	m_itemTexts[ACTIONBAR].objectFlags = FLAG_USABLE;
	m_itemTexts[ACTIONBAR].valid = false;

	m_itemTexts[BACK].text = Text();
	m_itemTexts[BACK].text.setText("Back");
	m_itemTexts[BACK].objectFlags = 0;
	m_itemTexts[BACK].valid = false;
}

bool ObjectAction::_isActionValid(int actionIndex) const {
	unsigned int context = m_itemTexts[actionIndex].context;
	return m_card->hasFlags(m_itemTexts[actionIndex].objectFlags);
}

void ObjectAction::open(std::shared_ptr<ObjectCard> card, bool inActionBar) {
	_reset();
	m_card = card;
	for (int i = 0; i < NB_ITEMS; ++i) {
		if (_isActionValid(i)) {
			++m_iNbVisibleItems;
			m_itemTexts[i].valid = true;
		}
		else {
			m_itemTexts[i].valid = false;
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
	for (int i = 0; i < NB_ITEMS; ++i) {
		m_itemTexts[i].valid = false;
	}
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
		if (m_itemTexts[itemIndex].valid) {
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
		if (m_itemTexts[itemIndex].valid) {
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
	const int x = TEXT_POS_X + (TEXT_MAX_WIDTH - m_itemTexts[itemIndex].text.getLength()) / 2;
	const int y = TEXT_POS_Y + visibleIndex * 16;
	m_itemTexts[itemIndex].text.render(m_renderer->getRenderer(), x, y);
}
