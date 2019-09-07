#ifndef __SAVE__
#define __SAVE__

#include "../game/AbstractSave.hpp"
#include "Player.hpp"

class Save : public AbstractSave {
	private:
	Player &m_player;
	std::map<int, std::vector<std::pair<E_CardType, std::string>>> m_mUniqueCardsFound = {};

	void _loadPlayer();
	void _setPlayerInitialCards();
	void _savePlayer();

	public:
	Save(Player &player);
	static bool exists();
	void load();
	void create();
	void save();

	void addUniqueCardPicked(int floorLevel, E_CardType cardType, std::string cardID);
	std::vector<std::pair<E_CardType, std::string>> getFoundCards(int level);
};

#endif
