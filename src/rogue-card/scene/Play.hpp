#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <string.h>
#include <map>
#include "../game/State.hpp"
#include "../game/types.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "../Player.hpp"
#include "../CardDeck.hpp"
#include "../ActionCard.hpp"
#include "../ActionBar.hpp"
#include "../Fight.hpp"

enum PlayCursorPosition {Action, Object1, Object2, Object3, Object4, Floor, NbPositions};

enum ActionType {
	PickAction,
	LootAction,
	FloorAction,
	AttackAction,
	GetFinalGoalAction
};

class PlayScene : public State {
	private:
	Player &m_player;
	std::shared_ptr<SDL2Renderer> m_renderer;
	ActionCard m_actionCard;
	CardDeck m_deck;
	ActionBar m_actionBar;
	Text m_notification;
	Fight m_fight;

	ActionType m_action = PickAction;

	PlayCursorPosition m_cursorPosition = Action;
	std::map<PlayCursorPosition, S_Coordinates> m_mCursorPositions = {};
	std::shared_ptr<Card> m_pickedCard = nullptr;
	std::shared_ptr<Card> m_floorCard = nullptr;

	void _renderBackground() const;
	void _renderNotification() const;
	void _renderHealth() const;
	void _renderCursor();
	void _renderCards();
	void _renderActionCard();

	void _useCardUnderCursor();

	void _pickCard();
	void _lootObject();
	void _action();
	void _useObject(int objectIndex);
	void _changeFloor();

	void _attack(std::shared_ptr<ObjectCard> attackCard = nullptr);
	void _getFinalGoal();

	void _notify(std::string message);

	public:
	PlayScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
