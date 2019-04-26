#include <iostream>
#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Inventory.hpp"
#include "QuickActionBar.hpp"
#include "ObjectCard.hpp"

InventoryScene::InventoryScene(
	UserActions &userActions,
	ActionBar &actionBar,
	Player &player,
	std::shared_ptr<SDL2Renderer> renderer
) :
	State(userActions),
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
	)),
	m_actionBar(actionBar)
{
}

std::string InventoryScene::getStateID() const {
	return "InventoryScene";
}

bool InventoryScene::onEnter() {
	return true;
}

void InventoryScene::update(StateMachine &stateMachine) {
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
		if (m_player.getInventoryItem(_getCardIndex()) != nullptr) {
			auto card = m_player.getInventoryItem(_getCardIndex());
			m_objectActionMenu.setContext(
				(!m_player.isFighting() ? FLAG_CONTEXT_NOT_IN_FIGHT : 0)
				| (m_actionBar.hasCard(card) ? FLAG_CONTEXT_CARD_IN_ACTIONBAR : FLAG_CONTEXT_CARD_NOT_IN_ACTIONBAR)
			);
			m_objectActionMenu.open(card);
		}
	}
	else {
		m_cardsRenderer.update();
	}
}

void InventoryScene::_executeMenuAction(E_ObjectActionMenuItem action, StateMachine &stateMachine) {
	auto card = m_player.getInventoryItem(_getCardIndex());
	if (action == USE) {
		if (card->isConsumable()) {
			card->consume();
			if (card->getQuantity() == 0) {
				m_player.removeInventoryCard(card);
				if (m_actionBar.hasCard(card)) {
					m_actionBar.removeCard(card);
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
		if (m_actionBar.hasCard(card)) {
			m_actionBar.removeCard(card);
		}
	}
	else if (action == ADD_ACTIONBAR && !m_actionBar.hasCard(card)) {
		stateMachine.pushState(
			new QuickActionBarScene(
				m_userActions,
				m_actionBar,
				m_player,
				card,
				m_renderer
			)
		);
	}
	else if (action == REMOVE_ACTIONBAR && m_actionBar.hasCard(card)) {
		m_actionBar.removeCard(card);
	}
}

void InventoryScene::render() {
	m_cardsRenderer.render();
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
