#include "EndGame.hpp"
#include "../ObjectCard.hpp"

EndGameMenu::EndGameMenu(std::shared_ptr<SDL2Renderer> renderer, int x, int y) :
	Menu(renderer)
{
	m_iX = x;
	m_iY = y;

	m_itemTexts[ENDGAME_MAIN_MENU].text = Text();
	m_itemTexts[ENDGAME_MAIN_MENU].text.setText("BACK TO MAIN MENU");

	m_itemTexts[ENDGAME_QUIT].text = Text();
	m_itemTexts[ENDGAME_QUIT].text.setText("QUIT");
}

E_EndGameMenuItem EndGameMenu::getSelectedAction() const {
	return (E_EndGameMenuItem) m_selectedAction;
}

int EndGameMenu::_getNbItems() const {
	return ENDGAME_NB_ITEMS;
}

S_MenuItem &EndGameMenu::_getItem(int itemIndex) {
	return m_itemTexts[itemIndex];
}
