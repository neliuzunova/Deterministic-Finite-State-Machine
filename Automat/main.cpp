#include <iostream>
#include <fstream>
#include <string>
#include "State.h"
#include "Automat.h"
#include "AutomatOperations.h"

static int counter = 0;

int main() {
	/*
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

	AutomatOperations LA;
	Automat A3 = LA.Union(&A, &A2);
	A3.PrintAutomat();

	std::cout << (A3 << "a") << std::endl;
	std::cout << (A3 << "b") << std::endl;
	std::cout << (A3 << "c") << std::endl;

	Automat A4 = LA.Concatenation(&A, &A2);
	A4.PrintAutomat();

	std::cout << (A4 << "a" ) << std::endl;
	std::cout << (A4 << "b")  << std::endl;
	std::cout << (A4 << "àc")  << std::endl;
	std::cout << (A4 << "bc")  << std::endl;
	std::cout << (A4 << "àcb") << std::endl;
	std::cout << (A4 << "c") << std::endl;
	
	Automat A5 = LA.Iteration(&A2);
	A5.PrintAutomat();

	Automat A6 = LA.Addititon(&A4);
	A6.PrintAutomat();
	
	std::cout << A2.IsEmpty() << std::endl;
		//<< A4.HasWord("ac") << std::endl << A4.HasWord("cc");

	LA.AddAutomat('f')->PrintAutomat();

	Automat A7 = LA.Section(&A, &A2);
	A7.PrintAutomat();

	Automat* A8 = LA.RegToAutomat("a*");
	A8->PrintAutomat();

	Automat* A9 = LA.RegToAutomat("((a.b + b.a) & a.b)"); //not ready
	A9->PrintAutomat();

	Automat* A10 = LA.RegToAutomat("a.b.c + b.c.a");
	A10->PrintAutomat();

	std::cout << (*A10 << "abc") << std::endl;
	*/

	std::cout << "Input file name and a regular expression: \n";
	std::string filename, regExpr;

	std::getline(std::cin, filename);
	std::getline(std::cin, regExpr);

	AutomatOperations LA;
	Automat* A = LA.RegToAutomat(regExpr); 
	//A->PrintAutomat();

	std::ifstream f(filename + ".txt");
	int automatCount;
	f >> automatCount;
	for (int i = 0; i < automatCount; i++)
	{
		std::string row;
		f >> row;
		if (A->HasWord(row))
		{
			std::cout << row << std::endl;
		}
	}
	f.close();
	//example: (a+b)*  , (a . b)*+(b . c);
	//example: (a + b + c)*  , (a.b.c)*  , (c)*  , a.b+c ;

	system("pause");
	return 0;
}