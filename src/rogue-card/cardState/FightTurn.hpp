#ifndef __FIGHT_TURN_CARD_STATE__
#define __FIGHT_TURN_CARD_STATE__

#include "../CardState.hpp"
#include "../coordinates.hpp"
#include "../sdl2/Text.hpp"
#include "../common/types.hpp"

class FightTurnCardState : public CardState {
	private:
	const int STEP_PLAYER_ATTACK_ANIMATION = 1;
	const int STEP_ENEMY_ATTACK_ANIMATION = 2;
	const int STEP_PAUSE_ANIMATION = 4;
	const int STEP_DONE = (
		STEP_PLAYER_ATTACK_ANIMATION
		| STEP_ENEMY_ATTACK_ANIMATION
		| STEP_PAUSE_ANIMATION
	);

	int m_iStep = 0;
	int m_iDoneSteps = 0;
	unsigned int m_iStart = 0;

	S_FightTurnResult m_result;
	Text m_critical = Text();
	Text m_damagesFromPlayer = Text();
	Text m_damagesFromEnemy = Text();

	int m_iDamagesFromPlayerY = DAMAGES_FROM_PLAYER.y;
	int m_iDamagesFromEnemyY = DAMAGES_FROM_ENEMY.y;
	int m_iCriticalPlayerY = CRITICAL_FROM_PLAYER.y;
	int m_iCriticalEnemyY = CRITICAL_FROM_ENEMY.y;

	void _updatePlayerAttack();
	void _updateEnemyAttack();
	void _updatePause();

	public:
	FightTurnCardState(S_FightTurnResult result);
	std::string getStateID() const;
	void update(StateMachine<CardState> &stateMachine);
	void render(SDL_Renderer *renderer, Card &card, int x, int y);
};

#endif
