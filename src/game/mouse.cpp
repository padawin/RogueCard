#include "mouse.hpp"

int lastX = 0;
int lastY = 0;

void mouse_setX(int x) {
	lastX = x;
}

void mouse_setY(int y) {
	lastY = y;
}

int mouse_getX() {
	return lastX;
}

int mouse_getY() {
	return lastY;
}
