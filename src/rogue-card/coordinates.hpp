#ifndef __COORDINATES__
#define __COORDINATES__

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

const S_Coordinates DECK_COORDINATES = {16, 16};
const S_Coordinates PICKED_CARD_COORDINATES = {138, 64};

const S_Coordinates DAMAGES_FROM_PLAYER = {158, 48};
const S_Coordinates DAMAGES_FROM_ENEMY = {66, 128};
const S_Coordinates CRITICAL_FROM_PLAYER = {122, 32};
const S_Coordinates CRITICAL_FROM_ENEMY = {30, 112};

const S_Coordinates HEALTH_POSITION = {16, 144};

#endif
