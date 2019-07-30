#include "PlayerCreation.hpp"
#include "Play.hpp"
#include "../game/StateMachine.hpp"
#include "../game/globals.hpp"
#include "../sdl2/TextureManager.hpp"
#include "Save.hpp"

char starterArmors[NB_ARMOR_CHOICES][32] = {
	"STARTER_LIGHT_ARMOR", "STARTER_MEDIUM_ARMOR", "STARTER_HEAVY_ARMOR"
};
char starterWeapons[NB_WEAPON_CHOICES][32] = {
	"STARTER_SWORD", "STARTER_SPEAR", "STARTER_AXE", "STARTER_BLUNT", "STARTER_RANGE"
};

PlayerCreationScene::PlayerCreationScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer) :
	SceneState(userActions),
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
	Save::clean();
	m_title.setText("Player Creation");
	m_armorText.setText("Do you feel like home in a:");
	m_weaponText.setText("Your best friend is a:");
	m_armorMenu.init();
	m_weaponMenu.init();
	return true;
}

void PlayerCreationScene::update(StateMachine<SceneState> &stateMachine) {
	if (m_userActions.getActionState("CURSOR_DOWN")) {
		Menu* menu = (m_step == ARMOR_CHOICE ? (Menu*) &m_armorMenu : (Menu*) &m_weaponMenu);
		menu->selectNext();
	}
	else if (m_userActions.getActionState("CURSOR_UP")) {
		Menu* menu = (m_step == ARMOR_CHOICE ? (Menu*) &m_armorMenu : (Menu*) &m_weaponMenu);
		menu->selectPrevious();
	}
	else if (m_userActions.getActionState("MENU_ACTION")) {
		if (m_step == ARMOR_CHOICE) {
			m_step = WEAPON_CHOICE;
		}
		else if (m_step == WEAPON_CHOICE) {
			Player player;
			_createPlayerInitialEquipment(player);
			stateMachine.changeState(new PlayScene(m_userActions, m_renderer, player));
		}
	}
}

void PlayerCreationScene::_createPlayerInitialEquipment(Player& player) const {
	std::string armorMetaID = starterArmors[m_armorMenu.getSelectedAction()];
	std::string weaponMetaID = starterWeapons[m_weaponMenu.getSelectedAction()];
	std::shared_ptr<ObjectCard> starterArmor = std::shared_ptr<ObjectCard>(
		new ObjectCard(armorMetaID.c_str())
	);
	std::shared_ptr<ObjectCard> starterWeapon = std::shared_ptr<ObjectCard>(
		new ObjectCard(weaponMetaID.c_str())
	);
	starterArmor->create();
	starterWeapon->create();
	player.addItemToInventory(starterArmor);
	player.addItemToInventory(starterWeapon);
	player.toggleEquip(starterArmor);
	player.toggleEquip(starterWeapon);
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
