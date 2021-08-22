#include <iostream>

template <class stateType>
void StateMachine<stateType>::pushState(stateType *pState) {
	// if the current state is the same as the pushed one, do nothing
	if (!m_vStates.empty() && m_vStates.back()->getStateID() == pState->getStateID()) {
		return;
	}

	m_vStates.push_back(pState);
	std::clog << "Push state " << pState->getStateID() << std::endl;
	if (!m_vStates.back()->onEnter()) {
		popState();
	}
}

template <class stateType>
void StateMachine<stateType>::changeState(stateType *pState) {
	std::clog << "Change state: \n";
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
	std::clog << "State changed\n";
}

template <class stateType>
bool StateMachine<stateType>::popState() {
	if (!m_vStates.empty() && m_vStates.back()->onExit()) {
		std::clog << "Pop state " << m_vStates.back()->getStateID() << std::endl;
		delete m_vStates.back();
		m_vStates.pop_back();
		if (!m_vStates.empty()) {
			m_vStates.back()->onResume();
		}
		return true;
	}

	return false;
}

template <class stateType>
void StateMachine<stateType>::clean() {
	while (popState()) {}
}

template <class stateType>
stateType* StateMachine<stateType>::getCurrentState() const {
	if (!m_vStates.empty()) {
		return m_vStates.back();
	}
	return NULL;
}

template <class stateType>
void StateMachine<stateType>::update() {
	if (!m_vStates.empty()) {
		m_vStates.back()->update(*this);
	}
}

template <class stateType>
void StateMachine<stateType>::render() const {
	if (!m_vStates.empty()) {
		m_vStates.back()->render();
	}
}
