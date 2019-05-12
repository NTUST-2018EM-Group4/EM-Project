#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Vector.h"
#include "Matrix.h"

//定義控管資料class
class DataManager
{
private:	
	//儲存向量資料
	std::vector<Vector> Vectors;
	//紀錄向量ID，用於控管
	int  VectorVariableIndex;

	//Store Matrix Data
	std::vector<Matrix> Matrices;
	//Record Matrix ID
	int MatrixVariableIndex;

	//紀錄檔案路徑名稱
	std::string FileName;
public:
	DataManager();

	//讀取向量資料
	bool LoadVectorData();
	//取得向量資料
	std::vector<Vector> GetVectors();
	// find vector index
	int findVector(std::string name);

	//Read Matrix Data
	bool LoadMatrixData();
	//Get Matrix Data
	std::vector<Matrix> GetMatrices();
	// find matrix index
	int findMatrix(std::string name);

	//設置檔案路徑名稱
	void SetFileName(std::string fileName);
};
