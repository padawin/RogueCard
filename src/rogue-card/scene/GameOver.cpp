#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "GameOver.hpp"

GameOverScene::GameOverScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_renderer(renderer),
	m_title(Text()),
	m_menu(GameOverMenu(renderer))
{}

std::string GameOverScene::getStateID() const {
	return "GameOverScene";
}

bool GameOverScene::onEnter() {
	m_title.setText("GAME OVER");
	m_iTitleXPos = (SCREEN_WIDTH - m_title.getLength()) / 2;
	m_menu.init();
	return true;
}

void GameOverScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
	}
}

void GameOverScene::render() {
	m_title.render(m_renderer->getRenderer(), m_iTitleXPos, 32);
	m_menu.render();
}
