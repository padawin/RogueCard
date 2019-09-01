#include <iostream>
#include "CardDeck.hpp"
#include "ObjectCard.hpp"
#include "EnemyCard.hpp"
#include "FinalGoalCard.hpp"

bool CardDeck::hasCards(Player &player) const {
	std::vector<S_FloorContent> &floorCards = player.getFloor().getContent();
	std::vector<S_FloorContent> extraCards = _getExtraCards(player);
	int floorMaxProba = _getProbaCardMax(floorCards, extraCards);
	return floorMaxProba != 0;
}

std::shared_ptr<Card> CardDeck::pickCard(Player &player) {
	std::vector<S_FloorContent> &floorCards = player.getFloor().getContent();
	std::vector<S_FloorContent> extraCards = _getExtraCards(player);
	std::shared_ptr<Card> card = _createCard(player, floorCards, extraCards);
	card->create();
	return card;
}

std::vector<S_FloorContent> CardDeck::_getExtraCards(Player &player) const {
	std::vector<S_FloorContent> extraCards;
	// get max proba for current floor
	bool isLastFloor = player.getFloor().isLast();
	if (isLastFloor && !player.foundFinalGoal()) {
		S_FloorContent finalGoalFloorCard;
		finalGoalFloorCard.type = FinalGoalCardType;
		finalGoalFloorCard.probability = 5;
		finalGoalFloorCard.unique = true;
		finalGoalFloorCard.found = false;
		extraCards.push_back(finalGoalFloorCard);
	}
	if (!player.foundFinalGoal() && !isLastFloor && !player.foundFloorCard()) {
		S_FloorContent nextFloorCard;
		nextFloorCard.type = FloorCardType;
		nextFloorCard.probability = 5;
		nextFloorCard.unique = true;
		nextFloorCard.found = false;
		extraCards.push_back(nextFloorCard);
	}
	return extraCards;
}

std::shared_ptr<FloorCard> CardDeck::createFloorCard(FloorDirection floorDirection) const {
	return std::shared_ptr<FloorCard>(new FloorCard(floorDirection));
}

std::shared_ptr<Card> CardDeck::_createCard(
	Player &player,
	std::vector<S_FloorContent> &floorCards,
	std::vector<S_FloorContent> &extraCards
) const {
	std::shared_ptr<Card> card = nullptr;
	int minProba = 0,
		maxProba = 0;
	int floorMaxProba = _getProbaCardMax(floorCards, extraCards);
	int proba = rand() % floorMaxProba;
	std::vector<S_FloorContent>* decks[] = {&floorCards, &extraCards};
	for (auto deck : decks) {
		for (S_FloorContent &cardType : *deck) {
			if (cardType.unique && cardType.found) {
				continue;
			}
			maxProba += cardType.probability;
			if (minProba <= proba && proba < maxProba) {
				if (cardType.type == EnemyCardType) {
					card = std::shared_ptr<EnemyCard>(new EnemyCard(cardType.id));
					player.setFighting(true);
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
				}
				cardType.found = cardType.unique;
				return card;
			}
			else {
				minProba += cardType.probability;
			}
		}
	}

	std::cerr << "Card is null (Proba: " << proba << ", maxProba: " << maxProba << ")\n";
	return nullptr;
}

int CardDeck::_getProbaCardMax(std::vector<S_FloorContent> &floorCards, std::vector<S_FloorContent> &extraCards) const {
	int probaBase = 0;
	std::vector<S_FloorContent>* decks[] = {&floorCards, &extraCards};
	for (auto deck : decks) {
		for (auto cardType : *deck) {
			// Ignore cards which are unique and found, we don't want to pick them
			// again
			if (!cardType.unique || !cardType.found) {
				probaBase += cardType.probability;
			}
		}
	}
	return probaBase;
}
