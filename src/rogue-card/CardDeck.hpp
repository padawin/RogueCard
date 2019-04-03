#ifndef __CARD_DECK__
#define __CARD_DECK___

#include <memory>
#include "Card.hpp"
#include "Player.hpp"
#include "FloorCard.hpp"

class CardDeck {
	private:
	bool m_bFoundFinalGoal = false;

	public:
	std::shared_ptr<Card> pickCard(Player &player, bool foundNextFloor);
	std::shared_ptr<FloorCard> createFloorCard(FloorDirection floorDirection) const;
};

#endif
