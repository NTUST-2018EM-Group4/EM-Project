#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include "Parameter.h"
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
	double f(std::vector<Parameter> paras);

	//
	// Compute Function
	//
	System::String^ Powell(std::vector<Parameter> paras);
	System::String^ Newton(std::vector<Parameter> paras);
	System::String^ Steep(std::vector<Parameter> paras);
	System::String^ Quasi(std::vector<Parameter> paras);
	System::String^ Conjuate(std::vector<Parameter> paras);

private:
	std::string formula;
	std::vector<std::string> postFormula;
};

int priority(System::String^ op);
int priority(std::string op);