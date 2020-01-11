#include "Edge.h"



Edge::Edge()
{
	m_fromState = nullptr;
	m_toState = nullptr;
	m_letter = '@';
}

Edge::Edge(State* fromState, State* toState, char letter)
{
	m_fromState = fromState;
	m_toState = toState;
	m_letter = letter;
}

State* Edge::GetFromState() const
{
	return m_fromState;
}

State* Edge::GetToState() const
{
	return m_toState;
}

char Edge::GetLetter() const
{
	return m_letter;
}

void Edge::SetFromState(State* fromState)
{
	m_fromState = fromState;
}

void Edge::SetToState(State* toState)
{
	m_toState = toState;
}

void Edge::SetLetter(char letter)
{
	m_letter = letter;
}

