#include "Main.hpp"
#include "../ObjectCard.hpp"

MainMenu::MainMenu(std::shared_ptr<SDL2Renderer> renderer) :
	Menu(renderer)
{
	m_iX = 32;
	m_iY = 80;

	m_itemTexts[NEW_GAME].text = Text();
	m_itemTexts[NEW_GAME].text.setText("NEW GAME");

	m_itemTexts[LOAD_GAME].text = Text();
	m_itemTexts[LOAD_GAME].text.setText("LOAD GAME");
	m_itemTexts[LOAD_GAME].context = FLAG_CONTEXT_SAVE_EXISTS;

	m_itemTexts[MAIN_MENU_QUIT].text = Text();
	m_itemTexts[MAIN_MENU_QUIT].text.setText("QUIT");
}

E_MainMenuItem MainMenu::getSelectedAction() const {
	return (E_MainMenuItem) m_selectedAction;
}

int MainMenu::_getNbItems() const {
	return MAIN_MENU_NB_ITEMS;
}

S_MenuItem &MainMenu::_getItem(int itemIndex) {
	return m_itemTexts[itemIndex];
}
