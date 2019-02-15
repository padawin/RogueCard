#ifndef __CARD__
#define __CARD__

enum E_CardType : short {ObjectCardType, FloorCardType, EnemyCardType, None};

class Card {
	protected:
	E_CardType m_type;

	public:
	Card(E_CardType type);
};

#endif
