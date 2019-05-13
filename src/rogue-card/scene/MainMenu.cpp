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
	m_mainMenu(MainMenu(renderer))
{
	m_title.setText("CARD ROGUE");
	m_iTitleXPos = (SCREEN_WIDTH - m_title.getLength()) / 2;
	if (Save::exists()) {
		m_mainMenu.setContext(FLAG_CONTEXT_SAVE_EXISTS);
	}
	m_mainMenu.init();
}

std::string MainMenuScene::getStateID() const {
	return "MainMenuScene";
}

bool MainMenuScene::onEnter() {
	return true;
}

void MainMenuScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
	}
	else if (m_userActions.getActionState("CURSOR_UP")) {
		m_mainMenu.selectPrevious();
	}
	else if (m_userActions.getActionState("CURSOR_DOWN")) {
		m_mainMenu.selectNext();
	}
	else if (m_userActions.getActionState("MENU_ACTION")) {
		_executeMenuAction(stateMachine);
	}
}

void MainMenuScene::_executeMenuAction(StateMachine &stateMachine) {
	if (m_mainMenu.getSelectedAction() == NEW_GAME) {
		stateMachine.pushState(new IntroScene(m_userActions, m_renderer));
	}
	else if (m_mainMenu.getSelectedAction() == LOAD_GAME) {
		stateMachine.pushState(new PlayScene(m_userActions, m_renderer));
	}
	else if (m_mainMenu.getSelectedAction() == MAIN_MENU_QUIT) {
		stateMachine.clean();
	}
}

void MainMenuScene::render() {
	m_title.render(m_renderer->getRenderer(), m_iTitleXPos, 32);
	m_mainMenu.render();
}
