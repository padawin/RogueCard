#include "../sdl2/TextureManager.hpp"
#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "QuickActionBar.hpp"

QuickActionBarScene::QuickActionBarScene(
	UserActions &userActions,
	ActionBar &actionBar,
	std::shared_ptr<ObjectCard> card,
	std::shared_ptr<SDL2Renderer> renderer
) :
	State(userActions),
	m_renderer(renderer),
	m_actionBar(actionBar),
	m_card(card)
{
	m_mCursorPositions[0] = {64, 64};
	m_mCursorPositions[1] = {112, 64};
	m_mCursorPositions[2] = {160, 64};
	m_mCursorPositions[3] = {208, 64};
}

std::string QuickActionBarScene::getStateID() const {
	return "QuickActionBarScene";
}

bool QuickActionBarScene::onEnter() {
	return true;
}

void QuickActionBarScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("BACK")) {
		stateMachine.popState();
	}
	else if (m_userActions.getActionState("CURSOR_LEFT")) {
		m_cursorPosition = ((ACTION_BAR_SIZE + m_cursorPosition - 1) % ACTION_BAR_SIZE);
	}
	else if (m_userActions.getActionState("CURSOR_RIGHT")) {
		m_cursorPosition = ((m_cursorPosition + 1) % ACTION_BAR_SIZE);
	}
}

void QuickActionBarScene::render() {
	_renderBackground();
	_renderCursor();
}

void QuickActionBarScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"quick-action-bar",  0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}

void QuickActionBarScene::_renderCursor() const {
	TextureManager::Instance()->draw(
		"cursor",
		m_mCursorPositions[m_cursorPosition].first,
		m_mCursorPositions[m_cursorPosition].second,
		48,
		64,
		m_renderer->getRenderer()
	);
}
