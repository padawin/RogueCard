#ifndef __GAME_TYPES__
#define __GAME_TYPES__

struct S_Coordinates {
	int x = -1;
	int y = -1;
	S_Coordinates() : x(0), y(0) {}
	S_Coordinates(int newX, int newY) : x(newX), y(newY) {}
};

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
