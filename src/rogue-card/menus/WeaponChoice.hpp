
#ifndef __WEAPON_CHOICE_MENU_ACTION__
#define __WEAPON_CHOICE_MENU_ACTION__

#include "../ObjectCard.hpp"
#include "Menu.hpp"

enum E_WeaponChoice {SWORD_CHOICE, SPEAR_CHOICE, AXE_CHOICE, BLUNT_CHOICE, RANGE_CHOICE, NB_WEAPON_CHOICES};

class WeaponChoiceMenu : public Menu {
	S_MenuItem m_itemTexts[NB_WEAPON_CHOICES] = {};
	int _getNbItems() const;
	S_MenuItem &_getItem(int itemIndex);

	public:
	WeaponChoiceMenu(std::shared_ptr<SDL2Renderer> renderer);
	~WeaponChoiceMenu() {}
	E_WeaponChoice getSelectedAction() const;
};

#endif
