#ifndef __ENEMY_CARD__
#define __ENEMY_CARD__

#include "../common/types.hpp"
#include "../common/ResourceManager.hpp"
#include "Card.hpp"

class EnemyCard : public Card {
	static ResourceManager<S_EnemyMeta> m_enemyMeta;
	char m_sName[MAX_CHAR_ENEMY_NAME];
	int m_iHealth = 0;
	int m_iMaxHealth = 0;
	int m_iStrength = 0;
	int m_iDefence = 0;

	public:
	EnemyCard();
	void create();
	static bool prepareMeta(std::string file);
};

#endif
