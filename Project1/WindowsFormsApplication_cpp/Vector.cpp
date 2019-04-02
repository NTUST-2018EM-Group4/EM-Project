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
	Vector ans, unit;
	unit = Vb * (1 / Vb.Norm());
	ans = this->Com(Vb) * unit;
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



const Vector  Vector::operator+(const Vector& Vb) const
{
	std::vector<double> ans;
	ans.resize(Vb.Data.size());
	for (int i = 0; i < Vb.Data.size(); i++)
	{
		ans[i] = this->Data[i] + Vb.Data[i];
	}
	return Vector("ans", ans);
}

const Vector Vector::operator-(const Vector & Vb) const
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


