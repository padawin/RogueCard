#ifndef __CARD__
#define __CARD__

#define CARD_WIDTH 48
#define CARD_HEIGHT 64

#include <SDL2/SDL.h>

enum E_CardType : short {ObjectCardType, FloorCardType, EnemyCardType, None};

class Card {
	protected:
	E_CardType m_type;

	public:
	Card(E_CardType type);
	void render(SDL_Renderer *renderer, int x, int y);
};

#endif
