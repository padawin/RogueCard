#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Inventory.hpp"
#include "ObjectCard.hpp"

InventoryScene::InventoryScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_player(player),
	m_renderer(renderer)
{
}

std::string InventoryScene::getStateID() const {
	return "InventoryScene";
}

bool InventoryScene::onEnter() {
	return true;
}

void InventoryScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("BACK")) {
		stateMachine.popState();
	}
}

void InventoryScene::render() {
	_renderBackground();
}

void InventoryScene::_renderBackground() const {
	TextureManager::Instance()->drawImage(
		"ui-inventory", m_renderer->getRenderer(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
	);
}
