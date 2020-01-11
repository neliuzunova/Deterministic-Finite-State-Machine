#include <iostream>
#include "State.h"
#include "Automat.h"
#include "ListOfAutomats.h"

static int counter = 0;

int main() {
	Automat A;
	State* s0 = A.AddState();
	s0->SetIsStarting(true);
	s0->SetIsFinal(false);
	A.SetStartingState(s0);

	State* s1 = A.AddState();
	s1->SetIsStarting(false);
	s1->SetIsFinal(true);

	State* s2 = A.AddState();
	s2->SetIsStarting(false);
	s2->SetIsFinal(true);

	Edge* e1 = A.AddEdge();
	e1->SetLetter('a');

	Edge* e2 = A.AddEdge();
	e2->SetLetter('b');

	e1->SetToState(s1);
	e2->SetToState(s2);

	s0->AddEdge(e1);
	s0->AddEdge(e2);

	std::cout << A.HasWord("a") << std::endl;
	std::cout << A.HasWord("b") << std::endl;
	std::cout << A.HasWord("c") << std::endl;

	Automat A2;
	State* s3 = A2.AddState();
	s3->SetIsStarting(true);
	s3->SetIsFinal(false);
	A2.SetStartingState(s3);

	State* s4 = A2.AddState();
	s4->SetIsStarting(false);
	s4->SetIsFinal(true);

	Edge* e3 = A2.AddEdge();
	e3->SetLetter('c');

	e3->SetToState(s4);
	s3->AddEdge(e3);

	A.PrintAutomat();
	A2.PrintAutomat();

	ListOfAutomats LA;
	Automat A3 = LA.Union(&A, &A2);
	A3.PrintAutomat();

	std::cout << (A3 << "a") << std::endl;
	std::cout << (A3 << "b") << std::endl;
	std::cout << (A3 << "c") << std::endl;

	Automat A4 = LA.Concatenation(&A, &A2);
	A4.PrintAutomat();

	Automat A5 = LA.Iteration(&A);
	A5.PrintAutomat();

	Automat A6 = LA.Addititon(&A);
	A6.PrintAutomat();

	std::cout << A2.IsEmpty() << std::endl;;
	system("pause");
	return 0;
}