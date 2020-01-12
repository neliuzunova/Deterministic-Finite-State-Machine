#include "Automat.h"
#include <iostream>

int Automat::counter = 0;

Automat::Automat()
{
	//to prevent vector from resizing and invalidating the states
	m_states.reserve(1024);
	m_edges.reserve(1024);
}

Automat::Automat(char letter)
{
	//to prevent vector from resizing and invalidating the states
	m_states.reserve(1024);
	m_edges.reserve(1024);

	State* s0 = AddState();
	s0->SetIsStarting(true);
	s0->SetIsFinal(false);
	SetStartingState(s0);
	State* s1 = AddState();
	s1->SetIsStarting(false);
	s1->SetIsFinal(true);

	Edge* e1 = AddEdge();
	e1->SetLetter(letter);
	e1->SetToState(s1);
	s0->AddEdge(e1);
}

State* Automat::GetStartingState() const
{
	return m_startingState;
}

std::vector<State> Automat::GetStates() const
{
	return m_states;
}

std::vector<State>& Automat::GetStatesRef()
{
	return m_states;
}

std::vector<Edge> Automat::GetEdges() const
{
	return m_edges;
}

State* Automat::AddState()
{
	State state;
	state.SetID(counter++);
	m_states.push_back(state);
	return &m_states.back();
}

void Automat::AddStates(std::vector<State> states)
{
	m_states.insert(m_states.end(), states.begin(), states.end());
}

Edge* Automat::AddEdge()
{
	Edge edge;
	m_edges.push_back(edge);
	return &m_edges.back();
}

void Automat::AddEdges(std::vector<Edge> edges)
{
	m_edges.insert(m_edges.end(), edges.begin(), edges.end());
}

void Automat::SetStartingState(State* state)
{
	m_startingState = state;
}

bool IsMember(std::vector<State>& usedStates, State* toState) {
	for (auto i : usedStates)
	{
		if (i == *toState)
		{
			return true;
		}
	}
	return false;
}

bool Automat::HasWord(std::string word)
{
	State current = *GetStartingState();
	int counter = 0;
	int NumberOfTransitions = GetEdges().size();

	while (counter < word.length())
	{
		for (int j = 0; j < NumberOfTransitions; j++)
		{
			if (word[counter] == GetEdges()[j].GetLetter() && current == *GetEdges()[j].GetFromState())
			{
				current = *GetEdges()[j].GetToState();
				counter++;
				j = 0;
			}
			if (current.GetIsFinal() && counter == word.length())
				return true;
			if (j + 1 == NumberOfTransitions)
				return false;
		}
	}

	

	return false;
}

void Automat::PrintAutomat()
{
	std::cout << "Starting state: " << std::endl << GetStartingState()->GetID() ;
	std::cout << std::endl;

	std::cout << "Final states: " << std::endl;
	for (auto state : m_states)
	{
		if (state.GetIsFinal())
		{
			std::cout << state.GetID() << " ";
		}
	}
	std::cout << std::endl;

	std::cout << "Transititons: " << std::endl;
	for (auto edge: m_edges )
	{
		std::cout << edge.GetFromState()->GetID() << " ";
		if (edge.GetLetter() == '\0')
		{
			std::cout << "@ ";
		}
		else
		{
			std::cout << edge.GetLetter() << " ";
		}
		std::cout << edge.GetToState()->GetID() << std::endl;
	}
	std::cout << std::endl;
}

bool Automat::IsEmpty() {
	bool result = true;
	for (auto state : GetStates())
	{
		if (state.GetIsFinal())
			result = false;
	}
	if (GetStates().size() == 0 || GetEdges().size() == 0 || result == true)
		return true;
	return false;
}





