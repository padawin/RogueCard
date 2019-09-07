#ifndef __CARD_DECK__
#define __CARD_DECK___

#include <memory>
#include "Save.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "FloorCard.hpp"

class CardDeck {
	private:
	std::vector<S_FloorContent> m_vContent = {};

	int _getProbaCardMax() const;

	public:
	void setCards(Player &player);
	bool hasCards() const;
	std::shared_ptr<Card> pickCard();
	std::shared_ptr<FloorCard> createFloorCard(FloorDirection floorDirection) const;

	void setFoundCards(std::vector<std::pair<E_CardType, std::string>> cardIDs);

	bool foundFloorCard() const;
};

#endif
