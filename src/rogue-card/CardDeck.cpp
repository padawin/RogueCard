#include <iostream>
#include "CardDeck.hpp"
#include "ObjectCard.hpp"
#include "FloorCard.hpp"
#include "EnemyCard.hpp"

std::shared_ptr<Card> CardDeck::pickCard() {
	int proba = rand() % 1000;
	E_CardType type;
	if (proba < 50) {
		type = FloorCardType;
	}
	else if (proba < 600) {
		type = EnemyCardType;
	}
	else {
		type = ObjectCardType;
	}

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
