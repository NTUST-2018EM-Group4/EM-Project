#include "WindowsForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	WindowsFormsApplication_cpp::WindowsForm windowsForm;
	Application::Run(%windowsForm);
}
namespace WindowsFormsApplication_cpp
{
	System::Void WindowsForm::loadMatrixToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//�}��Dialog
		openFileDialog2->ShowDialog();
	}
	System::Void WindowsForm::openFileDialog2_FileOk(System::Object ^ sender, System::ComponentModel::CancelEventArgs ^ e)
	{
		//�bDialog���UOK�K�|�i�J���禡
		//�r�����string^ to string
		std::string tempFileName;
		MarshalString(openFileDialog2->FileName, tempFileName);

		//�N�ɮ׸��|�W�ٶǤJdataManager
		dataManager->SetFileName(tempFileName);

		//�qŪ��Ū���V�q���
		if (dataManager->LoadMatrixData())
		{
			//�NForm::MatrixList�����إ����M��
			MatrixList->Items->Clear();

			//���o�Ҧ��V�q���
			std::vector<Matrix> matrices = dataManager->GetMatrices();

			for (unsigned int i = 0; i < matrices.size(); i++)
			{
				//�N�ɮצW�٦s�J�Ȧs
				std::string tempString = matrices[i].Name + "\n";
				
				//�N��X��Ʀs�J�Ȧs
				for (unsigned int j = 0; j < matrices[i].Data.size(); j++)
				{
					//�N��X�榡�s�J�Ȧs
					tempString += "[";

					for (unsigned int k = 0; k < matrices[i].Data[j].Data.size(); k++)
					{
						std::string scalarString = std::to_string(matrices[i].Data[j].Data[k]);
						tempString += scalarString.substr(0, scalarString.size() - 5);
						if (k != matrices[i].Data[j].Data.size() - 1)
							tempString += ",";
					}
					//�N��X�榡�s�J�Ȧs
					tempString += "]\n";
					
				}

				//�N���إ[�JVectorList��
				MatrixList->Items->Add(gcnew String(tempString.c_str()));
			}
			Output->Text += "-Matrix datas have been loaded-" + Environment::NewLine;
		}
	}
}
