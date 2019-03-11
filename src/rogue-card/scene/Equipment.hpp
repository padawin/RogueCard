#ifndef __EQUIPMENT_STATE__
#define __EQUIPMENT_STATE__

#include <memory>
#include <string.h>
#include "../game/State.hpp"
#include "../game/types.hpp"
#include "../sdl2/Renderer.hpp"

#define EQUIPMENT_SIZE 8

class EquipmentScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	int m_cursorPosition = 0;
	S_Coordinates m_mCursorPositions[EQUIPMENT_SIZE] = {};

	void _renderBackground() const;
	void _renderCursor();

	void _openListObjects();

	public:
	EquipmentScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
