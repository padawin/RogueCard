#include "Game.hpp"
#include <string.h>

std::string Game::m_sBinaryPath = "";

Game::Game(
	StateMachine<SceneState> stateMachine,
	std::shared_ptr<Renderer> renderer,
	std::shared_ptr<InputHandler> inputHandler
) :
	m_stateMachine(stateMachine),
	m_renderer(renderer),
	m_inputHandler(inputHandler)
{
}

bool Game::init() {
	bool res;
	res = m_renderer->init();
	m_bIsRunning = res;
	return res;
}

void Game::mainLoop() {
	while (m_stateMachine.getCurrentState() != NULL) {
		m_renderer->frame(this);
	}
}

void Game::frame() {
	if (m_inputHandler->update() == QUIT) {
		m_stateMachine.clean();
	}
	m_stateMachine.update();
	m_stateMachine.render();
}

void Game::shutdown() const {
	m_renderer->shutdown();
}

void Game::setBinaryPath(std::string binaryPath) {
	m_sBinaryPath = binaryPath;
}

const std::string Game::getBinaryPath() {
	return m_sBinaryPath;
}
