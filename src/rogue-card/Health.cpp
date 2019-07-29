#include "Health.hpp"

Health::Health(int current, int max) {
	m_iCurrent = current;
	m_iMax = max;
}

void Health::operator-=(int value) {
	m_iCurrent -= value;
	if (m_iCurrent < 0) {
		m_iCurrent = 0;
	}
	else if (m_iCurrent > m_iMax) {
		m_iCurrent = m_iMax;
	}
}

int Health::getCurrent() const {
	return m_iCurrent;
}

int Health::getMax() const {
	return m_iMax;
}

void Health::setCurrent(int value) {
	m_iCurrent = value;
}

void Health::setMax(int value) {
	m_iMax = value;
}
