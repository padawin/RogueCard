#include "ActionBar.hpp"

std::shared_ptr<ObjectCard> ActionBar::getCard(int index) const {
	if (index > ACTION_BAR_SIZE) {
		return nullptr;
	}
	return m_objectCards[index];
}
