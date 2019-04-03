#include "ObjectCardCollection.hpp"

void ObjectCardCollection::setCard(int index, std::shared_ptr<ObjectCard> card) {
	if (index < CARD_COLLECTION_SIZE) {
		m_cards[index] = card;
	}
}

bool ObjectCardCollection::addCard(std::shared_ptr<ObjectCard> card) {
	if (card->isConsumable()) {
		return _addConsumableCard(card);
	}
	else {
		return _addUniqueCard(card);
	}
}

bool ObjectCardCollection::_addUniqueCard(std::shared_ptr<ObjectCard> card) {
	int c = 0;
	for (c = 0; c < CARD_COLLECTION_SIZE && m_cards[c] != nullptr; ++c) {}
	if (c < CARD_COLLECTION_SIZE) {
		m_cards[c] = card;
		return true;
	}
	return false;
}

bool ObjectCardCollection::_addConsumableCard(std::shared_ptr<ObjectCard> card) {
	int c = 0, firstEmpty = -1;
	for (c = 0; c < CARD_COLLECTION_SIZE; ++c) {
		if (m_cards[c] == nullptr) {
			if (firstEmpty == -1) {
				firstEmpty = c;
			}
		}
		else if (m_cards[c]->isSameAs(card) && !m_cards[c]->reachedMaxQuantity()) {
			m_cards[c]->addInstance();
			return true;
		}
	}
	if (firstEmpty != -1) {
		m_cards[firstEmpty] = card;
		return true;
	}

	return false;
}

void ObjectCardCollection::removeCard(std::shared_ptr<ObjectCard> card) {
	for (int c = 0; c < CARD_COLLECTION_SIZE; ++c) {
		if (m_cards[c] == card) {
			setCard(c, nullptr);
			return;
		}
	}
}

std::shared_ptr<ObjectCard> ObjectCardCollection::getCard(int index) const {
	if (index >= CARD_COLLECTION_SIZE) {
		return nullptr;
	}

	return m_cards[index];
}

void ObjectCardCollection::clear() {
	for (int c = 0; c < CARD_COLLECTION_SIZE; ++c) {
		setCard(c, nullptr);
	}
}

bool ObjectCardCollection::isFull() const {
	int c;
	for (c = 0; c < CARD_COLLECTION_SIZE && m_cards[c] != nullptr; ++c) {}
	return c == CARD_COLLECTION_SIZE;
}

int ObjectCardCollection::getCardIndex(std::shared_ptr<ObjectCard> card) const {
	int c;
	for (c = 0; c < CARD_COLLECTION_SIZE && m_cards[c] != card; ++c) {}
	return c == CARD_COLLECTION_SIZE ? -1 : c;
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
