#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project2::MyForm windowsForm;
	Application::Run(%windowsForm);
}

namespace Project2
{
	System::Void MyForm::loadFileToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		openFileDialog1->ShowDialog();
	}

	System::Void MyForm::openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string FilePath;
		MarshalString(openFileDialog1->FileName, FilePath);

		dataManager->SetFileName(FilePath);

		if (dataManager->LoadEquationData())
		{
			std::vector<std::string> equations = dataManager->GetEquations();

			for (int i = 0; i < equations.size(); i++)
			{
				String^ StringTemp = gcnew String(equations[i].c_str());
				Input->Items->Add(StringTemp);
			}
		}
	}
	
	System::Void MyForm::EnterBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		// Process To Equation to postfix array
		std::string equation;
		MarshalString(Input->Text, equation);
		Equation formula(equation);

		// Store Setting
		double initX = System::Convert::ToDouble(xInitial->Text);
		double beginX = System::Convert::ToDouble(xBegin->Text);
		double endX = System::Convert::ToDouble(xEnd->Text);

		double initY = System::Convert::ToDouble(yInitial->Text);
		double beginY = System::Convert::ToDouble(yBegin->Text);
		double endY = System::Convert::ToDouble(yEnd->Text);

		try
		{
			if (Powell->Checked)
			{
				Output->Text += formula.Powell();
			}
			else if (Newton->Checked)
			{
				Output->Text += formula.Newton();
			}
			else if (Step->Checked)
			{
				Output->Text += formula.Steep();
			}
			else if (Quasi->Checked)
			{
				Output->Text += formula.Quasi();
			}
			else if (Conjuate->Checked)
			{
				Output->Text += formula.Conjuate();
			}

		}
		catch (const std::exception&)
		{
			std::cout << "ERROR" << std::endl;
		}
		catch (const char* ERRMSG)
		{
			std::cout << ERRMSG << std::endl;
			Output->Text += gcnew String(ERRMSG) + Environment::NewLine;
		}
	}
}