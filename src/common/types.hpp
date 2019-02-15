#ifndef __TYPES__
#define __TYPES__

#define MAX_LENGTH_TILESET_NAME 32
#define MAX_CHAR_RESOURCE_PATH 255

#define MAX_CHAR_ENEMY_NAME 32

struct S_TilesetMapping {
	char tileset[MAX_LENGTH_TILESET_NAME];
	char filePath[MAX_CHAR_RESOURCE_PATH];
};

struct S_EnemyMeta {
	char name[MAX_CHAR_ENEMY_NAME];
	int health;
	int strength;
	int defence;
	int tilesetX;
	int tilesetY;
	char dropRate;
	char minItems;
	char maxItems;
};

#endif
