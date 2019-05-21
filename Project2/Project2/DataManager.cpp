#include "DataManager.h"

DataManager::DataManager()
{
	EquationIndex = 0;
}

bool DataManager::LoadEquationData()
{
	std::fstream fin;
	fin.open(FileName, std::ios::in);

	if (!fin)
	{
		return false;
	}
	else
	{
		std::string tempSring;
		while (fin >> tempSring)
		{
			Equations.push_back(tempSring);
			EquationIndex++;
		}
		return true;
	}
}

std::vector<std::string> DataManager::GetEquations()
{
	return Equations;
}

void DataManager::SetFileName(std::string fileName)
{
	FileName = fileName;
}
