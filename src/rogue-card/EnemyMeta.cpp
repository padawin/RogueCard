#include <iostream>
#include "EnemyMeta.hpp"
#include "../common/ResourceManager.hpp"

EnemyMeta::EnemyMeta() :
	m_resourceManager(ResourceManager<S_EnemyMeta>())
{}

bool EnemyMeta::prepare(std::string file) {
	if (!m_resourceManager.setResourceFile(file)) {
		return false;
	}
	m_resourceManager.parseBinaryFile();
	for (auto it : m_resourceManager.getParsedResources()) {
		m_mMetaDataMapping[it.second.id] = it.first;
	}
	return true;
}

int EnemyMeta::getSize() {
	return (int) m_resourceManager.getParsedResources().size();
}

S_EnemyMeta EnemyMeta::get(int index) {
	if (index >= getSize()) {
		index = 0;
	}
	return m_resourceManager.getParsedResources()[index];
}
