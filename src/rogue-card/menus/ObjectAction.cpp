#include "ObjectAction.hpp"
#include "../ObjectCard.hpp"

ObjectAction::ObjectAction(std::shared_ptr<SDL2Renderer> renderer) :
	Menu(renderer)
{
	m_itemTexts[USE].text = Text();
	m_itemTexts[USE].text.setText("Use");
	m_itemTexts[USE].context = FLAG_CONTEXT_NOT_IN_FIGHT;
	m_itemsCardFlags[USE] = FLAG_USABLE | FLAG_APPLY_ON_SELF;

	m_itemTexts[INFO].text = Text();
	m_itemTexts[INFO].text.setText("Info");
	m_itemsCardFlags[INFO] = 0;

	m_itemTexts[DISCARD].text = Text();
	m_itemTexts[DISCARD].text.setText("Discard");
	m_itemsCardFlags[DISCARD] = 0;

	m_itemTexts[SORT].text = Text();
	m_itemTexts[SORT].text.setText("Sort");
	m_itemsCardFlags[SORT] = 0;

	m_itemTexts[ADD_ACTIONBAR].text = Text();
	m_itemTexts[ADD_ACTIONBAR].text.setText("Add to ActionBar");
	m_itemTexts[ADD_ACTIONBAR].context = FLAG_CONTEXT_CARD_NOT_IN_ACTIONBAR | FLAG_CONTEXT_NOT_IN_FIGHT;
	m_itemsCardFlags[ADD_ACTIONBAR] = FLAG_USABLE;

	m_itemTexts[REMOVE_ACTIONBAR].text = Text();
	m_itemTexts[REMOVE_ACTIONBAR].text.setText("Remove from ActionBar");
	m_itemTexts[REMOVE_ACTIONBAR].context = FLAG_CONTEXT_CARD_IN_ACTIONBAR | FLAG_CONTEXT_NOT_IN_FIGHT;
	m_itemsCardFlags[REMOVE_ACTIONBAR] = FLAG_USABLE;

	m_itemTexts[BACK].text = Text();
	m_itemTexts[BACK].text.setText("Back");
	m_itemsCardFlags[BACK] = 0;
}

bool ObjectAction::_isItemValid(int itemIndex) {
	return (
		m_card->hasFlags(m_itemsCardFlags[itemIndex])
		&& Menu::_isItemValid(itemIndex)
	);
}

void ObjectAction::open(std::shared_ptr<ObjectCard> card) {
	_reset();
	m_card = card;
	init();
}

bool ObjectAction::isOpen() const {
	return m_card != nullptr;
}

void ObjectAction::close() {
	for (int i = 0; i < NB_ITEMS; ++i) {
		m_itemTexts[i].valid = false;
	}
	_reset();
}

void ObjectAction::_reset() {
	m_card = nullptr;
	Menu::_reset();
}

E_ObjectActionMenuItem ObjectAction::getSelectedAction() const {
	return (E_ObjectActionMenuItem) m_selectedAction;
}

int ObjectAction::_getNbItems() const {
	return NB_ITEMS;
}

S_MenuItem &ObjectAction::_getItem(int itemIndex) {
	return m_itemTexts[itemIndex];
}
