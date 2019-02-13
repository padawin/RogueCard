#ifndef __GAME_STATE__
#define __GAME_STATE__

#include "../../State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../Player.hpp"

class PlayScene : public State {
	private:
	Player &m_player;
	std::shared_ptr<SDL2Renderer> m_renderer;

	void _renderBackground() const;

	public:
	PlayScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render(const Renderer *renderer);
	std::string getStateID() const;
};

#endif
