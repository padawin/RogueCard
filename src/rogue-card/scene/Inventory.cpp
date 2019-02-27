#include <iostream>
#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Inventory.hpp"
#include "ObjectCard.hpp"

InventoryScene::InventoryScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_player(player),
	m_renderer(renderer),
	m_objectActionMenu(ObjectAction(renderer))
{
	m_mCursorPositions[0] = {16, 16};
	m_mCursorPositions[1] = {64, 16};
	m_mCursorPositions[2] = {112, 16};
	m_mCursorPositions[3] = {160, 16};
	m_mCursorPositions[4] = {208, 16};
	m_mCursorPositions[5] = {256, 16};
	m_mCursorPositions[6] = {16, 80};
	m_mCursorPositions[7] = {64, 80};
	m_mCursorPositions[8] = {112, 80};
	m_mCursorPositions[9] = {160, 80};
	m_mCursorPositions[10] = {208, 80};
	m_mCursorPositions[11] = {256, 80};
	m_mCursorPositions[12] = {16, 144};
	m_mCursorPositions[13] = {64, 144};
	m_mCursorPositions[14] = {112, 144};
	m_mCursorPositions[15] = {160, 144};
	m_mCursorPositions[16] = {208, 144};
	m_mCursorPositions[17] = {256, 144};
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
			_executeMenuAction(m_objectActionMenu.getSelectedAction());
			m_objectActionMenu.close();
		}
	}
	else {
		if (m_userActions.getActionState("BACK")) {
			stateMachine.popState();
		}
		else if (m_userActions.getActionState("CURSOR_UP")) {
			_moveCursor('N');
		}
		else if (m_userActions.getActionState("CURSOR_DOWN")) {
			_moveCursor('S');
		}
		else if (m_userActions.getActionState("CURSOR_LEFT")) {
			_moveCursor('W');
		}
		else if (m_userActions.getActionState("CURSOR_RIGHT")) {
			_moveCursor('E');
		}
		else if (m_userActions.getActionState("USE_CARD")) {
			if (m_player.getInventoryItem(_getCardIndex()) != nullptr) {
				m_objectActionMenu.open(m_player.getInventoryItem(_getCardIndex()));
			}
		}
	}
}

void InventoryScene::_executeMenuAction(E_ObjectActionMenuItem action) {
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
	else if (action == ADD_TO_ACTIONBAR) {
		std::cout << "Add object to actionbar\n";
	}
}

void InventoryScene::_moveCursor(char direction) {
	if (direction == 'N') {
		if (m_cursorPosition < 6) {
			// go at the bottom
			if (m_iPage == 1) {
				m_cursorPosition += 12;
				m_iPage = 4; // hardcoded to display the 18 last items, @TODO maybe compute?
			}
			else {
				m_iPage--;
			}
		}
		else {
			m_cursorPosition -= 6;
		}
	}
	else if (direction == 'S') {
		if (m_cursorPosition >= 12) {
			// go at the top
			if (m_iPage == 4) {
				m_cursorPosition -= 12;
				m_iPage = 1; // hardcoded to display the 18 first items, @TODO maybe compute?
			}
			else {
				m_iPage++;
			}
		}
		else {
			m_cursorPosition += 6;
		}
	}
	else if (direction == 'W') {
		if (m_cursorPosition % 6 == 0) {
			m_cursorPosition += 5;
		}
		else {
			m_cursorPosition--;
		}
	}
	else if (direction == 'E') {
		if ((m_cursorPosition + 1) % 6 == 0) {
			m_cursorPosition -= 5;
		}
		else {
			m_cursorPosition++;
		}
	}
}

void InventoryScene::render() {
	_renderBackground();
	_renderCards();
	if (m_objectActionMenu.isOpen()) {
		m_objectActionMenu.render();
	}
	else {
		_renderCursor();
	}
}

void InventoryScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"ui-inventory",  0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}

void InventoryScene::_renderCursor() {
	TextureManager::Instance()->draw(
		"cursor",
		m_mCursorPositions[m_cursorPosition].first,
		m_mCursorPositions[m_cursorPosition].second,
		48,
		64,
		m_renderer->getRenderer()
	);
}

void InventoryScene::_renderCards() {
	int startCard = (m_iPage - 1) * 6;
	int endCard = startCard + INVENTORY_PAGE_SIZE;

	for (int c = startCard; c < endCard; ++c) {
		auto card = m_player.getInventoryItem(c);
		if (card == nullptr) {
			continue;
		}
		card->render(
			m_renderer->getRenderer(),
			m_mCursorPositions[c - startCard].first,
			m_mCursorPositions[c - startCard].second
		);
	}
}

/**
 * Return the index in the player's inventory of the card under the cursor.
 */
int InventoryScene::_getCardIndex() const {
	return (m_iPage - 1) * 6 + m_cursorPosition;
}
