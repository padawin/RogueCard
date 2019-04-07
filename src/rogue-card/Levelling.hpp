#ifndef __LEVELLING__
#define __LEVELLING__

#include "../common/types.hpp"

enum E_SkillIncreaseResult {NO_CHANGE, SKILL_ONLY, SKILL_LEVEL_UP};

class Levelling {
	private:
	int m_iLevel = 1;
	int m_aSkillXP[NB_XP_SKILLS] = {};

	int _convertSkillToLevel(int skillValue) const;

	public:
	void setLevel(int level);
	int getLevel() const;

	E_SkillIncreaseResult increaseSkillXP(E_XPSkill skill, int amount);
	int getSkillLevel(E_XPSkill skill) const;
};

#endif
