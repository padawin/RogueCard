#include <SDL2/SDL.h>
#include "../common/types.hpp"
#include "../game/Game.hpp"
#include "../game/globals.hpp"
#include "../sdl2/InputHandler.hpp"
#include "../sdl2/Renderer.hpp"
#include "EnemyCard.hpp"
#include "ResourceManager.hpp"
#include "scene/Play.hpp"
#include <iostream>
#include <memory> // shared_ptr
#include <libgen.h> // dirname

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

	if (!EnemyCard::prepareMeta(std::string(binaryPath) + "/../resources/enemies.dat")) {
		std::cerr << "An error occurred while loading the enemies meta\n";
		return 1;
	}

	Player p = Player();
	StateMachine stateMachine = StateMachine();
	stateMachine.pushState(new PlayScene(userActions, p, renderer));
	Game g(stateMachine, renderer, inputHandler);
	_prepareTilesets(binaryPath, renderer);
	if (g.init(binaryPath)) {
		g.mainLoop();
	}

	g.shutdown();
	return 0;
}


void _prepareTilesets(std::string binaryPath, std::shared_ptr<SDL2Renderer> renderer) {
	ResourceManager<S_TilesetMapping> resourceManager;
	if (!resourceManager.setResourceFile(binaryPath + "/../resources/tilesets.dat")) {
		std::cout << "Error parsing the tilesets resource file\n";
		return;
	}

	resourceManager.parseBinaryFile();
	for (auto tileset : resourceManager.getParsedResources()) {
		std::cout << "Resource found: "
			<< tileset.second.tileset
			<< " (" << tileset.second.filePath << ")\n";
		renderer->addResource(
			tileset.second.tileset,
			binaryPath + "/../resources/" + tileset.second.filePath
		);
	}
}
