#include "Vector.h"

Vector::Vector() :Name("")
{
	Data.resize(0);
}

Vector::Vector(std::vector<double> data) : Data(data) {}

Vector::Vector(double scalar)
{
	Data.push_back(scalar);
}

Vector::Vector(std::string name, std::vector<double> data) :Name(name), Data(data) {}

Vector::Vector(char op, Vector Va, Vector Vb)
{
	Name = "CalResult";
	switch (op)
	{
	case '+':
		*this = Va + Vb;
		break;
	case '-':
		*this = Va - Vb;
		break;
	case '*':
		*this = Va * Vb;
		break;
	default:
		break;
	}
}

bool Vector::dimCheck(const Vector& Vb)
{
	if (this->Data.size() == Vb.Data.size())
	{
		return true;
	}
	return false;
}

bool Vector::dimCheck(const Vector & Vb, char op) const
{
	switch (op)
	{
	case '+': case '-':
		if (this->Data.size() != Vb.Data.size())
		{
			throw "---ERROR in Vector::dimCheck(const Vector & Vb, char op): Dimension not same---";
			return false;
		}
		return true;
		break;
	case '*':
		if (this->Data.size() != Vb.Data.size() && \
			Vb.Data.size() != 1 && this->Data.size() != 1)
		{
			throw "---ERROR in Vector::dimCheck(const Vector & Vb, char op): Dimension not same---";
			return false;
		}
		return true;
		break;
	default:
		throw "---ERROR in Vector::dimCheck(const Vector & Vb, char op): Operator Check ERROR---";
		return false;
		break;
	}
}

bool Vector::zeroCheck()
{
	// check Vector is zero vector or not

	bool isZero = true;
	for (int i = 0; i < this->size(); i++)
	{
		if (this->Data[i] != 0)
		{
			isZero = false;
			break;
		}
	}
	return isZero;
}

void Vector::zeroExpand(int dim)
{
	this->Data.clear();
	this->Data.resize(dim, 0);
}

const double Vector::Norm() const
{
	double ans = 0;
	for (int i = 0; i < this->Data.size(); i++)
	{
		ans += pow(this->Data[i], 2.0);
	}
	ans = sqrt(ans);
	return ans;
}

System::String ^ Vector::outputStr()
{
	System::String^ Temp;
	Temp = gcnew System::String(Name.c_str());

	if (this->size() == 0)
	{
		Temp += System::Environment::NewLine;
		return Temp;
	}

	Temp += " = [";

	std::string temp = "";
	for (int i = 0; i < Data.size(); i++)
	{
		temp += std::to_string(Data[i]);
		if (i != Data.size() - 1)
		{
			temp += ",";
		}
	}
	temp += "]";
	Temp += gcnew System::String(temp.c_str());
	Temp += System::Environment::NewLine;
	return Temp;
}

std::string Vector::outputStdStr()
{
	std::string outputStr;
	outputStr = Name;

	if (this->size() == 0)
	{
		outputStr += "\n";
		return outputStr;
	}

	outputStr += " = [";

	for (int i = 0; i < Data.size(); i++)
	{
		outputStr += std::to_string(Data[i]);
		if (i != Data.size() - 1)
		{
			outputStr += ",";
		}
	}
	outputStr += "]";

	return outputStr;
}

int Vector::size() const
{
	return Data.size();
}

void Vector::push_back(const double & num)
{
	Data.push_back(num);
}

double& Vector::operator[](const int & index)
{
	return Data.at(index);
}

const Vector Vector::operator+(const Vector& Vb) const
{
	if (dimCheck(Vb, '+'))
	{
		Vector result;
		for (int i = 0; i < this->Data.size(); i++)
		{
			result.Data.push_back(this->Data[i] + Vb.Data[i]);

			if (abs(result[i]) < 1E-6)
			{
				result.Data[i] = 0;
			}
		}
		return result;
	}
	else
	{
		throw "---ERROR in Vector::operator+(const Vector& Vb): process ERROR---";
	}
}

const Vector Vector::operator-(const Vector & Vb) const
{
	if (dimCheck(Vb, '-'))
	{
		Vector result;
		for (int i = 0; i < this->Data.size(); i++)
		{
			result.Data.push_back(this->Data[i] - Vb.Data[i]);

			if (abs(result[i]) < 1E-6)
			{
				result.Data[i] = 0;
			}
		}
		return result;
	}
	else
	{
		throw "---ERROR in Vector::operator-(const Vector& Vb): process ERROR---";
	}
}

const Vector Vector::operator*(const Vector & Vb) const
{
	if (dimCheck(Vb, '*'))
	{
		Vector result;

		// Scalar Calculate
		if (this->Data.size() == 1 || Vb.Data.size() == 1)
		{
			for (int i = 0; i < this->Data.size(); i++)
			{
				for (int j = 0; j < Vb.Data.size(); j++)
				{
					result.Data.push_back(this->Data[i] * Vb.Data[j]);
				}
			}
		}
		// Dot Calculate
		else
		{
			double dotValue = 0;
			for (int i = 0; i < Vb.Data.size(); i++)
			{
				dotValue += this->Data[i] * Vb.Data[i];
			}
			result.Data.push_back(dotValue);
		}
		return result;
	}
	else
	{
		throw "---ERROR in Vector::operator*(const Vector& Vb): process ERROR---";
	}
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
