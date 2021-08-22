#include <iostream>
#include "game/config.hpp"
#include "../game/StateMachine.hpp"
#include "Intro.hpp"
#include "../Save.hpp"

const int LINE_MAX_LENGTH = 17;
const int LINES_PER_PAGE = 10;

IntroScene::IntroScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	SceneState(userActions),
	m_renderer(renderer),
	m_textField(Text())
{}

std::string IntroScene::getStateID() const {
	return "IntroScene";
}

bool IntroScene::onEnter() {
	// read resources/intro.txt
	_buildLines();
	m_textField.setText(m_vIntroText[m_iCurrentPage - 1]);
	// store it in m_vIntroText with each line as an element of the vector
	// set in m_text the first page
	return true;
}

void IntroScene::_buildLines() {
	std::ifstream in(
		config_getBinPath() + "/../resources/intro.txt", std::ios::in
	);
	if (!in) {
		std::cerr << "The introduction text can't be opened\n";
		return;
	}

	std::string line, page = "";
	int currLine = 0;
	while (std::getline(in, line)) {
		if (currLine > 0 || line != "") {
			page += line + "\n";
			++currLine;
		}
		if (currLine == LINES_PER_PAGE) {
			m_vIntroText.push_back(page);
			page = "";
			currLine = 0;
		}
	}
	if (currLine > 0) {
		m_vIntroText.push_back(page);
	}
	in.close();
}

void IntroScene::update(StateMachine<SceneState> &stateMachine) {
	if (m_userActions.getActionState("MENU_ACTION") == ActionState::ACTION_PRESSED) {
		++m_iCurrentPage;
		if (m_iCurrentPage > m_vIntroText.size()) {
			stateMachine.popState();
		}
		else {
			m_textField.setText(m_vIntroText[m_iCurrentPage - 1]);
		}
	}
}

void IntroScene::render() {
	m_textField.render(m_renderer->getRenderer(), 18, 16);
}
