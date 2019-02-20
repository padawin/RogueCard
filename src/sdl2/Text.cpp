#include <iostream>
#include "../game/globals.hpp"
#include "../common/types.hpp"
#include "TextureManager.hpp"
#include "Text.hpp"

ResourceManager<S_FontAtlasCoord> Text::m_fontAtlas = ResourceManager<S_FontAtlasCoord>();

bool Text::hasText() const {
	return m_sText != "";
}

void Text::setText(std::string text) {
	m_sText = text;
}

int Text::getLength() const {
	std::map<int, S_FontAtlasCoord> &meta = m_fontAtlas.getParsedResources();
	int charSize = meta[0].w;
	return (int) m_sText.size() * charSize;
}

int Text::getFontHeight() const {
	std::map<int, S_FontAtlasCoord> &meta = m_fontAtlas.getParsedResources();
	return meta[0].h;
}

std::string Text::getText() const {
	return m_sText;
}

void Text::render(SDL_Renderer* renderer, int x, int y) const {
	if (!hasText()) {
		return;
	}
	TextureManager* textureManager = TextureManager::Instance();
	std::map<int, S_FontAtlasCoord> &meta = m_fontAtlas.getParsedResources();
	S_FontAtlasCoord character;
	int charPosX = x;
	int charPosY = y;
	for (long unsigned c = 0; c < m_sText.size(); ++c) {
		// 32 is the first displayable ascii char (space)
		if (meta.find(m_sText[c] - 32) != meta.end()) {
			character = meta[m_sText[c] - 32];
		}
		else {
			character = meta[0];
		}
		if (m_sText[c] == '\n') {
			charPosX = x;
			charPosY += character.h;
			continue;
		}
		textureManager->drawFrame(
			"font",
			charPosX,
			charPosY,
			character.w,
			character.h,
			character.x,
			character.y,
			renderer
		);
		charPosX += character.w;
	}
}

bool Text::prepareMeta(std::string file) {
	if (!m_fontAtlas.setResourceFile(file)) {
		return false;
	}
	m_fontAtlas.parseBinaryFile();
	return true;
}
