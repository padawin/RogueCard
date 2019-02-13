#ifndef __GAME_STATE__
#define __GAME_STATE__

#include "../../State.hpp"
#include "../../renderer/Renderer.hpp"
#include "../Player.hpp"

class PlayScene : public State {
	private:
	Player &m_player;

	public:
	PlayScene(UserActions &userActions, Player &player);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render(const Renderer *renderer);
	std::string getStateID() const;
};

#endif
