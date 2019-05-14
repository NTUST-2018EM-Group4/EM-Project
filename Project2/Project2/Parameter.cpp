#include "Parameter.h"

Parameter::Parameter(std::string name, double init, double begin, double end)
{
	this->name = name;
	this->init = init;
	this->begin = begin;
	this->end = end;
}

Parameter::Parameter(std::string name, std::string formula)
{
	this->name = name;
	this->formula = formula;

	// avoid -2+a1 -> fix to 0-2+a1
	if (formula.size() != 0 && formula[0] == '-')
	{
		this->formula = "0" + formula;
	}
}
