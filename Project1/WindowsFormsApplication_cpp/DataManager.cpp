#include"DataManager.h"

DataManager::DataManager()
{
	VectorVariableIndex = 0;
	MatrixVariableIndex = 0;
}

bool DataManager::LoadVectorData()
{
	std::fstream fin;
	//開啟檔案，傳入open函數的參數有兩個，欲開起的檔案名稱，開啟檔案的模式參數(這邊std::ios::in為讀取(輸入)狀態)
	fin.open(FileName, std::ios::in);
	//讀取失敗回傳false
	if (!fin)
	{
		return false;
	}
	else
	{
		// reset the Variable list
		Vectors.clear();
		// reset indexValue
		VectorVariableIndex = 0;

		//定義讀取檔案字串暫存變數
		std::string tempString;
		//從檔案讀取字串，解析掉Vector總數(目前沒用到)
		fin >> tempString;

		//執行讀檔迴圈，並在讀到檔案結尾時結束
		while (!fin.eof())
		{
			//從檔案讀取字串
			fin >> tempString;

			//解析到Vector標記"V"
			if (tempString == "V")
			{
				Vector tempVector;

				int dim;
				// store dim of vector
				fin >> dim;
				for (int i = 0; i < dim; i++)
				{
					double tempValue;
					fin >> tempValue;
					tempVector.Data.push_back(tempValue);
				}
				// set Vector name as $v[Index]
				tempVector.Name = "$v" + std::to_string(VectorVariableIndex);
				// add to Vector List of DataManager
				Vectors.push_back(tempVector);
				// Index ++
				VectorVariableIndex++;
				// clean temp data to avoid duplicate data bug
				tempVector.Data.clear();
				tempVector.Name = "";
				tempString = "";
			}
		}
		//讀取成功回傳false
		return true;
	}
}
bool DataManager::LoadMatrixData()
{
	std::fstream fin;

	//開啟檔案，傳入open函數的參數有兩個，欲開起的檔案名稱，開啟檔案的模式參數(這邊std::ios::in為讀取(輸入)狀態)
	fin.open(FileName, std::ios::in);

	//讀取失敗回傳false
	if (!fin)
	{
		return false;
	}
	else
	{
		// reset the Variable list
		Matrices.clear();
		// reset indexValue
		MatrixVariableIndex = 0;

		//定義讀取檔案字串暫存變數
		std::string tempString;
		//從檔案讀取字串，解析掉Matrix總數(目前沒用到)
		fin >> tempString;

		//執行讀檔迴圈，並在讀到檔案結尾時結束
		while (!fin.eof())
		{
			//從檔案讀取字串
			fin >> tempString;

			//解析到Matrix標記"M"
			if (tempString == "M")
			{
				Matrix tempMatrix;

				int row, col;
				// store row & column dim
				fin >> row >> col;
				for (int i = 0; i < row; i++)
				{
					// to store row data as Vector
					Vector tempRowData;
					for (int j = 0; j < col; j++)
					{
						double tempValue;
						fin >> tempValue;
						tempRowData.Data.push_back(tempValue);
					}
					// add in tempMatrix Data
					tempMatrix.Data.push_back(tempRowData);
					// avoid duplicate data bug
					tempRowData.Data.clear();
				}
				// set Matrix name as $m[Index]
				tempMatrix.Name = "$m" + std::to_string(MatrixVariableIndex);
				// add to Matrix List of DataManager
				Matrices.push_back(tempMatrix);
				// Index ++
				MatrixVariableIndex++;
				// clean temp data to avoid bug
				tempMatrix.Data.clear();
				tempMatrix.Name = "";
				tempString = "";
			}
		}
		//讀取成功回傳false
		return true;
	}
}

std::vector<Vector> DataManager::GetVectors()
{
	return Vectors;
}
std::vector<Matrix> DataManager::GetMatrices()
{
	return Matrices;
}
void DataManager::SetFileName(std::string fileName)
{
	FileName = fileName;
}


