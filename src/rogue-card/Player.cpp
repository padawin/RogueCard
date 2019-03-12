#include "Player.hpp"
#include "EnemyCard.hpp"

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
	return card->setDamages(m_iStrength);
}

int Player::setDamages(int damages) {
	int finalDamages = damages - m_iDefence;
	if (finalDamages < 0) {
		finalDamages = 1;
	}
	m_iHealth -= finalDamages;
	if (m_iHealth < 0) {
		m_iHealth = 0;
	}
	return finalDamages;
}

bool Player::isDead() const {
	return m_iHealth == 0;
}

bool Player::hasSpaceInInventory() const {
	int i;
	for (i = 0; i < MAX_INVENTORY_SIZE && m_inventory[i] != nullptr; ++i) {}
	return i < MAX_INVENTORY_SIZE;

}

void Player::setInventoryItem(int index, std::shared_ptr<ObjectCard> card) {
	if (index < MAX_INVENTORY_SIZE) {
		m_inventory[index] = card;
	}
}

void Player::addItemToInventory(std::shared_ptr<ObjectCard> card) {
	int i = 0;
	while (i < MAX_INVENTORY_SIZE && m_inventory[i] != nullptr) {
		++i;
	}
	if (i < MAX_INVENTORY_SIZE) {
		m_inventory[i] = card;
	}
}

void Player::removeInventoryItem(int index) {
	m_inventory[index] = nullptr;
}

std::shared_ptr<ObjectCard> Player::getInventoryItem(int index) const {
	if (index >= MAX_INVENTORY_SIZE) {
		return nullptr;
	}
	return m_inventory[index];
}
