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

const Matrix Matrix::minor(const int i, const int j) const
{
	Matrix result;
	int dim = this->Data.size() - 1;
	//set result to n-1*n-1 matrix
	result.Data.resize(dim);
	for (int m = 0;m < dim; m++)
	{
		result.Data[m].Data.resize(dim);
	}

	for (int m = 0, I = 0; m < dim + 1; m++)
	{
		if (m != i)
		{
			for (int n = 0, J = 0; n < dim + 1; n++)
			{
				if (n != j)
					result.Data[I].Data[J++] = this->Data[m].Data[n];
			}
			I++;
		}
	}
	return result;
}

const double Matrix::cofactor(const int i, const int j) const
{
	//-1^i+j * det(minor(i,j))
	return pow(-1, i + j) * this->minor(i, j).det();
}

const Matrix Matrix::adjoint()
{
	Matrix result;
	int dim = this->size();
	// error handling
	if (this->Data.empty()) throw "---Empty Matrix---";
	if (this->Data.size() != this->Data[0].Data.size())
	{
		throw "---Matrix not square---";
	}
	
	//set result to n-1*n-1 matrix
	result.Data.resize(dim);
	for (int m = 0; m < dim; m++)
	{
		result.Data[m].Data.resize(dim);
	}

	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			result.Data[i].Data[j] = this->cofactor(i, j);
		}
	}
	return result.trans();
}

const Matrix Matrix::leastSquare(const Matrix & Mb)
{
	Matrix temp = *this;
	// error handling
	if (temp.Data.empty()) throw "---Empty Matrix---";
	if (Mb.Data.empty()) throw "---Empty Matrix---";

	temp = this->trans();
	temp = temp * *this;
	temp = temp.inverse();
	temp = temp * this->trans();
	temp = temp * Mb;

	return temp;
	throw "---LeastSquare process error---";
}

const std::vector<double> Matrix::eigenVal() const
{
	// error handling
	if (this->Data.empty()) throw "---Empty Matrix---";

	if (this->Data.size() != this->Data[0].Data.size())
	{
		throw "---Matrix not square---";
	}
	//get polynomial for lambda
	int dim = this->Data.size();
	std::vector<double> coe(dim + 1);
	//todo (3D matrix)
	std::vector<double> result;
	switch (this->size())
	{
	case 1:
		result.push_back(this->Data[0].Data[0]);
		break;
	case 2:
		//get polynomial for lambda
		/***explosion***/
		coe[2] = 1;	//lambda^2 = 1
		coe[1] = -this->Data[0].Data[0] - this->Data[1].Data[1];	//lambda
		coe[0] += this->Data[0].Data[0] * this->Data[1].Data[1];	//constant
		coe[0] -= this->Data[1].Data[0] * this->Data[0].Data[1];	//constant
		//use quadratic eqution get eigen value
		double D;
		D = std::pow(coe[1], 2) - 4 * coe[2] * coe[0];	//D = b^2 - 4ac
		result.push_back((-coe[1] + std::sqrt(D)) / (2 * coe[2]));	//x = (-b+D) / 2a
		result.push_back((-coe[1] - std::sqrt(D)) / (2 * coe[2]));	//x = (-b-D) / 2a
		break;
	case 3:
		//get polynomial for lambda
		/***explosion***/
		coe[3] = -1;
		for (int i = 0; i< 3; i++)
		{
			coe[2] += this->Data[i].Data[i];
			coe[1] -= this->Data[i % 3].Data[i % 3] * this->Data[(i + 1) % 3].Data[(i + 1) % 3];
			coe[1] += this->Data[i % 3].Data[(i + 1) % 3] * this->Data[(i + 1) % 3].Data[i % 3];
		}
		coe[0] = this->det();
		//同乘-1
		for (int i = 0; i < 4;i++)
		{
			coe[i] = -coe[i];
		}
		//use cubic eqution get eigen value	//x^3 + ax^2 + bx +c = 0
		double Q, R, theta, temp;
		Q = (pow(coe[2], 2) - 3 * coe[1]) / 9;	//Q = (a^2-3b)/9
		R = (2 * pow(coe[2], 3) - 9 * coe[2] * coe[1] + 27 * coe[0]) / 54;	//R = (2a^3-9ab+27c)/54
		temp = R / sqrt(pow(Q, 3));	//sqrt(pow(Q, 3))	pow(Q, 1.5)
		while (temp > 2 * PI)
			temp -= 2 * PI;	//acos argument can't > 1
		theta = acos(temp);	
		result.push_back(-2 * sqrt(Q)*cos(theta / 3) - coe[2] / 3);
		result.push_back(-2 * sqrt(Q)*cos((theta + 2 * PI) / 3) - coe[2] / 3);
		result.push_back(-2 * sqrt(Q)*cos((theta - 2 * PI) / 3) - coe[2] / 3);
		break;
	default:
		throw "---Dimension not support---";
		break;
	}
	//set precision
	for (int i = 0; i < result.size(); i++)
	{
		result[i] = Round(result[i], 6);
	}
	return result;
}

const Matrix Matrix::eigenVec(const std::vector<double>& val) const
{
	double dim = this->size();
	Matrix result, tempM;
	//set result to n(1)*n
	result.Data.resize(val.size());
	for (int i = 0; i < val.size(); i++)
	{
		result.Data[i].Data.resize(dim);
	}
	if (dim == 1)
	{
		result.Data[0].Data[0] = 1;
		return result;
	}
	for (int i = 0; i < val.size(); i++)
	{
		tempM = *this;
		for (int j = 0; j < dim; j++)
		{
			tempM.Data[j].Data[j] -= val[i];	//(A - lambda I)v = 0
		}
		tempM = tempM.gaussian(1, 0);

		for (int j = 0, k = dim - 1; j < dim; j++)
		{
			if (tempM.Data[j].Data[k] != 0)	//avoid -0
			{	
				//get eigen vector to return
				if (tempM.Data[j].Data[j] == 1)	//移項加負號	
				{
					result.Data[i].Data[j] = -tempM.Data[j].Data[k];
					result.Data[i].Data[dim - 1] = 1;	//最後一項自由變數補1
				}
				else if (tempM.Data[j].Data[j] == 0)	//0 輸出原向量
				{
					result.Data[i].Data[j] = tempM.Data[j].Data[k];
				}
			}
		}
		
		result.Data[i] = result.Data[i].Normal();	//normalization
	}

	return result;
}

const double Matrix::pm() const
{
	// error handling
	if (this->Data.empty()) throw "---Empty Matrix---";

	if (this->Data.size() != this->Data[0].Data.size())
	{
		throw "---Matrix not square---";
	}
	Matrix A = *this, X, temp;
	double lastEigen, max = 0;
	bool foundEigen;
	// set temp to n*1 and set all to 1
	X.Data.resize(this->size());

	for (int i = 0; i < this->size(); i++)
	{
		X.Data[i].Data.push_back(1);
	}
	foundEigen = false;
	//approaching
	for (int i = 0; i < 500 && !foundEigen; i++)
	{
		X = A * X;
		lastEigen = max;
		max = 0;
		for (int j = 0; j < this->size(); j++)
		{
			max = (abs(X.Data[j].Data[0]) > abs(max)) ? X.Data[j].Data[0] : max;
		}
		//zoom
		for (int j = 0; j < this->size(); j++)
		{
			X.Data[j] = X.Data[j] / max;
		}
		if (abs(lastEigen - max) < 1E-12)
		{
			foundEigen = true;
		}
	}
	temp = A * X;					//AX
	temp = temp.trans() * X;		//AX dot X = AX^t * X
	X = X.trans() * X;				//X*X
	return (temp.Data[0].Data[0] / X.Data[0].Data[0]);
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

const Matrix Ob(const int normal, const std::vector<Vector> ui)
{
	std::vector<Vector> Vi(normal);
	std::vector<Vector> ans(normal);

	Vi[0] = ui[0];
	ans[0] = Vi[0].Normal();
	//formula from wikipedia "Gram–Schmidt process"
	for (int i = 1; i < normal; i++)
	{
		Vector sum, temp;
		sum.Data.resize(normal);
		for (int j = 0; j <= i - 1; j++)
		{
			sum = sum + (ans[j] * (ans[j] * ui[i]));
		}
		Vi[i] = ui[i] - sum;
		ans[i] = Vi[i].Normal();
	}
	return Matrix("ans", ans);
}

const bool isLI(const int normal, const std::vector<Vector> ui)
{
	Matrix A(ui), At = A.trans(), temp;
	temp = At * A;
	if (temp.det() != 0)
		return true;
	return false;
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
