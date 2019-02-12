#include <SDL2/SDL.h>
#include "../Game.hpp"
#include "../globals.hpp"
#include "../ResourceManager.hpp"
#include "scene/Play.hpp"
#include "types.hpp"
#include <iostream>
#include <memory> // shared_ptr
#include <libgen.h> // dirname
#include "sdl2/InputHandler.hpp"
#include "sdl2/Renderer.hpp"

void _prepareTilesets(std::string binaryPath, std::shared_ptr<SDL2Renderer> renderer);

int main(int argc, char* args[]) {
	setlocale(LC_ALL,"");
	time_t t;
	srand((unsigned int) time(&t));
	std::shared_ptr<SDL2Renderer> renderer(new SDL2Renderer());
	renderer->setWindowInfo("rRpg", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	std::shared_ptr<SDL2InputHandler> inputHandler(new SDL2InputHandler());
	UserActions userActions(inputHandler);
	char binaryPath[PATH_MAX];
	{
		char *res = realpath(dirname(args[argc - argc]), binaryPath);
		if (!res) {
			return 1;
		}
	}

	{
		std::string controlsMapping = std::string(binaryPath) + "/config/playercontrolsmapping.txt";
		int actionsSet = userActions.setActionsFromFile(controlsMapping.c_str());
		if (actionsSet != 0) {
			std::cerr << "An error occured while loading the player controls mapping: " << actionsSet << "\n";
			return actionsSet;
		}
	}

	Player p = Player();
	StateMachine stateMachine = StateMachine();
	stateMachine.pushState(new PlayScene(userActions, p));
	Game g(stateMachine, renderer, inputHandler);
	if (g.init(binaryPath)) {
		g.mainLoop();
	}

	g.shutdown();
	return 0;
}
