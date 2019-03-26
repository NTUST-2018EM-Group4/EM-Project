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
		//開啟Dialog
		openFileDialog2->ShowDialog();
	}
	System::Void WindowsForm::openFileDialog2_FileOk(System::Object ^ sender, System::ComponentModel::CancelEventArgs ^ e)
	{
		//在Dialog按下OK便會進入此函式
		//字串轉制string^ to string
		std::string tempFileName;
		MarshalString(openFileDialog2->FileName, tempFileName);

		//將檔案路徑名稱傳入dataManager
		dataManager->SetFileName(tempFileName);

		//從讀取讀取向量資料
		if (dataManager->LoadMatrixData())
		{
			//將Form::MatrixList中項目先做清除
			MatrixList->Items->Clear();

			//取得所有向量資料
			std::vector<Matrix> matrices = dataManager->GetMatrices();

			for (unsigned int i = 0; i < matrices.size(); i++)
			{
				//將檔案名稱存入暫存
				std::string tempString = matrices[i].Name + "\n";
				
				//將輸出資料存入暫存
				for (unsigned int j = 0; j < matrices[i].Data.size(); j++)
				{
					//將輸出格式存入暫存
					tempString += "[";

					for (unsigned int k = 0; k < matrices[i].Data[j].Data.size(); k++)
					{
						std::string scalarString = std::to_string(matrices[i].Data[j].Data[k]);
						tempString += scalarString.substr(0, scalarString.size() - 5);
						if (k != matrices[i].Data[j].Data.size() - 1)
							tempString += ",";
					}
					//將輸出格式存入暫存
					tempString += "]\n";
					
				}

				//將項目加入VectorList中
				MatrixList->Items->Add(gcnew String(tempString.c_str()));
			}
			Output->Text += "-Matrix datas have been loaded-" + Environment::NewLine;
		}
	}
}
