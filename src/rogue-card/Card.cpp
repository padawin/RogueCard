#include "Card.hpp"
#include "../sdl2/TextureManager.hpp"

Card::Card(E_CardType type) : m_type(type) {

}

E_CardType Card::getType() const {
	return m_type;
}

void Card::render(SDL_Renderer *renderer, int x, int y) {
	TextureManager::Instance()->drawImage(
		"card", renderer, x, y, CARD_WIDTH, CARD_HEIGHT
	);
	TextureManager::Instance()->drawFrame(
		m_sImage,
		x + CARD_IMAGE_POSITION_X,
		y + CARD_IMAGE_POSITION_Y,
		CARD_IMAGE_WIDTH,
		CARD_IMAGE_HEIGHT,
		// @TODO Change this temporary coordinate
		0,
		0,
		renderer
	);
}
