#include "../../StateMachine.hpp"
#include "../../globals.hpp"
#include "../Save.hpp"
#include "Play.hpp"
#include "GameOver.hpp"
#include <iostream>

PlayScene::PlayScene(UserActions &userActions, Player &player) :
	State(userActions), m_player(player)
{
}

std::string PlayScene::getStateID() const {
	return "PlayScene";
}

bool PlayScene::onEnter() {
	Save s = Save(m_player);
	if (s.exists()) {
		std::clog << "Save found, load\n";
		s.load();
	}
	else {
		std::clog << "No save found, create new one\n";
		s.create();
	}
	return true;
}

void PlayScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}
}

void PlayScene::render(const Renderer *renderer __attribute__((unused))) {
}
