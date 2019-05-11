#ifndef __OBJECT_ACTION__
#define __OBJECT_ACTION__

#include "../ObjectCard.hpp"
#include "Menu.hpp"

enum E_ObjectActionMenuItem {USE, INFO, DISCARD, ADD_ACTIONBAR, REMOVE_ACTIONBAR, SORT, BACK, NB_ITEMS};

const unsigned int FLAG_CONTEXT_NOT_IN_FIGHT = 0x01;
const unsigned int FLAG_CONTEXT_CARD_IN_ACTIONBAR = 0x02;
const unsigned int FLAG_CONTEXT_CARD_NOT_IN_ACTIONBAR = 0x04;

class ObjectAction : public Menu {
	std::shared_ptr<ObjectCard> m_card = nullptr;
	unsigned int m_itemsCardFlags[NB_ITEMS] = {};

	S_MenuItem m_itemTexts[NB_ITEMS] = {};
	void _reset();
	bool _isItemValid(int itemIndex);
	int _getNbItems() const;
	S_MenuItem &_getItem(int itemIndex);

	public:
	ObjectAction(std::shared_ptr<SDL2Renderer> renderer);
	~ObjectAction() {}
	void open(std::shared_ptr<ObjectCard> card);
	bool isOpen() const;
	void close();
	E_ObjectActionMenuItem getSelectedAction() const;
};

#endif
