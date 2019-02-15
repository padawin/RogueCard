#ifndef __SDL2_RENDERER__
#define __SDL2_RENDERER__

#include <SDL2/SDL.h>
#include "../game/renderer/Renderer.hpp"

class SDL2Renderer : public Renderer {
	private:
	/**
	 * The game's window
	 */
	SDL_Window* m_window = 0;

	/**
	 * The game's renderer. Used to render graphics in the window
	 */
	SDL_Renderer* m_renderer = 0;

	std::string m_sTitle = "";

	/**
	 * Position of the screen
	 */
	int m_iScreenX = 0;
	int m_iScreenY = 0;

	/**
	 * Dimensions of the screen
	 */
	int m_iScreenWidth = 0;
	int m_iScreenHeight = 0;

	bool m_bFullScreen = false;

	/**
	 * List of files to use as graphic resources, each file is a pair composed
	 * of a resource name and of the file path.
	 */
	std::vector<std::pair<std::string, std::string>> m_vResourceFiles = {};

	/**
	 * Number of resources used by the game
	 */
	unsigned long m_iNbFiles = 0;

	/**
	 * Method to initialise the SDL. It takes in arguments the window's title,
	 * its position and dimensions, and a boolean to create it full screen or
	 * not.
	 */
	bool _initSDL(
		const char* title,
		const int x,
		const int y,
		const int w,
		const int h,
		const bool fullScreen
	);

	/**
	 * Method to load the game's resources.
	 */
	bool _loadResources();

	/**
	 * Method to free the game's resources.
	 */
	void _cleanResources();

	public:
	SDL_Renderer *getRenderer() const;
	void setWindowInfo(
		const char* title,
		const int x,
		const int y,
		const int w,
		const int h,
		const bool fullScreen
	);
	bool init(void);
	void frame(Game* game) const;
	void shutdown(void);

	void addResource(std::string resourceName, std::string resourcePath);
};

#endif
