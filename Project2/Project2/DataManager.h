#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Vector.h"
#include "Matrix.h"

//�w�q���޸��class
class DataManager
{
private:	
	//�x�s�V�q���
	std::vector<Vector> Vectors;
	//�����V�qID�A�Ω󱱺�
	int  VectorVariableIndex;

	//Store Matrix Data
	std::vector<Matrix> Matrices;
	//Record Matrix ID
	int MatrixVariableIndex;

	//�����ɮ׸��|�W��
	std::string FileName;
public:
	DataManager();

	//Ū���V�q���
	bool LoadVectorData();
	//���o�V�q���
	std::vector<Vector> GetVectors();
	// find vector index
	int findVector(std::string name);

	//Read Matrix Data
	bool LoadMatrixData();
	//Get Matrix Data
	std::vector<Matrix> GetMatrices();
	// find matrix index
	int findMatrix(std::string name);

	//�]�m�ɮ׸��|�W��
	void SetFileName(std::string fileName);
};
