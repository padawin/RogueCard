#include "ActionCard.hpp"
#include "../sdl2/TextureManager.hpp"

ActionCard::ActionCard() : Card(ActionCardType) {}

void ActionCard::create() {

}

void ActionCard::renderPick(SDL_Renderer *renderer, int x, int y) {
	Card::render(renderer, x, y);
	TextureManager::Instance()->draw(
		"action-pick", x, y, CARD_WIDTH, CARD_HEIGHT, renderer
	);
}

void ActionCard::renderLoot(SDL_Renderer *renderer, int x, int y) {
	Card::render(renderer, x, y);
}

void ActionCard::renderAttack(SDL_Renderer *renderer, int x, int y, std::shared_ptr<ObjectCard> weapon) {
	if (weapon != nullptr) {
		weapon->render(renderer, x, y);
	}
	else {
		Card::render(renderer, x, y);
	}
}
