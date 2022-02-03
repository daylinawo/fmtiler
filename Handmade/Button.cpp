#include "Button.h"

Button::Button()
{
	m_state = State::DEFAULT;
}

Button::~Button()
{
}

const AABB& Button::GetCollider()
{
	return m_boxCollider;
}

void Button::SetState(State state)
{
	m_state = state;
}

