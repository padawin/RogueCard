#include "ElementalEffects.hpp"

void ElementalEffects::setStat(E_ElementalElement stat, int value) {
	if (stat >= NB_ELEMENTS) {
		return;
	}
	m_aStats[stat] = value;
}

int ElementalEffects::getStat(E_ElementalElement stat) const {
	if (stat >= NB_ELEMENTS) {
		return 0;
	}
	return m_aStats[stat];
}

int ElementalEffects::sumPoints() const {
	int res = 0;
	for (int s = 0; s < NB_ELEMENTS; ++s) {
		res += m_aStats[s];
	}
	return res;
}

ElementalEffects ElementalEffects::operator+=(ElementalEffects effects) {
	for (int s = 0; s < NB_ELEMENTS; ++s) {
		setStat(
			(E_ElementalElement) s,
			m_aStats[s] + effects.getStat((E_ElementalElement) s)
		);
	}
	return *this;
}
