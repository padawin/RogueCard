#ifndef __ENEMY_CARD__
#define __ENEMY_CARD__

#include "../common/types.hpp"
#include "../common/ElementalEffects.hpp"
#include "Card.hpp"
#include "EnemyMeta.hpp"
#include "Player.hpp"

class EnemyCard : public Card {
	static EnemyMeta m_enemyMeta;
	char m_sName[MAX_CHAR_ENEMY_NAME];
	int m_iHealth = 0;
	int m_iMaxHealth = 0;
	int m_iStrength = 0;
	int m_iDefence = 0;

	/**
	 * Absolute damages values
	 */
	ElementalEffects m_elementalDamages;

	/**
	 * Percentages.
	 *
	 * x < 0: Vulnerable
	 * 0 < x < 100: Resistance
	 * 100 < x: Absorbs -> heals
	 */
	ElementalEffects m_elementalResistance;

	int m_iPlayerLevel;

	int _getEnemyIndex(int proba, int nbEnemies);

	int _calculateElementalDamages(ElementalEffects elementalDamages);

	public:
	EnemyCard(const int playerLevel);
	void create();
	static bool prepareMeta(std::string file);

	const char* getName() const;
	int setDamages(int physicalDamages, ElementalEffects elementalEffects);
	int attack(Player &player) const;
	bool isDead() const;
};

#endif
