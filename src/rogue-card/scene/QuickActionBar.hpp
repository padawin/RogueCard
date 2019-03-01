#ifndef __QUICK_ACTION_BAR__
#define __QUICK_ACTION_BAR__

#include <string.h>
#include "../sdl2/Renderer.hpp"
#include "../game/State.hpp"

class QuickActionBarScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	void _renderBackground() const;

	public:
	QuickActionBarScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
