#include "Floor.hpp"
#include "../common/ResourceManager.hpp"

std::map<int, std::vector<S_FloorContent>> Floor::m_mFloorContentMeta = {};

bool Floor::prepareMeta(std::string file) {
	ResourceManager<S_FloorContent> meta = ResourceManager<S_FloorContent>();
	if (!meta.setResourceFile(file)) {
		return false;
	}
	meta.parseBinaryFile();
	auto data = meta.getParsedResources();
	int nbRows = (int) data.size();
	int floorLevel;
	for (int i = 0; i < nbRows; ++i) {
		floorLevel = data[i].floorLevel;
		if (m_mFloorContentMeta.find(floorLevel) == m_mFloorContentMeta.end()) {
			m_mFloorContentMeta[floorLevel] = std::vector<S_FloorContent>();
		}
		m_mFloorContentMeta[floorLevel].push_back(data[i]);
	}
	return true;
}

std::vector<S_FloorContent> Floor::getContent() const {
	return m_mFloorContentMeta[m_iLevel];
}

int Floor::getLevel() const {
	return m_iLevel;
}

void Floor::setLevel(int level) {
	m_iLevel = level;
}

void Floor::toNextLevel() {
	if (!isLast()) {
		++m_iLevel;
	}
}

void Floor::toPreviousLevel() {
	if (m_iLevel >= 1) {
		--m_iLevel;
	}
}

bool Floor::isLast() const {
	return m_iLevel == (int) m_mFloorContentMeta.size();
}
