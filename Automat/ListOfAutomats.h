#pragma once
#include "Automat.h"
#include<string>
#include<stack>
class ListOfAutomats
{
private:
	std::vector<Automat> m_automats;
	Automat applyOp(Automat& a1,Automat& a2, char op);
	void AppplyFunction(std::stack<Automat*>& automat_stack, std::stack<char>& operations);

public:
	ListOfAutomats();
	void AddAutomat(Automat* automat);
	Automat* AddAutomat();

	//Functions
	Automat Union(Automat* a1, Automat* a2);
	Automat Concatenation(Automat* a1, Automat* a2);
	Automat Iteration(Automat* a1);
	Automat Addititon(Automat* a1); 
	Automat* RegToAutomat(const std::string& reg);
};

