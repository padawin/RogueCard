#ifndef __OBJECT_CARD__
#define __OBJECT_CARD__

#include "../common/types.hpp"
#include "../common/ResourceManager.hpp"
#include "Card.hpp"

const int FLAG_USABLE =        0x01;
const int FLAG_EQUIPABLE =     0x02;
const int FLAG_CONSUMABLE =    0x04;
const int FLAG_APPLY_ON_SELF = 0x08;

class ObjectCard : public Card {
	static ResourceManager<S_ObjectMeta> m_objectMeta;
	char m_sName[MAX_CHAR_OBJECT_NAME];

	int m_iMetaIndex = -1;
	char m_iFlags = 0;
	char m_iEquipableFlags = 0;

	void _setFlags(const S_ObjectMeta &meta);
	void _setEquipableFlags(const S_ObjectMeta &meta);

	public:
	ObjectCard();
	void create();
	static bool prepareMeta(std::string file);

	const char* getName() const;

	bool hasFlags(int flags) const;
	bool isUsable() const;
	bool isConsumable() const;
	bool canBeEquipped() const;
	bool applyOnSelf() const;
};

#endif
