#ifndef __FIGHT__
#define __FIGHT__

#include <memory>
#include "EnemyCard.hpp"
#include "ObjectCard.hpp"
#include "Player.hpp"

struct S_FightTurnResult {
	int damagesDealtToEnemy = 0;
	int damagesDealtToPlayer = 0;
};

class Fight {
	private:
	bool m_bRanaway = false;
	Player &m_player;
	std::shared_ptr<EnemyCard> m_enemy = nullptr;
	std::shared_ptr<ObjectCard> m_playerWeapon = nullptr;

	int m_fightXP[NB_XP_SKILLS] = {};


	public:
	~Fight() {}
	Fight(Player &player);
	void start(std::shared_ptr<EnemyCard> enemy);
	S_FightTurnResult turn(std::shared_ptr<ObjectCard> weapon);
	S_FightTurnResult runaway();
	int pointsEarnedIn(E_XPSkill skill) const;
	bool isFighting() const;
	std::shared_ptr<EnemyCard> getEnemy() const;
	void finalise();
};

#endif
