#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Equipment.hpp"

const int CURRENT_EQUIP_STAT_X = 16;
const int CURRENT_EQUIP_STAT_Y = 152;

const int SELECTED_EQUIP_STAT_X = 160;
const int SELECTED_EQUIP_STAT_Y = 152;

const int STAT_VAL_X_SHIFT = 72;

EquipmentScene::EquipmentScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_renderer(renderer),
	m_availableCards(ObjectCardCollection()),
	m_availableCardsRenderer(ObjectCardCollectionRenderer(
		userActions,
		m_availableCards,
		player.getEquipment(),
		12,
		"ui-equipment-select",
		m_renderer
	)),
	m_player(player),
	m_statLabel(Text()),
	m_statValue(Text())
{
	m_mCursorPositions[0] = {16, 16};
	m_mCursorPositions[1] = {64, 16};
	m_mCursorPositions[2] = {112, 16};
	m_mCursorPositions[3] = {160, 16};
	m_mCursorPositions[4] = {208, 16};
	m_mCursorPositions[5] = {256, 16};
	m_mCursorPositions[6] = {16, 80};
	m_mCursorPositions[7] = {256, 80};
	m_equipmentFlags[0] = FLAG_EQUIPMENT_HEAD;
	m_equipmentFlags[1] = FLAG_EQUIPMENT_SHOULDERS;
	m_equipmentFlags[2] = FLAG_EQUIPMENT_CHEST;
	m_equipmentFlags[3] = FLAG_EQUIPMENT_BELT;
	m_equipmentFlags[4] = FLAG_EQUIPMENT_FEET;
	m_equipmentFlags[5] = FLAG_EQUIPMENT_HANDS;
	m_equipmentFlags[6] = FLAG_EQUIPMENT_WEAPON;
	m_equipmentFlags[7] = FLAG_EQUIPMENT_SHIELD;
}

std::string EquipmentScene::getStateID() const {
	return "EquipmentScene";
}

bool EquipmentScene::onEnter() {
	return true;
}

void EquipmentScene::update(StateMachine &stateMachine) {
	if (m_bSelectViewOpen) {
		if (m_userActions.getActionState("BACK")) {
			m_bSelectViewOpen = false;
			m_availableCardsRenderer.reset();
		}
		else if (m_userActions.getActionState("USE_CARD")) {
			auto card = m_availableCards.getCard(
				m_availableCardsRenderer.getSelectedCardIndex()
			);
			if (card != nullptr) {
				m_player.equip(card);
				m_bSelectViewOpen = false;
			}
		}
		else {
			m_availableCardsRenderer.update();
		}
	}
	else {
		if (m_userActions.getActionState("BACK")) {
			stateMachine.popState();
		}
		else if (m_userActions.getActionState("CURSOR_LEFT")) {
			m_cursorPosition = (SIZE_EQUIPMENT + m_cursorPosition - 1) % SIZE_EQUIPMENT;
		}
		else if (m_userActions.getActionState("CURSOR_RIGHT")) {
			m_cursorPosition = (m_cursorPosition + 1) % SIZE_EQUIPMENT;
		}
		else if (m_userActions.getActionState("USE_CARD")) {
			_openListObjects();
		}
	}
}

void EquipmentScene::render() {
	std::shared_ptr<ObjectCard> equippedCard = nullptr,
								selectedCard = nullptr;
	equippedCard = m_player.getEquipment().getCardWithFlag(
		m_equipmentFlags[m_cursorPosition]
	);
	if (m_bSelectViewOpen) {
		m_availableCardsRenderer.render();
		selectedCard = m_availableCards.getCard(
			m_availableCardsRenderer.getSelectedCardIndex()
		);
	}
	else {
		_renderBackground();
		_renderCards();
		_renderCursor();
	}
	_renderCardStats(equippedCard, selectedCard, CURRENT_EQUIP_STAT_X);
	_renderCardStats(selectedCard, equippedCard, SELECTED_EQUIP_STAT_X);
}

void EquipmentScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"ui-equipment", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}

void EquipmentScene::_renderCards() const {
	for (int c = 0; c < SIZE_EQUIPMENT; ++c) {
		auto card = m_player.getEquipment().getCardWithFlag(m_equipmentFlags[c]);
		if (card != nullptr) {
			card->render(
				m_renderer->getRenderer(),
				m_mCursorPositions[c].x,
				m_mCursorPositions[c].y
			);
		}
	}
}

void EquipmentScene::_renderCursor() {
	TextureManager::Instance()->draw(
		"cursor",
		m_mCursorPositions[m_cursorPosition].x,
		m_mCursorPositions[m_cursorPosition].y,
		48,
		64,
		m_renderer->getRenderer()
	);
}

void EquipmentScene::_openListObjects() {
	m_availableCards.clear();
	m_player.getInventory().reset();
	do {
		auto card = m_player.getInventory().current();
		if (card != nullptr && card->hasEquipableFlag(m_equipmentFlags[m_cursorPosition])) {
			m_availableCards.addCard(card);
		}
	} while (m_player.getInventory().next());
	m_bSelectViewOpen = true;
}

void EquipmentScene::_renderCardStats(std::shared_ptr<ObjectCard> card, std::shared_ptr<ObjectCard> compareCard, int x) {
	if (card == nullptr) {
		return;
	}
	char statStr[4];
	int y = CURRENT_EQUIP_STAT_Y;
	S_CardStats stats = card->getStats();
	S_CardStats compareStats;
	ElementalEffects elementalEffects = card->getElementalEffects();
	ElementalEffects compareElementalEffects;
	if (compareCard == nullptr) {
		compareStats = card->getStats();
		compareElementalEffects = card->getElementalEffects();
	}
	else {
		compareStats = compareCard->getStats();
		compareElementalEffects = compareCard->getElementalEffects();
	}

	if (stats.points != 0) {
		if (card->applyOnSelf()) {
			m_statLabel.setText("DEFENCE");
		}
		else {
			m_statLabel.setText("ATTACK");
		}
		m_statLabel.render(m_renderer->getRenderer(), x, y);
		sprintf(statStr, "%d", _boundVal(stats.points, -99, 999));
		m_statValue.setFont(_getStatColor(stats.points, compareStats.points));
		m_statValue.setText(statStr);
		m_statValue.render(m_renderer->getRenderer(), x + STAT_VAL_X_SHIFT, y);
	}
	if (stats.maxHealthPoints != 0) {
		y += 16;
		m_statLabel.setText("MAX HP");
		m_statLabel.render(m_renderer->getRenderer(), x, y);
		sprintf(statStr, "%d", _boundVal(stats.maxHealthPoints, -99, 999));
		m_statValue.setFont(_getStatColor(stats.maxHealthPoints, compareStats.maxHealthPoints));
		m_statValue.setText(statStr);
		m_statValue.render(m_renderer->getRenderer(), x + STAT_VAL_X_SHIFT, y);
	}

	for (int s = 0; s < NB_ELEMENTS; ++s) {
		int statValue = elementalEffects.getStat((E_ElementalElement) s);
		if (statValue != 0) {
			y += 16;
			if (card->applyOnSelf()) {
				m_statLabel.setText("FIR DEF");
			}
			else {
				m_statLabel.setText("FIR ATK");
			}
			m_statLabel.render(m_renderer->getRenderer(), x, y);
			sprintf(statStr, "%d", _boundVal(statValue, -99, 999));
			m_statValue.setFont(
				_getStatColor(
					statValue,
					compareElementalEffects.getStat((E_ElementalElement) s)
				)
			);
			m_statValue.setText(statStr);
			m_statValue.render(m_renderer->getRenderer(), x + STAT_VAL_X_SHIFT, y);
		}
	}
}

int EquipmentScene::_boundVal(int val, int minVal, int maxVal) const {
	if (val > maxVal) {
		return maxVal;
	}
	else if (val < minVal) {
		return minVal;
	}
	else {
		return val;
	}
}

std::string EquipmentScene::_getStatColor(int stat1, int stat2) const {
	if (stat1 == stat2) {
		return "font";
	}
	else if (stat1 > stat2) {
		return "font-green";
	}
	else {
		return "font-red";
	}
}
