#include <iostream>
#include "CardDeck.hpp"
#include "ObjectCard.hpp"
#include "EnemyCard.hpp"
#include "FinalGoalCard.hpp"

std::shared_ptr<Card> CardDeck::pickCard(Player &player) {
	bool isLastFloor = player.getFloor().isLast();
	int proba = rand() % 1000;
	std::shared_ptr<Card> card = nullptr;
	if (isLastFloor && !player.foundFinalGoal() && proba < 50) {
		card = std::shared_ptr<FinalGoalCard>(new FinalGoalCard());
	}
	else if (!player.foundFinalGoal() && !isLastFloor && !player.foundFloorCard() && proba < 50) {
		card = createFloorCard(FLOOR_DOWN);
	}
	else {
		card = _createCard(player);
	}
	card->create();
	return card;
}

std::shared_ptr<FloorCard> CardDeck::createFloorCard(FloorDirection floorDirection) const {
	return std::shared_ptr<FloorCard>(new FloorCard(floorDirection));
}

std::shared_ptr<Card> CardDeck::_createCard(Player &player) const {
	std::vector<S_FloorContent> potentialCards = player.getFloor().getContent();
	std::shared_ptr<Card> card = nullptr;
	int proba = rand() % 100;
	int minProba = 0,
		maxProba = 0;
	for (auto cardType : potentialCards) {
		maxProba += cardType.probability;
		if (minProba <= proba && proba < maxProba) {
			if (cardType.type == EnemyCardType) {
				card = std::shared_ptr<EnemyCard>(new EnemyCard(cardType.id));
				player.setFighting(true);
			}
			else if (cardType.type == ObjectCardType) {
				card = std::shared_ptr<ObjectCard>(new ObjectCard(cardType.id));
			}
			else {
				std::cerr << "Invalid card type: " << cardType.type << std::endl;
			}
			cardType.found = cardType.unique;
			break;
		}
		else {
			minProba += cardType.probability;
		}
	}
	if (card == nullptr) {
		std::cerr << "Card is null (Proba: " << proba << ", maxProba: " << maxProba << ")\n";
	}
	return card;
}
