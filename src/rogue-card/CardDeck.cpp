#include <iostream>
#include "CardDeck.hpp"
#include "ObjectCard.hpp"
#include "FloorCard.hpp"
#include "EnemyCard.hpp"

std::shared_ptr<Card> CardDeck::pickCard(Player &player, bool foundNextFloor) {
	int proba = rand() % 1000;
	std::shared_ptr<Card> card = nullptr;
	if (!foundNextFloor && proba < 50) {
		FloorDirection floorDirection = player.getDirection() ? FLOOR_DOWN : FLOOR_UP;
		card = std::shared_ptr<FloorCard>(new FloorCard(floorDirection));
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
