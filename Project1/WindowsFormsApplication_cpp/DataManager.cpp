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
		// reset the Variable list
		Vectors.clear();
		// reset indexValue
		VectorVariableIndex = 0;

		//�w�qŪ���ɮצr��Ȧs�ܼ�
		std::string tempString;
		//�q�ɮ�Ū���r��A�ѪR��Vector�`��(�ثe�S�Ψ�)
		fin >> tempString;

		//����Ū�ɰj��A�æbŪ���ɮ׵����ɵ���
		while (!fin.eof())
		{
			//�q�ɮ�Ū���r��
			fin >> tempString;

			//�ѪR��Vector�аO"V"
			if (tempString == "V")
			{
				Vector tempVector;

				int dim;
				// store dim of vector
				fin >> dim;
				for (int i = 0; i < dim; i++)
				{
					double tempValue;
					fin >> tempValue;
					tempVector.Data.push_back(tempValue);
				}
				// set Vector name as $v[Index]
				tempVector.Name = "$v" + std::to_string(VectorVariableIndex);
				// add to Vector List of DataManager
				Vectors.push_back(tempVector);
				// Index ++
				VectorVariableIndex++;
				// clean temp data to avoid duplicate data bug
				tempVector.Data.clear();
				tempVector.Name = "";
				tempString = "";
			}
		}
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
		// reset the Variable list
		Matrices.clear();
		// reset indexValue
		MatrixVariableIndex = 0;

		//�w�qŪ���ɮצr��Ȧs�ܼ�
		std::string tempString;
		//�q�ɮ�Ū���r��A�ѪR��Matrix�`��(�ثe�S�Ψ�)
		fin >> tempString;

		//����Ū�ɰj��A�æbŪ���ɮ׵����ɵ���
		while (!fin.eof())
		{
			//�q�ɮ�Ū���r��
			fin >> tempString;

			//�ѪR��Matrix�аO"M"
			if (tempString == "M")
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
				tempString = "";
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


