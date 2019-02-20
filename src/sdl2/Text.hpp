#ifndef __SDL2_TEXT__
#define __SDL2_TEXT__

#include <string>
#include <SDL2/SDL_image.h>
#include "ResourceManager.hpp"

class Text {
	static ResourceManager<S_FontAtlasCoord> m_fontAtlas;
	std::string m_sText = "";

	public:
	static bool prepareMeta(std::string file);
	bool hasText() const;
	void setText(std::string text);
	int getLength() const;
	std::string getText() const;
	int getFontHeight() const;
	void render(SDL_Renderer* renderer, int x, int y) const;
};

#endif
