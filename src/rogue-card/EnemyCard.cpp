#include "EnemyCard.hpp"

ContentMeta<S_EnemyMeta> EnemyCard::m_enemyMeta = ContentMeta<S_EnemyMeta>();

EnemyCard::EnemyCard(const char *id) :
	Card(EnemyCardType),
	m_health(Health(0, 0)),
	m_elementalDamages(ElementalEffects()),
	m_elementalResistance(ElementalEffects())
{
	strncpy(m_sMetaID, id, MAX_CHAR_CARD_ID - 1);
	m_sImage = "monsters";
}

void EnemyCard::create() {
	S_EnemyMeta meta = m_enemyMeta.getFromID(m_sMetaID);
	strncpy(m_sName, meta.name, MAX_CHAR_ENEMY_NAME);
	m_iTileX = meta.tilesetX;
	m_iTileY = meta.tilesetY;
	m_health.setCurrent(meta.health);
	m_health.setMax(meta.health);
	m_iStrength = meta.strength;
	m_iDefence = meta.defence;
	m_elementalDamages = meta.elementalDamages;
	m_elementalResistance = meta.elementalResistance;
}


bool EnemyCard::prepareMeta(std::string file) {
	return m_enemyMeta.prepare(file);
}

const char* EnemyCard::getName() const {
	return m_sName;
}

const char* EnemyCard::getID() const {
	return m_sMetaID;
}

int EnemyCard::getStrength() const {
	return m_iStrength;
}

int EnemyCard::getDefence() const {
	return m_iDefence;
}

ElementalEffects EnemyCard::getElementalDamages() const {
	return m_elementalDamages;
}

ElementalEffects EnemyCard::getElementalDefence() const {
	return m_elementalResistance;
}

void EnemyCard::setDamages(int damages) {
	m_health -= damages;
}

bool EnemyCard::isDead() const {
	return m_health.getCurrent() == 0;
}
