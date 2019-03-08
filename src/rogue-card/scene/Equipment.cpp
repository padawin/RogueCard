#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Equipment.hpp"

EquipmentScene::EquipmentScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_renderer(renderer)
{
	m_mCursorPositions[0] = {16, 8};
	m_mCursorPositions[1] = {64, 8};
	m_mCursorPositions[2] = {112, 8};
	m_mCursorPositions[3] = {160, 8};
	m_mCursorPositions[4] = {208, 8};
	m_mCursorPositions[5] = {256, 8};
	m_mCursorPositions[6] = {16, 72};
	m_mCursorPositions[7] = {256, 72};
}

std::string EquipmentScene::getStateID() const {
	return "EquipmentScene";
}

bool EquipmentScene::onEnter() {
	return true;
}

void EquipmentScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("BACK")) {
		stateMachine.popState();
	}
	else if (m_userActions.getActionState("CURSOR_LEFT")) {
		m_cursorPosition = (EQUIPMENT_SIZE + m_cursorPosition - 1) % EQUIPMENT_SIZE;
	}
	else if (m_userActions.getActionState("CURSOR_RIGHT")) {
		m_cursorPosition = (m_cursorPosition + 1) % EQUIPMENT_SIZE;
	}
}

void EquipmentScene::render() {
	_renderBackground();
	_renderCursor();
}

void EquipmentScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"ui-equipment", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
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
