#include "../sdl2/TextureManager.hpp"
#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "QuickActionBar.hpp"

QuickActionBarScene::QuickActionBarScene(
	UserActions &userActions,
	ActionBar &actionBar,
	std::shared_ptr<SDL2Renderer> renderer
) :
	State(userActions),
	m_renderer(renderer),
	m_actionBar(actionBar)
{}

std::string QuickActionBarScene::getStateID() const {
	return "QuickActionBarScene";
}

bool QuickActionBarScene::onEnter() {
	return true;
}

void QuickActionBarScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("BACK")) {
		stateMachine.popState();
	}
}

void QuickActionBarScene::render() {
	_renderBackground();
}

void QuickActionBarScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"quick-action-bar",  0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}
