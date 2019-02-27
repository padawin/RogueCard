#include "ActionBar.hpp"

std::shared_ptr<Card> ActionBar::getCard(int index) const {
	if (index > MAX_OBJECTS) {
		return nullptr;
	}
	return m_objectCards[index];
}
