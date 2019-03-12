#ifndef __INVENTORY_STATE__
#define __INVENTORY_STATE__

#include <string.h>
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../Player.hpp"
#include "../ActionBar.hpp"
#include "../menus/ObjectAction.hpp"

#define INVENTORY_PAGE_SIZE 18

class InventoryScene : public State {
	private:
	Player &m_player;
	std::shared_ptr<SDL2Renderer> m_renderer;
	ObjectAction m_objectActionMenu;
	ActionBar &m_actionBar;

	unsigned int m_cursorPosition = 0;
	std::pair<int, int> m_mCursorPositions[INVENTORY_PAGE_SIZE] = {};
	unsigned int m_iPage = 1;

	void _moveCursor(char direction);
	unsigned int _getCardIndex() const;

	void _renderBackground() const;
	void _renderCards();
	void _renderCursor();

	/* Menu actions */
	void _executeMenuAction(E_ObjectActionMenuItem action, StateMachine &stateMachine);
	void _useObject();
	void _equipObject();
	void _getObjectInfo();
	void _discardObject();
	void _openActionBar();

	public:
	InventoryScene(
		UserActions &userActions,
		ActionBar &m_actionBar,
		Player &player,
		std::shared_ptr<SDL2Renderer> renderer
	);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
