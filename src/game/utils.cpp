#include "globals.hpp"
#include "utils.hpp"
#include <fstream>
#include <ftw.h>
#include <iostream>

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

std::string utils_readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if(!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while(!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

bool utils_isRegularFile(const char *path) {
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode) != 0;
}

int unlinkCb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

std::string utils_getDataPath() {
	char filePath[255];
	std::string ret;

	sprintf(
		filePath,
		"%s/%s",
		getenv("HOME"),
		GAME_DATA_FOLDER
	);

	ret = filePath;
	return ret;
}

void utils_createFolder(const char *path) {
	struct stat st;
	if (stat(path, &st) == -1) {
		if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
			std::cerr << "An error occured while trying to create the folder "
				<< path << "\n";
		}
	}
}

int unlinkCb(
	const char *fpath,
	const struct stat *sb __attribute__((unused)),
	int typeflag __attribute__((unused)),
	struct FTW *ftwbuf __attribute__((unused))
) {
	int rv = remove(fpath);

	if (rv) {
		perror(fpath);
	}

	return rv;
}

int utils_emptyFolder(const char *path) {
	return nftw(path, unlinkCb, 64, FTW_DEPTH | FTW_PHYS);
}

int utils_getFileContent(const char *path, std::string *fileContent) {
	std::ifstream ifs(path);
	std::string content(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
	);
	*fileContent = content;
	return 0;
}

float utils_lerp(const float start, const float end, const float t) {
	return (1 - t) * start + t * end;
}
