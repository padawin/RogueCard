#ifndef __GAMEOVER_STATE__
#define __GAMEOVER_STATE__

#include <string.h>
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "menus/GameOver.hpp"

class GameOverScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	int m_iTitleXPos = 0;
	Text m_title;
	GameOverMenu m_menu;

	public:
	GameOverScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
