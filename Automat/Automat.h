#pragma once
#include "State.h"
class Automat
{
private:
	std::vector<State> m_states;
	std::vector<Edge> m_edges;
	State* m_startingState;
	static int counter;
	
public:
	Automat();
	State* GetStartingState() const;
	std::vector<State> GetStates() const;
	std::vector<State>& GetStatesRef();
	std::vector<Edge> GetEdges() const;

	bool operator<< (std::string word)
	{
		return (HasWord(word));
	}

	State* AddState();
	void AddStates(std::vector<State> states);
	Edge* AddEdge();
	void AddEdges(std::vector<Edge> edges);
	void SetStartingState(State* state);

	//Functions
	bool HasWord(std::string word);
	void PrintAutomat();
	bool IsEmpty();
};

