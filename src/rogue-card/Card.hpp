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

enum E_CardType : short {ObjectCardType, FloorCardType, EnemyCardType, None};

class Card {
	protected:
	E_CardType m_type;
	std::string m_sImage = "";

	public:
	Card(E_CardType type);
	void render(SDL_Renderer *renderer, int x, int y);
};

#endif
