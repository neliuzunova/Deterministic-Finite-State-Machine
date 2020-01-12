#include "State.h"



State::State()
{
	m_isStarting = 0;
	m_isFinal = 0;
	m_Edges.reserve(1024);
	m_Edges = std::vector<Edge*>();
}

int State::GetID() const
{
	return m_ID;
}

bool State::GetIsStarting() const
{
	return m_isStarting;
}

bool State::GetIsFinal() const
{
	return m_isFinal;
}

std::vector<Edge*>* State::GetEdges()
{
	return &m_Edges;
}

void State::SetID(int ID)
{
	m_ID = ID;
}

void State::SetIsStarting(bool isStarting)
{
	m_isStarting = isStarting;
}

void State::SetIsFinal(bool isFinal)
{
	m_isFinal = isFinal;
}

void State::AddEdge(Edge* edge)
{
	edge->SetFromState(this);
	m_Edges.push_back(edge);
}


