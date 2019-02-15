#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "../common/types.hpp"
#include "ResourceManager.hpp"

std::string cleanFileInPath(std::string path);
void writeTilesetMapping(std::ofstream &fileOutStream, S_TilesetMapping tile);
void writeEnemy(std::ofstream &fileOutStream, S_EnemyMeta tile);

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
	fileOutStream << " "
		<< enemy.name << " "
		<< enemy.health << " "
		<< enemy.strength << " "
		<< enemy.defense << " "
		<< enemy.tilesetX << " "
		<< enemy.tilesetY << " "
		<< enemy.dropRate << " "
		<< enemy.minItems << " "
		<< enemy.maxItems << "\n";
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
