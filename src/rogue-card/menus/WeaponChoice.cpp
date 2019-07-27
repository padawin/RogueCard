#include "WeaponChoice.hpp"
#include "../common/types.hpp"

WeaponChoiceMenu::WeaponChoiceMenu(std::shared_ptr<SDL2Renderer> renderer) :
	Menu(renderer)
{
	m_iX = 32;
	m_iY = 72;

	m_itemTexts[SWORD_CHOICE].text = Text();
	m_itemTexts[SWORD_CHOICE].text.setText(getSkillLabel(SWORD));

	m_itemTexts[SPEARS_CHOICE].text = Text();
	m_itemTexts[SPEARS_CHOICE].text.setText(getSkillLabel(SPEARS));

	m_itemTexts[AXE_CHOICE].text = Text();
	m_itemTexts[AXE_CHOICE].text.setText(getSkillLabel(AXE));

	m_itemTexts[BLUNT_CHOICE].text = Text();
	m_itemTexts[BLUNT_CHOICE].text.setText(getSkillLabel(BLUNT));

	m_itemTexts[RANGE_CHOICE].text = Text();
	m_itemTexts[RANGE_CHOICE].text.setText(getSkillLabel(RANGE));
}

E_WeaponChoice WeaponChoiceMenu::getSelectedAction() const {
	return (E_WeaponChoice) m_selectedAction;
}

int WeaponChoiceMenu::_getNbItems() const {
	return NB_WEAPON_CHOICES;
}

S_MenuItem &WeaponChoiceMenu::_getItem(int itemIndex) {
	return m_itemTexts[itemIndex];
}
