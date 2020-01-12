#pragma once
#include "Automat.h"
#include<string>
#include<stack>
class ListOfAutomats
{
private:
	std::vector<Automat> m_automats;
public:
	ListOfAutomats();
	void AddAutomat(Automat* automat);

	//Functions
	Automat Union(Automat* a1, Automat* a2);
	Automat Concatenation(Automat* a1, Automat* a2);
	Automat Iteration(Automat* a1);
	Automat Addititon(Automat* a1); 
	Automat applyOp(Automat& a1,Automat& a2, char op);
	Automat* RegToAutomat(const std::string& reg);
};

