#ifndef __GAMEOVER_STATE__
#define __GAMEOVER_STATE__

#include <string.h>
#include "../game/State.hpp"

class GameOverScene : public State {
	public:
	GameOverScene(UserActions &userActions);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
