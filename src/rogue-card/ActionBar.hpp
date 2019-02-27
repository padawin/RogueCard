#ifndef __ACTION_BAR__
#define __ACTION_BAR__

#include <memory>
#include "Card.hpp"

const int MAX_OBJECTS = 4;

class ActionBar {
	private:
	std::shared_ptr<Card> m_objectCards[MAX_OBJECTS] = {nullptr, nullptr, nullptr, nullptr};

	public:
	std::shared_ptr<Card> getCard(int index) const;
};

#endif
