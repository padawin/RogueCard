#ifndef __ENEMY_CARD__
#define __ENEMY_CARD__

#include "Card.hpp"
#include "../common/types.hpp"
#include "../common/ResourceManager.hpp"

class EnemyCard : public Card {
	static ResourceManager<S_EnemyMeta> m_enemyMeta;

	public:
	EnemyCard();
	void create();
	static bool prepareMeta(std::string file);
};

#endif
