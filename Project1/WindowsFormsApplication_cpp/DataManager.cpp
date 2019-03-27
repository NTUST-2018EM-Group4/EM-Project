#include"DataManager.h"
#include <cmath>
#define PI 3.1415926535897936384626

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
		//標記當前讀取向量ID
		int currentLoadVectorID = 0;
		//定義向量資料暫存變數
		std::vector<double> tempVectorData;
		//定義讀取檔案字串暫存變數
		std::string tempSring;
		//從檔案讀取字串，解析掉向量總數
		fin >> tempSring;

		//執行讀檔迴圈，並在讀到檔案結尾時結束
		while (!fin.eof())
		{
			//從檔案讀取字串
			fin >> tempSring;
			//解析到向量標記"V"
			if (tempSring == "V")
			{
				if (currentLoadVectorID != 0)
				{
					//定義暫存向量資料結構
					Vector tempVector;
					//存入向量資料
					tempVector.Data = tempVectorData;
					//定義向量變數名稱，依VectorVariableIndex變數作名稱的控管
					std::string vectorVariableTemp = "$v" + std::to_string(VectorVariableIndex);
					//存入向量變數名稱
					tempVector.Name = vectorVariableTemp;
					//存入向量
					Vectors.push_back(tempVector);
					//遞增VectorVariableIndex，以確保變數名稱不重複
					VectorVariableIndex++;
					//清除向量資料暫存
					tempVectorData.clear();
				}
				//遞增currentLoadVectorID，標記到當前讀取向量ID
				currentLoadVectorID++;
				//從檔案讀取字串，解析掉向量維度
				fin >> tempSring;
			}
			else
			{
				//讀取向量資料，並將string轉為double
				double value;
				value = (double)strtod(tempSring.c_str(), NULL);
				//將向量資料存入暫存
				tempVectorData.push_back(value);
			}

		}
		//讀入輸入檔案中最後一個向量資訊
		Vector tempVector;
		tempVector.Data = tempVectorData;
		std::string vectorVariableTemp = "$v" + std::to_string(VectorVariableIndex);
		tempVector.Name = vectorVariableTemp;
		Vectors.push_back(tempVector);
		VectorVariableIndex++;
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
		//定義讀取檔案字串暫存變數
		std::string tempSring;
		//從檔案讀取字串，解析掉Matrix總數(目前沒用到)
		fin >> tempSring;

		//執行讀檔迴圈，並在讀到檔案結尾時結束
		while (!fin.eof())
		{
			//從檔案讀取字串
			fin >> tempSring;

			//解析到Matrix標記"M"
			if (tempSring == "M")
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


Vector::Vector() :Name("")
{
	Data.resize(0);
}

Vector::Vector(std::vector<double> data) : Data(data) {}

Vector::Vector(double scalar)
{
	Data.push_back(scalar);
}

Vector::Vector(std::string name, std::vector<double> data) :Name(name), Data(data) {};

bool Vector::dimCheck(const Vector& Vb)
{
	if (this->Data.size() == Vb.Data.size())
	{
		return true;
	}
	return false;
}

const double Vector::Norm() const
{
	double ans = 0;
	for (int i = 0;i < this->Data.size(); i++)
	{
		ans += pow(this->Data[i], 2.0);
	}
	ans = sqrt(ans);
	return ans;
}

const Vector Vector::Normal()
{
	double norm = this->Norm();
	std::vector<double> ans(this->Data.size());
	for (int i = 0; i < this->Data.size(); i++)
	{
		ans[i] = this->Data[i] / norm;
	}
	return Vector("ans", ans);
}

const double Vector::Angle(const Vector& Vb)
{
	double cosTheta, theta = 0;
	cosTheta = (*this * Vb) / (this->Norm() * Vb.Norm());
	theta = acos(cosTheta);
	theta *= (180 / PI);
	return theta;
}

const double Vector::Com(const Vector& Vb)
{
	double ans;
	ans = (*this * Vb) / Vb.Norm();
	return ans;
}

const Vector Vector::Proj(const Vector & Vb)
{
	Vector ans, unit(Vb.Data.size());
	unit = Vb * (1 / Vb.Norm());
	ans = this->Com(Vb) * unit;
	return ans;
}

const Vector  Vector::operator+(const Vector& Vb)
{
	std::vector<double> ans;
	ans.resize(Vb.Data.size());
	for (int i = 0; i < Vb.Data.size(); i++)
	{
		ans[i] = this->Data[i] + Vb.Data[i];
	}
	return Vector("ans",ans);
}

const Vector Vector::operator-(const Vector & Vb)
{
	std::vector<double> ans;
	ans.resize(Vb.Data.size());
	for (int i = 0; i < Vb.Data.size(); i++)
	{
		ans[i] = this->Data[i] - Vb.Data[i];
	}
	return Vector("ans", ans);
}

//dot
const double Vector::operator*(const Vector & Vb)
{

	double ans = 0;
	for (int i = 0; i < Vb.Data.size(); i++)
	{
		ans += this->Data[i] * Vb.Data[i];
	}
	return ans;
}

//scalar
const Vector operator*(const Vector & Va, const Vector & Vb)
{
	std::vector<double> ans;

	for (int i = 0; i < Va.Data.size(); i++)
	{
		for (int j = 0; j < Vb.Data.size(); j++)
		{
			ans.push_back(Va.Data[i] * Vb.Data[j]);
		}
	}
	return Vector("ans", ans);
}

Matrix::Matrix() :Name("")
{
	Data.resize(0);
}

Matrix::Matrix(std::vector<Vector> data) : Data(data) {}

Matrix::Matrix(std::string name, std::vector<Vector> data) : Name(name), Data(data) {}
