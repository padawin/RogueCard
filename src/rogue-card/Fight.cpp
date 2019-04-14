#include "Fight.hpp"

Fight::Fight(Player &player) : m_player(player) {
}

void Fight::start(std::shared_ptr<EnemyCard> enemy) {
	m_player.setFighting(true);
	m_enemy = enemy;
	for (int skill = NONE; skill < NB_XP_SKILLS; ++skill) {
		m_fightXP[skill] = 0;
	}
}

S_FightTurnResult Fight::turn(std::shared_ptr<ObjectCard> weapon) {
	S_FightTurnResult res;
	res.damagesDealtToEnemy = m_player.attack(m_enemy, weapon);
	m_player.getXPAttack(weapon, m_fightXP);
	if (!m_enemy->isDead()) {
		res.damagesDealtToPlayer = m_enemy->attack(m_player);
		m_player.getXPDefence(m_fightXP);
	}
	return res;
}

void Fight::finalise() {
	m_enemy = nullptr;
	m_player.setFighting(false);
	for (int skill = NONE; skill < NB_XP_SKILLS; ++skill) {
		m_player.getLevelling().increaseSkillXP((E_XPSkill) skill, m_fightXP[skill]);
	}
}

bool Fight::isFighting() const {
	return m_enemy != nullptr && !m_enemy->isDead();
}

int Fight::pointsEarnedIn(E_XPSkill skill) const {
	return m_fightXP[skill];
}

std::shared_ptr<EnemyCard> Fight::getEnemy() const {
	return m_enemy;
}
