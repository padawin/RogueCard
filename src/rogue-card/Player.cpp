#include "Player.hpp"
#include "EnemyCard.hpp"

Player::Player() :
	m_equipment(Equipment()),
	m_inventory(ObjectCardCollection()),
	m_floor(Floor())
{}

int Player::getHealth() const { return m_iHealth; }
int Player::getMaxHealth() const {
	int equipmentHealth = _getEquipmentStats(false).maxHealthPoints;
	return m_iMaxHealth + equipmentHealth;
}
int Player::getStrength() const { return m_iStrength; }
int Player::getDefence() const { return m_iDefence; }
Floor &Player::getFloor() { return m_floor; }
long Player::getGold() const { return m_iGold; }
int Player::getLevel() const { return m_iLevel; }

void Player::setHealth(int health) { m_iHealth = health;}
void Player::setMaxHealth(int maxHealth) { m_iMaxHealth = maxHealth;}
void Player::setStrength(int strength) { m_iStrength = strength;}
void Player::setDefence(int defence) { m_iDefence = defence;}

void Player::setGold(long gold) { m_iGold = gold;}
void Player::setLevel(int level) { m_iLevel = level;}

int Player::attack(std::shared_ptr<EnemyCard> card, std::shared_ptr<ObjectCard> attackCard) const {
	int damages;
	if (attackCard == nullptr) {
		damages = m_iStrength + _getEquipmentStats(0).points;
	}
	else {
		damages = attackCard->getStats().points;
	}
	return card->setDamages(damages);
}

int Player::setDamages(int damages) {
	int gearDefence = _getEquipmentStats(FLAG_APPLY_ON_SELF).points;
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

S_CardStats Player::_getEquipmentStats(unsigned int applyOnSelfFlag) const {
	S_CardStats stats;
	stats.points = 0;
	stats.healthPoints = 0;
	stats.maxHealthPoints = 0;
	stats.firePoints = 0;
	applyOnSelfFlag &= FLAG_APPLY_ON_SELF;
	for (int c = 0; c < SIZE_EQUIPMENT; ++c) {
		auto card = m_equipment.getCard(c);
		if (card != nullptr && card->hasFlags(applyOnSelfFlag)) {
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

void Player::setInventoryItem(int index, std::shared_ptr<ObjectCard> card) {
	m_inventory.setCard(index, card);
}

void Player::addItemToInventory(std::shared_ptr<ObjectCard> card) {
	m_inventory.addCard(card);
}

void Player::removeInventoryCard(std::shared_ptr<ObjectCard> card) {
	m_inventory.removeCard(card);
}

std::shared_ptr<ObjectCard> Player::getInventoryItem(int index) const {
	return m_inventory.getCard(index);
}

void Player::equip(std::shared_ptr<ObjectCard> card) {
	applyCardStats(card);
	// If there was a previously equipped card boosting the player's max HP,
	// make sure the current HP are still <= max HP
	if (getHealth() > getMaxHealth()) {
		setHealth(getMaxHealth());
	}
	m_equipment.equip(card);
}

Equipment &Player::getEquipment() {
	return m_equipment;
}

void Player::applyCardStats(std::shared_ptr<ObjectCard> card) {
	// The player's health depends on the max health, so if the player equips a
	// piece of equipment altering the max health and if the health is full,
	// adapt it to the max health
	int cardMaxHealthStat = card->getStats().maxHealthPoints;
	int cardHealthStat = card->getStats().healthPoints;
	int currPlayerMaxHealth = getMaxHealth();
	if (cardMaxHealthStat != 0 && getHealth() == getMaxHealth()) {
		setHealth(currPlayerMaxHealth + cardMaxHealthStat);
	}

	if (cardHealthStat != 0) {
		setHealth(getHealth() + cardHealthStat);
		if (getHealth() > getMaxHealth()) {
			setHealth(getMaxHealth());
		}
	}
}

FloorDirection Player::getDirection() const {
	return m_floorDirection;
}

void Player::toNextFloor() {
	if (m_floorDirection == FLOOR_DOWN) {
		getFloor().toNextLevel();
	}
	else {
		getFloor().toPreviousLevel();
	}
}
