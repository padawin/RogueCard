#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

#include <map>

enum JoystickControl {LEFT_STICK_X, LEFT_STICK_Y, RIGHT_STICK_X, RIGHT_STICK_Y, NULL_CONTROL};

enum InputType {KEYBOARD_KEY, CONTROLLER_BUTTON, CONTROLLER_STICK, NULL_TYPE};

enum InputUpdateResult {QUIT, HAS_EVENT, HAS_NO_EVENT};

class InputHandler {
	protected:
	/**
	 * State of the pressed keys on the keyboard;
	 */

	/**
	 * Maps joysticks ids and buttons state, each joystick has a list of
	 * buttons set to true or false depending on if the button is pressed
	 * the first bool is true if the button is pressed, as soon as this value is
	 * tested, it becomes false. The second bool is true if the button if down,
	 * it becomes false if the button is released.
	 */
	std::map<int, std::pair<bool, bool>> m_mKeysStates = {};

	virtual InputUpdateResult _processEvents() = 0;

	/**
	 * Method called when a keyboard key is pressed or released.
	 */
	virtual void _handleKeyEvent(const int key, const bool isDown);

	public:
	virtual ~InputHandler() {}

	/**
	 * Method used to process the events poll.
	 */
	InputUpdateResult update();

	/**
	 * Returns true if the provided key (from the keyboard) is pressed, false
	 * otherwise
	 */
	bool isKeyPressed(const int key);

	/**
	 * Returns true if the provided key (from the keyboard) is down, false
	 * otherwise
	 */
	bool isKeyDown(const int key);

	/**
	 * Method to set the state of a given key
	 */
	void setKeyState(const int key, bool value);
};

#endif
