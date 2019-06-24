#ifndef __PLAYER__
#define __PLAYER__

#include <memory>
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
	int m_iHealth = 30;
	int m_iMaxHealth = 30;
	int m_iEquipmentMaxHealth = 0;
	int m_iStrength = 3;
	int m_iDefence = 1;
	long m_iGold = 0;

	bool m_bFighting = false;
	bool m_bFoundFinalGoal = false;
	bool m_bFoundFloorCard = false;

	S_CardStats _getEquipmentStats(bool applyOnSelf);

	int _calculateElementalDamages(ElementalEffects effects);

	public:
	Player();
	~Player() {}
	int getHealth() const;
	int getMaxHealth() const;
	int getStrength() const;
	int getDefence() const;
	short getInventorySize() const;
	Floor &getFloor();
	long getGold() const;
	Levelling &getLevelling();
	void setHealth(int health);
	void setMaxHealth(int maxHealth);
	void setStrength(int strength);
	void setDefence(int defence);
	void setGold(long gold);
	void setLevel(int level);

	int setDamages(int physicalDamages, ElementalEffects elementalEffects);
	int attack(std::shared_ptr<EnemyCard> card, std::shared_ptr<ObjectCard> attackCard);
	void getXPAttack(std::shared_ptr<ObjectCard> weapon, int xp[NB_XP_SKILLS]);
	void getXPDefence(int xp[NB_XP_SKILLS]);

	bool isDead() const;
	bool isFighting() const;

	void setFighting(bool fighting);

	ElementalEffects getElementalEffects(bool applyOnSelf);

	ObjectCardCollection &getInventory();
	bool hasSpaceInInventory() const;
	void setInventoryItem(int index, std::shared_ptr<ObjectCard> card);
	bool addItemToInventory(std::shared_ptr<ObjectCard> card);
	void removeInventoryCard(std::shared_ptr<ObjectCard> card);
	std::shared_ptr<ObjectCard> getInventoryItem(int index) const;

	void equip(std::shared_ptr<ObjectCard> card);
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
