#include <iostream>
#include "PickedCard.hpp"
#include "../coordinates.hpp"

const int STEP_X = 12;
const int STEP_Y = 5;

PickedCardState::PickedCardState() : CardState() {
	m_iX = DECK_COORDINATES.x;
	m_iY = DECK_COORDINATES.y;
}

std::string PickedCardState::getStateID() const {
	return "PickedCardState";
}

void PickedCardState::update(StateMachine<CardState> &stateMachine) {
	int endX = PICKED_CARD_COORDINATES.x;
	int endY = PICKED_CARD_COORDINATES.y;
	int oldX = m_iX;
	int oldY = m_iY;
	if (m_iX != endX) {
		m_iX += STEP_X;
		if (oldX < endX && m_iX > endX) {
			m_iX = endX;
		}
	}
	if (m_iY != endY) {
		m_iY += STEP_Y;
		if (oldY < endY && m_iY > endY) {
			m_iY = endY;
		}
	}

	if (m_iX == endX && m_iY == endY) {
		stateMachine.popState();
	}
}
