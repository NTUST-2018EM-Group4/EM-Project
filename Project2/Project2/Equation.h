#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#define OPSIZE 6

class Equation
{
public:
	//
	// Constructor
	//
	Equation();
	Equation(std::string formula);

	//
	// Tool Function
	//
	std::vector<std::string> inToPostfix();
	System::String^ FormulaOutputStr();
	double Calculate();

	//
	// Compute Function
	//
	System::String^ Powell();
	System::String^ Newton();
	System::String^ Step();
	System::String^ Quasi();
	System::String^ Conjuate();

private:
	std::string formula;
	std::vector<std::string> postFormula;
};

int priority(System::String^ op);
int priority(std::string op);