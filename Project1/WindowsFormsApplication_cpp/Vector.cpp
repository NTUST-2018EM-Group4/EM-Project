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
			throw "---Dimension not same---";
			return false;
		}
		return true;
		break;
	case '*':
		if (this->Data.size() != Vb.Data.size() && \
			Vb.Data.size() != 1 && this->Data.size() != 1)
		{
			throw "---Dimension not same---";
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

const Vector Vector::Normal() const
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
	Vector temp = Vector('*', *this, Vb);
	cosTheta = temp.Data[0] / (this->Norm() * Vb.Norm());
	theta = acos(cosTheta);
	theta *= (180 / PI);
	return theta;
}

const double Vector::Com(const Vector& Vb)
{
	double ans;
	Vector temp = Vector('*',*this, Vb);
	ans = temp.Data[0] / Vb.Norm();
	return ans;
}

const Vector Vector::Proj(const Vector & Vb)
{
	Vector ans, unit;
	unit = Vb * (1 / Vb.Norm());
	ans = unit * this->Com(Vb);
	return ans;
}

const Vector Vector::Cross(const Vector & Vb) const
{
	std::vector<double> ans(3);
	for (int i = 0; i < 3; i++)
	{
		ans[i] = this->Data[(i + 1) % 3] * Vb.Data[(i + 2) % 3] \
			- Vb.Data[(i + 1) % 3] * this->Data[(i + 2) % 3];
	}
	return Vector("ans", ans);
}

const double Vector::Area(const Vector & Vb)
{
	double ans, theta;
	theta = this->Angle(Vb) * (PI / 180);	//deg to rad
	ans = this->Norm() * Vb.Norm() * sin(theta) / 2;
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

int Vector::size()
{
	return Data.size();
}

void Vector::push_back(double & num)
{
	Data.push_back(num);
}

double Vector::operator[](const int & index)
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
		throw "---Operator + process ERROR!---";
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
		throw "---Operator - process ERROR!---";
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
		throw "---Operator * process ERROR!---";
	}
}

//dot
//const double Vector::operator*(const Vector & Vb)
//{
//
//	double ans = 0;
//	for (int i = 0; i < Vb.Data.size(); i++)
//	{
//		ans += this->Data[i] * Vb.Data[i];
//	}
//	return ans;
//}

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
//const Vector operator*(const Vector & Va, const Vector & Vb)
//{
//	std::vector<double> ans;
//
//	for (int i = 0; i < Va.Data.size(); i++)
//	{
//		for (int j = 0; j < Vb.Data.size(); j++)
//		{
//			ans.push_back(Va.Data[i] * Vb.Data[j]);
//		}
//	}
//	return Vector("ans", ans);
//}
