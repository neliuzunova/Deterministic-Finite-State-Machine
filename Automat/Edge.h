#pragma once

class State;
class Edge
{
public:
	State* m_fromState;
	State* m_toState;
	char m_letter;
public:
	Edge();
	Edge(State* fromState, State* toState, char letter);

	State* GetFromState() const;
	State* GetToState() const;
	char GetLetter() const;

	void SetFromState(State* fromState);
	void SetToState(State* toState);
	void SetLetter(char letter);

};

