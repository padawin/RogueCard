#include "../../Game.hpp"
#include "Renderer.hpp"
#include "TextureManager.hpp"
#include <iostream>

const char FPS = 60;
const int DELAY_TIME = 1000 / FPS;

void SDL2Renderer::setWindowInfo(
	const char* title,
	const int x,
	const int y,
	const int w,
	const int h,
	const bool fullScreen
) {
	m_sTitle = title;
	m_iScreenX = x;
	m_iScreenY = y;
	m_iScreenWidth = w;
	m_iScreenHeight = h;
	m_bFullScreen = fullScreen;
}

bool SDL2Renderer::init(void) {
	bool SDLInitialised = _initSDL(
		m_sTitle.c_str(),
		m_iScreenX,
		m_iScreenY,
		m_iScreenWidth,
		m_iScreenHeight,
		m_bFullScreen
	);
	return SDLInitialised && _loadResources();
}

/**
 * Classic SDL initialisation.
 */
bool SDL2Renderer::_initSDL(
	const char* title,
	const int x,
	const int y,
	const int w,
	const int h,
	const bool fullScreen
) {
	bool ret = true;
	Uint32 flags = 0;

	if (fullScreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL Init failed\n";
		ret = false;
	}
	else {
		// if succeeded create our window
		m_window = SDL_CreateWindow(title, x, y, w, h, flags);
		// if the window creation succeeded create our renderer
		if (m_window == 0) {
			std::cout << "Window creation failed\n";
			ret = false;
		}
		else {
			m_renderer = SDL_CreateRenderer(m_window, -1, 0);
			if (m_renderer == 0) {
				std::cout << "Renderer creation failed\n";
				ret = false;
			}
		}
	}
	std::cout << "SDL initialised\n";
	return ret;
}

void SDL2Renderer::addResource(std::string resourceName, std::string resourcePath) {
	m_vResourceFiles.push_back(std::make_pair(resourceName, resourcePath));
	m_iNbFiles = m_vResourceFiles.size();
}

/**
 * Loads each resource. Returns false if a resource is failed to be loaded (for
 * example if the file does not exist or is not readable).
 */
bool SDL2Renderer::_loadResources() {
	const char errorPattern[] = "An error occured while loading the file %s";

	bool ret = true;
	for (unsigned long i = 0; i < m_iNbFiles; ++i) {
		char* errorMessage = (char*) calloc(
			strlen(errorPattern) + m_vResourceFiles[i].second.length(), sizeof(char)
		);
		std::cout << "Load resource " << m_vResourceFiles[i].second << "\n";
		bool textureLoaded = TextureManager::Instance()->load(
			m_vResourceFiles[i].second,
			m_vResourceFiles[i].first,
			m_renderer
		);

		if (!textureLoaded) {
			sprintf(errorMessage, errorPattern, m_vResourceFiles[i].second.c_str());
			std::cout << errorMessage << "\n";
			std::cout << strerror(errno) << "\n";
			ret = false;
		}
		else {
			std::cout << "Resource " << m_vResourceFiles[i].second << " loaded\n";
		}
		free(errorMessage);
	}

	return ret;
}

/**
 * Clean every resources.
 */
void SDL2Renderer::_cleanResources() {
	std::cout << "Clean resources\n";
	for (unsigned long i = 0; i < m_iNbFiles; ++i) {
		std::cout << "Clean resource " << m_vResourceFiles[i].second << "\n";
		TextureManager::Instance()->clearFromTextureMap(m_vResourceFiles[i].first.c_str());
	}
}

void SDL2Renderer::frame(Game* game) const {
	Uint32 frameStart, frameTime;
	frameStart = SDL_GetTicks();
	// set to black
	// This function expects Red, Green, Blue and
	// Alpha as color values
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	// clear the window to black
	SDL_RenderClear(m_renderer);

	game->frame();

	// show the window
	SDL_RenderPresent(m_renderer);
	// use a delay to cap the fps
	frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < DELAY_TIME) {
		SDL_Delay(DELAY_TIME - frameTime);
	}
}

void SDL2Renderer::shutdown(void) {
	_cleanResources();
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

SDL_Renderer *SDL2Renderer::getRenderer() const {
	return m_renderer;
}
