#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include "Menu.hpp"

enum E_MainMenuItem {LOAD_GAME, NEW_GAME, MAIN_MENU_QUIT, MAIN_MENU_NB_ITEMS};

const unsigned int FLAG_CONTEXT_SAVE_EXISTS = 0x01;

class MainMenu : public Menu {
	S_MenuItem m_itemTexts[MAIN_MENU_NB_ITEMS] = {};
	int _getNbItems() const;
	S_MenuItem &_getItem(int itemIndex);

	public:
	MainMenu(std::shared_ptr<SDL2Renderer> renderer);
	~MainMenu() {}
	E_MainMenuItem getSelectedAction() const;
};

#endif
