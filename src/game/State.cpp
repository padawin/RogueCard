#include "State.hpp"

State::State(UserActions &userActions) :
	m_userActions(userActions)
{
}

void State::render() {
}

bool State::onEnter() {
	return true;
}

bool State::onExit() {
	return true;
}
