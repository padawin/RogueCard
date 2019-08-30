#ifndef __CARD_DECK__
#define __CARD_DECK___

#include <memory>
#include "Card.hpp"
#include "Player.hpp"
#include "FloorCard.hpp"

class CardDeck {
	private:
	std::shared_ptr<Card> _createCard(
		Player &player,
		std::vector<S_FloorContent> &floorCards,
		std::vector<S_FloorContent> &extraCards
	) const;
	int _getProbaCardMax(
		std::vector<S_FloorContent> &floorCards,
		std::vector<S_FloorContent> &extraCards
	) const;
	std::vector<S_FloorContent> _getExtraCards(Player &player) const;

	public:
	std::shared_ptr<Card> pickCard(Player &player);
	std::shared_ptr<FloorCard> createFloorCard(FloorDirection floorDirection) const;
};

#endif
