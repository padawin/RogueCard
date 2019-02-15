#include "InputHandler.hpp"

/**
 * Processes the SDL events and acts accordingly depending on the event type.
 */
InputUpdateResult InputHandler::update() {
	return _processEvents();
}

/**
 * Change the state of a pressed or released keyboard key.
 */
void InputHandler::_handleKeyEvent(const int key, const bool isDown) {
	setKeyState(key, isDown);
}

bool InputHandler::isKeyPressed(const int key) {
	bool ret = m_mKeysStates[key].first;
	m_mKeysStates[key].first = false;
	return ret;
}

bool InputHandler::isKeyDown(const int key) {
	return m_mKeysStates[key].second;
}

void InputHandler::setKeyState(const int key, bool value) {
	m_mKeysStates[key] = std::make_pair(value, value);
}
