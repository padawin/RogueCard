#include "ObjectCard.hpp"

const int BODY_PART_HEAD =       0x01;
const int BODY_PART_SHOULDERS =  0x02;
const int BODY_PART_LEFT_HAND =  0x04;
const int BODY_PART_RIGHT_HAND = 0x08;
const int BODY_PART_CHEST =      0x10;
const int BODY_PART_LEGS =       0x20;
const int BODY_PART_FEET =       0x40;

ResourceManager<S_ObjectMeta> ObjectCard::m_objectMeta = ResourceManager<S_ObjectMeta>();

ObjectCard::ObjectCard() : Card(ObjectCardType) {
	m_sImage = "objects";
}

void ObjectCard::create() {
	int index = rand() % (int) m_objectMeta.getParsedResources().size();
	createFromMeta(index);
}

void ObjectCard::createFromMeta(int metaIndex) {
	std::map<int, S_ObjectMeta> &meta = m_objectMeta.getParsedResources();
	m_iMetaIndex = metaIndex;
	strncpy(m_sName, meta[metaIndex].name, MAX_CHAR_OBJECT_NAME);
	m_iTileX = meta[metaIndex].tilesetX;
	m_iTileY = meta[metaIndex].tilesetY;
	_setFlags(meta[metaIndex]);
	if (meta[metaIndex].equipable) {
		_setEquipableFlags(meta[metaIndex]);
	}
}

void ObjectCard::_setFlags(const S_ObjectMeta &meta) {
	if (meta.usable) {
		m_iFlags |= FLAG_USABLE;
	}
	if (meta.consumable) {
		m_iFlags |= FLAG_CONSUMABLE;
	}
	if (meta.equipable) {
		m_iFlags |= FLAG_EQUIPABLE;
	}
	if (meta.applyOnSelf) {
		m_iFlags |= FLAG_APPLY_ON_SELF;
	}
}

void ObjectCard::_setEquipableFlags(const S_ObjectMeta &meta) {
	if (meta.equipHead) {
		m_iEquipableFlags |= BODY_PART_HEAD;
	}
	if (meta.equipShoulders) {
		m_iEquipableFlags |= BODY_PART_SHOULDERS;
	}
	if (meta.equipLeftHand) {
		m_iEquipableFlags |= BODY_PART_LEFT_HAND;
	}
	if (meta.equipRightHand) {
		m_iEquipableFlags |= BODY_PART_RIGHT_HAND;
	}
	if (meta.equipChest) {
		m_iEquipableFlags |= BODY_PART_CHEST;
	}
	if (meta.equipLegs) {
		m_iEquipableFlags |= BODY_PART_LEGS;
	}
	if (meta.equipFeet) {
		m_iEquipableFlags |= BODY_PART_FEET;
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

bool ObjectCard::hasFlags(int flags) const {
	return (m_iFlags & flags) == flags;
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
