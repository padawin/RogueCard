#include <math.h>
#include "Levelling.hpp"

void Levelling::setLevel(int level) {
	m_iLevel = level;
}

int Levelling::getLevel() const {
	return m_iLevel;
}

void Levelling::increaseSkillXP(E_XPSkill skill, int amount) {
	if (skill < NB_XP_SKILLS) {
		m_aSkillXP[skill] += amount;
	}
}

int Levelling::getSkillLevel(E_XPSkill skill) const {
	if (skill >= NB_XP_SKILLS) {
		return 0;
	}
	return _convertSkillToLevel(m_aSkillXP[skill]);
}

int Levelling::_convertSkillToLevel(int skillValue) const {
	return (int) floor(sqrt(skillValue / 17+ 1));
}
