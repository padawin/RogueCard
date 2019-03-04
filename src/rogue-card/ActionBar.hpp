#ifndef __ACTION_BAR__
#define __ACTION_BAR__

#include <memory>
#include "ObjectCard.hpp"

const int ACTION_BAR_SIZE= 4;

class ActionBar {
	private:
	std::shared_ptr<ObjectCard> m_objectCards[ACTION_BAR_SIZE] = {nullptr, nullptr, nullptr, nullptr};

	public:
	std::shared_ptr<ObjectCard> getCard(int index) const;
};

#endif
