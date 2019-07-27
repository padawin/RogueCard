#ifndef __ARMOR_CHOICE_MENU_ACTION__
#define __ARMOR_CHOICE_MENU_ACTION__

#include "../ObjectCard.hpp"
#include "Menu.hpp"

enum E_ArmorChoice {LIGHT_ARMOR_CHOICE, MEDIUM_ARMOR_CHOICE, HEAVY_ARMOR_CHOICE, NB_ARMOR_CHOICES};

class ArmorChoiceMenu : public Menu {
	S_MenuItem m_itemTexts[NB_ARMOR_CHOICES] = {};
	int _getNbItems() const;
	S_MenuItem &_getItem(int itemIndex);

	public:
	ArmorChoiceMenu(std::shared_ptr<SDL2Renderer> renderer);
	~ArmorChoiceMenu() {}
	E_ArmorChoice getSelectedAction() const;
};

#endif
