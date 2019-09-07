#include <memory>
#include "ObjectCard.hpp"

const int CARD_QUANTITY_LOW_X = 32;
const int CARD_QUANTITY_HIGH_X = 23;
const int CARD_QUANTITY_Y = 46;

ContentMeta<S_ObjectMeta> ObjectCard::m_objectMeta = ContentMeta<S_ObjectMeta>();

ObjectCard::ObjectCard(const char *id) :
	Card(ObjectCardType),
	m_quantityText(Text()),
	m_elementEffects(ElementalEffects())
{
	strncpy(m_sMetaID, id, MAX_CHAR_CARD_ID - 1);
	m_sImage = "objects";
	m_quantityText.setFont("font-black");
}

void ObjectCard::create() {
	S_ObjectMeta meta = m_objectMeta.getFromID(m_sMetaID);
	m_iMetaIndex = m_objectMeta.getIndex(m_sMetaID);
	strncpy(m_sName, meta.name, MAX_CHAR_OBJECT_NAME);
	m_iTileX = meta.tilesetX;
	m_iTileY = meta.tilesetY;
	m_sStats = meta.stats;
	m_elementEffects = meta.elementalEffects;
	_setFlags(meta);
}

void ObjectCard::render(SDL_Renderer *renderer, int x, int y) {
	Card::render(renderer, x, y);
	if (isConsumable()) {
		int xPos = m_quantityText.getText().length() == 2 ? CARD_QUANTITY_HIGH_X : CARD_QUANTITY_LOW_X;
		m_quantityText.render(
			renderer,
			getX(x) + xPos,
			getY(y) + CARD_QUANTITY_Y
		);
	}
}

int ObjectCard::getMetaIndex() const {
	return m_objectMeta.getIndex(m_sMetaID);
}

void ObjectCard::_setFlags(const S_ObjectMeta &meta) {
	_setEquipableFlags(meta);
	if (meta.usable) {
		m_iFlags |= FLAG_USABLE;
	}
	if (meta.consumable) {
		m_iFlags |= FLAG_CONSUMABLE;
	}
	if (m_iEquipableFlags) {
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
	return m_objectMeta.prepare(file);
}

const char* ObjectCard::getName() const {
	return m_sName;
}

const char* ObjectCard::getID() const {
	return m_sMetaID;
}

bool ObjectCard::hasFlags(unsigned int flags) const {
	return (m_iFlags & flags) == flags;
}

bool ObjectCard::hasEquipableFlag(unsigned int flag) const {
	return m_iEquipableFlags & flag;
}

unsigned int ObjectCard::getEquipableflags() const {
	return m_iEquipableFlags;
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

int ObjectCard::getQuantity() const {
	return m_iQuantity;
}

void ObjectCard::setQuantity(int quantity) {
	m_iQuantity = quantity;
	_setQuantityText();
}

bool ObjectCard::reachedMaxQuantity() const {
	return !isConsumable() || m_iQuantity == MAX_QUANTITY;
}

void ObjectCard::addInstance() {
	if (!reachedMaxQuantity()) {
		++m_iQuantity;
		_setQuantityText();
	}
}

void ObjectCard::consume() {
	--m_iQuantity;
	_setQuantityText();
}

S_CardStats ObjectCard::getStats() const {
	return m_sStats;
}

ElementalEffects ObjectCard::getElementalEffects() {
	return m_elementEffects;
}

bool ObjectCard::isSameAs(std::shared_ptr<ObjectCard> card) const {
	int compRes = strncmp(getName(), card->getName(), MAX_CHAR_OBJECT_NAME);
	return compRes == 0;
}

void ObjectCard::_setQuantityText() {
	char text[3];
	sprintf(text, "%d", m_iQuantity);
	m_quantityText.setText(text);
}
