#include "EnemyCard.hpp"

ResourceManager<S_EnemyMeta> EnemyCard::m_enemyMeta = ResourceManager<S_EnemyMeta>();

EnemyCard::EnemyCard() : Card(EnemyCardType) {
	m_sImage = "monsters";
}

void EnemyCard::create() {
}

bool EnemyCard::prepareMeta(std::string file) {
	if (!m_enemyMeta.setResourceFile(file)) {
		return false;
	}
	m_enemyMeta.parseBinaryFile();
	return true;
}
