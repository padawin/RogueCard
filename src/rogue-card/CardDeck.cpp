#include <iostream>
#include "CardDeck.hpp"
#include "ObjectCard.hpp"
#include "EnemyCard.hpp"
#include "FinalGoalCard.hpp"

std::shared_ptr<Card> CardDeck::pickCard(Player &player, bool foundNextFloor) {
	bool isLastFloor = player.getFloor().isLast();
	int proba = rand() % 1000;
	std::shared_ptr<Card> card = nullptr;
	if (isLastFloor && !player.foundFinalGoal() && proba < 50) {
		card = std::shared_ptr<FinalGoalCard>(new FinalGoalCard());
	}
	else if (!player.foundFinalGoal() && !isLastFloor && !foundNextFloor && proba < 50) {
		card = createFloorCard(FLOOR_DOWN);
	}
	else if (proba < 600) {
		card = std::shared_ptr<EnemyCard>(new EnemyCard(player.getFloor().getLevel()));
		player.setFighting(true);
	}
	else {
		card = std::shared_ptr<ObjectCard>(new ObjectCard());
	}
	card->create();
	return card;
}

std::shared_ptr<FloorCard> CardDeck::createFloorCard(FloorDirection floorDirection) const {
	return std::shared_ptr<FloorCard>(new FloorCard(floorDirection));
}
