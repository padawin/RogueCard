#include "../game/Game.hpp"
#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "MainMenu.hpp"
#include "Play.hpp"
#include "Intro.hpp"
#include "../Save.hpp"

MainMenuScene::MainMenuScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
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

void MainMenuScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
	}
	else if (m_userActions.getActionState("CURSOR_UP")) {
		m_menu.selectPrevious();
	}
	else if (m_userActions.getActionState("CURSOR_DOWN")) {
		m_menu.selectNext();
	}
	else if (m_userActions.getActionState("MENU_ACTION")) {
		_executeMenuAction(stateMachine);
	}
}

void MainMenuScene::_executeMenuAction(StateMachine &stateMachine) {
	switch (m_menu.getSelectedAction()) {
		case NEW_GAME:
			stateMachine.changeState(new IntroScene(m_userActions, m_renderer));
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
