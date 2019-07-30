#ifndef __FINAL_GOAL_CARD__
#define __FINAL_GOAL_CARD__

#include "Card.hpp"

class FinalGoalCard : public Card {
	public:
	FinalGoalCard();
	void create();
	const char* getName() const { return ""; }
};

#endif
