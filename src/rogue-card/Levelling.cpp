#include <iostream>
#include <math.h>
#include "Levelling.hpp"

void Levelling::setLevel(int level) {
	m_iLevel = level;
}

int Levelling::getLevel() const {
	return m_iLevel;
}

E_SkillIncreaseResult Levelling::increaseSkillXP(E_XPSkill skill, int amount) {
	if (skill < NB_XP_SKILLS) {
		int oldAmount = m_aSkillXP[skill];
		m_aSkillXP[skill] += amount;
		if (_convertSkillToLevel(oldAmount) != _convertSkillToLevel(m_aSkillXP[skill])) {
			_skillLevelUp();
		}
		return SKILL_ONLY;
	}

	return NO_CHANGE;
}

E_SkillIncreaseResult Levelling::_skillLevelUp() {
	--m_iStepsBeforeNextLevel;
	if (m_iStepsBeforeNextLevel <= 0) {
		_levelUp();
		return GLOBAL_LEVEL_UP;
	}
	else {
		return SKILL_LEVEL_UP;
	}
}

void Levelling::_levelUp() {
	m_iStepsBeforeNextLevel = m_iStepsBeforeNextLevel + STEPS_TO_NEXT_LEVEL;
	++m_iLevel;
}

int Levelling::getSkill(E_XPSkill skill) const {
	return m_aSkillXP[skill];
}

int Levelling::getSkillLevel(E_XPSkill skill) const {
	if (skill >= NB_XP_SKILLS) {
		return 0;
	}
	return _convertSkillToLevel(m_aSkillXP[skill]);
}

int Levelling::_convertSkillToLevel(int skillValue) const {
	return (int) floor(sqrt(skillValue / 17 + 1));
}

int Levelling::_convertLevelToSkillXP(int level) const {
	return 17 * (level * level - 1);
}

/**
 * Returns a number between 0 and 100 (percent) representing the progress in the
 * given skill. 0 means no XP points earnt since the last level up, 99 means
 * about to level up
 */
int Levelling::getProgressToNextSkillLevel(E_XPSkill skill) const {
	int skillCurrentLevel = getSkillLevel(skill);
	int xpLevel = _convertLevelToSkillXP(skillCurrentLevel);
	int xpNextLevel = _convertLevelToSkillXP(skillCurrentLevel + 1);
	int xpDelta = xpNextLevel - xpLevel;
	int xpInLevel = m_aSkillXP[skill] - xpLevel;
	return xpInLevel * 100 / xpDelta;
}

bool Levelling::isEnoughForNextSkillLevel(E_XPSkill skill, int amount) const {
	int skillCurrentLevel = getSkillLevel(skill);
	int xpNextLevel = _convertLevelToSkillXP(skillCurrentLevel + 1);
	std::clog << " - Current xp for skill: " << m_aSkillXP[skill];
	std::clog << " - XP to next level: " << xpNextLevel;
	std::clog << " - Earn XP: " << amount << std::endl;
	return xpNextLevel - m_aSkillXP[skill] <= amount;
}

int Levelling::getStepsBeforeLevelUp() const {
	return m_iStepsBeforeNextLevel;
}

void Levelling::setStepsBeforeLevelUp(int steps) {
	m_iStepsBeforeNextLevel = steps;
}
