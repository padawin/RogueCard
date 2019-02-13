#include <sys/stat.h>
#include <fstream>
#include "../Utils.hpp"
#include "Save.hpp"

const char* PLAYER_FILE = "player.dat";

Save::Save(Player &player) : m_player(player) {}

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
			m_player.setFloor(floorLevel);
		}
		if (type == 'g') {
			long gold = 0;
			sscanf(line, "g %ld\n", &gold);
			m_player.setGold(gold);
		}
		if (type == 'i') {
			int inventorySize;
			sscanf(line, "i %d\n", &inventorySize);
			m_player.setInventory(inventorySize && 255);
		}
	}

	fin.close();
	return;
}

void Save::create() {
	Utils::createFolder(Utils::getDataPath().c_str());
	_setPlayerInitialCards();
	_savePlayer();
}

void Save::_setPlayerInitialCards() {
}

void Save::_savePlayer() {
	std::string playerPath = Utils::getDataPath() + "/" + PLAYER_FILE;
	FILE *playerFile = fopen(playerPath.c_str(), "w");
	fprintf(playerFile, "h %d\n", m_player.getHealth());
	fprintf(playerFile, "H %d\n", m_player.getHealth());
	fprintf(playerFile, "s %d\n", m_player.getStrength());
	fprintf(playerFile, "d %d\n", m_player.getDefence());
	fprintf(playerFile, "f %d\n", m_player.getFloor());
	fprintf(playerFile, "g %ld\n", m_player.getGold());
	fprintf(playerFile, "i %d\n", m_player.getInventorySize());
	fclose(playerFile);
}
