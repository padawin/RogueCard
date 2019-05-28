#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "../common/types.hpp"
#include "ResourceManager.hpp"

std::string cleanFileInPath(std::string path);
bool readTilesetFileLine(char line[MAX_CHARS_PER_LINE], S_TilesetMapping &data);
bool readEnemyFileLine(char line[MAX_CHARS_PER_LINE], S_EnemyMeta &data);
bool readObjectFileLine(char line[MAX_CHARS_PER_LINE], S_ObjectMeta &data);
bool readFontFileLine(char line[MAX_CHARS_PER_LINE], S_FontAtlasCoord &data);

int main(int argc, char* argv[]) {
	// expects the following arguments:
	// dataType (tiles),
	// dataFileIn (path to the humanly readable file),
	// dataFileOut (path to the compiled file)

	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " dataType dataFileIn dataFileOut\n";
		return 1;
	}

	std::string type = argv[1],
		fileIn = cleanFileInPath(argv[2]),
		fileOut = argv[3];

	if (type == "tilesets") {
		ResourceManager<S_TilesetMapping> resourceManager;
		bool res = resourceManager.compileFile(fileIn, fileOut, readTilesetFileLine);
		if (!res) {
			return 1;
		}
	}
	else if (type == "enemies") {
		ResourceManager<S_EnemyMeta> resourceManager;
		bool res = resourceManager.compileFile(fileIn, fileOut, readEnemyFileLine);
		if (!res) {
			std::cerr << res << std::endl;
			return 1;
		}
	}
	else if (type == "objects") {
		ResourceManager<S_ObjectMeta> resourceManager;
		bool res = resourceManager.compileFile(fileIn, fileOut, readObjectFileLine);
		if (!res) {
			std::cerr << res << std::endl;
			return 1;
		}
	}
	else if (type == "font-atlas") {
		ResourceManager<S_FontAtlasCoord> resourceManager;
		bool res = resourceManager.compileFile(fileIn, fileOut, readFontFileLine);
		if (!res) {
			std::cerr << res << std::endl;
			return 1;
		}
	}
	else {
		std::cerr << "Invalid type: " << type << "\n";
		return 2;
	}
	return 0;
}

std::string cleanFileInPath(std::string path) {
	if (path[0] == '/') {
		return path;
	}
	else {
		char cwd[1024];
		char* res = getcwd(cwd, sizeof(cwd));
		if (!res) {
			return "./" + path;
		}

		return std::string(cwd) + "/" + path;
	}
}

bool readTilesetFileLine(char line[MAX_CHARS_PER_LINE], S_TilesetMapping &data) {
	int result = sscanf(
		line,
		"%s %s\n",
		data.tileset, data.filePath);
	return result == 2;
}

bool readEnemyFileLine(char line[MAX_CHARS_PER_LINE], S_EnemyMeta &data) {
	int dropRate, minItems, maxItems;
	int fireAttack, fireResistance;
	int result = sscanf(
		line,
		"\"%[^\"]\" \"%[^\"]\" %d %d %d %d %d %d %d %d %d %d\n",
		data.id,
		data.name,
		&data.tilesetX,
		&data.tilesetY,
		&data.health,
		&data.strength,
		&data.defence,
		&fireAttack,
		&fireResistance,
		&dropRate,
		&minItems,
		&maxItems
	);
	data.elementalDamages.setStat(ELEMENT_FIRE, fireAttack);
	data.elementalResistance.setStat(ELEMENT_FIRE, fireResistance);
	data.dropRate = (char) dropRate;
	data.minItems = (char) minItems;
	data.maxItems = (char) maxItems;
	return result == 12;
}

bool readObjectFileLine(char line[MAX_CHARS_PER_LINE], S_ObjectMeta &data) {
	int usable, consumable, applyOnSelf, isHelm, isShoulders, isGlove, isChest,
		isBelt, isShoe, isWeapon, isShield, xpSkill;
	int statFire;
	int result = sscanf(
		line,
		"\"%[^\"]\" \"%[^\"]\" %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		data.id,
		data.name,
		&data.tilesetX,
		&data.tilesetY,
		&usable,
		&consumable,
		&applyOnSelf,
		&isHelm,
		&isShoulders,
		&isGlove,
		&isChest,
		&isBelt,
		&isShoe,
		&isWeapon,
		&isShield,
		&data.stats.points,
		&data.stats.healthPoints,
		&data.stats.maxHealthPoints,
		&statFire,
		&xpSkill,
		&data.stats.xp
	);
	data.elementalEffects.setStat(ELEMENT_FIRE, statFire);
	data.stats.xpSkill = (E_XPSkill) xpSkill;
	data.usable = (bool) usable;
	data.consumable = (bool) consumable;
	data.applyOnSelf = (bool) applyOnSelf;
	data.isHelm = (bool) isHelm;
	data.isShoulders = (bool) isShoulders;
	data.isGlove = (bool) isGlove;
	data.isChest = (bool) isChest;
	data.isBelt = (bool) isBelt;
	data.isShoe = (bool) isShoe;
	data.isWeapon = (bool) isWeapon;
	data.isShield = (bool) isShield;
	return result == 21;
}

bool readFontFileLine(char line[MAX_CHARS_PER_LINE], S_FontAtlasCoord &data) {
	int result = sscanf(
		line,
		"%d %d %d %d\n",
		&data.x, &data.y, &data.w, &data.h
	);
	return result == 4;
}
