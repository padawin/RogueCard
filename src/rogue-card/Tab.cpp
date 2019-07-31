#include "Tab.hpp"
#include "../sdl2/TextureManager.hpp"

const int STAT_CURSOR_WIDTH = 144;
const int STAT_CURSOR_HEIGHT = 14;

const int CURSOR_X_POSITIONS[2] = {8, 166};

Tab::Tab(std::string text1, std::string text2, int y, int selected) {
	m_text1.setText(text1);
	m_text2.setText(text2);
	m_iY = y;
	m_iSelectedTab = selected;
	if (m_iSelectedTab < 0) {
		m_iSelectedTab = 0;
	}
	if (m_iSelectedTab > 1) {
		m_iSelectedTab = 1;
	}
	// Horizontally center the titles
	m_iText1X = CURSOR_X_POSITIONS[0] + (STAT_CURSOR_WIDTH - m_text1.getLength()) / 2;
	m_iText2X = CURSOR_X_POSITIONS[1] + (STAT_CURSOR_WIDTH - m_text2.getLength()) / 2;
}

void Tab::render(SDL_Renderer *renderer) {
	m_text1.render(renderer, m_iText1X, m_iY);
	m_text2.render(renderer, m_iText2X, m_iY);
	TextureManager::Instance()->draw(
		"cursor-tab",
		CURSOR_X_POSITIONS[m_iSelectedTab],
		m_iY,
		STAT_CURSOR_WIDTH,
		STAT_CURSOR_HEIGHT,
		renderer
	);
}

void Tab::selectNext() {
	if (m_iSelectedTab == 0) {
		m_iSelectedTab = 1;
	}
}

void Tab::selectPrev() {
	if (m_iSelectedTab == 1) {
		m_iSelectedTab = 0;
	}
}
