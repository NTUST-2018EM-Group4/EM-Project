#include "Parameter.h"

// Exception Constructor
Parameter::Parameter()
{
	this->name = "";
	this->init = 0;
	this->begin = 0;
	this->end = 0;
}

// Default Constructor
Parameter::Parameter(std::string name, double init, double begin, double end)
{
	this->name = name;
	this->init = init;
	this->begin = begin;
	this->end = end;
}

// Constructor for alter Variable
Parameter::Parameter(std::string name, std::string formula)
{
	this->name = name;

	// avoid -2+a1 -> fix to 0-2+a1
	if (formula.size() != 0 && formula[0] == '-')
	{
		formula = "0" + formula;
	}
	this->equa.setFormula(formula);

}

// Create Unit Vector List
std::vector<Vec> createUnitVectors(int size)
{
	std::vector<Vec> units(size);
	for (unsigned int i = 0; i < units.size(); i++)
	{
		for (unsigned int j = 0; j < units[i].list.size(); j++)
		{
			if (i == j)
			{
				units[i].list[j].init = 1;
			}
			else
			{
				units[i].list[j].init = 0;
			}
		}
	}
	return units;
}

// Exception Constructor
Vec::Vec()
{
	list.resize(0);
}

// Scalar Vector
// ex. a1*(x,y)
void Vec::scalar(std::string variable)
{
	for (int i = 0; i < list.size(); i++)
	{
		list[i].equa.setFormula(variable + "*(" + list[i].equa.getString() + ")");
	}
}
