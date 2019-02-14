#ifndef __GAME__
#define __GAME__

#include "StateMachine.hpp"
#include "renderer/Renderer.hpp"
#include "InputHandler.hpp"
#include <memory>
#include <limits.h>

class Game {
	private:
	bool m_bIsRunning = false;
	char m_sBinaryPath[PATH_MAX];
	StateMachine m_stateMachine;
	std::shared_ptr<Renderer> m_renderer;
	std::shared_ptr<InputHandler> m_inputHandler;

	public:
	Game(
		StateMachine stateMachine,
		std::shared_ptr<Renderer> renderer,
		std::shared_ptr<InputHandler> inputHandler
	);
	~Game() { }
	bool init(char binaryPath[PATH_MAX]);
	void mainLoop();
	void frame();
	void shutdown() const;
	const char* getBinaryPath() const;
};

#endif
