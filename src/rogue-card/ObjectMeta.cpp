#include <iostream>
#include "ObjectMeta.hpp"
#include "../common/ResourceManager.hpp"

ObjectMeta::ObjectMeta() :
	m_resourceManager(ResourceManager<S_ObjectMeta>())
{}

bool ObjectMeta::prepare(std::string file) {
	if (!m_resourceManager.setResourceFile(file)) {
		return false;
	}
	m_resourceManager.parseBinaryFile();
	for (auto it : m_resourceManager.getParsedResources()) {
		m_mMetaDataMapping[it.second.id] = it.first;
	}
	return true;
}

int ObjectMeta::getSize() {
	return (int) m_resourceManager.getParsedResources().size();
}

S_ObjectMeta ObjectMeta::get(int index) {
	if (index >= getSize()) {
		index = 0;
	}
	return m_resourceManager.getParsedResources()[index];
}
