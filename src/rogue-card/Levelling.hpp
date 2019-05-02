#ifndef __LEVELLING__
#define __LEVELLING__

#include "../common/types.hpp"

enum E_SkillIncreaseResult {NO_CHANGE, SKILL_ONLY, SKILL_LEVEL_UP, GLOBAL_LEVEL_UP};

const int STEPS_TO_NEXT_LEVEL = 10;

class Levelling {
	private:
	int m_iLevel = 1;
	int m_iStepsBeforeNextLevel = STEPS_TO_NEXT_LEVEL;
	int m_aSkillXP[NB_XP_SKILLS] = {};

	int _convertLevelToSkillXP(int level) const;
	int _convertSkillToLevel(int skillValue) const;
	E_SkillIncreaseResult _skillLevelUp();
	void _levelUp();

	public:
	void setLevel(int level);
	int getLevel() const;

	E_SkillIncreaseResult increaseSkillXP(E_XPSkill skill, int amount);
	int getSkillLevel(E_XPSkill skill) const;
	int getPointsForNextLevel(E_XPSkill skill) const;
	int getSkill(E_XPSkill skill) const;
	int getStepsBeforeLevelUp() const;
};

#endif
