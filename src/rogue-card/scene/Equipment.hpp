#ifndef __EQUIPMENT_STATE__
#define __EQUIPMENT_STATE__

#include <memory>
#include <string.h>
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"

class EquipmentScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;

	void _renderBackground() const;

	public:
	EquipmentScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
