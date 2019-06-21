#include "PlayerStats.hpp"
#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "../sdl2/TextureManager.hpp"

const int STAT_CURSOR_WIDTH = 144;
const int STAT_CURSOR_HEIGHT = 14;

PlayerStatsScene::PlayerStatsScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_renderer(renderer),
	m_statsTitle(Text()),
	m_levelsTitle(Text())
{
}

std::string PlayerStatsScene::getStateID() const {
	return "PlayerStatsScene";
}

bool PlayerStatsScene::onEnter() {
	m_mCursorPositions[Stats] = {9, 8};
	m_mCursorPositions[Levels] = {167, 8};
	m_statsTitle.setText("Stats");
	m_levelsTitle.setText("Levels");
	m_iStatsTitleX = m_mCursorPositions[Stats].x + (STAT_CURSOR_WIDTH - m_statsTitle.getLength()) / 2;
	m_iLevelsTitleX = m_mCursorPositions[Levels].x + (STAT_CURSOR_WIDTH - m_levelsTitle.getLength()) / 2;
	return true;
}

void PlayerStatsScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("BACK")) {
		stateMachine.popState();
	}
	else if (m_userActions.getActionState("CURSOR_LEFT")) {
		m_cursorPosition = (StatCursorPosition) ((NbStatPositions + m_cursorPosition - 1) % NbStatPositions);
	}
	else if (m_userActions.getActionState("CURSOR_RIGHT")) {
		m_cursorPosition = (StatCursorPosition) ((m_cursorPosition + 1) % NbStatPositions);
	}
}

void PlayerStatsScene::render() {
	_renderBackground();
	_renderCursor();
	_renderTitles();
}

void PlayerStatsScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"ui-player-stats", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}

void PlayerStatsScene::_renderCursor() {
	TextureManager::Instance()->draw(
		"cursor-player-stats",
		m_mCursorPositions[m_cursorPosition].x,
		m_mCursorPositions[m_cursorPosition].y,
		STAT_CURSOR_WIDTH,
		STAT_CURSOR_HEIGHT,
		m_renderer->getRenderer()
	);
}

void PlayerStatsScene::_renderTitles() {
	m_statsTitle.render(
		m_renderer->getRenderer(),
		m_iStatsTitleX,
		m_mCursorPositions[Stats].y
	);
	m_levelsTitle.render(
		m_renderer->getRenderer(),
		m_iLevelsTitleX,
		m_mCursorPositions[Levels].y
	);
}
