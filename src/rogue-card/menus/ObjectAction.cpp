#include "ObjectAction.hpp"
#include "../ObjectCard.hpp"
#include "../game/globals.hpp"

const int POSITION_X = 32;
const int POSITION_Y = 32;
const int TEXT_MAX_WIDTH = SCREEN_WIDTH - 64;

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
	int renderIndex = 0;
	for (int i = 0; i < m_iNbItems; ++i) {
		if (card->hasFlags(m_itemTexts[i].second)) {
			_renderItem(i, renderIndex);
			++renderIndex;
		}
	}
}

void ObjectAction::_renderItem(int itemIndex, int visibleIndex) {
	const int x = POSITION_X + (TEXT_MAX_WIDTH - m_itemTexts[itemIndex].first.getLength()) / 2;
	const int y = POSITION_Y + visibleIndex * m_itemTexts[itemIndex].first.getFontHeight();
	m_itemTexts[itemIndex].first.render(m_renderer->getRenderer(), x, y);
}
