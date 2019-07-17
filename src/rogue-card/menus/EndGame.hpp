#ifndef __ENDGAME_MENU__
#define __ENDGAME_MENU__

#include "Menu.hpp"

enum E_EndGameMenuItem {ENDGAME_MAIN_MENU, ENDGAME_QUIT, ENDGAME_NB_ITEMS};

class EndGameMenu : public Menu {
	S_MenuItem m_itemTexts[ENDGAME_NB_ITEMS] = {};
	int _getNbItems() const;
	S_MenuItem &_getItem(int itemIndex);

	public:
	EndGameMenu(std::shared_ptr<SDL2Renderer> renderer, int x, int y);
	~EndGameMenu() {}
	E_EndGameMenuItem getSelectedAction() const;
};

#endif
