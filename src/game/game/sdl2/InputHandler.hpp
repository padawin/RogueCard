#ifndef __SDL2_INPUT_HANDLER__
#define __SDL2_INPUT_HANDLER__

#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>
#include <vector>
#include <map>
#include "../../Vector2D.hpp"
#include "../../InputHandler.hpp"

class SDL2InputHandler : public InputHandler {
	private:
	/**
	 * Sticks sensibility, the lowest, the more sensible the sticks are.
	 */
	const int M_JOYSTICK_DEADZONE = 10000;

	/**
	 * Code of each stick axis given back by SDL.
	 */
	const int M_LEFT_STICK_X_AXIS = 0;
	const int M_LEFT_STICK_Y_AXIS = 1;
	const int M_RIGHT_STICK_X_AXIS = 3;
	const int M_RIGHT_STICK_Y_AXIS = 4;

	/**
	 * Stores each joystick in a vector of pairs, the first element of the pair
	 * being the joystick id and the second element, the joystick itself
	 */
	std::vector<std::pair<int, SDL_Joystick*>> m_vJoysticks = {};

	/**
	 * Maps joysticks ids and pairs of stick values (one element per stick,
	 * each stick has a value per axis (x and y)
	 * The first being the left stick, the second bein the right stick
	 */
	std::map<int, std::pair<Vector2D, Vector2D>> m_mJoystickAxisValues = {};

	/**
	 * Maps joysticks ids and buttons state, each joystick has a list of
	 * buttons set to true or false depending on if the button is pressed
	 */
	std::map<int, std::vector<bool>> m_mButtonStates = {};

	/**
	 * State of the pressed keys on the keyboard;
	 */

	/**
	 * True if any joystick is initialised. If no joystick is present, the flag
	 * will be set to false.
	 */
	bool m_bJoysticksInitialised = false;

	void _clean();

	/**
	 * Initialises a joystick being at the given index .
	 */
	void _initialiseJoystick(const int index);

	/**
	 * Update the value of a joystick's stick axis.
	 */
	void _setJoystickValue(const int value, Vector2D* axisVector, Vector2DCoord coord);

	/**
	 * Method called when a stick event is fired.
	 */
	void _handleStickEvent(const SDL_Event event);

	/**
	 * Method called when a joystick button is pressed or released.
	 */
	void _handleButtonEvent(const SDL_Event event, const bool isDown);

	/**
	 * Method called when a keyboard key is pressed or released.
	 */
	void _handleKeyEvent(const SDL_Event event, const bool isDown);

	/**
	 * Method called when a joystick is unplugged.
	 */
	void _handleJoystickRemoved();

	protected:
	InputUpdateResult _processEvents();

	public:
	/**
	 * Method to know if any joystick is initialised.
	 */
	bool joysticksInitialised();

	/**
	 * Method to get the X or Y value of the given stick if a given joystick
	 */
	int stickValue(const unsigned long joy, const JoystickControl stick);

	/**
	 * Method to get the state of the given button if a given joystick
	 */
	bool getButtonState(const unsigned long joyIndex, const unsigned long buttonNumber);

	/**
	 * Method to set the state of the given button if a given joystick
	 */
	void setButtonState(const unsigned long joyIndex, const unsigned long button, const bool down);
};

#endif
