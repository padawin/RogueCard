#ifndef __PLAYER_STATS_STATE__
#define __PLAYER_STATS_STATE__

#include <string.h>
#include <memory>
#include "../game/types.hpp"
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"

enum StatCursorPosition {Stats, Levels, NbStatPositions};

class PlayerStatsScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	StatCursorPosition m_cursorPosition = Stats;
	std::map<StatCursorPosition, S_Coordinates> m_mCursorPositions = {};
	Text m_statsTitle;
	Text m_levelsTitle;

	int m_iStatsTitleX = 0;
	int m_iLevelsTitleX = 0;

	void _renderBackground() const;
	void _renderCursor();
	void _renderTitles();

	public:
	PlayerStatsScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
