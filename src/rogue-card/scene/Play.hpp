#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <string.h>
#include <map>
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../Player.hpp"
#include "../CardDeck.hpp"

enum CursorPosition {Action, Object1, Object2, Object3, Object4, Floor, NbPositions};

const int MAX_OBJECTS = 4;

class PlayScene : public State {
	private:
	Player &m_player;
	std::shared_ptr<SDL2Renderer> m_renderer;
	CardDeck m_deck;

	CursorPosition m_cursorPosition = Action;
	std::map<CursorPosition, std::pair<int, int>> m_mCursorPositions = {};
	std::shared_ptr<Card> m_pickedCard = nullptr;
	std::shared_ptr<Card> m_objectCards[MAX_OBJECTS] = {nullptr, nullptr, nullptr, nullptr};
	std::shared_ptr<Card> m_floorCard = nullptr;

	void _renderBackground() const;
	void _renderCursor();
	void _renderCards();
	void _useCardUnderCursor();

	void _pickCard();
	void _pickObject();
	void _action();
	void _useObject(int objectIndex);
	void _changeFloor();

	void _attack();

	void _notify(std::string message) const;

	public:
	PlayScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
