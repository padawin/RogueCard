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

// Looping methods
bool ActionBar::next() {
	if (m_iCurrentCard >= ACTION_BAR_SIZE - 1) {
		return false;
	}

	++m_iCurrentCard;
	return true;
}

std::shared_ptr<ObjectCard> ActionBar::current() const {
	return m_objectCards[m_iCurrentCard];
}

void ActionBar::reset() {
	m_iCurrentCard = 0;
}
