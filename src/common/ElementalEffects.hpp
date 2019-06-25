#ifndef __ELEMENTAL_EFFECTS__
#define __ELEMENTAL_EFFECTS__

#include <string>

enum E_ElementalElement {
	ELEMENT_FIRE,
	NB_ELEMENTS
};

class ElementalEffects {
	private:
	int m_aStats[NB_ELEMENTS] = {};
	static const char** m_aLabels;

	public:
	void setStat(E_ElementalElement stat, int value);
	static std::string getElementLabel(E_ElementalElement element);
	int getStat(E_ElementalElement stat) const;
	int sumPoints() const;

	ElementalEffects operator+=(ElementalEffects effects);
};

#endif
