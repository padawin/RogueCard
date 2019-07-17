#ifndef __WIN_STATE__
#define __WIN_STATE__

#include <string.h>
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "menus/EndGame.hpp"

class WinScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	int m_iTitleXPos = 0;
	Text m_title;
	Text m_text;
	EndGameMenu m_menu;

	void _executeMenuAction(StateMachine &stateMachine);

	public:
	WinScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
