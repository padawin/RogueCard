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
	if (meta[index].usable) {
		m_iFlags |= FLAG_USABLE;
	}
	if (meta[index].consumable) {
		m_iFlags |= FLAG_CONSUMABLE;
	}
	if (meta[index].equipable) {
		m_iFlags |= FLAG_EQUIPABLE;
	}
	if (meta[index].applyOnSelf) {
		m_iFlags |= FLAG_APPLY_ON_SELF;
	}
}

bool ObjectCard::prepareMeta(std::string file) {
	if (!m_objectMeta.setResourceFile(file)) {
		return false;
	}
	m_objectMeta.parseBinaryFile();
	return true;
}

const char* ObjectCard::getName() const {
	return m_sName;
}

bool ObjectCard::isUsable() const {
	return m_iFlags & FLAG_USABLE;
}

bool ObjectCard::isConsumable() const {
	return m_iFlags & FLAG_CONSUMABLE;
}

bool ObjectCard::canBeEquipped() const {
	return m_iFlags & FLAG_EQUIPABLE;
}

bool ObjectCard::applyOnSelf() const {
	return m_iFlags & FLAG_APPLY_ON_SELF;
}
