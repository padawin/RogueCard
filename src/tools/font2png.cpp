#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sdl2/Surface.hpp"


int main(int argc, char* args[]) {
	if (TTF_Init() == -1) {
		fprintf(stderr, "Failed initialising SDL_ttf\n");
		exit(-1);
	}


	TTF_Font* font = TTF_OpenFont(args[1], 16);
	if (!font) {
		std::cerr << "Failing opening font " << args[1] << ": " << TTF_GetError() << std::endl;
		exit(-1);
	}
	SDL_Color color = {255, 255, 255, 255};
	char letter[2], filePath[11] = "char_#.png";
	letter[1] = '\0';
	for (char c = 32; c < 127; ++c) {
		letter[0] = c;
		Surface surface(TTF_RenderText_Solid(font, letter, color));
		if (!surface.getSDLSurface()) {
			std::cerr << "Failing creating surface\n";
			continue;
		}
		if (c != '/') {
			filePath[4] = '_';
			filePath[5] = c;
		}
		else {
			filePath[4] = '#';
			filePath[5] = '#';
		}
		IMG_SavePNG(surface.getSDLSurface(), filePath);
	}
	TTF_CloseFont(font);
	SDL_Quit();
	return 0;
}
