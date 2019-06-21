#ifndef __PLAYER_STATS_STATE__
#define __PLAYER_STATS_STATE__

#include <string.h>
#include <memory>
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"

class PlayerStatsScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;

	void _renderBackground() const;

	public:
	PlayerStatsScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
