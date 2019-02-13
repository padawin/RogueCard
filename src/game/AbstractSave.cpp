#include "AbstractSave.hpp"
#include "Utils.hpp"

void AbstractSave::clean() {
	Utils::emptyFolder(Utils::getDataPath().c_str());
}
