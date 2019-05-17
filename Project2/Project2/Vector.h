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
	const Vector operator * (const double& num);
	const Vector operator / (const double& num);

	//
	// Calculate Function
	//
	const double Norm() const;

	//
	// Tool Function
	//
	bool dimCheck(const Vector& Vb);
	bool dimCheck(const Vector& Vb, char op) const;
	bool zeroCheck();
	void zeroExpand(int dim);
	System::String^ outputStr();
	std::string outputStdStr();

	//
	// Simulate vector function
	//
	int size() const;
	void push_back(double& num);
	double& operator [] (const int& index);
};
