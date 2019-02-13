#include "GameOver.hpp"
#include "../../StateMachine.hpp"

const std::string GameOverScene::s_stateID = "GAME_OVER";

GameOverScene::GameOverScene(UserActions &userActions) :
	State(userActions)
{
}
void GameOverScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}
}

void GameOverScene::render() {
}


std::string GameOverScene::getStateID() const {
	return s_stateID;
}
