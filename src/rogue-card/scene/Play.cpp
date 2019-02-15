#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../Save.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Play.hpp"
#include <iostream>

PlayScene::PlayScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions), m_player(player), m_renderer(renderer)
{
	m_mCursorPositions[Deck] = {16, 16};
	m_mCursorPositions[Action] = {16, 160};
	m_mCursorPositions[Object1] = {64, 160};
	m_mCursorPositions[Object2] = {112, 160};
	m_mCursorPositions[Object3] = {160, 160};
	m_mCursorPositions[Object4] = {208, 160};
	m_mCursorPositions[Floor] = {256, 160};
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
		Save s = Save(m_player);
		s.save();
		stateMachine.clean();
		return;
	}
	else if (m_userActions.getActionState("USE_CARD")) {
		_useCardUnderCursor();
	}
	else if (m_userActions.getActionState("CURSOR_TO_DECK")) {
		m_cursorPosition = Deck;
	}
	else if (m_userActions.getActionState("CURSOR_TO_ACTION")) {
		m_cursorPosition = Action;
	}
	else if (m_userActions.getActionState("CURSOR_PREVIOUS_POSITION")) {
		m_cursorPosition = (CursorPosition) ((NbPositions + m_cursorPosition - 1) % NbPositions);
	}
	else if (m_userActions.getActionState("CURSOR_NEXT_POSITION")) {
		m_cursorPosition = (CursorPosition) ((m_cursorPosition + 1) % NbPositions);
	}
}

void PlayScene::render() {
	_renderBackground();
	_renderCursor();
}

void PlayScene::_renderBackground() const {
	TextureManager::Instance()->drawImage(
		"ui", m_renderer->getRenderer(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
	);
}

void PlayScene::_renderCursor() {
	TextureManager::Instance()->drawImage(
		"cursor",
		m_renderer->getRenderer(),
		m_mCursorPositions[m_cursorPosition].first,
		m_mCursorPositions[m_cursorPosition].second,
		48,
		64
	);
}

void PlayScene::_useCardUnderCursor() {
	switch (m_cursorPosition) {
		case Deck:
			_pickCard();
			break;
		case Action:
			_action();
			break;
		case Object1:
			_useObject(0);
			break;
		case Object2:
			_useObject(1);
			break;
		case Object3:
			_useObject(2);
			break;
		case Object4:
			_useObject(3);
			break;
		case Floor:
			_changeFloor();
			break;
		case NbPositions:
		default:
			break;
	}
}

void PlayScene::_pickCard() {
	if (m_pickedCard == nullptr) {
		std::cout << "Pick card\n";
	}
	else {
		_notify("A card is already picked");
	}
}

void PlayScene::_action() {
	if (m_pickedCard != nullptr) {
		std::cout << "Action\n";
	}
	else {
		_notify("Pick a card first");
	}
}

void PlayScene::_useObject(int objectIndex) {
	if (objectIndex >= MAX_OBJECTS) {
		return;
	}

	if (m_objectCards[objectIndex] != nullptr) {
		std::cout << "Use object\n";
	}
}

void PlayScene::_changeFloor() {
	if (m_floorCard != nullptr) {
		std::cout << "Change floor\n";
	}
	else {
		_notify("You haven't found the next floor yet");
	}
}

void PlayScene::_notify(std::string message) const {
	std::cout << message << std::endl;
}
