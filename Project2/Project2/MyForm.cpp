#include "MyForm.h"

//#define DEBUG_TESTDATA

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
#ifdef DEBUG_TESTDATA
		Input->Text = "7+x^2-3*x*y+3.25*y^2-4*y";

		xInitial->Text = "6";
		xBegin->Text = "0";
		xEnd->Text = "0";

		yInitial->Text = "5";
		yBegin->Text = "-70";
		yEnd->Text = "70";

		Quasi->Checked = true;
#endif // DEBUG_TESTDATA

		// Process To Equation to postfix array

		std::string equation;
		MarshalString(Input->Text, equation);

		double initX, beginX, endX, initY, beginY, endY;
		Equation formula;

		// if only x used
		if (xInitial->Text != "NULL" && yInitial->Text == "NULL")
		{
			initX = System::Convert::ToDouble(xInitial->Text);
			beginX = System::Convert::ToDouble(xBegin->Text);
			endX = System::Convert::ToDouble(xEnd->Text);
			formula = Equation(equation, "x", initX, beginX, endX);
		}

		// if only y used
		else if (xInitial->Text == "NULL" && yInitial->Text != "NULL")
		{
			initY = System::Convert::ToDouble(yInitial->Text);
			beginY = System::Convert::ToDouble(yBegin->Text);
			endY = System::Convert::ToDouble(yEnd->Text);
			formula = Equation(equation, "y", initY, beginY, endY);
		}

		// if x & y used
		else if (xInitial->Text != "NULL" && yInitial->Text != "NULL")
		{
			initX = System::Convert::ToDouble(xInitial->Text);
			beginX = System::Convert::ToDouble(xBegin->Text);
			endX = System::Convert::ToDouble(xEnd->Text);
			initY = System::Convert::ToDouble(yInitial->Text);
			beginY = System::Convert::ToDouble(yBegin->Text);
			endY = System::Convert::ToDouble(yEnd->Text);
			formula = Equation(equation, "x", initX, beginX, endX, "y", initY, beginY, endY);
		}

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