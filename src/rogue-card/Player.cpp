#include "Player.hpp"
#include "EnemyCard.hpp"

Player::Player() :
	m_equipment(Equipment()),
	m_inventory(ObjectCardCollection())
{}

int Player::getHealth() const { return m_iHealth; }
int Player::getMaxHealth() const { return m_iMaxHealth; }
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
	int damages = m_iStrength + _getEquipmentPoints(false);
	return card->setDamages(damages);
}

int Player::setDamages(int damages) {
	int gearDefence = _getEquipmentPoints(true);
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

int Player::_getEquipmentPoints(bool applyOnSelf) const {
	int points = 0;
	for (int c = 0; c < SIZE_EQUIPMENT; ++c) {
		auto card = m_equipment.getCard(c);
		if (card != nullptr && applyOnSelf == card->hasFlags(FLAG_APPLY_ON_SELF)) {
			points += m_equipment.getCard(c)->getStats().points;
		}
	}
	return points;
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
