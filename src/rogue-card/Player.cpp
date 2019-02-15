#include "Player.hpp"

int Player::getHealth() const { return m_iHealth; }
int Player::getMaxHealth() const { return m_iMaxHealth; }
int Player::getStrength() const { return m_iStrength; }
int Player::getDefence() const { return m_iDefence; }
short Player::getInventorySize() const { return m_iInventorySize; }
int Player::getFloor() const { return m_iFloor; }
long Player::getGold() const { return m_iGold; }

void Player::setHealth(int health) { m_iHealth = health;}
void Player::setMaxHealth(int maxHealth) { m_iMaxHealth = maxHealth;}
void Player::setStrength(int strength) { m_iStrength = strength;}
void Player::setDefence(int defence) { m_iDefence = defence;}
void Player::setInventory(/*ObjectCard *inventory,*/ char size) { m_iInventorySize = size;}
void Player::setFloor(int floorLevel) { m_iFloor = floorLevel;}
void Player::setGold(long gold) { m_iGold = gold;}
