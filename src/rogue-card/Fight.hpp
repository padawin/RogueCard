#ifndef __FIGHT__
#define __FIGHT__

#include <memory>
#include "EnemyCard.hpp"
#include "ObjectCard.hpp"
#include "Player.hpp"

class Fight {
	private:
	Player &m_player;
	std::shared_ptr<EnemyCard> m_enemy = nullptr;
	std::shared_ptr<ObjectCard> m_playerWeapon = nullptr;

	int m_fightXP[NB_XP_SKILLS] = {};


	public:
	~Fight() {}
	Fight(Player &player);
	void start(std::shared_ptr<EnemyCard> enemy);
	std::string turn(std::shared_ptr<ObjectCard> weapon);
	int pointsEarnedIn(E_XPSkill skill) const;
	bool isFighting() const;
	std::shared_ptr<EnemyCard> getEnemy() const;
	void finalise();
};

#endif
