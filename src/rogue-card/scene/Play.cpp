#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../Save.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Intro.hpp"
#include "GameOver.hpp"
#include "Win.hpp"
#include "Inventory.hpp"
#include "FightResult.hpp"
#include "PlayerStats.hpp"
#include "Equipment.hpp"
#include "Play.hpp"
#include "EnemyCard.hpp"
#include "ObjectCard.hpp"
#include <iostream>

#define ATTACK_RES_TPL "You hit %s (%d DP)\n%s hits you (%d DP)"
#define USE_OBJECT_TPL "%s used"
#define USE_OBJECT_IN_FIGHT_TPL "%s used\n%s hits you (%d DP)"

const int HEALTH_X = 16;
const int HEALTH_Y = 144;

PlayScene::PlayScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer, Player player) :
	State(userActions),
	m_player(player),
	m_renderer(renderer),
	m_actionCard(ActionCard()),
	m_deck(CardDeck()),
	m_actionBar(ActionBar()),
	m_notification(Text()),
	m_fight(Fight(m_player)),
	m_progressBar(ProgressBar())
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
		if (m_player.foundFinalGoal()) {
			m_floorCard = m_deck.createFloorCard(FLOOR_UP);
		}
		else if (m_player.foundFloorCard()) {
			m_floorCard = m_deck.createFloorCard(FLOOR_DOWN);
		}
	}
	else {
		std::clog << "No save found, create new one\n";
		m_bShowIntro = true;
		s.create();
	}
	_updateHealthBar();
	return true;
}

void PlayScene::update(StateMachine &stateMachine) {
	if (m_bShowIntro) {
		stateMachine.pushState(new IntroScene(m_userActions, m_renderer));
		m_bShowIntro = false;
		return;
	}

	// Update animations
	m_pickedCardAnim.update();

	if (_hasAnimationsRunning()) {
		return;
	}

	_handleControls(stateMachine);
	_updateHealthBar();

	// Reached the top
	if (m_player.getFloor().getLevel() == 0) {
		stateMachine.changeState(new WinScene(m_userActions, m_renderer));
	}
	else if (m_player.isDead()) {
		Save::clean();
		stateMachine.changeState(new GameOverScene(m_userActions, m_renderer));
	}
}

void PlayScene::_handleControls(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		Save s = Save(m_player, m_actionBar);
		s.save();
		stateMachine.clean();
	}
	else if (m_userActions.getActionState("INVENTORY")) {
		stateMachine.pushState(
			new InventoryScene(m_userActions, m_actionBar, m_player, m_renderer)
		);
	}
	else if (m_userActions.getActionState("PLAYER_STATS")) {
		stateMachine.pushState(
			new PlayerStatsScene(m_userActions, m_renderer, m_player)
		);
	}
	else if (m_userActions.getActionState("EQUIPMENT")) {
		stateMachine.pushState(new EquipmentScene(m_userActions, m_player, m_renderer));
	}
	else if (m_userActions.getActionState("USE_CARD")) {
		bool wasFighting = m_fight.isFighting();
		_useCardUnderCursor();
		// Killed the enemy
		if (wasFighting && !m_fight.isFighting()) {
			m_pickedCard = nullptr;
			_notify("");
			stateMachine.pushState(
				new FightResultScene(m_userActions, m_fight, m_renderer)
			);
		}

		if (m_pickedCard == nullptr) {
			m_action = PickAction;
		}
	}
	else if (m_userActions.getActionState("CURSOR_LEFT")) {
		m_cursorPosition = (PlayCursorPosition) ((NbPositions + m_cursorPosition - 1) % NbPositions);
	}
	else if (m_userActions.getActionState("CURSOR_RIGHT")) {
		m_cursorPosition = (PlayCursorPosition) ((m_cursorPosition + 1) % NbPositions);
	}
	else if (m_userActions.getActionState("CURSOR_UP")) {
		_setNextAction(1);
	}
	else if (m_userActions.getActionState("CURSOR_DOWN")) {
		_setNextAction(-1);
	}
}

void PlayScene::_setNextAction(int way) {
	way = way > 0 ? 1 : 0;
	m_action = (ActionType) POSSIBLE_ACTIONS[m_action][way];
}

void PlayScene::render() {
	if (m_bShowIntro) {
		return;
	}
	_renderBackground();
	_renderNotification();
	_renderCards();
	m_progressBar.render(m_renderer, HEALTH_X, HEALTH_Y);
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
		m_mCursorPositions[m_cursorPosition].x,
		m_mCursorPositions[m_cursorPosition].y,
		CARD_WIDTH,
		CARD_HEIGHT,
		m_renderer->getRenderer()
	);

	if (m_cursorPosition == Action) {
		if (POSSIBLE_ACTIONS[m_action][0] != m_action) {
			m_actionCard.renderPrevious(
				m_renderer->getRenderer(),
				m_mCursorPositions[Action].x,
				m_mCursorPositions[Action].y
			);
		}
		if (POSSIBLE_ACTIONS[m_action][1] != m_action) {
			m_actionCard.renderNext(
				m_renderer->getRenderer(),
				m_mCursorPositions[Action].x,
				m_mCursorPositions[Action].y
			);
		}
	}
}

void PlayScene::_renderCards() {
	_renderActionCard();
	if (m_pickedCard) {
		m_pickedCard->render(
			m_renderer->getRenderer(),
			m_pickedCardAnim.getX(),
			m_pickedCardAnim.getY()
		);
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
		case GetFinalGoalAction:
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
		case RunawayAction:
			m_actionCard.renderRunaway(
				m_renderer->getRenderer(),
				m_mCursorPositions[Action].x,
				m_mCursorPositions[Action].y
			);
			break;
		case DiscardAction:
			m_actionCard.renderDiscard(
				m_renderer->getRenderer(),
				m_mCursorPositions[Action].x,
				m_mCursorPositions[Action].y
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
		_notify("");
		m_pickedCard = m_deck.pickCard(m_player);
		m_pickedCardAnim.init();
		E_CardType type = m_pickedCard->getType();
		if (type == ObjectCardType) {
			char message[44];
			snprintf(message, 44, "You find:\n%s", m_pickedCard->getName());
			_notify(message);
			m_action = LootAction;
		}
		else if (type == FloorCardType) {
			m_action = FloorAction;
		}
		else if (type == EnemyCardType) {
			char message[50];
			snprintf(message, 44, "A %s attacks you!", m_pickedCard->getName());
			_notify(message);
			m_action = AttackAction;
			m_fight.start(std::static_pointer_cast<EnemyCard>(m_pickedCard));
		}
		else if (type == FinalGoalCardType) {
			m_action = GetFinalGoalAction;
		}
	}
}

void PlayScene::_lootObject() {
	std::shared_ptr<ObjectCard> objectCard(std::static_pointer_cast<ObjectCard>(m_pickedCard));
	if (!m_player.addItemToInventory(objectCard)) {
		_notify("Your inventory is full");
	}
	else {
		char message[44];
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
			m_player.setFoundFloorCard(true);
			m_pickedCard = nullptr;
			break;
		case AttackAction:
			_attack();
			break;
		case GetFinalGoalAction:
			_getFinalGoal();
			break;
		case RunawayAction:
			_runaway();
			break;
		case DiscardAction:
			_discardCard();
			break;
		default:
			break;
	}
}

void PlayScene::_useObject(int objectIndex) {
	auto card = m_actionBar.getCard(objectIndex);
	if (card != nullptr) {
		bool isFighting = m_fight.isFighting();
		bool used = true;
		if (card->applyOnSelf()) {
			m_player.applyCardStats(card);
			char message[80];
			if (isFighting) {
				S_FightTurnResult res = m_fight.skip();
				snprintf(
					message,
					80,
					USE_OBJECT_IN_FIGHT_TPL,
					card->getName(),
					m_fight.getEnemy()->getName(),
					res.damagesDealtToPlayer
				);
			}
			else {
				snprintf(
					message,
					80,
					USE_OBJECT_TPL,
					card->getName()
				);
			}
			_notify(message);
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
		if (m_fight.isFighting()) {
			_notify("Can't change floor while\nfighting");
		}
		else {
			m_player.toNextFloor();
			char floorStr[25];
			if (!m_player.foundFinalGoal()) {
				m_floorCard = nullptr;
				m_player.setFoundFloorCard(false);
				snprintf(
					floorStr,
					25,
					"You reached floor %d",
					m_player.getFloor().getLevel()
				);
			}
			else {
				snprintf(
					floorStr,
					25,
					"You go back to floor %d",
					m_player.getFloor().getLevel()
				);
			}
			m_pickedCard = nullptr;
			_notify(floorStr);
		}
	}
}

void PlayScene::_attack(std::shared_ptr<ObjectCard> attackCard) {
	S_FightTurnResult res = m_fight.turn(attackCard);
	if (m_fight.isFighting()) {
		char message[80];
		snprintf(
			message,
			80,
			ATTACK_RES_TPL,
			m_fight.getEnemy()->getName(),
			res.damagesDealtToEnemy,
			m_fight.getEnemy()->getName(),
			res.damagesDealtToPlayer
		);
		_notify(message);
	}
}

void PlayScene::_getFinalGoal() {
	m_pickedCard = nullptr;
	m_player.setFoundFinalGoal();
	m_floorCard = m_deck.createFloorCard(FLOOR_UP);
	_notify("You found\nThe Artefact of Power");
}

void PlayScene::_notify(std::string message) {
	m_notification.setText(message);
}

void PlayScene::_discardCard() {
	char message[51];
	auto objectCard(std::static_pointer_cast<ObjectCard>(m_pickedCard));
	snprintf(message, 51, "You discard card:\n%s", objectCard->getName());
	_notify(message);
	m_pickedCard = nullptr;
}

void PlayScene::_runaway() {
	S_FightTurnResult res = m_fight.runaway();
	if (!m_fight.isFighting()) {
		_notify("You run away");
	}
	else {
		_notify("");
		char message[80];
		snprintf(
			message,
			80,
			"You failed run away\n%s hits you (%d DP)",
			m_fight.getEnemy()->getName(),
			res.damagesDealtToPlayer
		);
		_notify(message);
	}
}

void PlayScene::_updateHealthBar() {
	m_progressBar.setProgress(m_player.getHealth() * 100 / m_player.getMaxHealth());
}

bool PlayScene::_hasAnimationsRunning() const {
	return m_pickedCardAnim.running();
}
