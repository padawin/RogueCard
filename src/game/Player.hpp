#ifndef __PLAYER__
#define __PLAYER__

#define MAX_INVENTORY_SIZE 32

class Player {
	private:
	// Equipment m_equipment;
	short m_iInventorySize = 0;
	// ObjectCard[MAX_INVENTORY_SIZE] m_inventory = {};
	int m_iHealth = 0;
	int m_iMaxHealth = 0;
	int m_iStrength = 0;
	int m_iDefence = 0;
	int m_iFloor = 0;
	long m_iGold = 0;

	public:
	int getHealth() const;
	int getMaxHealth() const;
	int getStrength() const;
	int getDefence() const;
	short getInventorySize() const;
	int getFloor() const;
	long getGold() const;
};

#endif
