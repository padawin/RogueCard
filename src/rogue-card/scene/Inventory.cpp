#include <iostream>
#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Inventory.hpp"
#include "Equipment.hpp"
#include "QuickActionBar.hpp"
#include "ObjectCard.hpp"

InventoryScene::InventoryScene(
	UserActions &userActions,
	Player &player,
	std::shared_ptr<SDL2Renderer> renderer
) :
	SceneState(userActions),
	m_titlesTab("Inventory", "Equipment", 8),
	m_player(player),
	m_renderer(renderer),
	m_objectActionMenu(ObjectAction(renderer)),
	m_cardsRenderer(ObjectCardCollectionRenderer(
		userActions,
		player.getInventory(),
		player.getEquipment(),
		18,
		"ui-inventory",
		m_renderer
	))
{
}

std::string InventoryScene::getStateID() const {
	return "InventoryScene";
}

bool InventoryScene::onEnter() {
	return true;
}

void InventoryScene::update(StateMachine<SceneState> &stateMachine) {
	bool pressedBack = m_userActions.getActionState("BACK"),
		 pressedAction = m_userActions.getActionState("USE_CARD");
	if (m_objectActionMenu.isOpen()) {
		if (pressedBack ||
			(pressedAction && m_objectActionMenu.getSelectedAction() == BACK)
		) {
			m_objectActionMenu.close();
		}
		else if (m_userActions.getActionState("CURSOR_UP")) {
			m_objectActionMenu.selectPrevious();
		}
		else if (m_userActions.getActionState("CURSOR_DOWN")) {
			m_objectActionMenu.selectNext();
		}
		else if (pressedAction) {
			_executeMenuAction(
				m_objectActionMenu.getSelectedAction(),
				stateMachine
			);
			m_objectActionMenu.close();
		}
	}
	else if (pressedBack) {
		stateMachine.popState();
	}
	else if (pressedAction) {
		auto card = m_player.getInventoryItem(_getCardIndex());
		if (card != nullptr) {
			m_objectActionMenu.setContext(
				(!m_player.isFighting() ? FLAG_CONTEXT_NOT_IN_FIGHT : 0)
				| (m_player.getActionBar().hasCard(card) ? FLAG_CONTEXT_CARD_IN_ACTIONBAR : FLAG_CONTEXT_CARD_NOT_IN_ACTIONBAR)
			);
			m_objectActionMenu.open(card);
		}
	}
	else if (m_userActions.getActionState("EQUIPMENT")) {
		stateMachine.changeState(new EquipmentScene(m_userActions, m_player, m_renderer));
	}
	else {
		m_cardsRenderer.update();
	}
}

void InventoryScene::_executeMenuAction(E_ObjectActionMenuItem action, StateMachine<SceneState> &stateMachine) {
	auto card = m_player.getInventoryItem(_getCardIndex());
	if (action == USE) {
		if (card->isConsumable()) {
			card->consume();
			if (card->getQuantity() == 0) {
				m_player.removeInventoryCard(card);
				if (m_player.getActionBar().hasCard(card)) {
					m_player.getActionBar().removeCard(card);
				}
			}
		}
		if (card->applyOnSelf()) {
			m_player.applyCardStats(card);
		}
	}
	else if (action == SORT) {
		m_player.getInventory().sort();
	}
	else if (action == INFO) {
		std::cout << "Info object\n";
	}
	else if (action == DISCARD) {
		m_player.removeInventoryCard(card);
		m_player.getEquipment().remove(card);
		if (m_player.getActionBar().hasCard(card)) {
			m_player.getActionBar().removeCard(card);
		}
	}
	else if (action == ADD_ACTIONBAR && !m_player.getActionBar().hasCard(card)) {
		stateMachine.pushState(
			new QuickActionBarScene(
				m_userActions,
				m_player,
				card,
				m_renderer
			)
		);
	}
	else if (action == REMOVE_ACTIONBAR && m_player.getActionBar().hasCard(card)) {
		m_player.getActionBar().removeCard(card);
	}
}

void InventoryScene::render() {
	m_cardsRenderer.render();
	m_titlesTab.render(m_renderer->getRenderer());
	if (m_objectActionMenu.isOpen()) {
		m_objectActionMenu.render();
	}
}

/**
 * Return the index in the player's inventory of the card under the cursor.
 */
int InventoryScene::_getCardIndex() const {
	return m_cardsRenderer.getSelectedCardIndex();
}
