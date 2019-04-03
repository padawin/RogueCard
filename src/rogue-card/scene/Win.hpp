#ifndef __WIN_STATE__
#define __WIN_STATE__

#include <string.h>
#include "../game/State.hpp"

class WinScene : public State {
	public:
	WinScene(UserActions &userActions);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
