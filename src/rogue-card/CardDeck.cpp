#include <iostream>
#include "CardDeck.hpp"
#include "ObjectCard.hpp"
#include "FloorCard.hpp"
#include "EnemyCard.hpp"

std::shared_ptr<Card> CardDeck::pickCard() {
	E_CardType possibleTypes[] = {ObjectCardType, FloorCardType, EnemyCardType};
	E_CardType type = possibleTypes[rand() % 3];

	if (type == ObjectCardType) {
		return std::shared_ptr<ObjectCard>(new ObjectCard());
	}
	else if (type == FloorCardType) {
		return std::shared_ptr<FloorCard>(new FloorCard());
	}
	else if (type == EnemyCardType) {
		return std::shared_ptr<EnemyCard>(new EnemyCard());
	}
	else {
		std::cerr << "Unknown card type " << type << "!\n";
		return NULL;
	}
}
