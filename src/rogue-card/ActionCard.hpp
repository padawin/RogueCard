#ifndef __ACTION_CARD__
#define __ACTION_CARD__

#include <memory>
#include "Card.hpp"
#include "ObjectCard.hpp"

class ActionCard : public Card {
	public:
	ActionCard();
	void create();
	void renderPick(SDL_Renderer *renderer, int x, int y);
	void renderLoot(SDL_Renderer *renderer, int x, int y);
	void renderRunaway(SDL_Renderer *renderer, int x, int y);
	void renderDiscard(SDL_Renderer *renderer, int x, int y);
	void renderAttack(SDL_Renderer *renderer, int x, int y, std::shared_ptr<ObjectCard> weapon);
};

#endif
