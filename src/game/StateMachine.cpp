#include "StateMachine.hpp"

void StateMachine::pushState(State *pState) {
	// if the current state is the same as the pushed one, do nothing
	if (!m_vStates.empty() && m_vStates.back()->getStateID() == pState->getStateID()) {
		return;
	}

	m_vStates.push_back(pState);
	if (!m_vStates.back()->onEnter()) {
		popState();
	}
}

void StateMachine::changeState(State *pState) {
	// If there is at least one state
	if (!m_vStates.empty()) {
		// and if it is the state we want to add
		if (m_vStates.back()->getStateID() == pState->getStateID()) {
			return;
		}

		// remove the state
		popState();
	}

	// add the new one
	pushState(pState);
}

bool StateMachine::popState() {
	if (!m_vStates.empty() && m_vStates.back()->onExit()) {
		delete m_vStates.back();
		m_vStates.pop_back();
		return true;
	}

	return false;
}

void StateMachine::clean() {
	while (popState()) {}
}

State* StateMachine::getCurrentState() const {
	if (!m_vStates.empty()) {
		return m_vStates.back();
	}
	return NULL;
}

void StateMachine::update() {
	if (!m_vStates.empty()) {
		m_vStates.back()->update(*this);
	}
}
void StateMachine::render() const {
	if (!m_vStates.empty()) {
		m_vStates.back()->render();
	}
}
