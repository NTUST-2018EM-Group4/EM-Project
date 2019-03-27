#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>

//定義向量資料結構
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

//定義控管資料class
class DataManager
{
private:
	//儲存向量資料
	std::vector<Vector> Vectors;
	//紀錄向量ID，用於控管
	int  VectorVariableIndex;

	//Store Matrix Data
	std::vector<Matrix> Matrices;
	//Record Matrix ID
	int MatrixVariableIndex;

	//紀錄檔案路徑名稱
	std::string FileName;
public:
	DataManager();

	//讀取向量資料
	bool LoadVectorData();
	//取得向量資料
	std::vector<Vector> GetVectors();

	//Read Matrix Data
	bool LoadMatrixData();
	//Get Matrix Data
	std::vector<Matrix> GetMatrices();

	//設置檔案路徑名稱
	void SetFileName(std::string fileName);
};
