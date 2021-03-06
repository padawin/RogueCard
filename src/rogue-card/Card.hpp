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

const unsigned int CARD_FLAG_UNIQUE =  0x1;
const unsigned int CARD_FLAG_SPECIAL = 0x2;

class Card {
	protected:
	E_CardType m_type;
	std::string m_sImage = "";
	int m_iTileX = 0;
	int m_iTileY = 0;
	bool m_bIsUnique = false;
	bool m_bIsSpecial = false;
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
	// To be called by the state
	void _renderCard(SDL_Renderer *renderer, int x, int y) const;

	virtual const char* getID() const = 0;
	int getX(int defaultX) const;
	int getY(int defaultY) const;
	bool ready() const;

	void setFlags(unsigned char flags);
	bool isUnique() const;
};

#endif
