#include "SDL2/SDL.h"
#include <math.h>
#include "FightTurn.hpp"
#include "../Card.hpp"
#include "../coordinates.hpp"

const int MAX_DURATION_PLAYER_ATTACK = 250;

const int MAX_DURATION_PAUSE = 300;

const int MAX_DURATION_ENEMY_ATTACK_PHASE1 = 50;
const int MAX_DURATION_ENEMY_ATTACK_PHASE2 = 50;
const int SPEED_ATTACK_ENEMY_PHASE1 = 4;
const int SPEED_ATTACK_ENEMY_PHASE2 = 4;

FightTurnCardState::FightTurnCardState() : CardState() {
	m_iStart = SDL_GetTicks();
	m_iStep = STEP_PLAYER_ATTACK_ANIMATION;
}

std::string FightTurnCardState::getStateID() const {
	return "FightTurnCardState";
}

void FightTurnCardState::update(StateMachine<CardState> &stateMachine) {
	if (m_iStep == STEP_PLAYER_ATTACK_ANIMATION) {
		_updatePlayerAttack();
	}
	else if (m_iStep == STEP_ENEMY_ATTACK_ANIMATION) {
		_updateEnemyAttack();
	}
	else if (m_iStep == STEP_PAUSE_ANIMATION) {
		_updatePause();
	}

	if (m_iDoneSteps == STEP_DONE) {
		stateMachine.popState();
	}
	// Current step is finished, define next step
	else if (m_iDoneSteps & m_iStep) {
		// we haven't paused between the animations, so let's pause
		if (!(m_iDoneSteps & STEP_PAUSE_ANIMATION)) {
			m_iStep = STEP_PAUSE_ANIMATION;
		}
		// otherwise, set the other animation
		else {
			m_iStep = ~m_iDoneSteps & STEP_DONE;
		}
	}
}

void FightTurnCardState::_updatePlayerAttack() {
	unsigned int currTime = SDL_GetTicks();
	unsigned int duration = currTime - m_iStart;
	m_iX = (int) (sin(duration / 25.0) * 5);
	if (duration > MAX_DURATION_PLAYER_ATTACK) {
		m_iX = 0;
		m_iStart = currTime;
		m_iDoneSteps |= STEP_PLAYER_ATTACK_ANIMATION;
	}
}

void FightTurnCardState::_updateEnemyAttack() {
	unsigned int currTime = SDL_GetTicks();
	unsigned int duration = currTime - m_iStart;
	if (duration <= MAX_DURATION_ENEMY_ATTACK_PHASE1) {
		m_iY += SPEED_ATTACK_ENEMY_PHASE1;
	}
	else if (duration <= MAX_DURATION_ENEMY_ATTACK_PHASE1 + MAX_DURATION_ENEMY_ATTACK_PHASE2) {
		m_iY -= SPEED_ATTACK_ENEMY_PHASE2;
	}
	else {
		m_iY = 0;
		m_iStart = currTime;
		m_iDoneSteps |= STEP_ENEMY_ATTACK_ANIMATION;
	}
}

void FightTurnCardState::_updatePause() {
	unsigned int currTime = SDL_GetTicks();
	unsigned int duration = currTime - m_iStart;
	if (duration > MAX_DURATION_PAUSE) {
		m_iStart = currTime;
		m_iDoneSteps |= STEP_PAUSE_ANIMATION;
	}
}

void FightTurnCardState::render(SDL_Renderer *renderer, Card &card, int x, int y) {
	card._renderCard(renderer, x + m_iX, y + m_iY);
}
