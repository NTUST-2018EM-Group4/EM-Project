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

		// Store Parameter Setting
		std::vector<Parameter> paras;

		// if x used
		if (xInitial->Text != "NULL")
		{
			double initX = System::Convert::ToDouble(xInitial->Text);
			double beginX = System::Convert::ToDouble(xBegin->Text);
			double endX = System::Convert::ToDouble(xEnd->Text);
			paras.push_back(Parameter("x", initX, beginX, endX));
		}

		// if y used
		if (yInitial->Text != "NULL")
		{
			double initY = System::Convert::ToDouble(yInitial->Text);
			double beginY = System::Convert::ToDouble(yBegin->Text);
			double endY = System::Convert::ToDouble(yEnd->Text);
			paras.push_back(Parameter("y", initY, beginY, endY));
		}

		try
		{
			if (Powell->Checked)
			{
				Output->Text += formula.Powell(paras);
			}
			else if (Newton->Checked)
			{
				Output->Text += formula.Newton(paras);
			}
			else if (Step->Checked)
			{
				Output->Text += formula.Steep(paras);
			}
			else if (Quasi->Checked)
			{
				Output->Text += formula.Quasi(paras);
			}
			else if (Conjuate->Checked)
			{
				Output->Text += formula.Conjuate(paras);
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
	System::Void MyForm::clearOutputToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Output->Text = "";
	}
	System::Void MyForm::resetXToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		xInitial->Text = "NULL";
		xBegin->Text = "NULL";
		xEnd->Text = "NULL";
	}
	System::Void MyForm::resetYToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		yInitial->Text = "NULL";
		yBegin->Text = "NULL";
		yEnd->Text = "NULL";
	}
}