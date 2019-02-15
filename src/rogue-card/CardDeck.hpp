#ifndef __CARD_DECK__
#define __CARD___

#include <memory>
#include "Card.hpp"
#include "Player.hpp"

class CardDeck {
	public:
	std::shared_ptr<Card> pickCard(Player &player, bool foundNextFloor);
};

#endif
