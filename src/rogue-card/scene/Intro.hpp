#ifndef __INTRO_STATE__
#define __INTRO_STATE__

#include <string.h>
#include <memory>
#include "../game/SceneState.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"

class IntroScene : public SceneState {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	unsigned int m_iCurrentPage = 1;
	std::vector<std::string> m_vIntroText = {};
	Text m_textField;
	void _buildLines();

	public:
	IntroScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
