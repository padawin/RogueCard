#ifndef __PLAYER_STATS_STATE__
#define __PLAYER_STATS_STATE__

#include <string.h>
#include <memory>
#include "common/ElementalEffects.hpp"
#include "game/SceneState.hpp"
#include "sdl2/Renderer.hpp"
#include "sdl2/Text.hpp"

#include "Player.hpp"
#include "Tab.hpp"
#include "ProgressBar.hpp"

enum StatCursorPosition {Stats, Levels, NbStatPositions};

class PlayerStatsScene : public SceneState {
	private:
	Player &m_player;

	std::shared_ptr<SDL2Renderer> m_renderer;
	StatCursorPosition m_cursorPosition = Stats;
	ElementalEffects m_elementalEffectsAtk;
	ElementalEffects m_elementalEffectsDef;

	// Titles
	Tab m_titlesTab;

	// Stats texts
	Text m_elementTexts[NB_ELEMENTS * 2] = {}; // x2 to have attack and defence texts
	Text m_healthTitle;
	Text m_floorTitle;

	// Levels texts
	Text m_nextLevel;
	Text m_skillsTexts[NB_XP_SKILLS] = {};
	ProgressBar m_aSkillsProgress[NB_XP_SKILLS];

	int m_iPage = 1;
	int m_iNBPages[NbStatPositions] = {
		1,
		1
	};

	int m_iStatsTitleX = 0;
	int m_iLevelsTitleX = 0;

	void _setDynamicTitles();
	void _setElementTitles();
	void _setSkillsTextsAndProgress();

	void _renderBackground() const;
	void _renderPagination() const;

	void _renderStats() const;
	void _renderLevels() const;

	public:
	PlayerStatsScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer, Player &player);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
