#ifndef __PLAYER__
#define __PLAYER__

#define MAX_INVENTORY_SIZE 36

#include <memory>
#include "ObjectCard.hpp"
#include "ObjectCardCollection.hpp"

class EnemyCard;

class Player {
	private:
	// Equipment m_equipment;
	ObjectCardCollection m_inventory;
	int m_iHealth = 30;
	int m_iMaxHealth = 30;
	int m_iStrength = 5;
	int m_iDefence = 5;
	int m_iFloor = 0;
	long m_iGold = 0;
	int m_iLevel = 1;

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
	int attack(std::shared_ptr<EnemyCard> card) const;

	bool isDead() const;

	bool hasSpaceInInventory() const;
	void setInventoryItem(unsigned int index, std::shared_ptr<ObjectCard> card);
	void addItemToInventory(std::shared_ptr<ObjectCard> card);
	void removeInventoryItem(unsigned int index);
	std::shared_ptr<ObjectCard> getInventoryItem(unsigned int index) const;
};

#endif
