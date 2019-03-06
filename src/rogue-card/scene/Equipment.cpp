#include "../game/globals.hpp"
#include "../game/StateMachine.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Equipment.hpp"

EquipmentScene::EquipmentScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_renderer(renderer)
{}

std::string EquipmentScene::getStateID() const {
	return "EquipmentScene";
}

bool EquipmentScene::onEnter() {
	return true;
}

void EquipmentScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("BACK")) {
		stateMachine.popState();
	}
}

void EquipmentScene::render() {
	_renderBackground();
}

void EquipmentScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"ui-equipment", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}

