#pragma once
#include <string>
#include <vector>
#include <cmath>
#define PI 3.1415926535897936384626

// Defined Struct Vector
struct Vector
{
	//
	// data member
	//
	std::string Name;
	std::vector<double> Data;

	//
	// Constructor
	//
	Vector();
	Vector(std::vector<double> data);
	Vector(double scalar);
	Vector(std::string name, std::vector<double> data);
	Vector(char op, Vector Va, Vector Vb);

	//
	// Operator Overloading
	//
	const Vector operator + (const Vector& Vb) const;
	const Vector operator - (const Vector& Vb) const;
	const Vector operator * (const Vector& Vb) const;
	// const double operator * (const Vector& Vb);
	const Vector operator * (const double& num);
	const Vector operator / (const double& num);
	// friend const  Vector operator * (const Vector& Va, const Vector& Vb);

	//
	// Calculate Function
	//
	const double Norm() const;
	const Vector Normal() const;
	const double Angle(const Vector& Vb);
	const double Com(const Vector& Vb);
	const Vector Proj(const Vector& Vb);
	const Vector Cross(const Vector& Vb) const;
	const double Area(const Vector& Vb);

	//
	// Tool Function
	//
	bool dimCheck(const Vector& Vb);
	bool dimCheck(const Vector& Vb, char op) const;
	System::String^ outputStr();
};