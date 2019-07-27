#include "PlayerCreation.hpp"
#include "Intro.hpp"
#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../sdl2/TextureManager.hpp"

PlayerCreationScene::PlayerCreationScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	State(userActions),
	m_renderer(renderer),
	m_title(Text()),
	m_armorText(Text()),
	m_weaponText(Text()),
	m_armorMenu(ArmorChoiceMenu(m_renderer)),
	m_weaponMenu(WeaponChoiceMenu(m_renderer))
{}

std::string PlayerCreationScene::getStateID() const {
	return "PlayerCreationScene";
}

bool PlayerCreationScene::onEnter() {
	m_title.setText("Player Creation");
	m_armorText.setText("Do you feel like home in a:");
	m_weaponText.setText("Your best friend is a:");
	m_armorMenu.init();
	m_weaponMenu.init();
	return true;
}

void PlayerCreationScene::update(StateMachine &stateMachine) {
	Menu* menu = (m_step == ARMOR_CHOICE ? (Menu*) &m_armorMenu : (Menu*) &m_weaponMenu);
	if (m_userActions.getActionState("CURSOR_DOWN")) {
		menu->selectNext();
	}
	else if (m_userActions.getActionState("CURSOR_UP")) {
		menu->selectPrevious();
	}
	else if (m_userActions.getActionState("MENU_ACTION")) {
		if (m_step == ARMOR_CHOICE) {
			m_step = WEAPON_CHOICE;
		}
		else if (m_step == WEAPON_CHOICE) {
			stateMachine.changeState(new IntroScene(m_userActions, m_renderer));
		}
	}
}

void PlayerCreationScene::render() {
	_renderBackground();
	m_title.render(m_renderer->getRenderer(), (SCREEN_WIDTH - m_title.getLength()) / 2, 7);
	if (m_step == ARMOR_CHOICE) {
		m_armorText.render(m_renderer->getRenderer(), 4, 40);
		m_armorMenu.render();
	}
	else if (m_step == WEAPON_CHOICE) {
		m_weaponText.render(m_renderer->getRenderer(), 4, 40);
		m_weaponMenu.render();
	}
}

void PlayerCreationScene::_renderBackground() const {
	TextureManager::Instance()->draw(
		"ui-player-creation", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer->getRenderer()
	);
}
