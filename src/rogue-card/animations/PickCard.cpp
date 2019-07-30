#include "PickCard.hpp"

const int START_X = 16;
const int START_Y = 16;
const int END_X = 138;
const int END_Y = 64;

const int STEP_X = 12;
const int STEP_Y = 5;

void PickCardAnimation::init() {
	m_iX = START_X;
	m_iY = START_Y;
	m_bRunning = true;
}

void PickCardAnimation::update() {
	if (!m_bRunning) {
		return;
	}
	int oldX = m_iX;
	int oldY = m_iY;
	if (m_iX != END_X) {
		m_iX += STEP_X;
		if (oldX < END_X && m_iX > END_X) {
			m_iX = END_X;
		}
	}
	if (m_iY != END_Y) {
		m_iY += STEP_Y;
		if (oldY < END_Y && m_iY > END_Y) {
			m_iY = END_Y;
		}
	}

	if (m_iX == END_X && m_iY == END_Y) {
		m_bRunning = false;
	}
}

bool PickCardAnimation::running() const {
	return m_bRunning;
}

int PickCardAnimation::getX() const {
	return m_iX;
}

int PickCardAnimation::getY() const {
	return m_iY;
}
