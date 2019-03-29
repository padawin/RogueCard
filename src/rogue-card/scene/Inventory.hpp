#ifndef __INVENTORY_STATE__
#define __INVENTORY_STATE__

#include <string.h>
#include "../game/types.hpp"
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../Player.hpp"
#include "../ActionBar.hpp"
#include "../menus/ObjectAction.hpp"
#include "../ObjectCardCollectionRenderer.hpp"

class InventoryScene : public State {
	private:
	Player &m_player;
	std::shared_ptr<SDL2Renderer> m_renderer;
	ObjectAction m_objectActionMenu;
	ObjectCardCollectionRenderer m_cardsRenderer;
	ActionBar &m_actionBar;

	int _getCardIndex() const;

	void _renderBackground() const;
	void _renderCards();

	/* Menu actions */
	bool _executeMenuAction(E_ObjectActionMenuItem action, StateMachine &stateMachine);
	void _useObject();
	void _equipObject();
	void _getObjectInfo();
	void _discardObject();
	void _openActionBar();

	public:
	InventoryScene(
		UserActions &userActions,
		ActionBar &m_actionBar,
		Player &player,
		std::shared_ptr<SDL2Renderer> renderer
	);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
