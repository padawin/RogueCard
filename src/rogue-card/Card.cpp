#include "Card.hpp"
#include "../sdl2/TextureManager.hpp"

Card::Card(E_CardType type) : m_type(type) {

}

E_CardType Card::getType() const {
	return m_type;
}

void Card::setState(CardState* state) {
	m_stateMachine.changeState(state);
}

void Card::render(SDL_Renderer *renderer, int x, int y) {
	x = getX(x);
	y = getY(y);
	TextureManager::Instance()->draw(
		"card", x, y, CARD_WIDTH, CARD_HEIGHT, renderer
	);
	TextureManager::Instance()->drawFrame(
		m_sImage,
		x + CARD_IMAGE_POSITION_X,
		y + CARD_IMAGE_POSITION_Y,
		CARD_IMAGE_WIDTH,
		CARD_IMAGE_HEIGHT,
		m_iTileX,
		m_iTileY,
		renderer
	);
}

void Card::update() {
	m_stateMachine.update();
}

int Card::getX(int defaultX) const {
	CardState* state = m_stateMachine.getCurrentState();
	if (state != nullptr) {
		return state->getX();
	}
	return defaultX;
}

int Card::getY(int defaultY) const {
	CardState* state = m_stateMachine.getCurrentState();
	if (state != nullptr) {
		return state->getY();
	}
	return defaultY;
}

bool Card::ready() const {
	CardState* state = m_stateMachine.getCurrentState();
	return state == nullptr;
}
