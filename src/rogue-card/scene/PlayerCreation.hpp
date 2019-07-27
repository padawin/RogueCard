#ifndef __PLAYER_CREATION_STATE__
#define __PLAYER_CREATION_STATE__

#include <memory>
#include "../game/State.hpp"
#include "../sdl2/Renderer.hpp"
#include "../sdl2/Text.hpp"
#include "../menus/ArmorChoice.hpp"
#include "../menus/WeaponChoice.hpp"

enum PlayerCreationStep {ARMOR_CHOICE, WEAPON_CHOICE};

class PlayerCreationScene : public State {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	unsigned int m_iCurrentPage = 1;
	Text m_title;
	Text m_armorText;
	Text m_weaponText;
	PlayerCreationStep m_step = ARMOR_CHOICE;
	ArmorChoiceMenu m_armorMenu;
	WeaponChoiceMenu m_weaponMenu;

	void _renderBackground() const;

	public:
	PlayerCreationScene(UserActions &userActions, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
