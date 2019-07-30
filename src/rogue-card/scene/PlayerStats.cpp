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

const int NB_ELEMENTS_PER_PAGE = 10;
const int NB_SKILLS_PER_PAGE = 5;
const int NEXT_PAGE_X = 152;
const int NEXT_PAGE_Y = 42;
const int PREV_PAGE_X = 152;
const int PREV_PAGE_Y = 220;

const int FIRST_ELEMENT_Y = 62;
const int FIRST_SKILL_LEVEL_Y = 55;
const int FIRST_SKILL_PROGRESS_Y = 77;

const int SKILL_TEXT_X = 8;
const int SKILL_DELTA_Y = 32;

const int NEXT_LEVELS_X = 8;
const int NEXT_LEVELS_Y = 39;

const int SKILL_PROGRESS_X = 168;

PlayerStatsScene::PlayerStatsScene(
	UserActions &userActions,
	std::shared_ptr<SDL2Renderer> renderer,
	Player &player
) :
	SceneState(userActions),
	m_player(player),
	m_renderer(renderer),
	m_elementalEffectsAtk(ElementalEffects()),
	m_elementalEffectsDef(ElementalEffects()),
	m_statsTitle(Text()),
	m_levelsTitle(Text()),
	m_healthTitle(Text()),
	m_floorTitle(Text()),
	m_nextLevel(Text())
{
}

std::string PlayerStatsScene::getStateID() const {
	return "PlayerStatsScene";
}

bool PlayerStatsScene::onEnter() {
	m_elementalEffectsAtk = m_player.getElementalEffects(false);
	m_elementalEffectsDef = m_player.getElementalEffects(true);
	m_mCursorPositions[Stats] = {9, 8};
	m_mCursorPositions[Levels] = {167, 8};
	m_statsTitle.setText("Stats");
	m_levelsTitle.setText("Levels");
	m_nextLevel.setText("To next level:");

	_setDynamicTitles();
	_setElementTitles();
	_setSkillsTextsAndProgress();

	// Horizontally center the titles
	m_iStatsTitleX = m_mCursorPositions[Stats].x + (STAT_CURSOR_WIDTH - m_statsTitle.getLength()) / 2;
	m_iLevelsTitleX = m_mCursorPositions[Levels].x + (STAT_CURSOR_WIDTH - m_levelsTitle.getLength()) / 2;
	return true;
}

void PlayerStatsScene::update(StateMachine<SceneState> &stateMachine) {
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
		if (m_iPage > 1) {
			m_iPage--;
		}
	}
	else if (m_userActions.getActionState("CURSOR_DOWN")) {
		if (m_iPage < m_iNBPages[m_cursorPosition]) {
			m_iPage++;
		}
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
	else {
		_renderLevels();
	}
}

void PlayerStatsScene::_setDynamicTitles() {
	char hpText[64],
		 floorText[64];
	snprintf(hpText, 64, "Health points: %d/%d", m_player.getHealth(), m_player.getMaxHealth());
	snprintf(floorText, 64, "Current floor: %d", m_player.getFloor().getLevel());
	m_healthTitle.setText(hpText);
	m_floorTitle.setText(floorText);
}

void PlayerStatsScene::_setElementTitles() {
	int currentRow = 0;
	for (int e = 0; e < NB_ELEMENTS; ++e) {
		char elemAtkText[64],
			 elemDefText[64];
		std::string elementLabel = ElementalEffects::getElementLabel((E_ElementalElement)e);
		int atkStat = m_elementalEffectsAtk.getStat((E_ElementalElement) e),
			defStat = m_elementalEffectsDef.getStat((E_ElementalElement) e);
		if (atkStat != 0) {
			m_elementTexts[currentRow] = Text();
			snprintf(elemAtkText, 64, "%s attack: %d", elementLabel.c_str(), atkStat);
			m_elementTexts[currentRow].setText(elemAtkText);
			currentRow++;
		}

		if (defStat != 0) {
			m_elementTexts[currentRow] = Text();
			snprintf(elemDefText, 64, "%s defence: %d", elementLabel.c_str(), defStat);
			m_elementTexts[currentRow].setText(elemDefText);
			currentRow++;
		}
	}

	int nbElementsPages = (currentRow / NB_ELEMENTS_PER_PAGE) + (currentRow % NB_ELEMENTS_PER_PAGE != 0);
	m_iNBPages[Stats] = 1 + nbElementsPages;
}

void PlayerStatsScene::_setSkillsTextsAndProgress() {
	int currentRow = 0;
	char skillText[64];
	for (int skill = 0; skill < NB_XP_SKILLS; ++skill) {
		std::string skillLabel = getSkillLabel((E_XPSkill) skill);
		if (skillLabel == "") {
			continue;
		}
		m_skillsTexts[currentRow] = Text();
		snprintf(
			skillText, 64,
			"%s: %d",
			skillLabel.c_str(),
			m_player.getLevelling().getSkillLevel((E_XPSkill) skill)
		);
		m_skillsTexts[currentRow].setText(skillText);
		m_aSkillsProgress[currentRow].setProgress(
			m_player.getLevelling().getProgressToNextSkillLevel((E_XPSkill) skill)
		);
		currentRow++;
	}

	m_iNBPages[Levels] = (currentRow / NB_SKILLS_PER_PAGE) + (currentRow % NB_SKILLS_PER_PAGE != 0);
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
	if (m_iPage == 1) {
		m_healthTitle.render(m_renderer->getRenderer(), STAT_TEXT_X, STAT_HP_Y);
		m_floorTitle.render(m_renderer->getRenderer(), STAT_TEXT_X, STAT_FLOOR_Y);
	}
	else {
		int startElem = (m_iPage - 2) * NB_ELEMENTS_PER_PAGE,
			elem = startElem,
			displayedElems = 0;
		int y = FIRST_ELEMENT_Y;
		while (elem < NB_ELEMENTS * 2 && displayedElems < NB_ELEMENTS_PER_PAGE) {
			if (m_elementTexts[elem].getText() != "") {
				m_elementTexts[elem].render(
					m_renderer->getRenderer(),
					STAT_TEXT_X,
					y
				);
				displayedElems++;
				y += FONT_HEIGHT;
			}
			elem++;
		}
	}
}

void PlayerStatsScene::_renderLevels() const {
	m_nextLevel.render(
		m_renderer->getRenderer(),
		SCREEN_WIDTH - (m_nextLevel.getLength() + NEXT_LEVELS_X),
		NEXT_LEVELS_Y
	);
	int startElem = (m_iPage - 1) * NB_SKILLS_PER_PAGE,
		elem = startElem;
	int elemIndex = 0;
	while (elem - startElem < NB_SKILLS_PER_PAGE && elem < NB_XP_SKILLS) {
		if (m_skillsTexts[elem].getLength()) {
			int yPos = elemIndex * SKILL_DELTA_Y;
			m_skillsTexts[elem].render(
				m_renderer->getRenderer(), SKILL_TEXT_X, FIRST_ELEMENT_Y + yPos
			);
			m_aSkillsProgress[elem].render(
				m_renderer, SKILL_PROGRESS_X, FIRST_SKILL_PROGRESS_Y + yPos
			);
			elemIndex++;

		}
		elem++;
	}
}
