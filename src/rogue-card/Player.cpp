#include "Player.hpp"
#include "EnemyCard.hpp"

Player::Player() :
	m_equipment(Equipment()),
	m_inventory(ObjectCardCollection()),
	m_actionBar(ActionBar()),
	m_floor(Floor()),
	m_levelling(Levelling()),
	m_health(30, 30)
{}

int Player::getHealth() const { return m_health.getCurrent(); }
int Player::getMaxHealth() const {
	return m_health.getMax() + m_iEquipmentMaxHealth;
}
Floor &Player::getFloor() { return m_floor; }
long Player::getGold() const { return m_iGold; }

Levelling &Player::getLevelling() { return m_levelling; }

void Player::setHealth(int health) { m_health.setCurrent(health);}
void Player::setMaxHealth(int maxHealth) { m_health.setMax(maxHealth);}

void Player::setGold(long gold) { m_iGold = gold;}
void Player::setLevel(int level) { m_levelling.setLevel(level); }

void Player::setDamages(int damages) {
	m_health -= damages;
}

int Player::getDefence() {
	return getEquipmentStats(true).points;
}

void Player::getXPAttack(std::shared_ptr<ObjectCard> weapon, int xp[NB_XP_SKILLS]) {
	if (weapon == nullptr) {
		weapon = m_equipment.getCardWithFlag(FLAG_EQUIPMENT_WEAPON);
	}

	if (weapon != nullptr) {
		E_XPSkill skill = weapon->getStats().xpSkill;
		int points = weapon->getStats().xp;
		xp[skill] += points;
	}
}

void Player::getXPDefence(int xp[NB_XP_SKILLS]) {
	m_equipment.reset();
	do {
		auto card = m_equipment.current();
		if (card != nullptr
			&& card->hasEquipableFlag(FLAG_EQUIPMENT_ARMOR)
			&& !card->hasEquipableFlag(FLAG_EQUIPMENT_WEAPON)
		) {
			E_XPSkill skill = card->getStats().xpSkill;
			int points = card->getStats().xp;
			xp[skill] += points;
		}
	} while (m_equipment.next());
}

S_CardStats Player::getEquipmentStats(bool applyOnSelf) {
	S_CardStats stats;
	stats.points = 0;
	stats.healthPoints = 0;
	stats.maxHealthPoints = 0;
	m_equipment.reset();
	do {
		auto card = m_equipment.current();
		if (card != nullptr && applyOnSelf == card->hasFlags(FLAG_APPLY_ON_SELF)) {
			S_CardStats cardStats = card->getStats();
			stats.points += cardStats.points * m_levelling.getSkillLevel(cardStats.xpSkill);
			stats.healthPoints += cardStats.healthPoints;
			stats.maxHealthPoints += cardStats.maxHealthPoints;
		}
	} while (m_equipment.next());
	return stats;
}

ElementalEffects Player::getElementalEffects(bool applyOnSelf) {
	ElementalEffects stats = ElementalEffects();
	m_equipment.reset();
	do {
		auto card = m_equipment.current();
		if (card != nullptr && applyOnSelf == card->hasFlags(FLAG_APPLY_ON_SELF)) {
			stats += card->getElementalEffects();
		}
	} while (m_equipment.next());
	return stats;
}

bool Player::isDead() const {
	return m_health.getCurrent() == 0;
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

bool Player::addItemToInventory(std::shared_ptr<ObjectCard> card) {
	return m_inventory.addCard(card);
}

void Player::removeInventoryCard(std::shared_ptr<ObjectCard> card) {
	m_inventory.removeCard(card);
}

std::shared_ptr<ObjectCard> Player::getInventoryItem(int index) const {
	return m_inventory.getCard(index);
}

void Player::toggleEquip(std::shared_ptr<ObjectCard> card) {
	if (m_equipment.isEquipped(card)) {
		m_equipment.remove(card);
	}
	else {
		m_equipment.equip(card);
	}

	int health = getHealth(),
		newMaxHealth;
	bool isHealthMax = health == getMaxHealth();

	// Update equipment max health bonus
	S_CardStats equipmentStats = getEquipmentStats(FLAG_APPLY_ON_SELF);
	m_iEquipmentMaxHealth = equipmentStats.maxHealthPoints;

	newMaxHealth = getMaxHealth();
	// If there was a previously equipped card boosting the player's max HP,
	// make sure the current HP are still <= max HP
	// Or if the health was at the max, and now an object boosts max health,
	// keep the health at the max still
	if (health > newMaxHealth || (isHealthMax && health < newMaxHealth)) {
		setHealth(newMaxHealth);
	}
}

Equipment &Player::getEquipment() {
	return m_equipment;
}

void Player::applyCardStats(std::shared_ptr<ObjectCard> card) {
	int cardHealth = card->getStats().healthPoints;
	int currentHealth = getHealth();
	int currentMaxHealth = getMaxHealth();
	if (cardHealth != 0) {
		int health = currentHealth + cardHealth;
		setHealth(health);
		if (health > currentMaxHealth) {
			setHealth(currentMaxHealth);
		}
	}
}

void Player::toNextFloor() {
	if (m_bFoundFinalGoal) {
		getFloor().toPreviousLevel();
	}
	else {
		getFloor().toNextLevel();
	}
}

void Player::setFoundFinalGoal() {
	m_bFoundFinalGoal = true;
}

bool Player::foundFinalGoal() const {
	return m_bFoundFinalGoal;
}

ActionBar &Player::getActionBar() {
	return m_actionBar;
}
