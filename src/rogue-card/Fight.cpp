#include "Fight.hpp"

Fight::Fight(Player &player) : m_player(player) {
}

void Fight::start(std::shared_ptr<EnemyCard> enemy) {
	m_player.setFighting(true);
	m_bRanaway = false;
	m_enemy = enemy;
	for (int skill = NONE; skill < NB_XP_SKILLS; ++skill) {
		m_fightXP[skill] = 0;
	}
}

S_FightTurnResult Fight::turn(std::shared_ptr<ObjectCard> weapon) {
	S_FightTurnResult res;
	_turnPlayer(weapon, res);
	if (!m_enemy->isDead()) {
		_turnEnemy(res);
	}
	return res;
}

void Fight::_turnPlayer(std::shared_ptr<ObjectCard> weapon, S_FightTurnResult &res) {
	int physicalDamages;
	ElementalEffects elementalDamages;
	if (weapon == nullptr) {
		physicalDamages = m_player.getEquipmentStats(false).points;
		elementalDamages = m_player.getElementalEffects(false);
	}
	else {
		physicalDamages = weapon->getStats().points;
		elementalDamages = weapon->getElementalEffects();
	}
	res.damagesDealtToEnemy = _getFinalDamages(
		physicalDamages,
		elementalDamages,
		m_enemy->getDefence(),
		m_enemy->getElementalDefence()
	);
	m_enemy->setDamages(res.damagesDealtToEnemy);
	m_player.getXPAttack(weapon, m_fightXP);
}

void Fight::_turnEnemy(S_FightTurnResult &res) {
	res.damagesDealtToPlayer = _getFinalDamages(
		m_enemy->getStrength(),
		m_enemy->getElementalDamages(),
		m_player.getDefence(),
		m_player.getElementalEffects(true)
	);
	m_player.setDamages(res.damagesDealtToPlayer);
	m_player.getXPDefence(m_fightXP);
}

int Fight::_getFinalDamages(int physicalDamages, ElementalEffects elementalDamages, int physicalDefence, ElementalEffects elementalDefence) const {
	physicalDamages = physicalDamages - physicalDefence;
	if (physicalDamages < 0) {
		physicalDamages = 0;
	}
	return physicalDamages + _calculateElementalDamages(elementalDamages, elementalDefence);
}

int Fight::_calculateElementalDamages(ElementalEffects damages, ElementalEffects defence) const {
	ElementalEffects elementalDamages = ElementalEffects();
	for (int s = 0; s < NB_ELEMENTS; ++s) {
		E_ElementalElement element = (E_ElementalElement) s;
		int percentDamages = 100 - defence.getStat(element);
		int elementDamages = percentDamages * damages.getStat(element) / 100;
		elementalDamages.setStat(element, elementDamages);
	}
	return elementalDamages.sumPoints();
}

void Fight::finalise() {
	m_enemy = nullptr;
	m_player.setFighting(false);
	for (int skill = NONE; skill < NB_XP_SKILLS; ++skill) {
		m_player.getLevelling().increaseSkillXP((E_XPSkill) skill, m_fightXP[skill]);
	}
}

bool Fight::isFighting() const {
	return !m_bRanaway && m_enemy != nullptr && !m_enemy->isDead();
}

bool Fight::ranAway() const {
	return m_bRanaway;
}

int Fight::pointsEarnedIn(E_XPSkill skill) const {
	return m_fightXP[skill];
}

std::shared_ptr<EnemyCard> Fight::getEnemy() const {
	return m_enemy;
}

Player &Fight::getPlayer() const {
	return m_player;
}

S_FightTurnResult Fight::runaway() {
	S_FightTurnResult res;
	if (!isFighting()) {
		return res;
	}
	// @TODO Use speed skill to try to runaway
	int proba = rand() % 1000;
	if (proba >= 500) {
		m_bRanaway = true;
		return res;
	}
	else {
		return skip();
	}
}

S_FightTurnResult Fight::skip() {
	S_FightTurnResult res;
	if (!isFighting()) {
		return res;
	}
	_turnEnemy(res);
	return res;
}
