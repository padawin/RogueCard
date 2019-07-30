#ifndef __SCENE_STATE__
#define __SCENE_STATE__

#include "State.hpp"
#include "StateMachine.hpp"

class SceneState : public State {
	protected:
	UserActions &m_userActions;

	public:
	SceneState(UserActions &userActions);
	virtual void update(StateMachine<SceneState> &stateMachine) = 0;
};

#endif
