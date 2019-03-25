#include <iostream>
#include "Equipment.hpp"

bool Equipment::equip(std::shared_ptr<ObjectCard> card) {
	unsigned int cardEquipableFlags = card->getEquipableflags();
	int candidate = SIZE_EQUIPMENT, i = 0;
	for (; i < SIZE_EQUIPMENT; ++i) {
		if (m_cards[i] == nullptr) {
			if (candidate == SIZE_EQUIPMENT) {
				candidate = i;
			}
		}
		else if (m_cards[i]->hasEquipableFlag(cardEquipableFlags)) {
			candidate = i;
		}
	}

	// No free spot, should not happen though, that means all spots are taken
	// but there are as many flags as spots, so the previous test should have
	// returned
	if (candidate == SIZE_EQUIPMENT) {
		std::cerr << "Equipment full, but flag of card (" << cardEquipableFlags
			<< ") not found!\n";
		return false;
	}

	m_cards[candidate] = card;
	return true;
}

bool Equipment::remove(std::shared_ptr<ObjectCard> card) {
	for (int c = 0; c < SIZE_EQUIPMENT; ++c) {
		if (m_cards[c] == card) {
			m_cards[c] = nullptr;
			return true;
		}
	}
	return false;
}

std::shared_ptr<ObjectCard> Equipment::getCardWithFlag(unsigned int flag) const {
	for (int c = 0; c < SIZE_EQUIPMENT; ++c) {
		if (m_cards[c] != nullptr && m_cards[c]->hasEquipableFlag(flag)) {
			return m_cards[c];
		}
	}
	return nullptr;
}

std::shared_ptr<ObjectCard> Equipment::getCard(int index) const {
	if (index >= SIZE_EQUIPMENT) {
		return nullptr;
	}
	return m_cards[index];
}
