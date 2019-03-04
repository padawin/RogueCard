#include "ActionBar.hpp"

std::shared_ptr<ObjectCard> ActionBar::getCard(int index) const {
	if (index > ACTION_BAR_SIZE) {
		return nullptr;
	}
	return m_objectCards[index];
}

void ActionBar::setCard(int index, std::shared_ptr<ObjectCard> card) {
	m_objectCards[index] = card;
}

void ActionBar::removeCard(std::shared_ptr<ObjectCard> card) {
	for (int index = 0; index < ACTION_BAR_SIZE; ++index) {
		if (m_objectCards[index] == card) {
			m_objectCards[index] = nullptr;
		}
	}
}

bool ActionBar::hasCard(std::shared_ptr<ObjectCard> card) const {
	int index = 0;
	for (; index < ACTION_BAR_SIZE && m_objectCards[index] != card; ++index) {}
	return index < ACTION_BAR_SIZE;
}
