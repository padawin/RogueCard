#ifndef __TYPES__
#define __TYPES__

#include <string>

#include "ElementalEffects.hpp"

#define MAX_LENGTH_TILESET_NAME 32
#define MAX_CHAR_RESOURCE_PATH 255

#define MAX_CHAR_CARD_ID 32

#define MAX_CHAR_ENEMY_NAME 32
#define MAX_CHAR_OBJECT_NAME 32

enum E_CardType : short {
	ActionCardType,
	ObjectCardType,
	FloorCardType,
	EnemyCardType,
	FinalGoalCardType,
	None
};

enum E_XPSkill {
	NONE,
	LIGHT_ARMOR,
	MEDIUM_ARMOR,
	HEAVY_ARMOR,
	SWORD,
	SPEARS,
	AXE,
	BLUNT,
	RANGE,
	MAGIC,
	PERCEPTION,
	SPEED,
	NB_XP_SKILLS
};

std::string getSkillLabel(E_XPSkill skill);

struct S_TilesetMapping {
	char tileset[MAX_LENGTH_TILESET_NAME];
	char filePath[MAX_CHAR_RESOURCE_PATH];
};

struct S_CardStats {
	int points = 0; // For damages and armor points
	int healthPoints = 0; // For health recovery
	int maxHealthPoints = 0; // For health boost
	E_XPSkill xpSkill = NONE;
	int xp = 0;
};

struct S_EnemyMeta {
	char id[MAX_CHAR_CARD_ID];
	char name[MAX_CHAR_ENEMY_NAME];
	int health = 0;
	int strength = 0;
	int defence = 0;
	int tilesetX = 0;
	int tilesetY = 0;
	char dropRate = 0;
	char minItems = 0;
	char maxItems = 0;
	ElementalEffects elementalDamages = ElementalEffects();
	ElementalEffects elementalResistance = ElementalEffects();
};

struct S_ObjectMeta {
	char id[MAX_CHAR_CARD_ID];
	char name[MAX_CHAR_OBJECT_NAME];
	int tilesetX = 0;
	int tilesetY = 0;
	bool usable = false;
	bool consumable = false;
	bool applyOnSelf = false;
	bool isHelm = false;
	bool isShoulders = false;
	bool isGlove = false;
	bool isChest = false;
	bool isBelt = false;
	bool isShoe = false;
	bool isWeapon = false;
	bool isShield = false;
	S_CardStats stats = {};
	ElementalEffects elementalEffects = ElementalEffects();
};

struct S_FontAtlasCoord {
	int x;
	int y;
	int w;
	int h;
};

struct S_FloorContent {
	int floorLevel;
	E_CardType type;
	char id[MAX_CHAR_CARD_ID];
	char probability;
};

#endif
