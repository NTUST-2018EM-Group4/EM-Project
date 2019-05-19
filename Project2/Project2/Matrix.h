#pragma once
#include <string>
#include <vector>
#include "Vector.h"

//set precision
double Round(double num, int index);

//Defined Struct Matrix
struct Matrix
{
	//
	// data member
	//
	std::string Name;
	std::vector<Vector> Data;

	//
	// Struct Constructor
	//
	Matrix();
	Matrix(std::vector<Vector> data);
	Matrix(std::string name, std::vector<Vector> data);
	Matrix(char op, Matrix Ma, Matrix Mb);

	//
	// Operator Overloading
	//
	const Matrix operator + (const Matrix& Mb);
	const Matrix operator - (const Matrix& Mb);
	const Matrix operator * (const Matrix& Mb) const;
	const Matrix operator * (const double& num);
	const Matrix operator / (const Matrix& Mb);

	//
	// Calculate Function
	//
	const Matrix trans();
	const Matrix gaussian(int sign, bool mode) const;
	const double rank();
	const double det() const;
	const Matrix inverse();



	//
	// Tool Function
	//
	System::String^ outputStr();
	std::string outputStdStr();
	bool dimCheck(const Matrix Mb, char op) const;

	//
	// Simulate vector function
	//
	int size() const;
	void push_back(Vector& num);
	Vector& operator [] (const int& index);
};
