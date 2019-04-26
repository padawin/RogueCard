#include "FightResult.hpp"
#include <string>

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
}

std::string FightResultScene::getStateID() const {
	return "FightResultScene";
}

void FightResultScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("CONFIRM") || m_userActions.getActionState("QUIT")) {
		m_fight.finalise();
		stateMachine.popState();
	}
}

void FightResultScene::render() {
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
