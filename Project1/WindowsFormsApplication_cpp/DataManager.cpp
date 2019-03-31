#include"DataManager.h"
#include <math.h>

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

bool Vector::dimCheck(Vector Vb)
{
	if (this->Data.size() == Vb.Data.size())
	{
		return true;
	}
	return false;
}

const double Vector::Norm()
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
		if (abs(ans[i]) < 1E-10)
		{
			ans[i] = 0;
		}
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

const Vector Vector::operator*(const double & num)
{
	Vector temp = *this;
	for (int i = 0; i < this->Data.size(); i++)
	{
		temp.Data[i] *= num;
	}
	temp.Name = "result";
	return temp;
}

const Vector Vector::operator/(const double & num)
{
	Vector temp = *this;
	for (int i = 0; i < this->Data.size(); i++)
	{
		temp.Data[i] /= num;
	}
	temp.Name = "result";
	return temp;
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

Matrix::Matrix(char op, Matrix Ma, Matrix Mb)
{
	Matrix temp;

	switch (op)
	{
	case '+':
		temp = Ma + Mb;
		break;
	case '-':
		temp = Ma - Mb;
		break;
	case '*':
		temp = Ma * Mb;
		break;
	case '\\':
		throw "---Operator not Support---";
		break;
	default:
		break;
	}
	Name = "CalResult";
	this->Data = temp.Data;
}

const Matrix Matrix::operator+(const Matrix & Mb)
{
	if (dimCheck(Mb, '+'))
	{
		std::vector<Vector> ans;
		for (int i = 0; i < this->Data.size(); i++)
		{
			ans.push_back(this->Data[i] + Mb.Data[i]);
		}
		return Matrix("ans", ans);
	}
	else
	{
		throw "---Operator + process ERROR!---";
	}
}

const Matrix Matrix::operator-(const Matrix & Mb)
{
	if (dimCheck(Mb, '-'))
	{
		std::vector<Vector> ans;
		for (int i = 0; i < this->Data.size(); i++)
		{
			ans.push_back(this->Data[i] - Mb.Data[i]);
		}
		return Matrix("ans", ans);
	}
	else
	{
		throw "---Operator - process ERROR!---";
	}
}

const Matrix Matrix::operator*(const Matrix & Mb)
{
	if (dimCheck(Mb, '*'))
	{
		Matrix result;
		result.Data.resize(this->Data.size());
		for (int i = 0; i < this->Data.size(); i++)
		{
			for (int j = 0; j < Mb.Data[0].Data.size(); j++)
			{
				double temp = 0;
				for (int k = 0; k < Mb.Data.size(); k++)
				{
					temp += this->Data[i].Data[k] * Mb.Data[k].Data[j];
				}
				result.Data[i].Data.push_back(temp);
			}
		}
		return result;
	}
	else
	{
		throw "---Operator * process ERROR!---";
	}
}

const Matrix Matrix::trans()
{
	Matrix temp;
	if (Data.empty())
	{
		throw "---Empty Matrix---";
	}
	temp.Data.resize(Data[0].Data.size());
	for (int i = 0; i < Data.size(); i++)
	{
		for (int j = 0; j < Data[i].Data.size(); j++)
		{
			temp.Data[j].Data.push_back(Data[i].Data[j]);
		}
	}
	temp.Name = "Trans Result";
	return temp;
}

const Matrix Matrix::gaussian()
{
	Matrix temp = *this;
	// error handling
	if (temp.Data.empty())
	{
		throw "---Empty Matrix---";
	}
	// set dim
	int dim = temp.Data.size();
	if (temp.Data[0].Data.size() < dim)
	{
		dim = temp.Data[0].Data.size();
	}
	// Gaussian
	for (int i = 0; i < dim; i++)
	{
		// 如果橫條的首項係數為零，嘗試與下方橫條交換。
		if (temp.Data[i].Data[i] == 0)
		{
			for (int j = i + 1; j < temp.Data.size(); j++)
			{
				if (temp.Data[j].Data[i] != 0)
				{
					// swap(Data[i], Data[j])
					Vector tempVec = temp.Data[i];
					temp.Data[i] = temp.Data[j];
					temp.Data[j] = tempVec;
					break;
				}
			}
		}
		// 如果首項係數都是零，那就略過。
		if (temp.Data[i].Data[i] == 0) continue;

		// 抵銷下方橫條，令下方橫條的首項係數化成零。
		for (int j = i + 1; j < temp.Data.size(); j++)
		{
			if (temp.Data[j].Data[i] != 0)
			{
				double t = temp.Data[j].Data[i] / temp.Data[i].Data[i];
				temp.Data[j] = temp.Data[j] - temp.Data[i] * t;
			}
		}
	}
	return temp;
	throw "---Gaussian process error---";
}

const double Matrix::rank()
{
	// error handling
	if (this->Data.empty())
	{
		throw "---Empty Matrix---";
	}
	double rankValue = 0;
	Matrix gauss = this->gaussian();
	for (int i = 0; i < gauss.Data.size(); i++)
	{
		for (int j = 0; j < gauss.Data[i].Data.size(); j++)
		{
			if (gauss.Data[i].Data[j] != 0)
			{
				rankValue++;
				break;
			}
		}
	}
	return rankValue;
}

const double Matrix::det()
{
	Matrix temp = this->gaussian();
	// error handling
	if (temp.Data.empty())
	{
		throw "---Empty Matrix---";
	}
	// set dim
	int dim = temp.Data.size();
	if (temp.Data[0].Data.size() < dim)
	{
		dim = temp.Data[0].Data.size();
	}
	double detValue = 1.0;
	// Determinant
	for (int i = 0; i < dim; i++)
	{
		detValue *= temp.Data[i].Data[i];
	}
	return detValue;
}


System::String^ Matrix::outputStr()
{
	System::String^ Temp;
	Temp = gcnew System::String(Name.c_str());
	Temp += " = " + System::Environment::NewLine;

	for (int i = 0; i < Data.size(); i++)
	{
		std::string temp;
		temp += "[";
		for (int j = 0; j < Data[i].Data.size(); j++)
		{
			temp += std::to_string(Data[i].Data[j]);
			if (j != Data[i].Data.size() - 1)
				temp += ",";
		}
		temp += "]";
		Temp += gcnew System::String(temp.c_str());
		Temp += System::Environment::NewLine;
	}
	return Temp;
}

bool Matrix::dimCheck(Matrix Mb, char op)
{
	switch (op)
	{
	case '+' : case '-':
		if (this->Data.size() == Mb.Data.size())
		{
			for (int i = 0; i < this->Data.size(); i++)
			{
				if (this->Data[i].Data.size() != Mb.Data[i].Data.size())
				{
					throw "---Dimension not same---";
					return false;
				}
			}
		}
		else
		{
			throw "---Dimension not same---";
			return false;
		}
		return true;
		break;
	case '*':
		for (int i = 0; i < this->Data.size(); i++)
		{
			if (this->Data[i].Data.size() != Mb.Data.size())
			{
				throw "---Dimension not same---";
				return false;
			}
		}
		return true;
		break;
	default:
		throw "---Operator Check ERROR---";
		return false;
		break;
	}
}
