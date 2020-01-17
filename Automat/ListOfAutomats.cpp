#include "ListOfAutomats.h"
#include <iostream>


ListOfAutomats::ListOfAutomats()
{
	m_automats.reserve(1024);
}

void ListOfAutomats::AddAutomat(Automat* automat)
{
	m_automats.push_back(*automat);
}

Automat* ListOfAutomats::AddAutomat()
{
	Automat newAutomat;
	m_automats.push_back(newAutomat);
	return &m_automats.back();
}

Automat* ListOfAutomats::AddAutomat(char letter)
{
	Automat* a = AddAutomat();
	//to prevent vector from resizing and invalidating the states

	State* s0 = a->AddState();
	s0->SetIsStarting(true);
	s0->SetIsFinal(false);
	a->SetStartingState(s0);
	State* s1 = a->AddState();
	s1->SetIsStarting(false);
	s1->SetIsFinal(true);

	Edge* e1 = a->AddEdge();
	e1->SetLetter(letter);
	e1->SetToState(s1);
	s0->AddEdge(e1);
	return a;
}

Automat ListOfAutomats::Union(Automat* a1, Automat* a2)
{
	Automat a3;
	State* s0 = a3.AddState();
	s0->SetIsStarting(true);
	s0->SetIsFinal(false);

	for (auto edge: a1->GetEdges())
	{
		if (edge.GetFromState() == a1->GetStartingState())
		{
			Edge* e1 = a3.AddEdge();
			e1->SetLetter(edge.GetLetter());
			e1->SetToState(edge.GetToState());
			s0->AddEdge(e1);
		}
	}
	for (auto edge : a2->GetEdges())
	{
		if (edge.GetFromState() == a2->GetStartingState())
		{
			Edge* e1 = a3.AddEdge();
			e1->SetLetter(edge.GetLetter());
			e1->SetToState(edge.GetToState());
			s0->AddEdge(e1);
		}
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
			for (auto newEdge : *(a3.GetStartingState())->GetEdges())
			{
				Edge* e1 = a3.AddEdge();
				e1->SetLetter(newEdge->GetLetter());
				e1->SetToState(newEdge->GetToState());
				state.AddEdge(e1);
			}
		}
		if (state.GetIsStarting())
		{
			state.SetIsFinal(true);
		}
	}
	return a3;
}

Automat ListOfAutomats::Addititon(Automat * a1)
{
	Automat a3;
	a3.AddStates(a1->GetStates());
	a3.AddEdges(a1->GetEdges());
	a3.SetStartingState(a1->GetStartingState());

	for (auto& state: a3.GetStatesRef())
	{
		if (state.GetIsFinal())
		{
			state.SetIsFinal(false);
		}
		else
		{
			state.SetIsFinal(true);
		}
	}
	return a3;
}

Automat ListOfAutomats::Section(Automat * a1, Automat * a2)
{
	Automat a4 = Addititon(a1);
	Automat a5 = Addititon(a2);
	return Union(&a4, &a5);
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
			state.SetIsFinal(false); 
			for (auto& newEdge : *(a2->GetStartingState())->GetEdges())
			{
				Edge* e1 = a3.AddEdge();
				e1->SetLetter(newEdge->GetLetter());
				e1->SetToState(newEdge->GetToState());
				state.AddEdge(e1);
			}
		}	
	}
	a3.AddStates(a2->GetStates());
	a3.AddEdges(a2->GetEdges());
	
	return a3;
}

int precedence(char operation) {
	switch (operation)
	{
	case '+': return 1;
	case '&': return 1;
	case '.': return 2;
	case '*': return 3;
	//case '(': return 4;
	//case ')': return 4;
	default:
		return 0;
	}
}

Automat ListOfAutomats::applyOp(Automat& a1,Automat& a2, char op) {
	switch (op) {
	case '+': return Union(&a1, &a2);
	case '.': return Concatenation(&a1, &a2);
	case '&': return Section(&a1, &a2);
	}
}

bool isNotSpecialSymbol(char symbol) {
	return (symbol != '(' && symbol != ')' && symbol != '+' &&
		symbol != '.' && symbol != '*' && symbol != '&');
}

void ListOfAutomats::AppplyFunction( std::stack<Automat*>& automat_stack, std::stack<char>& operations) {
	char op = operations.top();
	operations.pop();
	if (op == '*')
	{
		Automat* newAutomat = AddAutomat();
		*newAutomat = Iteration(automat_stack.top());
		automat_stack.pop();
	}
	else
	{
		Automat* newAutomat2 = AddAutomat();
		newAutomat2 = automat_stack.top();
		automat_stack.pop();

		Automat* newAutomat1 = AddAutomat();
		newAutomat1 = automat_stack.top();
		automat_stack.pop();

		Automat* newAutomat3 = AddAutomat();
		*newAutomat3 = applyOp(*newAutomat1, *newAutomat2, op);
		automat_stack.push(newAutomat3);
	}
}

Automat* ListOfAutomats::RegToAutomat(const std::string& reg)
{
	std::vector<Automat*> automats; //for every letter

	//to prevent vector from resizing and invalidating the states
	automats.reserve(1024);

	for (int i = 0; i < reg.size(); i++) 
	{
		if (reg[i] == ' ')
		{
			continue;
		}
		if (isNotSpecialSymbol(reg[i])) 
		{
			Automat* newAutomat = AddAutomat(reg[i]);
			automats.push_back(newAutomat);
		}
	}

	std::stack<Automat*> automat_stack;
	std::stack<char> operations;
	int j = 0;

	for (int i = 0; i < reg.size(); i++) 
	{
		if (reg[i] == ' ')
		{
			continue;
		}
		else if (reg[i] == '(') 
		{
			operations.push(reg[i]);
		} 
		else if (isNotSpecialSymbol(reg[i])) 
		{
			Automat* newAutomat = AddAutomat();
			*newAutomat = Automat(*automats[j]);
			automat_stack.push(newAutomat);
			j++;
		}
		else if (reg[i] == ')')
		{
			while (!operations.empty() && operations.top() != '(')
			{
				AppplyFunction(automat_stack, operations);
			}
			operations.pop();
		}
		else // if a special symbol: +, ., *, & 
		{
			while (!operations.empty() && precedence(operations.top()) >= precedence(reg[i])) {
				AppplyFunction(automat_stack, operations);
			}
			operations.push(reg[i]);
		}
	}

	while (!operations.empty()) 
	{
		AppplyFunction(automat_stack, operations);
	}

	return &m_automats.back();
}
