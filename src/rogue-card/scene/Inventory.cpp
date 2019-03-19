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
	if (m_objectActionMenu.isOpen()) {
		bool pressedBack = m_userActions.getActionState("BACK"),
			 pressedAction = m_userActions.getActionState("USE_CARD");
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
	else if (m_userActions.getActionState("BACK")) {
		stateMachine.popState();
	}
	else if (m_userActions.getActionState("USE_CARD")) {
		if (m_player.getInventoryItem(_getCardIndex()) != nullptr) {
			auto card = m_player.getInventoryItem(_getCardIndex());
			m_objectActionMenu.open(card, m_actionBar.hasCard(card));
		}
	}
	else {
		m_cardsRenderer.update();
	}
}

void InventoryScene::_executeMenuAction(E_ObjectActionMenuItem action, StateMachine &stateMachine) {
	if (action == USE) {
		std::cout << "Use object\n";
		m_player.removeInventoryItem(_getCardIndex());
	}
	else if (action == EQUIP) {
		std::cout << "Equip object\n";
	}
	else if (action == INFO) {
		std::cout << "Info object\n";
	}
	else if (action == DISCARD) {
		std::cout << "Discard object\n";
		m_player.removeInventoryItem(_getCardIndex());
	}
	else if (action == ACTIONBAR) {
		auto card = m_player.getInventoryItem(_getCardIndex());
		if (m_actionBar.hasCard(card)) {
			m_actionBar.removeCard(card);
		}
		else {
			stateMachine.pushState(
				new QuickActionBarScene(
					m_userActions,
					m_actionBar,
					card,
					m_renderer
				)
			);
		}
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
unsigned int InventoryScene::_getCardIndex() const {
	return m_cardsRenderer.getSelectedCardIndex();
}
