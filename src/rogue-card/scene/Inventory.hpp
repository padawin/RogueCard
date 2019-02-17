#ifndef __INVENTORY_STATE__
#define __INVENTORY_STATE__

#include <string.h>
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../Player.hpp"

#define INVENTORY_PAGE_SIZE 18

class InventoryScene : public State {
	private:
	Player &m_player;
	std::shared_ptr<SDL2Renderer> m_renderer;

	int m_cursorPosition = 0;
	std::pair<int, int> m_mCursorPositions[INVENTORY_PAGE_SIZE] = {};
	int m_iPage = 1;

	void _moveCursor(char direction);

	void _renderBackground() const;
	void _renderCards();
	void _renderCursor();

	public:
	InventoryScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
