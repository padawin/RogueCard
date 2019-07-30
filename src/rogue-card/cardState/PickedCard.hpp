#ifndef __PICKED_CARD_STATE__
#define __PICKED_CARD_STATE__

#include "../CardState.hpp"

class PickedCardState : public CardState {
	public:
	PickedCardState();
	std::string getStateID() const;
	void update(StateMachine<CardState> &stateMachine);
	void render(SDL_Renderer *renderer, Card &card, int x, int y);
};

#endif
