#pragma once
#include <vector>
#include "Edge.h"

class State
{
private:
	int m_ID;
	bool m_isStarting;
	bool m_isFinal;
	std::vector<Edge*> m_Edges;

public:
	State();

	const bool operator== (const State& other) const 
	{
		return (m_ID == other.GetID());
	}

	int GetID() const;
	bool GetIsStarting() const;
	bool GetIsFinal() const;
	std::vector<Edge*>* GetEdges();

	void SetID(int ID);
	void SetIsStarting(bool isStarting);
	void SetIsFinal(bool isFinal);
	void AddEdge(Edge* edge);

};

