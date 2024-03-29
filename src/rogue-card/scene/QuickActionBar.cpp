#include "sdl2/TextureManager.hpp"
#include "globals.hpp"
#include "game/StateMachine.hpp"
#include "QuickActionBar.hpp"

QuickActionBarScene::QuickActionBarScene(
	UserActions &userActions,
	Player &player,
	std::shared_ptr<ObjectCard> card,
	std::shared_ptr<SDL2Renderer> renderer
) :
	SceneState(userActions),
	m_renderer(renderer),
	m_player(player),
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

void QuickActionBarScene::update(StateMachine<SceneState> &stateMachine) {
	if (m_userActions.getActionState("BACK") == ActionState::ACTION_PRESSED) {
		stateMachine.popState();
	}
	else if (m_userActions.is("CURSOR_LEFT", ActionState::ACTION_PRESSED | ActionState::ACTION_DOWN)) {
		m_cursorPosition = ((ACTION_BAR_SIZE + m_cursorPosition - 1) % ACTION_BAR_SIZE);
	}
	else if (m_userActions.is("CURSOR_RIGHT", ActionState::ACTION_PRESSED | ActionState::ACTION_DOWN)) {
		m_cursorPosition = ((m_cursorPosition + 1) % ACTION_BAR_SIZE);
	}
	else if (m_userActions.getActionState("USE_CARD") == ActionState::ACTION_PRESSED) {
		m_player.getActionBar().setCard(m_cursorPosition, m_card);
		stateMachine.popState();
		// If fighting, remove the Inventory state.
		// This assumes the current state comes from the inventory, which is
		// the case at the time of writing of the code
		if (m_player.isFighting()) {
			stateMachine.popState();
		}
	}
}

void QuickActionBarScene::render() {
	_renderBackground();
	_renderCards();
	_renderCursor();
}

void QuickActionBarScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"quick-action-bar",  0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}

void QuickActionBarScene::_renderCards() const {
	for (int pos = 0; pos < ACTION_BAR_SIZE; ++pos) {
		if (m_player.getActionBar().getCard(pos) != nullptr) {
			m_player.getActionBar().getCard(pos)->render(
				m_renderer->getRenderer(),
				m_mCursorPositions[pos].x,
				m_mCursorPositions[pos].y
			);
		}
	}
}

void QuickActionBarScene::_renderCursor() const {
	TextureManager::Instance()->draw(
		"cursor",
		m_mCursorPositions[m_cursorPosition].x,
		m_mCursorPositions[m_cursorPosition].y,
		CARD_WIDTH,
		CARD_HEIGHT,
		m_renderer->getRenderer()
	);
}
