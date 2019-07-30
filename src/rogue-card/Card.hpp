#ifndef __CARD__
#define __CARD__

#define CARD_WIDTH 48
#define CARD_HEIGHT 64
#define CARD_IMAGE_WIDTH 32
#define CARD_IMAGE_HEIGHT 32
#define CARD_IMAGE_POSITION_X 8
#define CARD_IMAGE_POSITION_Y 16

#include <string>
#include <SDL2/SDL.h>

#include "../common/types.hpp"
#include "../game/StateMachine.hpp"
#include "CardState.hpp"

class Card {
	protected:
	E_CardType m_type;
	std::string m_sImage = "";
	int m_iTileX = 0;
	int m_iTileY = 0;
	StateMachine<CardState> m_stateMachine = StateMachine<CardState>();

	public:
	virtual ~Card() {}
	Card(E_CardType type);
	E_CardType getType() const;
	void setState(CardState* state);
	virtual void create() = 0;
	virtual const char* getName() const = 0;
	void update();
	void render(SDL_Renderer *renderer, int x, int y);

	int getX(int defaultX) const;
	int getY(int defaultY) const;
};

#endif
