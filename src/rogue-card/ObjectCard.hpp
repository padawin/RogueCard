#ifndef __OBJECT_CARD__
#define __OBJECT_CARD__

#include "../common/types.hpp"
#include "../common/ResourceManager.hpp"
#include "Card.hpp"

const int FLAG_USABLE =        0x01;
const int FLAG_EQUIPABLE =     0x02;
const int FLAG_CONSUMABLE =    0x04;
const int FLAG_APPLY_ON_SELF = 0x08;

const unsigned char FLAG_EQUIPMENT_HEAD =      0x01;
const unsigned char FLAG_EQUIPMENT_SHOULDERS = 0x02;
const unsigned char FLAG_EQUIPMENT_HANDS =     0x04;
const unsigned char FLAG_EQUIPMENT_CHEST =     0x08;
const unsigned char FLAG_EQUIPMENT_BELT =      0x10;
const unsigned char FLAG_EQUIPMENT_FEET =      0x20;
const unsigned char FLAG_EQUIPMENT_WEAPON =    0x40;
const unsigned char FLAG_EQUIPMENT_SHIELD =    0x80;

class ObjectCard : public Card {
	static ResourceManager<S_ObjectMeta> m_objectMeta;
	char m_sName[MAX_CHAR_OBJECT_NAME];

	int m_iMetaIndex = -1;
	unsigned char m_iFlags = 0;
	unsigned char m_iEquipableFlags = 0;

	void _setFlags(const S_ObjectMeta &meta);
	void _setEquipableFlags(const S_ObjectMeta &meta);

	public:
	ObjectCard();
	void create();
	void createFromMeta(int metaIndex);
	static bool prepareMeta(std::string file);

	int getMetaIndex() const;
	const char* getName() const;

	bool hasFlags(int flags) const;
	bool isUsable() const;
	bool isConsumable() const;
	bool canBeEquipped() const;
	bool applyOnSelf() const;
};

#endif
