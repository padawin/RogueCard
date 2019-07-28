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

int EnemyCard::attack(Player &player) const {
	return player.setDamages(m_iStrength, m_elementalDamages);
}

int EnemyCard::setDamages(int physicalDamages, ElementalEffects elementalEffects) {
	physicalDamages = physicalDamages - m_iDefence;
	if (physicalDamages < 0) {
		physicalDamages = 0;
	}
	int elementalDamages = _calculateElementalDamages(elementalEffects);
	int finalDamages = physicalDamages + elementalDamages;
	m_health -= finalDamages;
	return finalDamages;
}

bool EnemyCard::isDead() const {
	return m_health.getCurrent() == 0;
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
