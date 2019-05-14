#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Equation.h"

struct Parameter
{
	//
	// Constructor
	//
	Parameter();
	Parameter(std::string name, double init, double begin, double end);
	Parameter(std::string name, std::string formula);

	//
	// Data Member
	//
	std::string name;
	Equation equa;
	double init;
	double begin;
	double end;
};

struct Vec
{
	//
	// Constructor
	//
	Vec();

	//
	// Tool Function
	//
	void scalar(std::string variable);

	//
	// Data Member
	//
	std::vector<Parameter> list;

};

std::vector<Vec> createUnitVectors(int size);

