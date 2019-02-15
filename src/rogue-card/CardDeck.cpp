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
	std::shared_ptr<Card> card = nullptr;

	if (type == ObjectCardType) {
		card = std::shared_ptr<ObjectCard>(new ObjectCard());
	}
	else if (type == FloorCardType) {
		card = std::shared_ptr<FloorCard>(new FloorCard());
	}
	else if (type == EnemyCardType) {
		card = std::shared_ptr<EnemyCard>(new EnemyCard());
	}
	else {
		std::cerr << "Unknown card type " << type << "!\n";
	}
	card->create();
	return card;
}
