#ifndef __FLOOR_CARD__
#define __FLOOR_CARD__

#include "Card.hpp"
#include "Floor.hpp"

const char FLOOR_CARD_ID[MAX_CHAR_CARD_ID] = "FLOOR";

class FloorCard : public Card {
	public:
	FloorCard(FloorDirection direction);
	void create();
	const char* getName() const { return ""; }
	const char* getID() const { return FLOOR_CARD_ID; }
};

#endif
