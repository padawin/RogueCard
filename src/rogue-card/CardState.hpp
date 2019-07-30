#ifndef __CARD_STATE__
#define __CARD_STATE__

#include "State.hpp"
#include "StateMachine.hpp"

class CardState : public State {
	protected:
	int m_iX = 0;
	int m_iY = 0;

	public:
	virtual void update(StateMachine<CardState> &stateMachine);
	int getX() const;
	int getY() const;
};

#endif
