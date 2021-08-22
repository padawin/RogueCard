#ifndef __EQUIPMENT_STATE__
#define __EQUIPMENT_STATE__

#include <memory>
#include <string.h>
#include "game/SceneState.hpp"
#include "rogue-card/coordinates.hpp"
#include "sdl2/Renderer.hpp"
#include "sdl2/Text.hpp"
#include "Player.hpp"
#include "Tab.hpp"
#include "ObjectCardCollectionRenderer.hpp"

class EquipmentScene : public SceneState {
	private:
	std::shared_ptr<SDL2Renderer> m_renderer;
	int m_cursorPosition = 0;
	S_Coordinates m_mCursorPositions[SIZE_EQUIPMENT] = {};
	unsigned int m_equipmentFlags[SIZE_EQUIPMENT] = {};
	Tab m_titlesTab;
	ObjectCardCollection m_availableCards;
	ObjectCardCollectionRenderer m_availableCardsRenderer;
	Player &m_player;

	Text m_statLabel;
	Text m_statValue;

	bool m_bSelectViewOpen = false;

	void _renderBackground() const;
	void _renderCards() const;
	void _renderCursor();
	void _renderCardStats(std::shared_ptr<ObjectCard> card, std::shared_ptr<ObjectCard> compareCard, int x);

	void _openListObjects();

	int _boundVal(int val, int minVal, int maxVal) const;
	std::string _getStatColor(int stat1, int stat2) const;

	public:
	EquipmentScene(UserActions &userActions, Player &player, std::shared_ptr<SDL2Renderer> renderer);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
