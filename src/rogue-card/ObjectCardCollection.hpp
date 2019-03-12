#ifndef __OBJECT_CARD_COLLECTION__
#define __OBJECT_CARD_COLLECTION__

#include <memory>
#include "ObjectCard.hpp"

#define CARD_COLLECTION_SIZE 36

class ObjectCardCollection {
	private:
	std::shared_ptr<ObjectCard> m_cards[CARD_COLLECTION_SIZE] = {};
	int m_iCurrentCard = 0;

	public:
	void setCard(unsigned int index, std::shared_ptr<ObjectCard> card);
	bool addCard(std::shared_ptr<ObjectCard> card);
	void removeCard(unsigned int index);
	std::shared_ptr<ObjectCard> getCard(unsigned int index) const;
	void clear();
	bool isFull() const;

	// Looping methods
	bool next();
	std::shared_ptr<ObjectCard> current() const;
	void reset();
};

#endif
