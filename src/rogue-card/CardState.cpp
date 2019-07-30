#include "CardState.hpp"
#include "Card.hpp"

void CardState::update(StateMachine<CardState> &stateMachine __attribute__((unused))) {
}

void CardState::render(SDL_Renderer *renderer, Card &card, int x, int y) {
	card._renderCard(renderer, x, y);
}

int CardState::getX() const {
	return m_iX;
}

int CardState::getY() const {
	return m_iY;
}
