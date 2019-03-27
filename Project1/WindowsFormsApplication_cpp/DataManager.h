#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>

//�w�q�V�q��Ƶ��c
struct Vector
{
	std::string Name;
	std::vector<double> Data;

	
	Vector();
	Vector(std::vector<double> data);
	Vector(double scalar);
	Vector(std::string name, std::vector<double> data);
	const Vector operator + (const Vector& Vb);
	const Vector operator - (const Vector& Vb);
	const double operator * (const Vector& Vb);
	friend const  Vector operator * (const Vector& Va, const Vector& Vb);

	bool dimCheck(const Vector& Vb);
	const double Norm() const;
	const Vector Normal();
	const double Angle(const Vector& Vb);
	const double Com(const Vector& Vb);
	const Vector Proj(const Vector& Vb);
	const Vector Cross(const Vector& Vb);
};

//Defined Struct Matrix
struct Matrix
{
	std::string Name;
	std::vector<Vector> Data;

	Matrix();
	Matrix(std::vector<Vector> data);
	Matrix(std::string name, std::vector<Vector> data);
};

//�w�q���޸��class
class DataManager
{
private:
	//�x�s�V�q���
	std::vector<Vector> Vectors;
	//�����V�qID�A�Ω󱱺�
	int  VectorVariableIndex;

	//Store Matrix Data
	std::vector<Matrix> Matrices;
	//Record Matrix ID
	int MatrixVariableIndex;

	//�����ɮ׸��|�W��
	std::string FileName;
public:
	DataManager();

	//Ū���V�q���
	bool LoadVectorData();
	//���o�V�q���
	std::vector<Vector> GetVectors();

	//Read Matrix Data
	bool LoadMatrixData();
	//Get Matrix Data
	std::vector<Matrix> GetMatrices();

	//�]�m�ɮ׸��|�W��
	void SetFileName(std::string fileName);
};
