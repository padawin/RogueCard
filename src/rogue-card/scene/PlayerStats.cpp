#include "PlayerStats.hpp"
#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "../sdl2/TextureManager.hpp"

const int STAT_CURSOR_WIDTH = 144;
const int STAT_CURSOR_HEIGHT = 14;

const int STAT_TEXT_X = 8;
const int STAT_HP_Y = 62;
const int STAT_FLOOR_Y = 78;
const int STAT_STR_Y = 110;
const int STAT_DEF_Y = 126;

const int NB_ELEMENTS_PER_PAGE = 5;
const int NEXT_PAGE_X = 152;
const int NEXT_PAGE_Y = 42;
const int PREV_PAGE_X = 152;
const int PREV_PAGE_Y = 220;

PlayerStatsScene::PlayerStatsScene(
	UserActions &userActions,
	std::shared_ptr<SDL2Renderer> renderer,
	Player &player
) :
	State(userActions),
	m_player(player),
	m_renderer(renderer),
	m_statsTitle(Text()),
	m_levelsTitle(Text()),
	m_healthTitle(Text()),
	m_floorTitle(Text()),
	m_strengthTitle(Text()),
	m_defenceTitle(Text())
{
}

std::string PlayerStatsScene::getStateID() const {
	return "PlayerStatsScene";
}

bool PlayerStatsScene::onEnter() {
	_setMaxPageNumbers();
	m_mCursorPositions[Stats] = {9, 8};
	m_mCursorPositions[Levels] = {167, 8};
	m_statsTitle.setText("Stats");
	m_levelsTitle.setText("Levels");

	_setDynamicTitles();

	// Horizontally center the titles
	m_iStatsTitleX = m_mCursorPositions[Stats].x + (STAT_CURSOR_WIDTH - m_statsTitle.getLength()) / 2;
	m_iLevelsTitleX = m_mCursorPositions[Levels].x + (STAT_CURSOR_WIDTH - m_levelsTitle.getLength()) / 2;
	return true;
}

void PlayerStatsScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("BACK")) {
		stateMachine.popState();
	}
	else if (m_userActions.getActionState("CURSOR_LEFT")) {
		m_iPage = 1;
		m_cursorPosition = (StatCursorPosition) ((NbStatPositions + m_cursorPosition - 1) % NbStatPositions);
	}
	else if (m_userActions.getActionState("CURSOR_RIGHT")) {
		m_iPage = 1;
		m_cursorPosition = (StatCursorPosition) ((m_cursorPosition + 1) % NbStatPositions);
	}
	else if (m_userActions.getActionState("CURSOR_UP")) {
		m_iPage = 1 + (m_iNBPages[m_cursorPosition] + m_iPage - 2) % m_iNBPages[m_cursorPosition];
	}
	else if (m_userActions.getActionState("CURSOR_DOWN")) {
		m_iPage = 1 + m_iPage % m_iNBPages[m_cursorPosition];
	}
}

void PlayerStatsScene::render() {
	_renderBackground();
	_renderCursor();
	_renderTitles();
	_renderPagination();
	if (m_cursorPosition == Stats) {
		_renderStats();
	}
}

void PlayerStatsScene::_setDynamicTitles() {
	char hpText[64],
		 floorText[64],
		 strText[64],
		 defText[64];
	snprintf(hpText, 64, "Health points: %d/%d", m_player.getHealth(), m_player.getMaxHealth());
	snprintf(floorText, 64, "Current floor: %d", m_player.getFloor().getLevel());
	snprintf(strText, 64, "Strength: %d", m_player.getStrength());
	snprintf(defText, 64, "Defence: %d", m_player.getDefence());
	m_healthTitle.setText(hpText);
	m_floorTitle.setText(floorText);
	m_strengthTitle.setText(strText);
	m_defenceTitle.setText(defText);
}

void PlayerStatsScene::_setMaxPageNumbers() {
	int nbElementsPages = NB_ELEMENTS / NB_ELEMENTS_PER_PAGE;
	if (NB_ELEMENTS % NB_ELEMENTS_PER_PAGE) {
		nbElementsPages++;
	}
	m_iNBPages[Stats] = 1 + nbElementsPages;
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

void PlayerStatsScene::_renderPagination() const {
	if (m_iPage > 1) {
		TextureManager::Instance()->drawFrame(
			"arrows",
			NEXT_PAGE_X,
			NEXT_PAGE_Y,
			ARROW_WIDTH, ARROW_HEIGHT,
			0,
			1,
			m_renderer->getRenderer()
		);
	}

	if (m_iPage < m_iNBPages[m_cursorPosition]) {
		TextureManager::Instance()->drawFrame(
			"arrows",
			PREV_PAGE_X,
			PREV_PAGE_Y,
			ARROW_WIDTH, ARROW_HEIGHT,
			0,
			0,
			m_renderer->getRenderer()
		);
	}
}

void PlayerStatsScene::_renderStats() const {
	m_healthTitle.render(m_renderer->getRenderer(), STAT_TEXT_X, STAT_HP_Y);
	m_floorTitle.render(m_renderer->getRenderer(), STAT_TEXT_X, STAT_FLOOR_Y);
	m_strengthTitle.render(m_renderer->getRenderer(), STAT_TEXT_X, STAT_STR_Y);
	m_defenceTitle.render(m_renderer->getRenderer(), STAT_TEXT_X, STAT_DEF_Y);
}
