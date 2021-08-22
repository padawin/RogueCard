#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

#include <map>

enum JoystickControl {LEFT_STICK_X, LEFT_STICK_Y, RIGHT_STICK_X, RIGHT_STICK_Y, NULL_CONTROL};

enum InputType {KEYBOARD_KEY, MOUSE_BUTTON, CONTROLLER_BUTTON, CONTROLLER_STICK, NULL_TYPE};

enum InputUpdateResult {QUIT, HAS_EVENT, HAS_NO_EVENT};

enum KeyState {KEY_PRESSED, KEY_DOWN, KEY_RELEASED};

class InputHandler {
	public:
	virtual ~InputHandler() {}

	virtual bool isKeyPressed(const int key) = 0;
	virtual bool isKeyDown(const int key) = 0;
	virtual bool isKeyReleased(const int key) = 0;

	virtual bool isJoystickButtonPressed(const int joystickID, const int button) = 0;
	virtual bool isJoystickButtonDown(const int joystickID, const int button) = 0;
	virtual bool isJoystickButtonReleased(const int joystickID, const int button) = 0;

	virtual bool isMouseButtonPressed(const int button) = 0;
	virtual bool isMouseButtonDown(const int button) = 0;
	virtual bool isMouseButtonReleased(const int button) = 0;

	virtual void setup() { }
	virtual void reset() { }
};

#endif
