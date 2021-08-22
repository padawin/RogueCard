#ifndef __INVENTORY_STATE__
#define __INVENTORY_STATE__

#include <string.h>
#include "game/SceneState.hpp"
#include "sdl2/Renderer.hpp"
#include "Player.hpp"
#include "menus/ObjectAction.hpp"
#include "ObjectCardCollectionRenderer.hpp"

#include "Tab.hpp"

class InventoryScene : public SceneState {
	private:
	Tab m_titlesTab;
	Player &m_player;
	std::shared_ptr<SDL2Renderer> m_renderer;
	ObjectAction m_objectActionMenu;
	ObjectCardCollectionRenderer m_cardsRenderer;

	int _getCardIndex() const;

	void _renderBackground() const;
	void _renderCards();

	/* Menu actions */
	void _executeMenuAction(E_ObjectActionMenuItem action, StateMachine<SceneState> &stateMachine);
	void _useObject();
	void _equipObject();
	void _getObjectInfo();
	void _discardObject();
	void _openActionBar();

	public:
	InventoryScene(
		UserActions &userActions,
		Player &player,
		std::shared_ptr<SDL2Renderer> renderer
	);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
