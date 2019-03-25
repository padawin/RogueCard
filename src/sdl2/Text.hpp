#ifndef __SDL2_TEXT__
#define __SDL2_TEXT__

#include <string>
#include <SDL2/SDL_image.h>
#include "ResourceManager.hpp"
#include "../common/types.hpp"

class Text {
	static ResourceManager<S_FontAtlasCoord> m_fontAtlas;
	std::string m_sText = "";
	std::string m_sFont = "font";

	public:
	void setFont(std::string fontName);
	static bool prepareMeta(std::string file);
	bool hasText() const;
	void setText(std::string text);
	int getLength() const;
	std::string getText() const;
	int getFontHeight() const;
	void render(SDL_Renderer* renderer, const int x, const int y) const;
};

#endif
