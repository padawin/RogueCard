#ifndef __QUICK_ACTION_BAR__
#define __QUICK_ACTION_BAR__

#include <string.h>
#include "sdl2/Renderer.hpp"
#include "game/SceneState.hpp"
#include "rogue-card/coordinates.hpp"
#include "Player.hpp"

class QuickActionBarScene : public SceneState {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	Player &m_player;
	std::shared_ptr<ObjectCard> m_card = nullptr;
	int m_cursorPosition = 0;
	S_Coordinates m_mCursorPositions[ACTION_BAR_SIZE] = {};

	void _renderBackground() const;
	void _renderCards() const;
	void _renderCursor() const;

	public:
	QuickActionBarScene(
		UserActions &userActions,
		Player &player,
		std::shared_ptr<ObjectCard> card,
		std::shared_ptr<SDL2Renderer> renderer
	);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
