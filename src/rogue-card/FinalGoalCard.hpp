#ifndef __FINAL_GOAL_CARD__
#define __FINAL_GOAL_CARD__

#include "Card.hpp"

const char FINAL_GOAL_CARD_ID[MAX_CHAR_CARD_ID] = "FINAL_GOAL";

class FinalGoalCard : public Card {
	public:
	FinalGoalCard();
	void create();
	const char* getName() const { return ""; }
	const char* getID() const { return FINAL_GOAL_CARD_ID; }
};

#endif
