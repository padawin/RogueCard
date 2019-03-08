#include "ObjectCard.hpp"

const unsigned char FLAG_EQUIPMENT_HEAD =      0x01;
const unsigned char FLAG_EQUIPMENT_SHOULDERS = 0x02;
const unsigned char FLAG_EQUIPMENT_HANDS =     0x04;
const unsigned char FLAG_EQUIPMENT_CHEST =     0x08;
const unsigned char FLAG_EQUIPMENT_BELT =      0x10;
const unsigned char FLAG_EQUIPMENT_FEET =      0x20;
const unsigned char FLAG_EQUIPMENT_WEAPON =    0x40;
const unsigned char FLAG_EQUIPMENT_SHIELD =    0x80;

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

int ObjectCard::getMetaIndex() const {
	return m_iMetaIndex;
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
	if (meta.isHelm) {
		m_iEquipableFlags |= FLAG_EQUIPMENT_HEAD;
	}
	if (meta.isShoulders) {
		m_iEquipableFlags |= FLAG_EQUIPMENT_SHOULDERS;
	}
	if (meta.isGlove) {
		m_iEquipableFlags |= FLAG_EQUIPMENT_HANDS;
	}
	if (meta.isChest) {
		m_iEquipableFlags |= FLAG_EQUIPMENT_CHEST;
	}
	if (meta.isBelt) {
		m_iEquipableFlags |= FLAG_EQUIPMENT_BELT;
	}
	if (meta.isShoe) {
		m_iEquipableFlags |= FLAG_EQUIPMENT_FEET;
	}
	if (meta.isWeapon) {
		m_iEquipableFlags |= FLAG_EQUIPMENT_WEAPON;
	}
	if (meta.isShield) {
		m_iEquipableFlags |= FLAG_EQUIPMENT_SHIELD;
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
