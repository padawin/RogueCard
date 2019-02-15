#ifndef __SAVE__
#define __SAVE__

#include "../game/AbstractSave.hpp"
#include "Player.hpp"

class Save : public AbstractSave {
	private:
	Player &m_player;

	void _loadPlayer();
	void _setPlayerInitialCards();
	void _savePlayer();

	public:
	Save(Player &playe);
	bool exists();
	void load();
	void create();
};

#endif
