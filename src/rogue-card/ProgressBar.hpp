#ifndef __PROGRESS_BAR__
#define __PROGRESS_BAR__

#include "../sdl2/Renderer.hpp"
#include <memory>

class ProgressBar {
	private:
	int m_iProgress = 0;

	public:
	void setProgress(int progress);
	void render(std::shared_ptr<SDL2Renderer> renderer, int x, int y) const;
};

#endif
