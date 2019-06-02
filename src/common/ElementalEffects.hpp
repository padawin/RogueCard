#ifndef __ELEMENTAL_EFFECTS__
#define __ELEMENTAL_EFFECTS__

enum E_ElementalElement {
	ELEMENT_FIRE,
	NB_ELEMENTS
};

class ElementalEffects {
	private:
	int m_aStats[NB_ELEMENTS] = {};

	public:
	void setStat(E_ElementalElement stat, int value);
	int getStat(E_ElementalElement stat) const;
	int sumPoints() const;

	ElementalEffects operator+=(ElementalEffects effects);
};

#endif
