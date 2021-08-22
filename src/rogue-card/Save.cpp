#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include "game/utils.hpp"
#include "Save.hpp"

const char* PLAYER_FILE = "player.dat";

Save::Save(Player &player) : m_player(player) {}

bool Save::exists() {
	struct stat st;
	std::string playerPath = utils_getDataPath() + "/" + PLAYER_FILE;
	return stat(playerPath.c_str(), &st) != -1;
}

void Save::load() {
	_loadPlayer();
}

void Save::_loadPlayer() {
	std::ifstream fin;
	std::string playerPath = utils_getDataPath() + "/" + PLAYER_FILE;
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
		else if (type == 'H') {
			int maxHealth = 0;
			sscanf(line, "H %d\n", &maxHealth);
			m_player.setMaxHealth(maxHealth);
		}
		else if (type == 'f') {
			int floorLevel = 0;
			sscanf(line, "f %d\n", &floorLevel);
			m_player.getFloor().setLevel(floorLevel);
		}
		else if (type == 'g') {
			long gold = 0;
			sscanf(line, "g %ld\n", &gold);
			m_player.setGold(gold);
		}
		else if (type == 'l') {
			int level = 1;
			sscanf(line, "l %d\n", &level);
			m_player.setLevel(level);
		}
		else if (type == 'L') {
			int steps = 0;
			sscanf(line, "L %d\n", &steps);
			m_player.getLevelling().setStepsBeforeLevelUp(steps);
		}
		else if (type == 'V') {
			int foundFinalGoal;
			sscanf(line, "V %d\n", &foundFinalGoal);
			if (foundFinalGoal == 1) {
				m_player.setFoundFinalGoal();
			}
		}
		else if (type == 'i') {
			int inventoryIndex;
			int cardQuantity;
			char metaID[MAX_CHAR_CARD_ID];
			sscanf(
				line,
				"i %d %s %d\n",
				&inventoryIndex, metaID, &cardQuantity
			);
			std::shared_ptr<ObjectCard> card = std::shared_ptr<ObjectCard>(new ObjectCard(metaID));
			card->create();
			card->setQuantity(cardQuantity);
			m_player.setInventoryItem(inventoryIndex, card);
		}
		else if (type == 'a') {
			int actionBarIndex;
			int cardIndex;
			sscanf(
				line,
				"a %d %d\n",
				&actionBarIndex, &cardIndex
			);
			m_player.getActionBar().setCard(
				actionBarIndex, m_player.getInventoryItem(cardIndex)
			);
		}
		else if (type == 'e') {
			int cardIndex;
			sscanf(line, "e %d\n", &cardIndex);
			m_player.getEquipment().equip(m_player.getInventoryItem(cardIndex));
		}
		else if (type == 'x') {
			int skill, xp;
			sscanf(line, "x %d %d\n", &skill, &xp);
			if (skill < NB_XP_SKILLS) {
				m_player.getLevelling().increaseSkillXP((E_XPSkill) skill, xp);
			}
		}
		else if (type == 'u') {
			int floor, cardType;
			char cardID[MAX_CHAR_CARD_ID];
			sscanf(line, "u %d %d %s\n", &floor, &cardType, cardID);
			addUniqueCardPicked(floor, (E_CardType) cardType, cardID);
		}
	}

	fin.close();
}

void Save::create() {
	utils_createFolder(utils_getDataPath().c_str());
	_setPlayerInitialCards();
	_savePlayer();
}

void Save::save() {
	_savePlayer();
}

void Save::_setPlayerInitialCards() {
}

void Save::_savePlayer() {
	std::string playerPath = utils_getDataPath() + "/" + PLAYER_FILE;
	FILE *playerFile = fopen(playerPath.c_str(), "w");
	fprintf(playerFile, "h %d\n", m_player.getHealth());
	fprintf(playerFile, "H %d\n", m_player.getMaxHealth());
	fprintf(playerFile, "f %d\n", m_player.getFloor().getLevel());
	fprintf(playerFile, "g %ld\n", m_player.getGold());
	fprintf(playerFile, "l %d\n", m_player.getLevelling().getLevel());
	fprintf(playerFile, "L %d\n", m_player.getLevelling().getStepsBeforeLevelUp());
	fprintf(playerFile, "V %d\n", m_player.foundFinalGoal());
	m_player.getInventory().reset();
	do {
		auto card = m_player.getInventory().current();
		if (card != nullptr) {
			fprintf(
				playerFile,
				"i %d %s %d\n",
				m_player.getInventory().getCurrentIndex(),
				card->getID(),
				card->getQuantity()
			);
		}
	} while (m_player.getInventory().next());
	// Action bar and Equipments must be saved after the inventory as it
	// references the inventory indexes
	m_player.getActionBar().reset();
	do {
		auto card = m_player.getActionBar().current();
		if (card != nullptr) {
			fprintf(
				playerFile,
				"a %d %d\n",
				m_player.getActionBar().getCurrentIndex(),
				m_player.getInventory().getCardIndex(card)
			);
		}
	} while (m_player.getActionBar().next());
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

	// Save unique cards found
	for (auto floorLevelCards : m_mUniqueCardsFound) {
		int floor = floorLevelCards.first;
		for (auto card : floorLevelCards.second) {
			fprintf(
				playerFile,
				"u %d %d %s\n",
				floor,
				card.first,
				card.second.c_str()
			);
		}
	}
	fclose(playerFile);
}

void Save::addUniqueCardPicked(int floorLevel, E_CardType cardType, std::string cardID) {
	if (m_mUniqueCardsFound.find(floorLevel) == m_mUniqueCardsFound.end()) {
		m_mUniqueCardsFound[floorLevel] = {};
	}
	m_mUniqueCardsFound[floorLevel].push_back(std::make_pair(cardType, cardID));
}

std::vector<std::pair<E_CardType, std::string>> Save::getFoundCards(int level) {
	if (m_mUniqueCardsFound.find(level) == m_mUniqueCardsFound.end()) {
		return {};
	}
	return m_mUniqueCardsFound[level];
}
