#include "types.hpp"

std::string getSkillLabel(E_XPSkill skill) {
	const char* labels[NB_XP_SKILLS + 1] = {
		"",
		"Light armor",
		"Medium armor",
		"Heavy armor",
		"Hand fight",
		"Sword",
		"Lance",
		"Spears",
		"Axe",
		"Magic",
		"Perception",
		"Speed",
		""
	};
	return labels[skill];
}
