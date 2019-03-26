#include"DataManager.h"

DataManager::DataManager()
{
	VectorVariableIndex = 0;
	MatrixVariableIndex = 0;
}

bool DataManager::LoadVectorData()
{
	std::fstream fin;
	//�}���ɮסA�ǤJopen��ƪ��ѼƦ���ӡA���}�_���ɮצW�١A�}���ɮת��Ҧ��Ѽ�(�o��std::ios::in��Ū��(��J)���A)
	fin.open(FileName, std::ios::in);
	//Ū�����Ѧ^��false
	if (!fin)
	{
		return false;
	}
	else
	{
		//�аO��eŪ���V�qID
		int currentLoadVectorID = 0;
		//�w�q�V�q��ƼȦs�ܼ�
		std::vector<double> tempVectorData;
		//�w�qŪ���ɮצr��Ȧs�ܼ�
		std::string tempSring;
		//�q�ɮ�Ū���r��A�ѪR���V�q�`��
		fin >> tempSring;
		
		//����Ū�ɰj��A�æbŪ���ɮ׵����ɵ���
		while (!fin.eof())
		{
			//�q�ɮ�Ū���r��
			fin >> tempSring;
			//�ѪR��V�q�аO"V"
			if (tempSring == "V")
			{
				if (currentLoadVectorID != 0)
				{
					//�w�q�Ȧs�V�q��Ƶ��c
					Vector tempVector;
					//�s�J�V�q���
					tempVector.Data = tempVectorData;
					//�w�q�V�q�ܼƦW�١A��VectorVariableIndex�ܼƧ@�W�٪�����
					std::string vectorVariableTemp = "$v" + std::to_string(VectorVariableIndex);
					//�s�J�V�q�ܼƦW��
					tempVector.Name = vectorVariableTemp;
					//�s�J�V�q
					Vectors.push_back(tempVector);
					//���WVectorVariableIndex�A�H�T�O�ܼƦW�٤�����
					VectorVariableIndex++;
					//�M���V�q��ƼȦs
					tempVectorData.clear();
				}
				//���WcurrentLoadVectorID�A�аO���eŪ���V�qID
				currentLoadVectorID++;
				//�q�ɮ�Ū���r��A�ѪR���V�q����
				fin >> tempSring;
			}
			else
			{
				//Ū���V�q��ơA�ñNstring�ରdouble
				double value;
				value = (double)strtod(tempSring.c_str(), NULL);
				//�N�V�q��Ʀs�J�Ȧs
				tempVectorData.push_back(value);
			}
			
		}
		//Ū�J��J�ɮפ��̫�@�ӦV�q��T
		Vector tempVector;
		tempVector.Data = tempVectorData;
		std::string vectorVariableTemp = "$v" + std::to_string(VectorVariableIndex);
		tempVector.Name = vectorVariableTemp;
		Vectors.push_back(tempVector);
		VectorVariableIndex++;
		//Ū�����\�^��false
		return true;
	}
}
bool DataManager::LoadMatrixData()
{
	std::fstream fin;

	//�}���ɮסA�ǤJopen��ƪ��ѼƦ���ӡA���}�_���ɮצW�١A�}���ɮת��Ҧ��Ѽ�(�o��std::ios::in��Ū��(��J)���A)
	fin.open(FileName, std::ios::in);

	//Ū�����Ѧ^��false
	if (!fin)
	{
		return false;
	}
	else
	{
		//�w�qŪ���ɮצr��Ȧs�ܼ�
		std::string tempSring;
		//�q�ɮ�Ū���r��A�ѪR��Matrix�`��(�ثe�S�Ψ�)
		fin >> tempSring;

		//����Ū�ɰj��A�æbŪ���ɮ׵����ɵ���
		while (!fin.eof())
		{
			//�q�ɮ�Ū���r��
			fin >> tempSring;

			//�ѪR��Matrix�аO"M"
			if (tempSring == "M")
			{
				Matrix tempMatrix;

				int row, col;
				// store row & column dim
				fin >> row >> col;
				for (int i = 0; i < row; i++)
				{
					// to store row data as Vector
					Vector tempRowData;
					for (int j = 0; j < col; j++)
					{
						double tempValue;
						fin >> tempValue;
						tempRowData.Data.push_back(tempValue);
					}
					// add in tempMatrix Data
					tempMatrix.Data.push_back(tempRowData);
					// avoid duplicate data bug
					tempRowData.Data.clear();
				}
				// set Matrix name as $m[Index]
				tempMatrix.Name = "$m" + std::to_string(MatrixVariableIndex);
				// add to Matrix List of DataManager
				Matrices.push_back(tempMatrix);
				// Index ++
				MatrixVariableIndex++;
				// clean temp data to avoid bug
				tempMatrix.Data.clear();
				tempMatrix.Name = "";
			}
		}
		//Ū�����\�^��false
		return true;
	}
}

std::vector<Vector> DataManager::GetVectors()
{
	return Vectors;
}
std::vector<Matrix> DataManager::GetMatrices()
{
	return Matrices;
}
void DataManager::SetFileName(std::string fileName)
{
	FileName = fileName;
}


bool Vector::dimCheck(Vector Vb)
{
	if (this->Data.size() == Vb.Data.size()) 
	{
		return true;
	}
	return false;
}

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

const Vector  Vector::operator+(const Vector& Vb)
{
	std::vector<double> ans;
	ans.resize(Vb.Data.size());
	for (int i = 0; i < Vb.Data.size(); i++)
	{
		ans[i] = this->Data[i] + Vb.Data[i];
	}
	return Vector("ans",ans);
}

const Vector Vector::operator-(const Vector & Vb)
{
	std::vector<double> ans;
	ans.resize(Vb.Data.size());
	for (int i = 0; i < Vb.Data.size(); i++)
	{
		ans[i] = this->Data[i] - Vb.Data[i];
	}
	return Vector("ans", ans);
}

const double Vector::operator*(const Vector & Vb)
{
	//dot
	double ans = 0;
	for (int i = 0; i < Vb.Data.size(); i++)
	{
		ans += this->Data[i] * Vb.Data[i];
	}
	return ans;
}

const Vector operator*(const Vector & Va, const Vector & Vb)
{
	std::vector<double> ans;
	//scalar
	for (int i = 0; i < Va.Data.size(); i++)
	{
		for (int j = 0; j < Vb.Data.size(); j++)
		{
			ans.push_back(Va.Data[i] * Vb.Data[j]);
		}
	}
	return Vector("ans", ans);
}

Matrix::Matrix() :Name("")
{
	Data.resize(0);
}

Matrix::Matrix(std::vector<Vector> data) : Data(data) {}

Matrix::Matrix(std::string name, std::vector<Vector> data) : Name(name), Data(data) {}
