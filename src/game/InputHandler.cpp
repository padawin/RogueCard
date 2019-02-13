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

bool InputHandler::getKeyState(const int key) {
	return m_mKeysStates[key];
}

void InputHandler::setKeyState(const int key, bool value) {
	m_mKeysStates[key] = value;
}
