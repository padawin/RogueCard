#include "../../StateMachine.hpp"
#include "../../globals.hpp"
#include "../Save.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Play.hpp"
#include "GameOver.hpp"
#include <iostream>

PlayScene::PlayScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions), m_player(player), m_renderer(renderer)
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
	_renderBackground();
}

void PlayScene::_renderBackground() const {
	TextureManager::Instance()->drawImage("ui", m_renderer->getRenderer());
}
