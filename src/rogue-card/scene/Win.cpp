#include "../game/StateMachine.hpp"
#include "Win.hpp"

WinScene::WinScene(UserActions &userActions) :
	State(userActions)
{}

std::string WinScene::getStateID() const {
	return "WinScene";
}

bool WinScene::onEnter() {
	return true;
}

void WinScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
	}
}

void WinScene::render() {
}
