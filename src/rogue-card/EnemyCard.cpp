#include "EnemyCard.hpp"

ResourceManager<S_EnemyMeta> EnemyCard::m_enemyMeta = ResourceManager<S_EnemyMeta>();

EnemyCard::EnemyCard() : Card(EnemyCardType) {
	m_sImage = "monsters";
}

void EnemyCard::create() {
	std::map<int, S_EnemyMeta> &meta = m_enemyMeta.getParsedResources();
	unsigned long index = (unsigned long) rand() % meta.size();
	int i = (int) index;
	strncpy(m_sName, meta[i].name, MAX_CHAR_ENEMY_NAME);
	m_iTileX = meta[i].tilesetX;
	m_iTileY = meta[i].tilesetY;
	m_iHealth = m_iMaxHealth = meta[i].health;
	m_iStrength = meta[i].strength;
	m_iDefence = meta[i].defence;
}

bool EnemyCard::prepareMeta(std::string file) {
	if (!m_enemyMeta.setResourceFile(file)) {
		return false;
	}
	m_enemyMeta.parseBinaryFile();
	return true;
}
