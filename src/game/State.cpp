#include "State.hpp"

State::State(UserActions &userActions) :
	m_userActions(userActions)
{
}

void State::render(const Renderer *renderer __attribute__((unused))) {
}

bool State::onEnter() {
	return true;
}

bool State::onExit() {
	return true;
}
