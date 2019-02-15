#ifndef __GAME_TYPES__
#define __GAME_TYPES__

typedef struct {
	int x = -1;
	int y = -1;
} S_Coordinates;

typedef struct {
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	int type = 0;
} S_Rectangle;

enum E_ActorType : short;
enum E_ActorRace : short;
enum E_Behaviours : short;
enum E_Event : short;

#endif
