#ifndef __PLAYER__
#define __PLAYER__

#include <memory>
#include "ObjectCard.hpp"
#include "Equipment.hpp"
#include "ObjectCardCollection.hpp"

class EnemyCard;

class Player {
	private:
	Equipment m_equipment;
	ObjectCardCollection m_inventory;
	int m_iHealth = 30;
	int m_iMaxHealth = 30;
	int m_iStrength = 5;
	int m_iDefence = 5;
	int m_iFloor = 0;
	long m_iGold = 0;
	int m_iLevel = 1;

	bool m_bFighting = false;

	S_CardStats _getEquipmentStats(unsigned int applyOnSelfFlag) const;

	public:
	Player();
	~Player() {}
	int getHealth() const;
	int getMaxHealth() const;
	int getStrength() const;
	int getDefence() const;
	short getInventorySize() const;
	int getFloor() const;
	long getGold() const;
	int getLevel() const;
	void setHealth(int health);
	void setMaxHealth(int maxHealth);
	void setStrength(int strength);
	void setDefence(int defence);
	void setFloor(int floorLevel);
	void setGold(long gold);
	void setLevel(int level);

	int setDamages(int damages);
	int attack(std::shared_ptr<EnemyCard> card, std::shared_ptr<ObjectCard> attackCard) const;

	bool isDead() const;
	bool isFighting() const;

	void setFighting(bool fighting);

	ObjectCardCollection &getInventory();
	bool hasSpaceInInventory() const;
	void setInventoryItem(int index, std::shared_ptr<ObjectCard> card);
	void addItemToInventory(std::shared_ptr<ObjectCard> card);
	void removeInventoryCard(std::shared_ptr<ObjectCard> card);
	std::shared_ptr<ObjectCard> getInventoryItem(int index) const;

	void equip(std::shared_ptr<ObjectCard> card);
	Equipment &getEquipment();

	void applyCardStats(std::shared_ptr<ObjectCard> card);
};

#endif
