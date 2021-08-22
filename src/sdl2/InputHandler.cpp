#include "InputHandler.hpp"
#include <iostream>

void SDL2InputHandler::setup() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_JOYAXISMOTION:
				_handleStickEvent(event);
				break;
			case SDL_JOYBUTTONDOWN:
				_handleJoystickButtonEvent(event, true);
				break;
			case SDL_JOYBUTTONUP:
				_handleJoystickButtonEvent(event, false);
				break;
			case SDL_JOYDEVICEADDED:
				_initialiseJoystick(event.cdevice.which);
				break;
			case SDL_JOYDEVICEREMOVED:
				_handleJoystickRemoved();
				break;
			case SDL_KEYDOWN:
				_handleKeyEvent(event, true);
				break;
			case SDL_KEYUP:
				_handleKeyEvent(event, false);
				break;
			default:
				break;
		}
	}
}

void SDL2InputHandler::reset() {
	m_mKeysStates.clear();
	for (auto joystickID = m_mJoystickButtonStates.cbegin(); joystickID != m_mJoystickButtonStates.cend();) {
		m_mJoystickButtonStates[joystickID->first].clear();
	}
}

/**
 * Set a joystick stick value depending on which stick is manipulated.
 */
void SDL2InputHandler::_handleStickEvent(const SDL_Event event) {
	int joystickID = event.jaxis.which;
	// left stick move left or right
	if (event.jaxis.axis == M_LEFT_STICK_X_AXIS) {
		_setJoystickValue(event.jaxis.value, &m_mJoystickAxisValues[joystickID].first, VECTOR_X);
	}
	// left stick move up or down
	if (event.jaxis.axis == M_LEFT_STICK_Y_AXIS) {
		_setJoystickValue(event.jaxis.value, &m_mJoystickAxisValues[joystickID].first, VECTOR_Y);
	}
	// right stick move left or right
	if (event.jaxis.axis == M_RIGHT_STICK_X_AXIS) {
		_setJoystickValue(event.jaxis.value, &m_mJoystickAxisValues[joystickID].second, VECTOR_X);
	}
	// right stick move up or down
	if (event.jaxis.axis == M_RIGHT_STICK_Y_AXIS) {
		_setJoystickValue(event.jaxis.value, &m_mJoystickAxisValues[joystickID].second, VECTOR_Y);
	}
}

/**
 * Change the state of a pressed or released joystick button.
 */
void SDL2InputHandler::_handleJoystickButtonEvent(const SDL_Event event, const bool isDown) {
	int joystickID = event.jaxis.which;
	if (isDown) {
		if (m_mJoystickButtonStates[joystickID].find(event.jbutton.button) == m_mJoystickButtonStates[joystickID].end()) {
			m_mJoystickButtonStates[joystickID][event.jbutton.button] = KeyState::KEY_PRESSED;
		}
		else if (m_mJoystickButtonStates[joystickID][event.jbutton.button] == KeyState::KEY_PRESSED) {
			m_mJoystickButtonStates[joystickID][event.jbutton.button] = KeyState::KEY_DOWN;
		}
	}
	else {
		m_mJoystickButtonStates[joystickID][event.jbutton.button] = KEY_RELEASED;
	}
}

/**
 * Change the state of a pressed or released keyboard key.
 */
void SDL2InputHandler::_handleKeyEvent(const SDL_Event event, const bool isDown) {
	if (isDown) {
		m_mKeysStates[event.key.keysym.scancode] = event.key.repeat ? KEY_DOWN : KEY_PRESSED;
	}
	else {
		m_mKeysStates[event.key.keysym.scancode] = KEY_RELEASED;
	}
}

/**
 * If a joystick is removed, completely clean the list of joysticks
 */
void SDL2InputHandler::_handleJoystickRemoved() {
	_clean();
}

/**
 * Set the value 1, -1 or 0 to a stick axis vector depending on the position of
 * the stick. 1 and -1 being on either side of the dead zone and 0 being within
 * the dead zone (stick considered as in neutral position).
 */
void SDL2InputHandler::_setJoystickValue(const int value, Vector2D* axisVector, Vector2DCoord coord) {
	if (value > M_JOYSTICK_DEADZONE) {
		axisVector->set(coord, 1.0);
	}
	else if (value < -M_JOYSTICK_DEADZONE) {
		axisVector->set(coord, -1.0);
	}
	else {
		axisVector->set(coord, 0.0);
	}
}

/**
 * Initialises a joystick, creates the maps and vectors to monitor its buttons
 * and sticks.
 */
void SDL2InputHandler::_initialiseJoystick(const int indexJoystick) {
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	SDL_Joystick* joy = SDL_JoystickOpen(indexJoystick);
	if (!joy) {
		std::cout << SDL_GetError();
	}
	else {
		int joystickID = SDL_JoystickInstanceID(joy);
		m_vJoysticks.push_back(std::make_pair(joystickID, joy));
		// for each joystick store their stick axises values
		m_mJoystickAxisValues[joystickID] = std::make_pair(
			Vector2D(0,0),
			Vector2D(0,0)
		);
		m_mJoystickButtonStates[joystickID] = {};
		m_bJoysticksInitialised = true;
		std::cout << "Initialised "<< m_vJoysticks.size() << " joystick(s)\n";
	}
}

/**
 * Clears every initialised joysticks.
 */
void SDL2InputHandler::_clean() {
	if (m_bJoysticksInitialised) {
		unsigned long nbJoysticks = m_vJoysticks.size();
		for (unsigned long i = 0; i < nbJoysticks; i++){
			SDL_JoystickClose(m_vJoysticks[i].second);
			m_vJoysticks[i].second = NULL;
		}

		std::cout << "Cleaned "<< m_vJoysticks.size() << " joystick(s)\n";
		m_vJoysticks.clear();
		m_mJoystickButtonStates.clear();
		m_mJoystickAxisValues.clear();

		m_bJoysticksInitialised = false;
	}
}

bool SDL2InputHandler::isKeyPressed(const int key) {
	return m_mKeysStates.find(key) != m_mKeysStates.end() && m_mKeysStates[key] == KeyState::KEY_PRESSED;
}

bool SDL2InputHandler::isKeyDown(const int key) {
	return m_mKeysStates.find(key) != m_mKeysStates.end() && m_mKeysStates[key] == KeyState::KEY_DOWN;
}

bool SDL2InputHandler::isKeyReleased(const int key) {
	return m_mKeysStates.find(key) != m_mKeysStates.end() && m_mKeysStates[key] == KeyState::KEY_RELEASED;
}

bool SDL2InputHandler::isJoystickButtonPressed(const int joystickID, const int button) {
	return m_mJoystickButtonStates.find(joystickID) != m_mJoystickButtonStates.end() &&
		m_mJoystickButtonStates[joystickID].find(button) != m_mJoystickButtonStates[joystickID].end() &&
		m_mJoystickButtonStates[joystickID][button] == KeyState::KEY_PRESSED;
}

bool SDL2InputHandler::isJoystickButtonDown(const int joystickID, const int button) {
	return m_mJoystickButtonStates.find(joystickID) != m_mJoystickButtonStates.end() &&
		m_mJoystickButtonStates[joystickID].find(button) != m_mJoystickButtonStates[joystickID].end() &&
		m_mJoystickButtonStates[joystickID][button] == KeyState::KEY_DOWN;
}

bool SDL2InputHandler::isJoystickButtonReleased(const int joystickID, const int button) {
	return m_mJoystickButtonStates.find(joystickID) != m_mJoystickButtonStates.end() &&
		m_mJoystickButtonStates[joystickID].find(button) != m_mJoystickButtonStates[joystickID].end() &&
		m_mJoystickButtonStates[joystickID][button] == KeyState::KEY_RELEASED;
}

bool SDL2InputHandler::isMouseButtonPressed(const int button __attribute__((unused))) {
	return false;
}

bool SDL2InputHandler::isMouseButtonDown(const int button __attribute__((unused))) {
	return false;
}

bool SDL2InputHandler::isMouseButtonReleased(const int button __attribute__((unused))) {
	return false;
}
