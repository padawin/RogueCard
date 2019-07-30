#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "GameOver.hpp"
#include "MainMenu.hpp"

GameOverScene::GameOverScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	SceneState(userActions),
	m_renderer(renderer),
	m_title(Text()),
	m_menu(EndGameMenu(renderer, 32, 80))
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

void GameOverScene::update(StateMachine<SceneState> &stateMachine) {
	if (m_userActions.getActionState("CURSOR_UP")) {
		m_menu.selectPrevious();
	}
	else if (m_userActions.getActionState("CURSOR_DOWN")) {
		m_menu.selectNext();
	}
	else if (m_userActions.getActionState("MENU_ACTION")) {
		_executeMenuAction(stateMachine);
	}
}

void GameOverScene::_executeMenuAction(StateMachine<SceneState> &stateMachine) {
	switch (m_menu.getSelectedAction()) {
		case ENDGAME_MAIN_MENU:
			stateMachine.changeState(new MainMenuScene(m_userActions, m_renderer));
			break;
		case ENDGAME_QUIT:
			stateMachine.clean();
			break;
		case ENDGAME_NB_ITEMS:
		default:
			break;
	}
}

void GameOverScene::render() {
	m_title.render(m_renderer->getRenderer(), m_iTitleXPos, 32);
	m_menu.render();
}
