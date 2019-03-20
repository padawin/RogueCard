#ifndef __EQUIPMENT__
#define __EQUIPMENT__

#include <memory>
#include "ObjectCard.hpp"

#define SIZE_EQUIPMENT 8

class Equipment {
	private:
	std::shared_ptr<ObjectCard> m_cards[SIZE_EQUIPMENT] = {};

	public:
	bool equip(std::shared_ptr<ObjectCard> card);
	bool remove(std::shared_ptr<ObjectCard> card);
	std::shared_ptr<ObjectCard> getCardWithFlag(unsigned int flag) const;
};

#endif
