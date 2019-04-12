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
	const Matrix minor(const int i, const int j) const;
	const double cofactor(const int i, const int j) const;
	const Matrix adjoint();
	const Matrix leastSquare(const Matrix& Mb);
	const std::vector<double> eigenVal() const;
	const Matrix eigenVec(const std::vector<double>& val) const;
	const double pm() const;

	//
	// Calculate Vector Function
	//
	friend const Matrix Ob(const int normal, const std::vector<Vector> ui);
	friend const bool isLI(const int normal, const std::vector<Vector> ui);

	//
	// Tool Function
	//
	System::String^ outputStr();
	bool dimCheck(const Matrix Mb, char op) const;

	//
	// Simulate vector function
	//
	int size() const;
	void push_back(Vector& num);
	Vector operator [] (const int& index);
};
