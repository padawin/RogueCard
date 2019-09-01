#include <iostream>
#include "CardDeck.hpp"
#include "ObjectCard.hpp"
#include "EnemyCard.hpp"
#include "FinalGoalCard.hpp"

void CardDeck::setCards(Player &player) {
	m_vContent = player.getFloor().getContent();
	bool isLastFloor = player.getFloor().isLast();
	if (isLastFloor && !player.foundFinalGoal()) {
		S_FloorContent finalGoalFloorCard;
		finalGoalFloorCard.type = FinalGoalCardType;
		finalGoalFloorCard.probability = 5;
		finalGoalFloorCard.unique = true;
		finalGoalFloorCard.found = false;
		m_vContent.push_back(finalGoalFloorCard);
	}
	if (!player.foundFinalGoal() && !isLastFloor && !player.foundFloorCard()) {
		S_FloorContent nextFloorCard;
		nextFloorCard.type = FloorCardType;
		nextFloorCard.probability = 5;
		nextFloorCard.unique = true;
		nextFloorCard.found = false;
		m_vContent.push_back(nextFloorCard);
	}
}

bool CardDeck::hasCards() const {
	int floorMaxProba = _getProbaCardMax();
	return floorMaxProba != 0;
}

std::shared_ptr<Card> CardDeck::pickCard() {
	std::shared_ptr<Card> card = nullptr;
	int minProba = 0,
		maxProba = 0;
	int floorMaxProba = _getProbaCardMax();
	int proba = rand() % floorMaxProba;
	for (S_FloorContent &cardType : m_vContent) {
		if (cardType.unique && cardType.found) {
			continue;
		}
		maxProba += cardType.probability;
		if (minProba <= proba && proba < maxProba) {
			if (cardType.type == EnemyCardType) {
				card = std::shared_ptr<EnemyCard>(new EnemyCard(cardType.id));
			}
			else if (cardType.type == ObjectCardType) {
				card = std::shared_ptr<ObjectCard>(new ObjectCard(cardType.id));
			}
			else if (cardType.type == FloorCardType) {
				card = createFloorCard(FLOOR_DOWN);
			}
			else if (cardType.type == FinalGoalCardType) {
				card = std::shared_ptr<FinalGoalCard>(new FinalGoalCard());
			}
			else {
				std::cerr << "Invalid card type: " << cardType.type << std::endl;
				break;
			}
			cardType.found = cardType.unique;
			card->setUnique(cardType.unique);
			card->create();
			break;
		}
		else {
			minProba += cardType.probability;
		}
	}

	return card;
}

std::shared_ptr<FloorCard> CardDeck::createFloorCard(FloorDirection floorDirection) const {
	return std::shared_ptr<FloorCard>(new FloorCard(floorDirection));
}

int CardDeck::_getProbaCardMax() const {
	int probaBase = 0;
	for (S_FloorContent cardType : m_vContent) {
		// Ignore cards which are unique and found, we don't want to pick them
		// again
		if (!cardType.unique || !cardType.found) {
			probaBase += cardType.probability;
		}
	}
	return probaBase;
}
