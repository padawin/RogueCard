#include "FloorCard.hpp"

FloorCard::FloorCard(FloorDirection direction) : Card(FloorCardType) {
	m_sImage = direction == FLOOR_DOWN ? "door-down" : "door-up";
}

void FloorCard::create() {
}
