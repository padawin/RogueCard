#ifndef __PLAYER_STATS_STATE__
#define __PLAYER_STATS_STATE__

#include <string.h>
#include <memory>
#include "../game/types.hpp"
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"

enum StatCursorPosition {Stats, Levels, NbStatPositions};

class PlayerStatsScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	StatCursorPosition m_cursorPosition = Stats;
	std::map<StatCursorPosition, S_Coordinates> m_mCursorPositions = {};

	void _renderBackground() const;
	void _renderCursor();

	public:
	PlayerStatsScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
