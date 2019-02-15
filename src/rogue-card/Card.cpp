#include "Card.hpp"
#include "../sdl2/TextureManager.hpp"

Card::Card(E_CardType type) : m_type(type) {

}

void Card::render(SDL_Renderer *renderer, int x, int y) {
	TextureManager::Instance()->drawImage(
		"card", renderer, x, y, CARD_WIDTH, CARD_HEIGHT
	);
}
