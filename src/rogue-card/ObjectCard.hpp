#ifndef __OBJECT_CARD__
#define __OBJECT_CARD__

#include <memory>
#include "../common/types.hpp"
#include "../common/ResourceManager.hpp"
#include "../common/ElementalEffects.hpp"
#include "Card.hpp"
#include "../sdl2/Text.hpp"

const unsigned char FLAG_USABLE =        0x01;
const unsigned char FLAG_EQUIPABLE =     0x02;
const unsigned char FLAG_CONSUMABLE =    0x04;
const unsigned char FLAG_APPLY_ON_SELF = 0x08;

const unsigned char FLAG_EQUIPMENT_HEAD =      0x01;
const unsigned char FLAG_EQUIPMENT_SHOULDERS = 0x02;
const unsigned char FLAG_EQUIPMENT_HANDS =     0x04;
const unsigned char FLAG_EQUIPMENT_CHEST =     0x08;
const unsigned char FLAG_EQUIPMENT_BELT =      0x10;
const unsigned char FLAG_EQUIPMENT_FEET =      0x20;
const unsigned char FLAG_EQUIPMENT_WEAPON =    0x40;
const unsigned char FLAG_EQUIPMENT_SHIELD =    0x80;

const unsigned char FLAG_EQUIPMENT_ARMOR = FLAG_EQUIPMENT_HEAD
										 | FLAG_EQUIPMENT_SHOULDERS
										 | FLAG_EQUIPMENT_HANDS
										 | FLAG_EQUIPMENT_CHEST
										 | FLAG_EQUIPMENT_BELT
										 | FLAG_EQUIPMENT_FEET
										 | FLAG_EQUIPMENT_SHIELD;

const int MAX_QUANTITY = 10;

class ObjectCard : public Card {
	static ResourceManager<S_ObjectMeta> m_objectMeta;
	char m_sName[MAX_CHAR_OBJECT_NAME];

	int m_iMetaIndex = -1;
	unsigned char m_iFlags = 0;
	unsigned char m_iEquipableFlags = 0;

	int m_iQuantity = 1;

	Text m_quantityText;

	S_CardStats m_sStats = {};
	ElementalEffects m_elementEffects;

	void _setFlags(const S_ObjectMeta &meta);
	void _setEquipableFlags(const S_ObjectMeta &meta);

	void _setQuantityText();

	public:
	ObjectCard();
	void create();
	void createFromMeta(int metaIndex);
	static bool prepareMeta(std::string file);

	void render(SDL_Renderer *renderer, int x, int y);

	int getMetaIndex() const;
	const char* getName() const;

	bool hasFlags(unsigned int flags) const;
	bool hasEquipableFlag(unsigned int flag) const;
	unsigned int getEquipableflags() const;
	bool isUsable() const;
	bool isConsumable() const;
	bool canBeEquipped() const;
	bool applyOnSelf() const;
	int getQuantity() const;
	void setQuantity(int quantity);
	bool reachedMaxQuantity() const;
	void addInstance();
	void consume();

	S_CardStats getStats() const;
	ElementalEffects getElementalEffects();

	bool isSameAs(std::shared_ptr<ObjectCard> card) const;
};

#endif
