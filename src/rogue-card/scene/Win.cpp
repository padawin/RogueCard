#include "globals.hpp"
#include "game/StateMachine.hpp"
#include "Win.hpp"
#include "MainMenu.hpp"

WinScene::WinScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	SceneState(userActions),
	m_renderer(renderer),
	m_title(Text()),
	m_text(Text()),
	m_menu(EndGameMenu(renderer, 32, 160))
{}

std::string WinScene::getStateID() const {
	return "WinScene";
}

bool WinScene::onEnter() {
	m_title.setText("CONGRATULATIONS");
	m_text.setText("YOU RETRIEVED THE ARTEFACT OF\nPOWER. WEALTH AND FAME NOW\nAWAITS YOU, UNLESS YOU FIND\nYOURSELF UP TO ANOTHER\nCHALLENGE?");
	m_iTitleXPos = (SCREEN_WIDTH - m_title.getLength()) / 2;
	m_menu.init();
	return true;
}

void WinScene::update(StateMachine<SceneState> &stateMachine) {
	if (m_userActions.is("CURSOR_UP", ActionState::ACTION_PRESSED | ActionState::ACTION_DOWN)) {
		m_menu.selectPrevious();
	}
	else if (m_userActions.is("CURSOR_DOWN", ActionState::ACTION_PRESSED | ActionState::ACTION_DOWN)) {
		m_menu.selectNext();
	}
	else if (m_userActions.getActionState("MENU_ACTION") == ActionState::ACTION_PRESSED) {
		_executeMenuAction(stateMachine);
	}
}

void WinScene::_executeMenuAction(StateMachine<SceneState> &stateMachine) {
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

void WinScene::render() {
	m_title.render(m_renderer->getRenderer(), m_iTitleXPos, 32);
	m_text.render(m_renderer->getRenderer(), 16, 64);
	m_menu.render();
}
