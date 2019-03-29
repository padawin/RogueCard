#ifndef __ACTION_BAR__
#define __ACTION_BAR__

#include <memory>
#include "ObjectCard.hpp"

const int ACTION_BAR_SIZE= 4;

class ActionBar {
	private:
	std::shared_ptr<ObjectCard> m_objectCards[ACTION_BAR_SIZE] = {nullptr, nullptr, nullptr, nullptr};

	public:
	~ActionBar() {}
	std::shared_ptr<ObjectCard> getCard(int index) const;
	void setCard(int index, std::shared_ptr<ObjectCard> card);
	void removeCard(std::shared_ptr<ObjectCard> card);
	bool hasCard(std::shared_ptr<ObjectCard> card) const;
};

#endif
