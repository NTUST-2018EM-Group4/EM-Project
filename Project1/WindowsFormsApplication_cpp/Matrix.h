#pragma once
#include <string>
#include <vector>
#include "Vector.h"

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
	const Matrix operator * (const Matrix& Mb);
	const Matrix operator / (const Matrix& Mb);

	//
	// Calculate Function
	//
	const Matrix trans();
	const Matrix gaussian();
	const double rank();
	const double det();
	const Matrix inverse();

	//
	// Tool Function
	//
	System::String^ outputStr();
	bool dimCheck(Matrix Mb, char op);
};

