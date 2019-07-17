#ifndef __SAVE__
#define __SAVE__

#include "../game/AbstractSave.hpp"
#include "Player.hpp"
#include "ActionBar.hpp"

class Save : public AbstractSave {
	private:
	Player &m_player;
	ActionBar &m_actionBar;

	void _loadPlayer();
	void _setPlayerInitialCards();
	void _savePlayer();

	public:
	Save(Player &player, ActionBar &actionBar);
	static bool exists();
	void load();
	void create();
	void save();
};

#endif
