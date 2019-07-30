#ifndef __CARD_STATE__
#define __CARD_STATE__

#include "../game/State.hpp"
#include "../game/StateMachine.hpp"
#include "../sdl2/Renderer.hpp"

class Card;

class CardState : public State {
	protected:
	int m_iX = 0;
	int m_iY = 0;

	public:
	virtual void update(StateMachine<CardState> &stateMachine);
	virtual void render(SDL_Renderer *renderer, Card &card, int x, int y);
	int getX() const;
	int getY() const;
};

#endif
