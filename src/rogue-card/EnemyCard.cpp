#include "EnemyCard.hpp"

ResourceManager<S_EnemyMeta> EnemyCard::m_enemyMeta = ResourceManager<S_EnemyMeta>();

EnemyCard::EnemyCard(const int playerLevel) :
	Card(EnemyCardType),
	m_elementalDamages(ElementalEffects()),
	m_elementalResistance(ElementalEffects()),
	m_iPlayerLevel(playerLevel)
{
	m_sImage = "monsters";
}

void EnemyCard::create() {
	std::map<int, S_EnemyMeta> &meta = m_enemyMeta.getParsedResources();
	int index = _getEnemyIndex(rand() % 1000, (int) meta.size());
	strncpy(m_sName, meta[index].name, MAX_CHAR_ENEMY_NAME);
	m_iTileX = meta[index].tilesetX;
	m_iTileY = meta[index].tilesetY;
	m_iHealth = m_iMaxHealth = meta[index].health;
	m_iStrength = meta[index].strength;
	m_iDefence = meta[index].defence;
	m_elementalDamages = meta[index].elementalDamages;
	m_elementalResistance = meta[index].elementalResistance;
}

int EnemyCard::_getEnemyIndex(int proba, int nbEnemies) {
	int index;
	if (proba <= 10) {
		index = m_iPlayerLevel - 4;
	}
	else if (proba <= 40) {
		index = m_iPlayerLevel - 3;
	}
	else if (proba <= 110) {
		index = m_iPlayerLevel - 2;
	}
	else if (proba <= 360) {
		index = m_iPlayerLevel - 1;
	}
	else if (proba <= 860) {
		index = m_iPlayerLevel;
	}
	else if (proba <= 990) {
		index = m_iPlayerLevel + 1;
	}
	else {
		index = m_iPlayerLevel + 2;
	}

	// index was created based on the player's level, which is 1-indexed, it now
	// needs to be 0-indexed
	--index;
	if (index < 0) {
		index = 0;
	}
	else if (index >= nbEnemies) {
		index = nbEnemies - 1;
	}

	return index;
}

bool EnemyCard::prepareMeta(std::string file) {
	if (!m_enemyMeta.setResourceFile(file)) {
		return false;
	}
	m_enemyMeta.parseBinaryFile();
	return true;
}

const char* EnemyCard::getName() const {
	return m_sName;
}

int EnemyCard::attack(Player &player) const {
	return player.setDamages(m_iStrength, m_elementalDamages);
}

int EnemyCard::setDamages(int physicalDamages, ElementalEffects elementalEffects) {
	physicalDamages = physicalDamages - m_iDefence;
	int elementalDamages = _calculateElementalDamages(elementalEffects);
	int finalDamages = physicalDamages + elementalDamages;
	m_iHealth -= finalDamages;
	if (m_iHealth < 0) {
		m_iHealth = 0;
	}
	else if (m_iHealth > m_iMaxHealth) {
		m_iHealth = m_iMaxHealth;
	}
	return finalDamages;
}

bool EnemyCard::isDead() const {
	return m_iHealth == 0;
}

int EnemyCard::_calculateElementalDamages(ElementalEffects effects) {
	ElementalEffects elementalDamages = ElementalEffects();
	for (int s = 0; s < NB_ELEMENTS; ++s) {
		E_ElementalElement element = (E_ElementalElement) s;
		int percentDamages = 100 - m_elementalResistance.getStat(element);
		int damages = percentDamages * effects.getStat(element) / 100;
		elementalDamages.setStat(element, damages);
	}
	return elementalDamages.sumPoints();
}
