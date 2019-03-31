#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../Save.hpp"
#include "../sdl2/TextureManager.hpp"
#include "GameOver.hpp"
#include "Inventory.hpp"
#include "Equipment.hpp"
#include "Play.hpp"
#include "EnemyCard.hpp"
#include "ObjectCard.hpp"
#include <iostream>

PlayScene::PlayScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_player(player),
	m_renderer(renderer),
	m_actionCard(ActionCard()),
	m_deck(CardDeck()),
	m_actionBar(ActionBar()),
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
	Save s = Save(m_player, m_actionBar);
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
		Save s = Save(m_player, m_actionBar);
		s.save();
		stateMachine.clean();
	}
	else if (m_player.isDead()) {
		stateMachine.changeState(new GameOverScene(m_userActions));
	}
	else if (m_userActions.getActionState("INVENTORY")) {
		stateMachine.pushState(
			new InventoryScene(m_userActions, m_actionBar, m_player, m_renderer)
		);
	}
	else if (m_userActions.getActionState("EQUIPMENT")) {
		stateMachine.pushState(new EquipmentScene(m_userActions, m_player, m_renderer));
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
	_renderHealth();
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

void PlayScene::_renderHealth() const {
	int healthWidth = m_player.getHealth() * 138 / m_player.getMaxHealth();
	TextureManager::Instance()->draw(
		"health-color", 20, 146, healthWidth, 10, m_renderer->getRenderer()
	);
}

void PlayScene::_renderCursor() {
	TextureManager::Instance()->draw(
		"cursor",
		m_mCursorPositions[m_cursorPosition].x,
		m_mCursorPositions[m_cursorPosition].y,
		CARD_WIDTH,
		CARD_HEIGHT,
		m_renderer->getRenderer()
	);
}

void PlayScene::_renderCards() {
	_renderActionCard();
	if (m_pickedCard) {
		m_pickedCard->render(m_renderer->getRenderer(), 138, 64);
	}
	for (int i = 0; i < ACTION_BAR_SIZE; ++i) {
		S_Coordinates pos = m_mCursorPositions[(PlayCursorPosition)(Object1 + i)];
		if (m_actionBar.getCard(i) != nullptr) {
			m_actionBar.getCard(i)->render(m_renderer->getRenderer(), pos.x, pos.y);
		}
	}
	if (m_floorCard) {
		m_floorCard->render(
			m_renderer->getRenderer(),
			m_mCursorPositions[Floor].x,
			m_mCursorPositions[Floor].y
		);
	}
}

void PlayScene::_renderActionCard() {
	switch (m_action) {
		case PickAction:
			m_actionCard.renderPick(
				m_renderer->getRenderer(),
				m_mCursorPositions[Action].x,
				m_mCursorPositions[Action].y
			);
			break;
		case FloorAction:
		case LootAction:
			m_actionCard.renderLoot(
				m_renderer->getRenderer(),
				m_mCursorPositions[Action].x,
				m_mCursorPositions[Action].y
			);
			break;
		case AttackAction:
			m_actionCard.renderAttack(
				m_renderer->getRenderer(),
				m_mCursorPositions[Action].x,
				m_mCursorPositions[Action].y,
				m_player.getEquipment().getCardWithFlag(FLAG_EQUIPMENT_WEAPON)
			);
			break;
		default:
			break;
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
		if (m_pickedCard->getType() == ObjectCardType) {
			m_action = LootAction;
		}
		else if (m_pickedCard->getType() == FloorCardType) {
			m_action = FloorAction;
		}
		else if (m_pickedCard->getType() == EnemyCardType) {
			m_action = AttackAction;
		}
	}
}

void PlayScene::_lootObject() {
	std::shared_ptr<ObjectCard> objectCard(std::static_pointer_cast<ObjectCard>(m_pickedCard));
	if (!m_player.hasSpaceInInventory()) {
		_notify("Your inventory is full");
	}
	else {
		char message[44];
		m_player.addItemToInventory(objectCard);
		snprintf(message, 44, "You picked:\n%s", objectCard->getName());
		_notify(message);
		m_pickedCard = nullptr;
	}
}

void PlayScene::_action() {
	switch (m_action) {
		case PickAction:
			_pickCard();
			break;
		case LootAction:
			_lootObject();
			break;
		case FloorAction:
			_notify("Found next floor");
			m_floorCard = m_pickedCard;
			m_pickedCard = nullptr;
			break;
		case AttackAction:
			_attack();
			break;
		default:
			break;
	}

	if (m_pickedCard == nullptr) {
		m_action = PickAction;
	}
}

void PlayScene::_useObject(int objectIndex) {
	auto card = m_actionBar.getCard(objectIndex);
	if (card != nullptr) {
		bool isFighting = m_player.isFighting();
		bool used = true;
		if (card->applyOnSelf()) {
			m_player.applyCardStats(card);
		}
		else if (isFighting) {
			_attack(card);
		}
		else {
			used = false;
		}

		if (used && card->isConsumable()) {
			card->consume();
			if (card->getQuantity() == 0) {
				m_player.removeInventoryCard(card);
				m_actionBar.removeCard(card);
			}
		}
	}
}

void PlayScene::_changeFloor() {
	if (m_floorCard != nullptr) {
		_notify("Change floor");
	}
}

void PlayScene::_attack(std::shared_ptr<ObjectCard> attackCard) {
	char message[80];
	std::shared_ptr<EnemyCard> enemyCard(std::static_pointer_cast<EnemyCard>(m_pickedCard));
	int damagesDealtToEnemy = m_player.attack(enemyCard, attackCard);
	if (!enemyCard->isDead()) {
		int damagesDealtToPlayer = enemyCard->attack(m_player);
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
		m_player.setFighting(false);
	}
	_notify(message);
}

void PlayScene::_notify(std::string message) {
	m_notification.setText(message);
}
