#ifndef __QUICK_ACTION_BAR__
#define __QUICK_ACTION_BAR__

#include <string.h>
#include "../sdl2/Renderer.hpp"
#include "../game/State.hpp"
#include "../ActionBar.hpp"

class QuickActionBarScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	ActionBar &m_actionBar;

	void _renderBackground() const;

	public:
	QuickActionBarScene(
		UserActions &userActions,
		ActionBar &actionBar,
		std::shared_ptr<SDL2Renderer> renderer
	);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
