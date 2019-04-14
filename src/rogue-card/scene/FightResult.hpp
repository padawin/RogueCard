#ifndef __FIGHT_RESULT__
#define __FIGHT_RESULT__

#include "../game/State.hpp"
#include "../game/StateMachine.hpp"
#include "../Fight.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"

class FightResultScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	Fight &m_fight;
	Text m_title;
	Text m_summary;

	public:
	FightResultScene(UserActions &userActions, Fight &fight, std::shared_ptr<SDL2Renderer> renderer);
	std::string getStateID() const;
	void update(StateMachine &stateMachine);
	void render();
};

#endif
