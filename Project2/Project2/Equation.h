#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <cmath>
#include "Matrix.h"

#define SYSENDL System::Environment::NewLine

class Equation
{
public:
	//
	// Constructor
	//
	Equation();
	Equation(std::string formula, int dim);
	Equation(std::string formula, std::string nameX, double initX, double beginX, double endX);
	Equation(std::string formula, std::string nameX, double initX, double beginX, double endX,	\
		std::string nameY, double initY, double beginY, double endY);

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
	std::string alterFormula(std::string key, std::string str);
	std::string alterFormula(std::string customFormula, std::string key, std::string str);
	double f(Vector vec, std::vector<std::string> name);
	double f(double val, std::string name);
	double f();
	double derivative(const std::string & diff);
	Vector gradient();
	Matrix hessian() const;
	double goldenSearch(std::string name, double a, double b, double c, double tau);

	//
	// Compute Function
	//
	System::String^ Powell();
	System::String^ Newton();
	System::String^ Steep();
	System::String^ Quasi();
	System::String^ Conjuate();

private:
	//
	// Data Member
	//
	bool XhasRadical = false;
	bool YhasRadical = false;
	int dim;				// dimension of this equation
	Vector init;			// initial Point Vector
	double xInterval[2];	// x interval ={ begin, end };
	double yInterval[2];	// y interval
	std::string formula;	// euquation string
	std::vector<std::string> name;	// variable name ex.{ x, y };
	std::vector<std::string> postFormula; // postfix formula
	
};

int priority(std::string& op);
double cal(double& a, double& b, char& op);
System::String^ ssTo_String(std::stringstream& ss);
