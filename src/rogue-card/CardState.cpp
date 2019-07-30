#include "CardState.hpp"

void CardState::update(StateMachine<CardState> &stateMachine __attribute__((unused))) {
}

int CardState::getX() const {
	return m_iX;
}

int CardState::getY() const {
	return m_iY;
}
