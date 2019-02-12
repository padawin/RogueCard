#include <sys/stat.h>
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
	fprintf(playerFile, "is %d\n", m_player.getInventorySize());
	fclose(playerFile);
}
