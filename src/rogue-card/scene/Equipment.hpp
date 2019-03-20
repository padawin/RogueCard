#ifndef __EQUIPMENT_STATE__
#define __EQUIPMENT_STATE__

#include <memory>
#include <string.h>
#include "../game/State.hpp"
#include "../game/types.hpp"
#include "../sdl2/Renderer.hpp"
#include "Player.hpp"
#include "ObjectCardCollectionRenderer.hpp"

class EquipmentScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	int m_cursorPosition = 0;
	S_Coordinates m_mCursorPositions[SIZE_EQUIPMENT] = {};
	unsigned int m_equipmentFlags[SIZE_EQUIPMENT] = {};
	ObjectCardCollection m_availableCards;
	ObjectCardCollectionRenderer m_availableCardsRenderer;
	Player &m_player;

	bool m_bSelectViewOpen = false;

	void _renderBackground() const;
	void _renderSelectBackground() const;
	void _renderCursor();

	void _openListObjects();

	public:
	EquipmentScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
