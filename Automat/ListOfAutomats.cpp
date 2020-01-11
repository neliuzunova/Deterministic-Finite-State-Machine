#include "ListOfAutomats.h"
#include <iostream>


ListOfAutomats::ListOfAutomats()
{
}

void ListOfAutomats::AddAutomat(Automat* automat)
{
	m_automats.push_back(*automat);
}

Automat ListOfAutomats::Union(Automat* a1, Automat* a2)
{
	Automat a3;
	State* s0 = a3.AddState();
	s0->SetIsStarting(true);
	s0->SetIsFinal(false);
	
	/*
	Edge* e1 = a3.AddEdge();
	Edge* e2 = a3.AddEdge();
	e1->SetLetter('\0');
	e2->SetLetter('\0');
	e1->SetToState(a1->GetStartingState());
	a1->GetStartingState()->SetIsStarting(false);
	e2->SetToState(a2->GetStartingState());
	a2->GetStartingState()->SetIsStarting(false);

	s0->AddEdge(e1);
	s0->AddEdge(e2);
	*/
	//a1->GetStartingState()->SetIsStarting(false);
	//a2->GetStartingState()->SetIsStarting(false);
	for (auto edge: a1->GetEdges())
	{
		Edge* e1 = a3.AddEdge();
		e1->SetLetter(edge.GetLetter());
		e1->SetToState(edge.GetToState());
		s0->AddEdge(e1);
	}
	for (auto edge : a2->GetEdges())
	{
		Edge* e1 = a3.AddEdge();
		e1->SetLetter(edge.GetLetter());
		e1->SetToState(edge.GetToState());
		s0->AddEdge(e1);
	}

	a3.SetStartingState(s0);

	a3.AddStates(a1->GetStates());
	a3.AddEdges(a1->GetEdges());
	a3.AddStates(a2->GetStates());
	a3.AddEdges(a2->GetEdges());
	return a3;
}

Automat ListOfAutomats::Iteration(Automat * a1)
{
	Automat a3;
	a3.AddStates(a1->GetStates());
	a3.AddEdges(a1->GetEdges());
	a3.SetStartingState(a1->GetStartingState());

	for (auto& state: a3.GetStatesRef())
	{
		if (state.GetIsFinal())
		{
			for (auto newEdge : *(a1->GetStartingState())->GetEdges())
			{
				Edge* e1 = a3.AddEdge();
				e1->SetLetter(newEdge->GetLetter());
				e1->SetToState(newEdge->GetToState());
				state.AddEdge(e1);//
			}
		}
	}

	return a3;
}

Automat ListOfAutomats::Addititon(Automat * a1)
{
	Automat a3;
	a3.SetStartingState(a1->GetStartingState());
	a3.AddStates(a1->GetStates());
	a3.AddEdges(a1->GetEdges());

	for (auto edge: a1->GetEdges())
	{
		//std::swap(edge.GetFromState(), edge.GetToState());
		State* temp = edge.GetFromState();
		edge.SetFromState(edge.GetToState()) ;
		edge.SetToState(temp) ;
	}
	return a3;
}

Automat ListOfAutomats::Concatenation(Automat * a1, Automat * a2)
{
	Automat a3;

	a3.AddStates(a1->GetStates());
	a3.AddEdges(a1->GetEdges());

	a3.SetStartingState(a1->GetStartingState());

	for (auto& state : a3.GetStatesRef())
	{
		if (state.GetIsFinal())
		{
			state.SetIsFinal(false); //
			for (auto& newEdge : *(a2->GetStartingState())->GetEdges())
			{
				Edge* e1 = a3.AddEdge();
				e1->SetLetter(newEdge->GetLetter());
				e1->SetToState(newEdge->GetToState());
				state.AddEdge(e1);//
				//e1->SetFromState(&state);
				//std::cout<<e1->GetFromState()->GetID();
			}
		}	
	}
	a3.AddStates(a2->GetStates());
	a3.AddEdges(a2->GetEdges());
	
	return a3;
}

