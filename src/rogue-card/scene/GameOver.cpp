#include "../game/StateMachine.hpp"
#include "GameOver.hpp"

GameOverScene::GameOverScene(UserActions &userActions) :
	State(userActions)
{}

std::string GameOverScene::getStateID() const {
	return "GameOverScene";
}

bool GameOverScene::onEnter() {
	return true;
}

void GameOverScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
	}
}

void GameOverScene::render() {
}
