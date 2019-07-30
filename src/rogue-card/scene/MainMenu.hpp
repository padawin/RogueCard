#ifndef __MAIN_MENU_STATE__
#define __MAIN_MENU_STATE__

#include <string.h>
#include <memory>
#include "../game/SceneState.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "menus/Main.hpp"

class MainMenuScene : public SceneState {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	int m_iTitleXPos = 0;
	Text m_title;
	MainMenu m_menu;

	void _executeMenuAction(StateMachine<SceneState> &stateMachine);

	public:
	MainMenuScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
