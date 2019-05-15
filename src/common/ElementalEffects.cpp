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
