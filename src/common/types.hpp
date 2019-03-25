#ifndef __TYPES__
#define __TYPES__

#define MAX_LENGTH_TILESET_NAME 32
#define MAX_CHAR_RESOURCE_PATH 255

#define MAX_CHAR_ENEMY_NAME 32
#define MAX_CHAR_OBJECT_NAME 32

struct S_TilesetMapping {
	char tileset[MAX_LENGTH_TILESET_NAME];
	char filePath[MAX_CHAR_RESOURCE_PATH];
};

struct S_CardStats {
	int points; // For damages and armor points
	int healthPoints; // For health recovery
	int maxHealthPoints; // For health boost
	int firePoints; // For fire damage/resistance
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

struct S_ObjectMeta {
	char name[MAX_CHAR_OBJECT_NAME];
	int tilesetX;
	int tilesetY;
	bool usable;
	bool consumable;
	bool applyOnSelf;
	bool isHelm;
	bool isShoulders;
	bool isGlove;
	bool isChest;
	bool isBelt;
	bool isShoe;
	bool isWeapon;
	bool isShield;
	S_CardStats stats;
};

struct S_FontAtlasCoord {
	int x;
	int y;
	int w;
	int h;
};

#endif
