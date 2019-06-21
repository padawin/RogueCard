#include "PlayerStats.hpp"
#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "../sdl2/TextureManager.hpp"

PlayerStatsScene::PlayerStatsScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_renderer(renderer)
{}

std::string PlayerStatsScene::getStateID() const {
	return "PlayerStatsScene";
}

bool PlayerStatsScene::onEnter() {
	return true;
}

void PlayerStatsScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("BACK")) {
		stateMachine.popState();
	}
}

void PlayerStatsScene::render() {
	_renderBackground();
}

void PlayerStatsScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"ui-player-stats", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}
