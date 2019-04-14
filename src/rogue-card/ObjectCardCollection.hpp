#ifndef __OBJECT_CARD_COLLECTION__
#define __OBJECT_CARD_COLLECTION__

#include <memory>
#include "ObjectCard.hpp"
#include "ObjectCardsLoopable.hpp"

#define CARD_COLLECTION_SIZE 36

class ObjectCardCollection : public IObjectCardsLoopable {
	private:
	std::shared_ptr<ObjectCard> m_cards[CARD_COLLECTION_SIZE] = {};

	bool _addUniqueCard(std::shared_ptr<ObjectCard> card);
	bool _addConsumableCard(std::shared_ptr<ObjectCard> card);

	void _group(int start);

	public:
	~ObjectCardCollection() {}
	void setCard(int index, std::shared_ptr<ObjectCard> card);
	bool addCard(std::shared_ptr<ObjectCard> card);
	void removeCard(std::shared_ptr<ObjectCard> card);
	std::shared_ptr<ObjectCard> getCard(int index) const;
	void clear();
	bool isFull() const;
	int getCardIndex(std::shared_ptr<ObjectCard> card) const;

	void sort();

	// Looping methods
	bool next();
	std::shared_ptr<ObjectCard> current() const;
	void reset();
};

#endif
