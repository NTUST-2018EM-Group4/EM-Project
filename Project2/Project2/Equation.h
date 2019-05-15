#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <cmath>
#define OPSIZE 6

class Parameter;

class Equation
{
public:
	//
	// Constructor
	//
	Equation();
	Equation(std::string formula);
	Equation(std::string formula, std::vector<Parameter> paras);

	//
	// Get / Set Function
	//
	void setFormula(std::string& formula);
	std::string getString();
	System::String^ getSystemString();

	//
	// Tool Function
	//
	std::vector<std::string> inToPostfix();
	double f(const std::vector<Parameter>& paras) const;
	double derivative(const std::vector<Parameter>& paras, const std::string& diff) const;

	//
	// Compute Function
	//
	System::String^ Powell(std::vector<Parameter>& paras);
	System::String^ Newton(std::vector<Parameter>& paras);
	System::String^ Steep(std::vector<Parameter>& paras);
	System::String^ Quasi(std::vector<Parameter>& paras);
	System::String^ Conjuate(std::vector<Parameter>& paras);

private:
	//
	// Data Member
	//
	std::string formula;
	std::vector<std::string> postFormula;
};

int priority(std::string& op);
double cal(double& a, double& b, char& op);
