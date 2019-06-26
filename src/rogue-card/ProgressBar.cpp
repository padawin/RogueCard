#include "ProgressBar.hpp"
#include "../sdl2/TextureManager.hpp"

const int PROGRESS_BACK_WIDTH = 144;
const int PROGRESS_BACK_HEIGHT = 16;
const int PROGRESS_MAX_WIDTH = 138;
const int PROGRESS_HEIGHT = 10;
const int PROGRESS_PADDING_X = 4;
const int PROGRESS_PADDING_Y = 2;

void ProgressBar::setProgress(int progress) {
	m_iProgress = progress;
}

void ProgressBar::render(std::shared_ptr<SDL2Renderer> renderer, int x, int y) const {
	int width = m_iProgress * PROGRESS_MAX_WIDTH / 100;
	TextureManager::Instance()->draw(
		"progress-back",
		x,
		y,
		PROGRESS_BACK_WIDTH,
		PROGRESS_BACK_HEIGHT,
		renderer->getRenderer()
	);
	TextureManager::Instance()->draw(
		"progress-red",
		x + PROGRESS_PADDING_X,
		y + PROGRESS_PADDING_Y,
		width,
		PROGRESS_HEIGHT,
		renderer->getRenderer()
	);
}
