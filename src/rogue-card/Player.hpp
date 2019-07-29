#ifndef __PLAYER__
#define __PLAYER__

#include <memory>
#include "Health.hpp"
#include "ObjectCard.hpp"
#include "Floor.hpp"
#include "Levelling.hpp"
#include "Equipment.hpp"
#include "ObjectCardCollection.hpp"

class EnemyCard;

class Player {
	private:
	Equipment m_equipment;
	ObjectCardCollection m_inventory;
	Floor m_floor;
	Levelling m_levelling;
	Health m_health;
	int m_iEquipmentMaxHealth = 0;
	long m_iGold = 0;

	bool m_bFighting = false;
	bool m_bFoundFinalGoal = false;
	bool m_bFoundFloorCard = false;

	public:
	Player();
	~Player() {}
	int getHealth() const;
	int getMaxHealth() const;
	short getInventorySize() const;
	Floor &getFloor();
	long getGold() const;
	Levelling &getLevelling();
	void setHealth(int health);
	void setMaxHealth(int maxHealth);
	void setGold(long gold);
	void setLevel(int level);

	int getDefence();
	void setDamages(int damages);
	void getXPAttack(std::shared_ptr<ObjectCard> weapon, int xp[NB_XP_SKILLS]);
	void getXPDefence(int xp[NB_XP_SKILLS]);

	bool isDead() const;
	bool isFighting() const;

	void setFighting(bool fighting);

	S_CardStats getEquipmentStats(bool applyOnSelf);
	ElementalEffects getElementalEffects(bool applyOnSelf);

	ObjectCardCollection &getInventory();
	bool hasSpaceInInventory() const;
	void setInventoryItem(int index, std::shared_ptr<ObjectCard> card);
	bool addItemToInventory(std::shared_ptr<ObjectCard> card);
	void removeInventoryCard(std::shared_ptr<ObjectCard> card);
	std::shared_ptr<ObjectCard> getInventoryItem(int index) const;

	void toggleEquip(std::shared_ptr<ObjectCard> card);
	Equipment &getEquipment();

	void applyCardStats(std::shared_ptr<ObjectCard> card);

	FloorDirection getDirection() const;
	void toNextFloor();

	void setFoundFinalGoal();
	void setFoundFloorCard(bool found);
	bool foundFinalGoal() const;
	bool foundFloorCard() const;
};

#endif
