#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Parameter
{
	std::string name;
	std::string formula;
	double init;
	double begin;
	double end;
	Parameter(std::string name, double init, double begin, double end);
	Parameter(std::string name, std::string formula);
};