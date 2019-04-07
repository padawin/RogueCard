#ifndef __LEVELLING__
#define __LEVELLING__

#include "../common/types.hpp"

class Levelling {
	private:
	int m_iLevel = 1;
	int m_aSkillXP[NB_XP_SKILLS] = {};

	int _convertSkillToLevel(int skillValue) const;

	public:
	void setLevel(int level);
	int getLevel() const;

	void increaseSkillXP(E_XPSkill skill, int amount);
	int getSkillLevel(E_XPSkill skill) const;
};

#endif
