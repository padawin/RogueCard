#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../Save.hpp"
#include "../sdl2/TextureManager.hpp"
#include "GameOver.hpp"
#include "Inventory.hpp"
#include "Play.hpp"
#include "EnemyCard.hpp"
#include "ObjectCard.hpp"
#include <iostream>

PlayScene::PlayScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_player(player),
	m_renderer(renderer),
	m_deck(CardDeck()),
	m_notification(Text())
{
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
	else if (m_player.isDead()) {
		stateMachine.changeState(new GameOverScene(m_userActions));
	}
	else if (m_userActions.getActionState("INVENTORY")) {
		stateMachine.pushState(new InventoryScene(m_userActions, m_player, m_renderer));
	}
	else if (m_userActions.getActionState("USE_CARD")) {
		_useCardUnderCursor();
	}
	else if (m_userActions.getActionState("CURSOR_LEFT")) {
		m_cursorPosition = (PlayCursorPosition) ((NbPositions + m_cursorPosition - 1) % NbPositions);
	}
	else if (m_userActions.getActionState("CURSOR_RIGHT")) {
		m_cursorPosition = (PlayCursorPosition) ((m_cursorPosition + 1) % NbPositions);
	}
}

void PlayScene::render() {
	_renderBackground();
	_renderNotification();
	_renderCards();
	_renderCursor();
}

void PlayScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"ui", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}

void PlayScene::_renderNotification() const {
	if (m_notification.hasText()) {
		m_notification.render(
			m_renderer->getRenderer(),
			80, 16
		);
	}
}

void PlayScene::_renderCursor() {
	TextureManager::Instance()->draw(
		"cursor",
		m_mCursorPositions[m_cursorPosition].first,
		m_mCursorPositions[m_cursorPosition].second,
		48,
		64,
		m_renderer->getRenderer()
	);
}

void PlayScene::_renderCards() {
	if (m_pickedCard) {
		m_pickedCard->render(m_renderer->getRenderer(), 138, 64);
	}
	for (int i = (int) Object1; i < MAX_OBJECTS; ++i) {
		PlayCursorPosition pos = (PlayCursorPosition) i;
		if (m_objectCards[pos] != nullptr) {
			m_objectCards[pos]->render(
				m_renderer->getRenderer(),
				m_mCursorPositions[pos].first,
				m_mCursorPositions[pos].second
			);
		}
	}
	if (m_floorCard) {
		m_floorCard->render(
			m_renderer->getRenderer(),
			m_mCursorPositions[Floor].first,
			m_mCursorPositions[Floor].second
		);
	}
}

void PlayScene::_useCardUnderCursor() {
	switch (m_cursorPosition) {
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
		m_pickedCard = m_deck.pickCard(m_player, m_floorCard != nullptr);
	}
	else {
		_notify("A card is already picked");
	}
}

void PlayScene::_pickObject() {
	std::shared_ptr<ObjectCard> objectCard(std::static_pointer_cast<ObjectCard>(m_pickedCard));
	if (!m_player.hasSpaceInInventory()) {
		_notify("Your inventory is full");
	}
	else {
		char message[44];
		m_player.addItemToInventory(objectCard);
		snprintf(message, 44, "You picked %s", objectCard->getName());
		_notify(message);
	}
}

void PlayScene::_action() {
	if (m_pickedCard == nullptr) {
		_pickCard();
	}
	else if (m_pickedCard->getType() == ObjectCardType) {
		_pickObject();
		m_pickedCard = nullptr;
	}
	else if (m_pickedCard->getType() == FloorCardType) {
		_notify("Found next floor");
		m_floorCard = m_pickedCard;
		m_pickedCard = nullptr;
	}
	else if (m_pickedCard->getType() == EnemyCardType) {
		_attack();
	}
}

void PlayScene::_useObject(int objectIndex) {
	if (objectIndex >= MAX_OBJECTS) {
		return;
	}

	if (m_objectCards[objectIndex] != nullptr) {
		_notify("Use object");
	}
}

void PlayScene::_changeFloor() {
	if (m_floorCard != nullptr) {
		_notify("Change floor");
	}
	else {
		_notify("You haven't found the next floor yet");
	}
}

void PlayScene::_attack() {
	char message[80];
	std::shared_ptr<EnemyCard> enemyCard(std::static_pointer_cast<EnemyCard>(m_pickedCard));
	int damagesDealtToEnemy = m_player.attack(enemyCard);
	int damagesDealtToPlayer = enemyCard->attack(m_player);
	if (!enemyCard->isDead()) {
		snprintf(
			message,
			80,
			"You hit %s (%d DP)\n%s hits you (%d DP)",
			enemyCard->getName(),
			damagesDealtToEnemy,
			enemyCard->getName(),
			damagesDealtToPlayer
		);
	}
	else {
		snprintf(
			message,
			80,
			"You defeated %s",
			enemyCard->getName()
		);
		m_pickedCard = nullptr;
	}
	_notify(message);
}

void PlayScene::_notify(std::string message) {
	m_notification.setText(message);
}
