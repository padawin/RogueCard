#ifndef __OBJECT_CARD__
#define __OBJECT_CARD__

#include "../common/types.hpp"
#include "../common/ResourceManager.hpp"
#include "Card.hpp"

class ObjectCard : public Card {
	static ResourceManager<S_ObjectMeta> m_objectMeta;
	char m_sName[MAX_CHAR_OBJECT_NAME];

	public:
	ObjectCard();
	void create();
	static bool prepareMeta(std::string file);
};

#endif
