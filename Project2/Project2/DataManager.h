#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


class DataManager
{
private:

	std::vector<std::string> Equations;
	int EquationIndex;
	std::string FileName;

public:
	//
	// Constructor
	//
	DataManager();

	//
	// Member Function
	//
	bool LoadEquationData();
	std::vector<std::string> GetEquations();
	void SetFileName(std::string fileName);
};
