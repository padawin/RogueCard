#include "ActionCard.hpp"
#include "../game/globals.hpp"
#include "../sdl2/TextureManager.hpp"

const int ARROW_X_POS = (CARD_WIDTH - ARROW_WIDTH) / 2;
const int ARROW_TOP_Y_POS = 2;
const int ARROW_BOTTOM_Y_POS = CARD_HEIGHT - ARROW_HEIGHT - 2;

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
	TextureManager::Instance()->draw(
		"action-loot", x, y, CARD_WIDTH, CARD_HEIGHT, renderer
	);
}

void ActionCard::renderRunaway(SDL_Renderer *renderer, int x, int y) {
	Card::render(renderer, x, y);
	TextureManager::Instance()->draw(
		"action-runaway", x, y, CARD_WIDTH, CARD_HEIGHT, renderer
	);
}

void ActionCard::renderDiscard(SDL_Renderer *renderer, int x, int y) {
	Card::render(renderer, x, y);
	TextureManager::Instance()->draw(
		"action-discard", x, y, CARD_WIDTH, CARD_HEIGHT, renderer
	);
}

void ActionCard::renderAttack(SDL_Renderer *renderer, int x, int y, std::shared_ptr<ObjectCard> weapon) {
	if (weapon != nullptr) {
		weapon->render(renderer, x, y);
	}
	else {
		Card::render(renderer, x, y);
		TextureManager::Instance()->draw(
			"action-attack", x, y, CARD_WIDTH, CARD_HEIGHT, renderer
		);
	}
}

void ActionCard::renderPrevious(SDL_Renderer *renderer, int x, int y) {
	TextureManager::Instance()->drawFrame(
		"arrows",
		x + ARROW_X_POS,
		y + ARROW_TOP_Y_POS,
		ARROW_WIDTH, ARROW_HEIGHT,
		0,
		1,
		renderer
	);
}

void ActionCard::renderNext(SDL_Renderer *renderer, int x, int y) {
	TextureManager::Instance()->drawFrame(
		"arrows",
		x + ARROW_X_POS,
		y + ARROW_BOTTOM_Y_POS,
		ARROW_WIDTH, ARROW_HEIGHT,
		0,
		0,
		renderer
	);
}
