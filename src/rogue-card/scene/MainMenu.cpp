#include "game/Game.hpp"
#include "globals.hpp"
#include "game/StateMachine.hpp"
#include "MainMenu.hpp"
#include "Play.hpp"
#include "PlayerCreation.hpp"
#include "../Save.hpp"

MainMenuScene::MainMenuScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	SceneState(userActions),
	m_renderer(renderer),
	m_title(Text()),
	m_menu(MainMenu(renderer))
{
}

std::string MainMenuScene::getStateID() const {
	return "MainMenuScene";
}

bool MainMenuScene::onEnter() {
	m_title.setText("CARD ROGUE");
	m_iTitleXPos = (SCREEN_WIDTH - m_title.getLength()) / 2;
	if (Save::exists()) {
		m_menu.setContext(FLAG_CONTEXT_SAVE_EXISTS);
	}
	m_menu.init();
	return true;
}

void MainMenuScene::update(StateMachine<SceneState> &stateMachine) {
	if (m_userActions.getActionState("QUIT") == ActionState::ACTION_PRESSED) {
		stateMachine.clean();
	}
	else if (m_userActions.is("CURSOR_UP", ActionState::ACTION_PRESSED | ActionState::ACTION_DOWN)) {
		m_menu.selectPrevious();
	}
	else if (m_userActions.is("CURSOR_DOWN", ActionState::ACTION_PRESSED | ActionState::ACTION_DOWN)) {
		m_menu.selectNext();
	}
	else if (m_userActions.getActionState("MENU_ACTION") == ActionState::ACTION_PRESSED) {
		_executeMenuAction(stateMachine);
	}
}

void MainMenuScene::_executeMenuAction(StateMachine<SceneState> &stateMachine) {
	switch (m_menu.getSelectedAction()) {
		case NEW_GAME:
			stateMachine.changeState(new PlayerCreationScene(m_userActions, m_renderer));
			break;
		case LOAD_GAME:
			stateMachine.changeState(new PlayScene(m_userActions, m_renderer));
			break;
		case MAIN_MENU_QUIT:
			stateMachine.clean();
			break;
		case MAIN_MENU_NB_ITEMS:
		default:
			break;
	}
}

void MainMenuScene::render() {
	m_title.render(m_renderer->getRenderer(), m_iTitleXPos, 32);
	m_menu.render();
}
