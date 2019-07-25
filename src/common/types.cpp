#include "types.hpp"

std::string getSkillLabel(E_XPSkill skill) {
	const char* labels[NB_XP_SKILLS + 1] = {
		"",
		"Light armor",
		"Medium armor",
		"Heavy armor",
		"Sword",
		"Spears",
		"Axe",
		"Blunt",
		"Range",
		"Magic",
		"Perception",
		"Speed",
		""
	};
	return labels[skill];
}
