#ifndef __TYPES__
#define __TYPES__

#define MAX_LENGTH_TILESET_NAME 32
#define MAX_CHAR_RESOURCE_PATH 255

struct S_TilesetMapping {
	char tileset[MAX_LENGTH_TILESET_NAME];
	char filePath[MAX_CHAR_RESOURCE_PATH];
};

#endif
