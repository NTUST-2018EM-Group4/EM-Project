#include "Matrix.h"
#include <cmath>

Matrix::Matrix() :Name("")
{
	Data.resize(0);
}

Matrix::Matrix(std::vector<Vector> data) : Data(data) {}

Matrix::Matrix(std::string name, std::vector<Vector> data) : Name(name), Data(data) {}

Matrix::Matrix(char op, Matrix Ma, Matrix Mb)
{
	Name = "CalResult";
	switch (op)
	{
	case '+':
		*this = Ma + Mb;
		break;
	case '-':
		*this = Ma - Mb;
		break;
	case '*':
		*this = Ma * Mb;
		break;
	case '\\':
		*this = Ma / Mb;
		break;
	default:
		break;
	}
}

const Matrix Matrix::operator+(const Matrix & Mb)
{
	if (dimCheck(Mb, '+'))
	{
		Matrix result;
		for (int i = 0; i < this->Data.size(); i++)
		{
			result.Data.push_back(this->Data[i] + Mb.Data[i]);
		}
		return result;
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
		Matrix result;
		for (int i = 0; i < this->Data.size(); i++)
		{
			result.Data.push_back(this->Data[i] + Mb.Data[i]);
		}
		return result;
	}
	else throw "---Operator - process ERROR!---";
}

const Matrix Matrix::operator*(const Matrix & Mb) const
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
	else throw "---Operator * process ERROR!---";
}

const Matrix Matrix::operator*(const double & num)
{
	Matrix temp = *this;
	// error handling
	if (temp.Data.empty()) throw "---Empty Matrix---";

	for (int i = 0; i < temp.Data.size(); i++)
	{
		temp.Data[i] = temp.Data[i] * num;
	}
	return temp;
	throw "---Operator * process ERROR!---";
}

const Matrix Matrix::operator/(const Matrix & Mb)
{
	if (dimCheck(Mb, '\\'))
	{
		Matrix inver = this->inverse();
		Matrix result = inver * Mb;
		result.Name = this->Name + " \\ " + Mb.Name;
		return result;
	}
	else throw "---Operator \\ process ERROR!---";
}

const Matrix Matrix::trans()
{
	Matrix temp;
	if (Data.empty()) throw "---Empty Matrix---";

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

const Matrix Matrix::gaussian(int sign, bool mode) const
{
	Matrix temp = *this;
	// error handling
	if (temp.Data.empty()) throw "---Empty Matrix---";

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
					Vector tempVec = temp.Data[i] * sign;
					temp.Data[i] = temp.Data[j];
					temp.Data[j] = tempVec;
					break;
				}
			}
		}
		// 如果首項係數都是零，那就略過。
		if (temp.Data[i].Data[i] == 0) continue;

		if (mode == true) // default Gaussian Method
		{
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
		else // Gauss-Jordan Method
		{
			// 將橫條首項變成1
			double t = temp.Data[i].Data[i];
			temp.Data[i] = temp.Data[i] / t;

			for (int j = 0; j < temp.Data.size(); j++)
			{
				if (i != j && temp.Data[j].Data[i] != 0)
				{
					double t = temp.Data[j].Data[i];
					temp.Data[j] = temp.Data[j] - temp.Data[i] * t;
					//zeroing to ignore the deviation
					for (int k = 0; k < temp.Data[j].size(); k++)
					{
						if (abs(temp.Data[j].Data[k]) < 1.5E-6)
							temp.Data[j].Data[k] = 0;
					}
				}
			}

			// Check zero row is under
			for (int i = 0; i < temp.size(); i++)
			{
				bool zeroCheck = true;
				for (int j = 0; j < temp[i].size(); j++)
				{
					if (temp[i][j] != 0)
					{
						zeroCheck = false;
						break;
					}
				}
				if (zeroCheck && i != temp.size() - 1)
				{
					Vector tempVec = temp[i];
					temp.Data.erase(temp.Data.begin() + i);
					temp.push_back(tempVec);
				}
			}
		}
	}


	return temp;
	throw "---Gaussian process error---";
}

const double Matrix::rank()
{
	// error handling
	if (this->Data.empty()) throw "---Empty Matrix---";
	double rankValue = 0;
	Matrix gauss = this->gaussian(1, true);
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

const double Matrix::det() const
{
	Matrix temp = this->gaussian(-1, true);
	// error handling
	if (temp.Data.empty()) throw "---Empty Matrix---";

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

const Matrix Matrix::inverse()
{
	Matrix temp = *this;
	// error handling
	if (temp.Data.empty()) throw "---Empty Matrix---";

	if (this->Data.size() != this->Data[0].Data.size())
	{
		throw "---Matrix not square---";
	}
	// 填好參數化的部分
	Matrix inver;
	inver.Data.resize(temp.Data.size());
	for (int i = 0; i < inver.Data.size(); i++)
	{
		for (int j = 0; j < inver.Data.size(); j++)
		{
			if (i == j)
			{
				inver.Data[i].Data.push_back(1.0);
			}
			else
			{
				inver.Data[i].Data.push_back(0.0);
			}
		}
	}

	// 開始進行高斯喬登消去法
	// 內容幾乎與高斯消去法相同
	for (int i = 0; i < temp.Data.size(); i++)
	{
		if (temp.Data[i].Data[i] == 0)
		{
			for (int j = i + 1; j < temp.Data.size(); j++)
			{
				if (temp.Data[j].Data[i] != 0)
				{
					// swap(temp.Data[i], temp.Data[j])
					Vector tempVec = temp.Data[i];
					temp.Data[i] = temp.Data[j];
					temp.Data[j] = tempVec;

					// swap(inver.Data[i], inver.Data[j])
					tempVec = inver.Data[i];
					inver.Data[i] = inver.Data[j];
					inver.Data[j] = tempVec;
					break;
				}
			}
		}
		// 反矩陣不存在
		if (temp.Data[i].Data[i] == 0) throw "---Inverse Matrix not exist---";

		// 將橫條首項變成1
		double t = temp.Data[i].Data[i];
		temp.Data[i] = temp.Data[i] / t;
		inver.Data[i] = inver.Data[i] / t;

		for (int j = 0; j < temp.Data.size(); j++)
		{
			if (i != j && temp.Data[j].Data[i] != 0)
			{
				double t = temp.Data[j].Data[i];
				temp.Data[j] = temp.Data[j] - temp.Data[i] * t;
				inver.Data[j] = inver.Data[j] - inver.Data[i] * t;
			}
		}
	}
	inver.Name = "Inverse (" + this->Name + ")";
	return inver;
	throw "---Inverse process error---";
}

// Ref: https://dotblogs.com.tw/forloop/2016/07/31/rounding
double Round(double num, int index)
{
	bool isNegative = false; // whether is negative number or not

	if (num < 0) // if this number is negative, then convert to positive number
	{
		isNegative = true;
		num = -num;
	}

	if (index >= 0)
	{
		int multiplier;
		multiplier = pow(10, index);
		num = (int)(num * multiplier + 0.5) / (multiplier * 1.0);
	}

	if (isNegative) // if this number is negative, then convert to negative number
	{
		num = -num;
	}

	return num;
}

System::String^ Matrix::outputStr()
{
	System::String^ Temp;
	Temp = gcnew System::String(Name.c_str());

	if (this->size() == 0)
	{
		Temp += System::Environment::NewLine;
		return Temp;
	}

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

std::string Matrix::outputStdStr()
{
	std::string result = "";

	if (this->size() == 0)
	{
		return result;
	}

	for (int i = 0; i < Data.size(); i++)
	{
		result += "[";
		for (int j = 0; j < Data[i].Data.size(); j++)
		{
			result += std::to_string(Data[i].Data[j]);
			if (j != Data[i].Data.size() - 1)
				result += ",";
		}
		result += "]";
	}
	return result;
}

bool Matrix::dimCheck(const Matrix Mb, char op) const
{
	switch (op)
	{
	case '+': case '-':
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
	case '\\':
		for (int i = 0; i < this->Data.size(); i++)
		{
			if (this->Data[i].Data.size() != this->Data.size())
			{
				throw "---Fisrt Matrix not square---";
				return false;
			}
		}
		if (Mb.Data.size() == this->Data.size())
		{
			for (int i = 0; i < Mb.Data.size(); i++)
			{
				if (Mb.Data[i].Data.size() != 1)
				{
					throw "---Second Matrix not n*1---";
					return false;
				}
			}
		}
		else
		{
			throw "---Second Matrix dimension not same as First's---";
			return false;
		}
		return true;
		break;
	default:
		throw "---Operator Check ERROR---";
		return false;
		break;
	}
}

int Matrix::size() const
{
	return Data.size();
}

void Matrix::push_back(Vector & num)
{
	Data.push_back(num);
}

Vector Matrix::operator[](const int & index)
{
	return Data.at(index);
}
