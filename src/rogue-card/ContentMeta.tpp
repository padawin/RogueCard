template <class contentType>
ContentMeta<contentType>::ContentMeta() :
	m_resourceManager(ResourceManager<contentType>())
{}

template <class contentType>
bool ContentMeta<contentType>::prepare(std::string file) {
	if (!m_resourceManager.setResourceFile(file)) {
		return false;
	}
	m_resourceManager.parseBinaryFile();
	for (auto it : m_resourceManager.getParsedResources()) {
		m_mMetaDataMapping[it.second.id] = it.first;
	}
	return true;
}

template <class contentType>
int ContentMeta<contentType>::getSize() {
	return (int) m_resourceManager.getParsedResources().size();
}

template <class contentType>
contentType ContentMeta<contentType>::get(int index) {
	if (index >= getSize()) {
		index = 0;
	}
	return m_resourceManager.getParsedResources()[index];
}

template <class contentType>
contentType ContentMeta<contentType>::getFromID(std::string id) {
	auto item = m_mMetaDataMapping.find(id);
	if (item == m_mMetaDataMapping.end()) {
		return get(0);
	}
	else {
		return get(item->second);
	}
}

template <class contentType>
int ContentMeta<contentType>::getIndex(std::string id) {
	auto item = m_mMetaDataMapping.find(id);
	if (item == m_mMetaDataMapping.end()) {
		return -1;
	}
	else {
		return item->second;
	}
}
