#ifndef __CARD_DECK__
#define __CARD_DECK___

#include <memory>
#include "Card.hpp"
#include "Player.hpp"

class CardDeck {
	private:
	bool m_bFoundFinalGoal = false;

	public:
	std::shared_ptr<Card> pickCard(Player &player, bool foundNextFloor);
};

#endif
