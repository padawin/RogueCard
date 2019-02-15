#include "EnemyCard.hpp"

ResourceManager<S_EnemyMeta> EnemyCard::m_enemyMeta = ResourceManager<S_EnemyMeta>();

EnemyCard::EnemyCard() : Card(EnemyCardType) {
	m_sImage = "monsters";
}

void EnemyCard::create() {
	std::map<int, S_EnemyMeta> &meta = m_enemyMeta.getParsedResources();
	unsigned long index = (unsigned long) rand() % meta.size();
	m_iTileX = meta[(int) index].tilesetX;
	m_iTileY = meta[(int) index].tilesetY;
}

bool EnemyCard::prepareMeta(std::string file) {
	if (!m_enemyMeta.setResourceFile(file)) {
		return false;
	}
	m_enemyMeta.parseBinaryFile();
	return true;
}
