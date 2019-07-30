#ifndef __GAMEOVER_STATE__
#define __GAMEOVER_STATE__

#include <string.h>
#include "../game/SceneState.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "menus/EndGame.hpp"

class GameOverScene : public SceneState {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	int m_iTitleXPos = 0;
	Text m_title;
	EndGameMenu m_menu;

	void _executeMenuAction(StateMachine<SceneState> &stateMachine);

	public:
	GameOverScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
