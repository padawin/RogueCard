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
		MAX_CHAR_ENEMY_NAME + 14,
		"You defeated %s",
		m_fight.getEnemy()->getName()
	);
	m_title.setText(title);

	m_iPage = PAGE_SKILLS;
	if (_wouldSkillLevelUp()) {
		m_iPagesToSee = m_iPagesToSee | PAGE_SKILLS_LEVEL;
	}
	if (_wouldLevelUp()) {
		m_iPagesToSee = m_iPagesToSee | PAGE_LEVEL;
	}
}

bool FightResultScene::_wouldSkillLevelUp() const {
	return false;
}

bool FightResultScene::_wouldLevelUp() const {
	return false;
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

}

void FightResultScene::_renderLevel() {

}
