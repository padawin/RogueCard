#ifndef __OBJECT_CARD_COLLECTION__
#define __OBJECT_CARD_COLLECTION__

#include <memory>
#include "ObjectCard.hpp"

#define CARD_COLLECTION_SIZE 36

class ObjectCardCollection {
	private:
	std::shared_ptr<ObjectCard> m_cards[CARD_COLLECTION_SIZE] = {};
	int m_iCurrentCard = 0;

	bool _addUniqueCard(std::shared_ptr<ObjectCard> card);
	bool _addConsumableCard(std::shared_ptr<ObjectCard> card);

	public:
	~ObjectCardCollection() {}
	void setCard(unsigned int index, std::shared_ptr<ObjectCard> card);
	bool addCard(std::shared_ptr<ObjectCard> card);
	void removeCard(std::shared_ptr<ObjectCard> card);
	std::shared_ptr<ObjectCard> getCard(unsigned int index) const;
	void clear();
	bool isFull() const;

	// Looping methods
	bool next();
	std::shared_ptr<ObjectCard> current() const;
	void reset();
};

#endif
