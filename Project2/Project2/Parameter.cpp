#include "Parameter.h"

Parameter::Parameter(std::string name, double init, double begin, double end)
{
	this->name = name;
	this->init = init;
	this->begin = begin;
	this->end = end;
}
