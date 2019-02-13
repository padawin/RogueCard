#ifndef __GAME_OVER_STATE__
#define __GAME_OVER_STATE__

#include "../../State.hpp"

class GameOverScene : public State {
	private:
	static const std::string s_stateID;

	public:
	GameOverScene(UserActions &userActions);
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
