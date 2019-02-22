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
	m_itemTexts[0].first = Text();
	m_itemTexts[0].first.setText("Use");
	m_itemTexts[0].second = FLAG_USABLE;

	m_itemTexts[1].first = Text();
	m_itemTexts[1].first.setText("Equip");
	m_itemTexts[1].second = FLAG_EQUIPABLE;

	m_itemTexts[2].first = Text();
	m_itemTexts[2].first.setText("Info");
	m_itemTexts[2].second = 0;

	m_itemTexts[3].first = Text();
	m_itemTexts[3].first.setText("Discard");
	m_itemTexts[3].second = 0;

	m_itemTexts[4].first = Text();
	m_itemTexts[4].first.setText("Add to ActionBar");
	m_itemTexts[4].second = FLAG_USABLE;

	m_itemTexts[5].first = Text();
	m_itemTexts[5].first.setText("Back");
	m_itemTexts[5].second = 0;
}

void ObjectAction::render(std::shared_ptr<ObjectCard> card) {
	_renderItems(card);
	_renderCursor();
}

void ObjectAction::_renderItems(std::shared_ptr<ObjectCard> card) {
	TextureManager::Instance()->drawFrame(
		"menu-background",
		POSITION_X,
		POSITION_Y,
		MENU_WIDTH,
		16,
		0, 0,
		m_renderer->getRenderer()
	);
	int itemIndex, renderIndex = 0;
	for (itemIndex = 0; itemIndex < m_iNbItems; ++itemIndex) {
		if (card->hasFlags(m_itemTexts[itemIndex].second)) {
			TextureManager::Instance()->drawFrame(
				"menu-background",
				POSITION_X,
				TEXT_POS_Y + renderIndex * m_itemTexts[itemIndex].first.getFontHeight(),
				MENU_WIDTH,
				16,
				0, 1,
				m_renderer->getRenderer()
			);
			_renderItem(itemIndex, renderIndex);
			++renderIndex;
		}
	}
	TextureManager::Instance()->drawFrame(
		"menu-background",
		POSITION_X,
		POSITION_Y + renderIndex * m_itemTexts[itemIndex].first.getFontHeight(),
		MENU_WIDTH,
		16,
		0, 2,
		m_renderer->getRenderer()
	);
}

void ObjectAction::_renderCursor() {

}

void ObjectAction::_renderItem(int itemIndex, int visibleIndex) {
	const int x = TEXT_POS_X + (TEXT_MAX_WIDTH - m_itemTexts[itemIndex].first.getLength()) / 2;
	const int y = TEXT_POS_Y + visibleIndex * m_itemTexts[itemIndex].first.getFontHeight();
	m_itemTexts[itemIndex].first.render(m_renderer->getRenderer(), x, y);
}
