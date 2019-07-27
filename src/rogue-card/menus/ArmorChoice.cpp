#include "ArmorChoice.hpp"
#include "../common/types.hpp"

ArmorChoiceMenu::ArmorChoiceMenu(std::shared_ptr<SDL2Renderer> renderer) :
	Menu(renderer)
{
	m_iX = 32;
	m_iY = 72;

	m_itemTexts[LIGHT_ARMOR_CHOICE].text = Text();
	m_itemTexts[LIGHT_ARMOR_CHOICE].text.setText(getSkillLabel(LIGHT_ARMOR));

	m_itemTexts[MEDIUM_ARMOR_CHOICE].text = Text();
	m_itemTexts[MEDIUM_ARMOR_CHOICE].text.setText(getSkillLabel(MEDIUM_ARMOR));

	m_itemTexts[HEAVY_ARMOR_CHOICE].text = Text();
	m_itemTexts[HEAVY_ARMOR_CHOICE].text.setText(getSkillLabel(HEAVY_ARMOR));
}

E_ArmorChoice ArmorChoiceMenu::getSelectedAction() const {
	return (E_ArmorChoice) m_selectedAction;
}

int ArmorChoiceMenu::_getNbItems() const {
	return NB_ARMOR_CHOICES;
}

S_MenuItem &ArmorChoiceMenu::_getItem(int itemIndex) {
	return m_itemTexts[itemIndex];
}
