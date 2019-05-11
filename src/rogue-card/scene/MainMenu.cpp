#include "../game/Game.hpp"
#include "../game/StateMachine.hpp"
#include "MainMenu.hpp"
#include "Play.hpp"

MainMenuScene::MainMenuScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_renderer(renderer),
	m_title(Text())
{
	m_title.setText("CARD ROGUE");
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
	else if (m_userActions.getActionState("MENU_ACTION")) {
	}
}

void MainMenuScene::render() {
	m_textField.render(m_renderer->getRenderer(), 18, 16);
}
