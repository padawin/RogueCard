#ifndef __FIGHT__
#define __FIGHT__

#include <memory>
#include "EnemyCard.hpp"
#include "ObjectCard.hpp"
#include "Player.hpp"
#include "../common/types.hpp"

class Fight {
	private:
	bool m_bRanaway = false;
	Player &m_player;
	std::shared_ptr<EnemyCard> m_enemy = nullptr;
	std::shared_ptr<ObjectCard> m_playerWeapon = nullptr;
	bool m_bPlayerHitCritical = false;
	bool m_bEnemyHitCritical = false;

	int m_fightXP[NB_XP_SKILLS] = {};

	void _turnPlayer(std::shared_ptr<ObjectCard> weapon, S_FightTurnResult &res);
	void _turnEnemy(S_FightTurnResult &res);
	int _setCriticalMultiplier(bool* actorCritical);

	int _getFinalDamages(int physicalDamages, ElementalEffects elementalDamages, int physicalDefence, ElementalEffects elementalDefence) const;
	int _calculateElementalDamages(ElementalEffects damages, ElementalEffects defence) const;

	public:
	~Fight() {}
	Fight(Player &player);
	void start(std::shared_ptr<EnemyCard> enemy);
	S_FightTurnResult turn(std::shared_ptr<ObjectCard> weapon);
	S_FightTurnResult runaway();
	S_FightTurnResult skip();
	int pointsEarnedIn(E_XPSkill skill) const;
	bool isFighting() const;
	bool ranAway() const;
	Player &getPlayer() const;
	std::shared_ptr<EnemyCard> getEnemy() const;
	void finalise();
};

#endif
