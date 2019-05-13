#ifndef __MAIN_MENU_STATE__
#define __MAIN_MENU_STATE__

#include <string.h>
#include <memory>
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "menus/Main.hpp"

class MainMenuScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	Text m_title;
	int m_iTitleXPos = 0;
	MainMenu m_mainMenu;

	void _executeMenuAction(StateMachine &stateMachine);

	public:
	MainMenuScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
