#include "ObjectCard.hpp"

ResourceManager<S_ObjectMeta> ObjectCard::m_objectMeta = ResourceManager<S_ObjectMeta>();

ObjectCard::ObjectCard() : Card(ObjectCardType) {
	m_sImage = "objects";
}

void ObjectCard::create() {
	std::map<int, S_ObjectMeta> &meta = m_objectMeta.getParsedResources();
	int index = rand() % (int) meta.size();
	strncpy(m_sName, meta[index].name, MAX_CHAR_OBJECT_NAME);
	m_iTileX = meta[index].tilesetX;
	m_iTileY = meta[index].tilesetY;
}

bool ObjectCard::prepareMeta(std::string file) {
	if (!m_objectMeta.setResourceFile(file)) {
		return false;
	}
	m_objectMeta.parseBinaryFile();
	return true;
}
