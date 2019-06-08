#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "../common/types.hpp"
#include "ResourceManager.hpp"

std::string cleanFileInPath(std::string path);
void writeTilesetMapping(std::ofstream &fileOutStream, S_TilesetMapping tile);
void writeEnemy(std::ofstream &fileOutStream, S_EnemyMeta enemy);
void writeObject(std::ofstream &fileOutStream, S_ObjectMeta object);
void writeFontAtlas(std::ofstream &fileOutStream, S_FontAtlasCoord object);
void writeFloorContent(std::ofstream &fileOutStream, S_FloorContent floorContent);

template <typename T>
bool decompileFile(
	ResourceManager<T> *resourceManager,
	void (callback)(std::ofstream&, T),
	std::string fileIn,
	std::string fileOut
);

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

	bool ret;
	if (type == "tilesets") {
		ret = decompileFile(new ResourceManager<S_TilesetMapping>(), writeTilesetMapping, fileIn, fileOut);
	}
	else if (type == "enemies") {
		ret = decompileFile(new ResourceManager<S_EnemyMeta>(), writeEnemy, fileIn, fileOut);
	}
	else if (type == "objects") {
		ret = decompileFile(new ResourceManager<S_ObjectMeta>(), writeObject, fileIn, fileOut);
	}
	else if (type == "font-atlas") {
		ret = decompileFile(new ResourceManager<S_FontAtlasCoord>(), writeFontAtlas, fileIn, fileOut);
	}
	else if (type == "floor-content") {
		ret = decompileFile(new ResourceManager<S_FloorContent>(), writeFloorContent, fileIn, fileOut);
	}
	else {
		std::cerr << "Invalid type: " << type << "\n";
		return 2;
	}

	return ret ? 0 : 1;
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

void writeTilesetMapping(std::ofstream &fileOutStream, S_TilesetMapping tile) {
	fileOutStream << tile.tileset << " " << tile.filePath << "\n";
}

void writeEnemy(std::ofstream &fileOutStream, S_EnemyMeta enemy) {
	fileOutStream << "\"" << enemy.name << "\" "
		<< enemy.tilesetX << " "
		<< enemy.tilesetY << " "
		<< enemy.health << " "
		<< enemy.strength << " "
		<< enemy.defence << " "
		<< enemy.elementalDamages.getStat(ELEMENT_FIRE) << " "
		<< enemy.elementalResistance.getStat(ELEMENT_FIRE) << " "
		<< enemy.dropRate << " "
		<< enemy.minItems << " "
		<< enemy.maxItems << "\n";
}

void writeObject(std::ofstream &fileOutStream, S_ObjectMeta object) {
	fileOutStream << "\"" << object.name << "\" "
		<< object.tilesetX << " "
		<< object.tilesetY << " "
		<< object.usable << " "
		<< object.consumable << " "
		<< object.applyOnSelf << " "
		<< object.isHelm << " "
		<< object.isShoulders << " "
		<< object.isGlove << " "
		<< object.isChest << " "
		<< object.isBelt << " "
		<< object.isShoe << " "
		<< object.isWeapon << " "
		<< object.isShield << " "
		<< object.stats.points << " "
		<< object.stats.healthPoints << " "
		<< object.stats.maxHealthPoints << " "
		<< object.elementalEffects.getStat(ELEMENT_FIRE) << " "
		<< object.stats.xpSkill << " "
		<< object.stats.xp << "\n";
}

void writeFontAtlas(std::ofstream &fileOutStream, S_FontAtlasCoord object) {
	fileOutStream << object.x << " "
		<< object.y << " "
		<< object.w << " "
		<< object.h << "\n";
}

void writeFloorContent(std::ofstream &fileOutStream, S_FloorContent floorContent) {
	char type;
	if (floorContent.type == EnemyCardType) {
		type = 'e';
	}
	else if (floorContent.type == ObjectCardType) {
		type = 'o';
	}
	else {
		type = '?';
	}
	fileOutStream << floorContent.floorLevel << " "
		<< type << " "
		<< "\"" << floorContent.id << "\" "
		<< (int) floorContent.probability << "\n";
}

template <typename T>
bool decompileFile(
	ResourceManager<T> *resourceManager,
	void (callback)(std::ofstream&, T),
	std::string fileIn,
	std::string fileOut
) {
	resourceManager->setResourceFile(fileIn);
	resourceManager->parseBinaryFile();
	bool ret = resourceManager->saveReadableFile(fileOut, callback);
	delete resourceManager;
	return ret;
}
