#include <sys/stat.h>
#include <fstream>
#include "../game/Utils.hpp"
#include "Save.hpp"

const char* PLAYER_FILE = "player.dat";

Save::Save(Player &player, ActionBar &actionBar) :
	m_player(player),
	m_actionBar(actionBar)
{}

bool Save::exists() {
	struct stat st;
	std::string playerPath = Utils::getDataPath() + "/" + PLAYER_FILE;
	return stat(playerPath.c_str(), &st) != -1;
}

void Save::load() {
	_loadPlayer();
}

void Save::_loadPlayer() {
	std::ifstream fin;
	std::string playerPath = Utils::getDataPath() + "/" + PLAYER_FILE;
	fin.open(playerPath.c_str());
	if (!fin.good()) {
		fin.close();
		return;
	}

	while (!fin.eof()) {
		char line[50];
		fin.getline(line, 50);

		char type = *line;
		if (type == 'h') {
			int health = 0;
			sscanf(line, "h %d\n", &health);
			m_player.setHealth(health);
		}
		if (type == 'H') {
			int maxHealth = 0;
			sscanf(line, "H %d\n", &maxHealth);
			m_player.setMaxHealth(maxHealth);
		}
		if (type == 's') {
			int strength = 0;
			sscanf(line, "s %d\n", &strength);
			m_player.setStrength(strength);
		}
		if (type == 'd') {
			int defence = 0;
			sscanf(line, "d %d\n", &defence);
			m_player.setDefence(defence);
		}
		if (type == 'f') {
			int floorLevel = 0;
			sscanf(line, "f %d\n", &floorLevel);
			m_player.getFloor().setLevel(floorLevel);
		}
		if (type == 'g') {
			long gold = 0;
			sscanf(line, "g %ld\n", &gold);
			m_player.setGold(gold);
		}
		if (type == 'l') {
			int level = 1;
			sscanf(line, "l %d\n", &level);
			m_player.setLevel(level);
		}
		if (type == 'S') {
			int foundFinalGoal;
			sscanf(line, "S %d\n", &foundFinalGoal);
			if (foundFinalGoal == 1) {
				m_player.setFoundFinalGoal();
			}
		}
		if (type == 'i') {
			int inventoryIndex;
			int cardMetaIndex;
			int cardQuantity;
			sscanf(
				line,
				"i %d %d %d\n",
				&inventoryIndex, &cardMetaIndex, &cardQuantity
			);
			if (cardMetaIndex != -1) {
				std::shared_ptr<ObjectCard> card = std::shared_ptr<ObjectCard>(new ObjectCard());
				card->createFromMeta(cardMetaIndex);
				card->setQuantity(cardQuantity);
				m_player.setInventoryItem(inventoryIndex, card);
			}
		}
		if (type == 'a') {
			int actionBarIndex;
			int cardIndex;
			sscanf(
				line,
				"a %d %d\n",
				&actionBarIndex, &cardIndex
			);
			m_actionBar.setCard(
				actionBarIndex, m_player.getInventoryItem(cardIndex)
			);
		}
		if (type == 'e') {
			int cardIndex;
			sscanf(line, "e %d\n", &cardIndex);
			m_player.getEquipment().equip(m_player.getInventoryItem(cardIndex));
		}
		if (type == 'x') {
			int skill, xp;
			sscanf(line, "x %d %d\n", &skill, &xp);
			if (skill < NB_XP_SKILLS) {
				m_player.getLevelling().increaseSkillXP((E_XPSkill) skill, xp);
			}
		}
	}

	fin.close();
}

void Save::create() {
	Utils::createFolder(Utils::getDataPath().c_str());
	_setPlayerInitialCards();
	_savePlayer();
}

void Save::save() {
	_savePlayer();
}

void Save::_setPlayerInitialCards() {
}

void Save::_savePlayer() {
	std::string playerPath = Utils::getDataPath() + "/" + PLAYER_FILE;
	FILE *playerFile = fopen(playerPath.c_str(), "w");
	fprintf(playerFile, "h %d\n", m_player.getHealth());
	fprintf(playerFile, "H %d\n", m_player.getMaxHealth());
	fprintf(playerFile, "s %d\n", m_player.getStrength());
	fprintf(playerFile, "d %d\n", m_player.getDefence());
	fprintf(playerFile, "f %d\n", m_player.getFloor().getLevel());
	fprintf(playerFile, "g %ld\n", m_player.getGold());
	fprintf(playerFile, "l %d\n", m_player.getLevelling().getLevel());
	fprintf(playerFile, "S %d\n", m_player.foundFinalGoal());
	m_player.getInventory().reset();
	do {
		auto card = m_player.getInventory().current();
		if (card != nullptr) {
			fprintf(
				playerFile,
				"i %d %d %d\n",
				m_player.getInventory().getCurrentIndex(),
				card->getMetaIndex(),
				card->getQuantity()
			);
		}
	} while (m_player.getInventory().next());
	// Action bar and Equipments must be saved after the inventory as it
	// references the inventory indexes
	m_actionBar.reset();
	do {
		auto card = m_actionBar.current();
		if (card != nullptr) {
			fprintf(
				playerFile,
				"a %d %d\n",
				m_actionBar.getCurrentIndex(),
				m_player.getInventory().getCardIndex(card)
			);
		}
	} while (m_actionBar.next());
	m_player.getEquipment().reset();
	do {
		auto card = m_player.getEquipment().current();
		if (card != nullptr) {
			fprintf(
				playerFile,
				"e %d\n",
				m_player.getInventory().getCardIndex(card)
			);
		}
	} while (m_player.getEquipment().next());

	// Save levelling
	for (int s = 0; s < NB_XP_SKILLS; ++s) {
		fprintf(
			playerFile,
			"x %d %d\n",
			s,
			m_player.getLevelling().getSkill((E_XPSkill) s)
		);
	}
	fclose(playerFile);
}
