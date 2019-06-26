#include <iostream>
#include "FightResult.hpp"
#include <string>

const unsigned int PAGE_SKILLS = 0x1;
const unsigned int PAGE_SKILLS_LEVEL = 0x2;
const unsigned int PAGE_LEVEL = 0x4;
const unsigned int LAST_PAGE = PAGE_LEVEL;

FightResultScene::FightResultScene(UserActions &userActions, Fight &fight, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_renderer(renderer),
	m_fight(fight),
	m_title(Text()),
	m_summary(Text())
{
	char title[MAX_CHAR_ENEMY_NAME + 14];
	snprintf(
		title,
		MAX_CHAR_ENEMY_NAME + 20,
		m_fight.ranAway() ? "You fled from %s" : "You defeated %s",
		m_fight.getEnemy()->getName()
	);
	m_title.setText(title);

	m_iPage = PAGE_SKILLS;
	if (_handleSkillsLevelUp()) {
		m_iPagesToSee = m_iPagesToSee | PAGE_SKILLS_LEVEL;
	}
	if (_handleLevelUp()) {
		m_iPagesToSee = m_iPagesToSee | PAGE_LEVEL;
	}
}

bool FightResultScene::_handleSkillsLevelUp() {
	Levelling &levelling = m_fight.getPlayer().getLevelling();
	bool res = false;
	for (int skill = NONE; skill < NB_XP_SKILLS; ++skill) {
		E_XPSkill xpSkill = (E_XPSkill) skill;
		std::clog << "Skill " << getSkillLabel(xpSkill);
		m_aSkillLevels[skill].first = levelling.getSkillLevel(xpSkill);
		m_aSkillLevels[skill].second = levelling.getSkillLevel(xpSkill);
		if (levelling.isEnoughForNextSkillLevel(xpSkill, m_fight.pointsEarnedIn(xpSkill))) {
			std::clog << "Skill level up\n" << std::endl;
			m_aSkillLevels[skill].second++;
			res = true;
		}
	}
	return res;
}

bool FightResultScene::_handleLevelUp() const {
	int nbSkillsLevelUp = 0;
	Levelling &levelling = m_fight.getPlayer().getLevelling();
	for (int skill = NONE; skill < NB_XP_SKILLS; ++skill) {
		if (m_aSkillLevels[skill].first < m_aSkillLevels[skill].second) {
			++nbSkillsLevelUp;
		}
	}
	return nbSkillsLevelUp >= levelling.getStepsBeforeLevelUp();
}

std::string FightResultScene::getStateID() const {
	return "FightResultScene";
}

void FightResultScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("CONFIRM")) {
		do {
			m_iPage = m_iPage << 1;
		} while (!(m_iPage & m_iPagesToSee) && m_iPage <= LAST_PAGE);

		if (m_iPage > LAST_PAGE) {
			m_fight.finalise();
			stateMachine.popState();
		}
	}
}

void FightResultScene::render() {
	if (m_iPage == PAGE_SKILLS) {
		_renderSkillsXP();
	}
	else if (m_iPage == PAGE_SKILLS_LEVEL) {
		_renderSkillsLevels();
	}
	else if (m_iPage == PAGE_LEVEL) {
		_renderLevel();
	}
}

void FightResultScene::_renderSkillsXP() {
	m_title.render(m_renderer->getRenderer(), 18, 16);
	std::string resTitle = "You earned:\n";
	std::string res = "";
	for (int skill = NONE; skill < NB_XP_SKILLS; ++skill) {
		int points = m_fight.pointsEarnedIn((E_XPSkill) skill);
		if (points > 0) {
			char xpStr[50];
			snprintf(xpStr, 50, "%d XP in %s\n", points, getSkillLabel((E_XPSkill) skill).c_str());
			res += xpStr;
		}
	}
	if (res != "") {
		m_summary.setText(resTitle + res);
		m_summary.render(m_renderer->getRenderer(), 18, 48);
	}
}

void FightResultScene::_renderSkillsLevels() {
	m_title.render(m_renderer->getRenderer(), 18, 16);
	std::string res = "Skills Level Up:\n";
	for (int skill = NONE; skill < NB_XP_SKILLS; ++skill) {
		if (m_aSkillLevels[skill].first < m_aSkillLevels[skill].second) {
			char xpStr[50];
			snprintf(
				xpStr,
				50,
				"%s: %d -> %d\n",
				getSkillLabel((E_XPSkill) skill).c_str(),
				m_aSkillLevels[skill].first,
				m_aSkillLevels[skill].second
			);
			res += xpStr;
		}
	}
	m_summary.setText(res);
	m_summary.render(m_renderer->getRenderer(), 18, 48);
}

void FightResultScene::_renderLevel() {
	m_title.render(m_renderer->getRenderer(), 18, 16);
	char levelStr[30];
	snprintf(
		levelStr,
		30,
		"You are now level %d",
		m_fight.getPlayer().getLevelling().getLevel() + 1
	);
	m_summary.setText(levelStr);
	m_summary.render(m_renderer->getRenderer(), 18, 48);
}
