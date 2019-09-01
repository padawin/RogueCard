#ifndef __FLOOR_CARD__
#define __FLOOR_CARD__

#include "Card.hpp"
#include "Floor.hpp"

class FloorCard : public Card {
	public:
	FloorCard(FloorDirection direction);
	void create();
	const char* getName() const { return ""; }
	const char* getID() const { return "FLOOR"; }
};

#endif
