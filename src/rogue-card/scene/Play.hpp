#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <string.h>
#include <map>
#include "../game/SceneState.hpp"
#include "../game/types.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "../Player.hpp"
#include "../CardDeck.hpp"
#include "../ActionCard.hpp"
#include "../ProgressBar.hpp"
#include "../Fight.hpp"

enum PlayCursorPosition {Action, Object1, Object2, Object3, Object4, Floor, NbPositions};

enum ActionType {
	PickAction,
	LootAction,
	DiscardAction,
	FloorAction,
	AttackAction,
	RunawayAction,
	GetFinalGoalAction,
};

// Yuck
// first element is the previous action,
// second element is the next action
const int POSSIBLE_ACTIONS[][2] = {
	{(int) PickAction, (int) PickAction},
	{(int) DiscardAction, (int) DiscardAction},
	{(int) LootAction, (int) LootAction},
	{(int) FloorAction, (int) FloorAction},
	{(int) RunawayAction, (int) RunawayAction},
	{(int) AttackAction, (int) AttackAction},
	{(int) GetFinalGoalAction, (int) GetFinalGoalAction}
};

class PlayScene : public SceneState {
	private:
	bool m_bShowIntro = false;
	Player m_player;
	std::shared_ptr<SDL2Renderer> m_renderer;
	ActionCard m_actionCard;
	CardDeck m_deck;
	Text m_notification;
	Fight m_fight;

	ProgressBar m_progressBar;

	ActionType m_action = PickAction;

	PlayCursorPosition m_cursorPosition = Action;
	std::map<PlayCursorPosition, S_Coordinates> m_mCursorPositions = {};
	std::shared_ptr<Card> m_pickedCard = nullptr;
	std::shared_ptr<Card> m_floorCard = nullptr;

	bool _updateCards() const;
	void _handleControls(StateMachine<SceneState> &stateMachine);
	void _monitorStates(StateMachine<SceneState> &stateMachine);

	void _renderBackground() const;
	void _renderNotification() const;
	void _renderCursor();
	void _renderCards();
	void _renderActionCard();

	void _updateHealthBar();

	void _useCardUnderCursor();

	void _pickCard();
	void _lootObject();
	void _action();
	void _useObject(int objectIndex);
	void _changeFloor();
	void _discardCard();
	void _runaway();

	void _attack(std::shared_ptr<ObjectCard> attackCard = nullptr);
	void _getFinalGoal();

	void _notify(std::string message);

	void _setNextAction(int way);

	public:
	PlayScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer, Player player=Player());
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
