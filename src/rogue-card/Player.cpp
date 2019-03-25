#include "Player.hpp"
#include "EnemyCard.hpp"

Player::Player() :
	m_equipment(Equipment()),
	m_inventory(ObjectCardCollection())
{}

int Player::getHealth() const { return m_iHealth; }
int Player::getMaxHealth() const {
	int equipmentHealth = _getEquipmentStats(false).maxHealthPoints;
	return m_iMaxHealth + equipmentHealth;
}
int Player::getStrength() const { return m_iStrength; }
int Player::getDefence() const { return m_iDefence; }
int Player::getFloor() const { return m_iFloor; }
long Player::getGold() const { return m_iGold; }
int Player::getLevel() const { return m_iLevel; }

void Player::setHealth(int health) { m_iHealth = health;}
void Player::setMaxHealth(int maxHealth) { m_iMaxHealth = maxHealth;}
void Player::setStrength(int strength) { m_iStrength = strength;}
void Player::setDefence(int defence) { m_iDefence = defence;}

void Player::setFloor(int floorLevel) { m_iFloor = floorLevel;}
void Player::setGold(long gold) { m_iGold = gold;}
void Player::setLevel(int level) { m_iLevel = level;}

int Player::attack(std::shared_ptr<EnemyCard> card) const {
	int damages = m_iStrength + _getEquipmentStats(false).points;
	return card->setDamages(damages);
}

int Player::setDamages(int damages) {
	int gearDefence = _getEquipmentStats(true).points;
	int finalDamages = damages - (m_iDefence + gearDefence);
	if (finalDamages < 0) {
		finalDamages = 1;
	}
	m_iHealth -= finalDamages;
	if (m_iHealth < 0) {
		m_iHealth = 0;
	}
	return finalDamages;
}

S_CardStats Player::_getEquipmentStats(bool applyOnSelf) const {
	S_CardStats stats;
	stats.points = 0;
	stats.healthPoints = 0;
	stats.maxHealthPoints = 0;
	stats.firePoints = 0;
	for (int c = 0; c < SIZE_EQUIPMENT; ++c) {
		auto card = m_equipment.getCard(c);
		if (card != nullptr && applyOnSelf == card->hasFlags(FLAG_APPLY_ON_SELF)) {
			stats.points += m_equipment.getCard(c)->getStats().points;
			stats.healthPoints += m_equipment.getCard(c)->getStats().healthPoints;
			stats.maxHealthPoints += m_equipment.getCard(c)->getStats().maxHealthPoints;
			stats.firePoints += m_equipment.getCard(c)->getStats().firePoints;
		}
	}
	return stats;
}

bool Player::isDead() const {
	return m_iHealth == 0;
}

bool Player::isFighting() const {
	return m_bFighting;
}

void Player::setFighting(bool fighting) {
	m_bFighting = fighting;
}

ObjectCardCollection &Player::getInventory() {
	return m_inventory;
}

bool Player::hasSpaceInInventory() const {
	return !m_inventory.isFull();
}

void Player::setInventoryItem(unsigned int index, std::shared_ptr<ObjectCard> card) {
	m_inventory.setCard(index, card);
}

void Player::addItemToInventory(std::shared_ptr<ObjectCard> card) {
	m_inventory.addCard(card);
}

void Player::removeInventoryItem(unsigned int index) {
	m_inventory.removeCard(index);
}

std::shared_ptr<ObjectCard> Player::getInventoryItem(unsigned int index) const {
	return m_inventory.getCard(index);
}

void Player::equip(std::shared_ptr<ObjectCard> card) {
	m_equipment.equip(card);
}

Equipment &Player::getEquipment() {
	return m_equipment;
}
