#ifndef __FIGHT_RESULT__
#define __FIGHT_RESULT__

#include "../game/SceneState.hpp"
#include "../game/StateMachine.hpp"
#include "../Fight.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"

class FightResultScene : public SceneState {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	Fight &m_fight;
	unsigned int m_iPage = 0;
	unsigned int m_iPagesToSee = 0;
	Text m_title;
	Text m_summary;
	std::pair<int, int> m_aSkillLevels[NB_XP_SKILLS] = {};

	bool _handleSkillsLevelUp();
	bool _handleLevelUp() const;

	void _renderSkillsXP();
	void _renderSkillsLevels();
	void _renderLevel();

	public:
	FightResultScene(UserActions &userActions, Fight &fight, std::shared_ptr<SDL2Renderer> renderer);
	std::string getStateID() const;
	void update(StateMachine<SceneState> &stateMachine);
	void render();
};

#endif
