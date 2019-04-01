#ifndef __FLOOR_CARD__
#define __FLOOR_CARD__

#include "Card.hpp"
#include "Floor.hpp"

class FloorCard : public Card {
	public:
	FloorCard(FloorDirection direction);
	void create();
};

#endif
