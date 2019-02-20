#ifndef __INVENTORY_STATE__
#define __INVENTORY_STATE__

#include <string.h>
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../Player.hpp"
#include "../menus/ObjectAction.hpp"

#define INVENTORY_PAGE_SIZE 18

class InventoryScene : public State {
	private:
	Player &m_player;
	std::shared_ptr<SDL2Renderer> m_renderer;
	ObjectAction m_objectActionMenu;

	int m_cursorPosition = 0;
	std::pair<int, int> m_mCursorPositions[INVENTORY_PAGE_SIZE] = {};
	int m_iPage = 1;

	bool m_bObjectMenuOpen = false;

	void _moveCursor(char direction);
	int _getCardIndex() const;

	void _renderBackground() const;
	void _renderCards();
	void _renderCursor();

	void _openMenu();
	/* Menu actions */
	void _useObject();
	void _equipObject();
	void _getObjectInfo();
	void _discardObject();
	void _openActionBar();
	void _closeMenu();

	public:
	InventoryScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
