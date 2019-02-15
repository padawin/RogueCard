#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../Save.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Play.hpp"
#include <iostream>

PlayScene::PlayScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions), m_player(player), m_renderer(renderer)
{
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
}

void PlayScene::render() {
	_renderBackground();
}

void PlayScene::_renderBackground() const {
	TextureManager::Instance()->drawImage("ui", m_renderer->getRenderer());
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
