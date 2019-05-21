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
		openFileDialog1->Title = "Choose Equation File to Load...";
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

			Input->Items->Clear();

			for (int i = 0; i < equations.size(); i++)
			{
				String^ StringTemp = gcnew String(equations[i].c_str());
				Input->Items->Add(StringTemp);
			}
			Output->Text += "---Equation File Loaded---" + Environment::NewLine;
		}
	}

	System::Void MyForm::EnterBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
#ifdef DEBUG_TESTDATA
		Input->Text = "7+x^2-3*x*y+3.25*y^2-4*y";

		xInitial->Text = "50";
		xBegin->Text = "-50";
		xEnd->Text = "70";

		yInitial->Text = "30";
		yBegin->Text = "-70";
		yEnd->Text = "70";

		Conjuate->Checked = true;
#endif // DEBUG_TESTDATA

		// Process To Equation to postfix array

		std::string equation;
		MarshalString(Input->Text, equation);

		double initX, beginX, endX, initY, beginY, endY;
		Equation formula;

		try
		{
			if (equation == "")
			{
				throw "---ERROR in MyForm::EnterBtn_Click(System::Object ^ sender, System::EventArgs ^ e): Empty Equation---";
			}
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
			else
			{
				throw "---ERROR in MyForm::EnterBtn_Click(System::Object ^ sender, System::EventArgs ^ e): No initial setting---";
			}


			if (Powell->Checked)
			{
				Output->Text += formula.Powell() + Environment::NewLine;
			}
			else if (Newton->Checked)
			{
				Output->Text += formula.Newton() + Environment::NewLine;
			}
			else if (Step->Checked)
			{
				Output->Text += formula.Steep() + Environment::NewLine;
			}
			else if (Quasi->Checked)
			{
				Output->Text += formula.Quasi() + Environment::NewLine;
			}
			else if (Conjuate->Checked)
			{
				Output->Text += formula.Conjuate() + Environment::NewLine;
			}
		}
		catch (const std::exception&)
		{
			std::cout << "---Something ERROR---" << std::endl;
			std::cout << "---Using Debug Mode to find the fxxk bug---" << std::endl;
			Output->Text += "---Something ERROR---" + Environment::NewLine;
			Output->Text += "---Using Debug Mode to find the fxxk bug---" + Environment::NewLine;
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
		xBegin->Text = "0";
		xEnd->Text = "0";
	}
	System::Void MyForm::resetYToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		yInitial->Text = "NULL";
		yBegin->Text = "0";
		yEnd->Text = "0";
	}
	System::Void MyForm::outputResultToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
		saveFileDialog1->Title = "Save Output Result";
		saveFileDialog1->Filter = "Text File|*.txt";
		saveFileDialog1->ShowDialog();

		// If the file name is not an empty string open it for saving.  
		if (saveFileDialog1->FileName != "")
		{
			System::IO::StreamWriter^ outfile = gcnew System::IO::StreamWriter(saveFileDialog1->FileName);
			outfile->Write(Output->Text);
			outfile->Close();
			MessageBox::Show("Saved Output Result");
		}
	}
	System::Void MyForm::Output_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
	{
		Output->SelectionStart = Output->Text->Length;
		Output->ScrollToCaret();
	}
	System::Void MyForm::Input_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Input->DroppedDown = true;
	}
	System::Void MyForm::xInitial_Click(System::Object^  sender, System::EventArgs^  e)
	{
		xInitial->SelectAll();
	}
	System::Void MyForm::xBegin_Click(System::Object^  sender, System::EventArgs^  e)
	{
		xBegin->SelectAll();
	}
	System::Void MyForm::xEnd_Click(System::Object^  sender, System::EventArgs^  e)
	{
		xEnd->SelectAll();
	}
	System::Void MyForm::yInitial_Click(System::Object^  sender, System::EventArgs^  e)
	{
		yInitial->SelectAll();
	}
	System::Void MyForm::yBegin_Click(System::Object^  sender, System::EventArgs^  e)
	{
		yBegin->SelectAll();
	}
	System::Void MyForm::yEnd_Click(System::Object^  sender, System::EventArgs^  e)
	{
		yEnd->SelectAll();
	}
}
