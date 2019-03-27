#include "ObjectCardCollection.hpp"

void ObjectCardCollection::setCard(unsigned int index, std::shared_ptr<ObjectCard> card) {
	if (index < CARD_COLLECTION_SIZE) {
		m_cards[index] = card;
	}
}

bool ObjectCardCollection::addCard(std::shared_ptr<ObjectCard> card) {
	unsigned int c = 0;
	for (c = 0; c < CARD_COLLECTION_SIZE && m_cards[c] != nullptr; ++c) {}
	if (c < CARD_COLLECTION_SIZE) {
		m_cards[c] = card;
		return true;
	}

	return false;
}

void ObjectCardCollection::removeCard(std::shared_ptr<ObjectCard> card) {
	for (unsigned int c = 0; c < CARD_COLLECTION_SIZE; ++c) {
		if (m_cards[c] == card) {
			setCard(c, nullptr);
			return;
		}
	}
}

std::shared_ptr<ObjectCard> ObjectCardCollection::getCard(unsigned int index) const {
	if (index >= CARD_COLLECTION_SIZE) {
		return nullptr;
	}

	return m_cards[index];
}

void ObjectCardCollection::clear() {
	for (unsigned int c = 0; c < CARD_COLLECTION_SIZE; ++c) {
		setCard(c, nullptr);
	}
}

bool ObjectCardCollection::isFull() const {
	unsigned int c;
	for (c = 0; c < CARD_COLLECTION_SIZE && m_cards[c] != nullptr; ++c) {}
	return c == CARD_COLLECTION_SIZE;
}

// Looping methods
bool ObjectCardCollection::next() {
	if (m_iCurrentCard >= CARD_COLLECTION_SIZE - 1) {
		return false;
	}

	++m_iCurrentCard;
	return true;
}

std::shared_ptr<ObjectCard> ObjectCardCollection::current() const {
	return m_cards[m_iCurrentCard];
}

void ObjectCardCollection::reset() {
	m_iCurrentCard = 0;
}
