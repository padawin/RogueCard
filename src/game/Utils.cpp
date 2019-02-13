#include "Utils.hpp"
#include <ftw.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "globals.hpp"
#include <sys/stat.h>

int unlinkCb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

std::string Utils::getDataPath() {
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

void Utils::createFolder(const char *path) {
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

int Utils::emptyFolder(const char *path) {
	return nftw(path, unlinkCb, 64, FTW_DEPTH | FTW_PHYS);
}
