#ifndef __EQUIPMENT__
#define __EQUIPMENT__

#include <memory>
#include "ObjectCard.hpp"
#include "ObjectCardsLoopable.hpp"

#define SIZE_EQUIPMENT 8

class Equipment : public IObjectCardsLoopable {
	private:
	std::shared_ptr<ObjectCard> m_cards[SIZE_EQUIPMENT] = {};

	public:
	~Equipment() {}
	bool isEquipped(std::shared_ptr<ObjectCard> card) const;
	bool equip(std::shared_ptr<ObjectCard> card);
	bool remove(std::shared_ptr<ObjectCard> card);
	std::shared_ptr<ObjectCard> getCardWithFlag(unsigned int flag) const;

	// Looping methods
	bool next();
	std::shared_ptr<ObjectCard> current() const;
	void reset();
};

#endif
