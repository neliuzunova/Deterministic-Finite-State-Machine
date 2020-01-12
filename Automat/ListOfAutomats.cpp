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
			for (auto newEdge : *(a3.GetStartingState())->GetEdges())
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

int precedence(char operation) {
	switch (operation)
	{
	case '+': return 1;
	case '&': return 1;
	case '.': return 2;
	case '*': return 3;
	//case '(': return 4;
	//case ')': return 1;
	default:
		return 0;
	}
}

Automat ListOfAutomats::applyOp(Automat& a1,Automat& a2, char op) {
	switch (op) {
	case '+': return Union(&a1, &a2);
	case '.': return Concatenation(&a1, &a2);
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
		Automat a1 = Iteration(automat_stack.top());
		automat_stack.pop();
		Automat* newAutomat = AddAutomat();
		*newAutomat = a1;
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
			Automat* newAutomat = AddAutomat();
			*newAutomat = Automat(reg[i]);
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

//stoqns code
/*
int precedence(char op) {
	if (op == 'U')
		return 1;
	if (op == '.')
		return 2;
	if (op == '+')
		return 3;
	return 0;
}

Automat applyUn(const Automat& a1, char op) {
	switch (op) {
	case '+': return Un(a1);
	}
}

Automat applyOp(const Automat& a1, const Automat& a2, char op) {
	switch (op) {
	case 'U': return Union(a1, a2);
	case '.': return Concat(a1, a2);
	}
}

Automat Reg_to_automat(const string& reg) {
	vector<Automat> automats;
	for (unsigned int i = 0; i < reg.size(); i++) {
		if (islower(reg[i]) || isdigit(reg[i])) {
			Automat automat(reg[i]);
			automats.push_back(automat);
		}
	}
	stack <Automat> automat_stack;
	stack <char> ops;
	int j = 0;
	for (unsigned int i = 0; i < reg.size(); i++) {
		if (reg[i] == ' ') continue;
		else if (reg[i] == '(') {
			ops.push(reg[i]);
		}
		else if (islower(reg[i]) || isdigit(reg[i])) {
			automat_stack.push(automats[j]);
			j++;
		}
		else if (reg[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				char op = ops.top();
				ops.pop();
				if (op == '+') {
					Automat a1 = automat_stack.top();
					automat_stack.pop();
					automat_stack.push(applyUn(a1, op));
				}
				else {
					Automat a2 = automat_stack.top();
					automat_stack.pop();

					Automat a1 = automat_stack.top();
					automat_stack.pop();

					automat_stack.push(applyOp(a1, a2, op));
				}
			}
			ops.pop();
		}
		else
		{
			while (!ops.empty() && precedence(ops.top()) >= precedence(reg[i])) {
				char op = ops.top();
				ops.pop();
				if (op == '+') {
					Automat a1 = automat_stack.top();
					automat_stack.pop();
					automat_stack.push(applyUn(a1, op));
				}
				else {
					Automat a2 = automat_stack.top();
					automat_stack.pop();

					Automat a1 = automat_stack.top();
					automat_stack.pop();

					automat_stack.push(applyOp(a1, a2, op));
				}
			}
			ops.push(reg[i]);
		}
	}
	while (!ops.empty()) {
		char op = ops.top();
		ops.pop();
		if (op == '+') {
			Automat a1 = automat_stack.top();
			automat_stack.pop();
			automat_stack.push(applyUn(a1, op));
		}
		else {
			Automat a2 = automat_stack.top();
			automat_stack.pop();

			Automat a1 = automat_stack.top();
			automat_stack.pop();

			automat_stack.push(applyOp(a1, a2, op));
		}
	}


	return automat_stack.top();
}
*/