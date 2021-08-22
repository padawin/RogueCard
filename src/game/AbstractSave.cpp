#include "AbstractSave.hpp"
#include "utils.hpp"

void AbstractSave::clean() {
	utils_emptyFolder(utils_getDataPath().c_str());
}
