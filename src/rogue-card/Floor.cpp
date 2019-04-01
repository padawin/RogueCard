#include "Floor.hpp"

const int MAX_LEVEL = 16;

int Floor::getLevel() const {
	return m_iLevel;
}

void Floor::setLevel(int level) {
	m_iLevel = level;
}

void Floor::toNextLevel() {
	if (!reachedMaxLevel()) {
		++m_iLevel;
	}
}

void Floor::toPreviousLevel() {
	if (m_iLevel > 1) {
		--m_iLevel;
	}
}

bool Floor::reachedMaxLevel() const {
	return m_iLevel == MAX_LEVEL;
}
