#include "WindowsForm.h"
#include <stack>

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
	int priority(String^ op)
	{
		switch (op[0]) 
		{
		case '+': case '-': 
			return 1;
		case '*': case '/': case'\\': 
			return 2;
		default:            
			return 0;
		}
	}
	
	int priority(std::string op)
	{
		String^ temp = gcnew String(op.c_str());
		return priority(temp);
	}

	Generic::List<String^>^ inToPostfix(array<String^>^ formulaList)
	{
		//�Y�B�⦡�����Ů���X�֦��L�Ů檩
		for (int i = 2; i < formulaList->Length; i++)
		{
			formulaList[1] += formulaList[i];
		}

		// infix formula (blank ver)
		String^ infixTemp = "";

		//�N�L�Ů檩�B�z���Ů檩
		for (int i = 0; i < formulaList[1]->Length; i++)
		{
			if (formulaList[1][i] == '(' ||	\
				formulaList[1][i] == ')' ||	\
				formulaList[1][i] == '+' ||	\
				formulaList[1][i] == '-' ||	\
				formulaList[1][i] == '*' ||	\
				formulaList[1][i] == '/' ||	\
				formulaList[1][i] == '\\')
			{
				infixTemp += " " + formulaList[1][i] + " ";
			}
			else
			{
				infixTemp += formulaList[1][i];
			}
		}
		// if head of String have ' '
		if (infixTemp[0] == ' ')
		{
			infixTemp = infixTemp->Remove(0, 1);
		}
		// if end of String have ' '
		if (infixTemp[infixTemp->Length - 1] == ' ')
		{
			infixTemp = infixTemp->Remove(infixTemp->Length - 1, 1);
		}

		// infix formula array
		array<String^> ^infixArray = infixTemp->Split(' ');
		
		// operator stack
		std::stack<std::string> opStack;

		// postfix array
		Generic::List<String^> ^postfixArray = gcnew Generic::List<String^>();

		// infix to postfix
		for (int i = 0; i < infixArray->Length; i++)
		{
			if (infixArray[i] == "(")
			{
				// �B��l���|
				std::string stdStringTemp;
				MarshalString(infixArray[i], stdStringTemp);
				opStack.push(stdStringTemp);
			}
			else if (infixArray[i] == "+"	\
				|| infixArray[i] == "-"		\
				|| infixArray[i] == "*"		\
				|| infixArray[i] == "/"		\
				|| infixArray[i] == "\\")
			{
				if (!opStack.empty())
				{
					while (priority(opStack.top()) >= priority(infixArray[i]))
					{
						String^ formStringTemp = gcnew String(opStack.top().c_str());
						postfixArray->Add(formStringTemp);
						opStack.pop();
						if (opStack.empty()) break;
					}
				}

				std::string stdStringTemp;
				MarshalString(infixArray[i], stdStringTemp);
				opStack.push(stdStringTemp); // �s�J���|
			}
			else if (infixArray[i] == ")")
			{
				while (opStack.top() != "(") 
				{ 
					// �J ) ��X�� (
					String^ formStringTemp = gcnew String(opStack.top().c_str());
					postfixArray->Add(formStringTemp);
					opStack.pop();
				}
				opStack.pop();  // ����X (
			}
			else
			{
				// �B�⤸������X
				if (infixArray[i] != " " && infixArray[i] != "")
				{
					postfixArray->Add(infixArray[i]);
				}
			}
		}
		while (!opStack.empty()) 
		{
			String^ formStringTemp = gcnew String(opStack.top().c_str());
			postfixArray->Add(formStringTemp);
			opStack.pop();
		}
		return postfixArray;
	}

	Generic::List<String^>^ CmdProcess(array<String^>^ CmdList)
	{
		//�Y�B�⦡�����Ů���X�֦��L�Ů檩
		for (int i = 2; i < CmdList->Length; i++)
		{
			CmdList[1] += CmdList[i];
		}
		String^ Cmdtemp = "";
		for (int i = 0; i < CmdList[1]->Length; i++)
		{
			if (CmdList[1][i] == '(' || CmdList[1][i] == ')' || CmdList[1][i] == ',')
			{
				Cmdtemp += " " + CmdList[1][i] + " ";
			}
			else
			{
				Cmdtemp += CmdList[1][i];
			}
		}
		if (Cmdtemp[0] == ' ')
		{
			Cmdtemp = Cmdtemp->Remove(0, 1);
		}
		if (Cmdtemp[Cmdtemp->Length - 1] == ' ')
		{
			Cmdtemp = Cmdtemp->Remove(Cmdtemp->Length - 1, 1);
		}
		array<String^> ^CmdArray = Cmdtemp->Split(' ');

		//�Narray(CmdArray)�নList
		Generic::List<String^> ^Cmd = gcnew Generic::List<String^>();
		for (int i = 0; i < CmdArray->Length; i++)
		{
			//Avoid " " bug
			if (CmdArray[i] != "" && CmdArray[i] != "(" && CmdArray[i] != ")" && CmdArray[i] != ",")
			{
				CmdArray[i] = CmdArray[i]->ToLower();
				Cmd->Add(CmdArray[i]);
			}
		}
		return Cmd;
	}

	System::Void WindowsForm::openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		//�bDialog���UOK�K�|�i�J���禡
		//�r�����string^ to string
		std::string tempFileName;
		MarshalString(openFileDialog1->FileName, tempFileName);
		//�N�ɮ׸��|�W�ٶǤJdataManager
		dataManager->SetFileName(tempFileName);
		//�qŪ��Ū���V�q���
		if (dataManager->LoadVectorData())
		{
			//�NVectorList�����إ����M��
			VectorList->Items->Clear();
			//���o�Ҧ��V�q���
			std::vector<Vector> vectors = dataManager->GetVectors();

			for (unsigned int i = 0; i < vectors.size(); i++)
			{
				//�N�ɮצW�٦s�J�Ȧs
				std::string tempString = vectors[i].Name;
				//�N��X�榡�s�J�Ȧs
				tempString += " [";
				//�N��X��Ʀs�J�Ȧs
				for (unsigned int j = 0; j < vectors[i].Data.size(); j++)
				{
					std::string scalarString = std::to_string(vectors[i].Data[j]);
					tempString += scalarString.substr(0, scalarString.size() - 5);
					if (j != vectors[i].Data.size() - 1)
						tempString += ",";
				}
				//�N��X�榡�s�J�Ȧs
				tempString += "]";
				//�N���إ[�JVectorList��
				VectorList->Items->Add(gcnew String(tempString.c_str()));
			}
			Output->Text += "---Vector datas have been loaded---" + Environment::NewLine;
		}
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
			Output->Text += "---Matrix datas have been loaded---" + Environment::NewLine;
		}
	}

	System::Void WindowsForm::loadVectorToolStripMenuItem1_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		//�}��Dialog
		openFileDialog1->ShowDialog();
	}

	System::Void WindowsForm::loadMatrixToolStripMenuItem1_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		//�}��Dialog
		openFileDialog2->ShowDialog();
	}

	System::Void WindowsForm::clearInputToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Input->Text = "";
	}

	System::Void WindowsForm::clearOutputToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Output->Text = "";
	}

	System::Void WindowsForm::VectorList_DoubleClick(System::Object ^ sender, System::EventArgs ^ e)
	{
		if (VectorList->SelectedItem != NULL)
		{
			Input->Text = Input->Text->Insert(Input->SelectionStart, "$v" + VectorList->SelectedIndex.ToString());
		}
	}
	System::Void WindowsForm::MatrixList_DoubleClick(System::Object ^ sender, System::EventArgs ^ e)
	{
		if (MatrixList->SelectedItem != NULL)
		{
			Input->Text = Input->Text->Insert(Input->SelectionStart, "$m" + MatrixList->SelectedIndex.ToString());
		}
	}
	System::Void WindowsForm::printVectorToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "printV ");
	}
	System::Void WindowsForm::calculateToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "calV ");
	}
	System::Void WindowsForm::normToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV Norm( )");
	}
	System::Void WindowsForm::normalToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV Normal( )");
	}
	System::Void WindowsForm::crossToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV Cross( , )");
	}
	System::Void WindowsForm::componentToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV Com( , )");
	}
	System::Void WindowsForm::projectionToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV Proj( , )");
	}
	System::Void WindowsForm::triangleAreaToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV Area( , )");
	}
	System::Void WindowsForm::parallelToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV isParallel( , )");
	}
	System::Void WindowsForm::orthogonalToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV isOrthogonal( , )");
	}
	System::Void WindowsForm::angleToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV Angle( , )");
	}
	System::Void WindowsForm::planeToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV pN( , )");
	}
	System::Void WindowsForm::linearIndependentToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV isLI( , )");
	}
	System::Void WindowsForm::gramschmidtToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcV Ob( , )");
	}
	System::Void WindowsForm::printMatrixToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "printM ");
	}
	System::Void WindowsForm::calculateToolStripMenuItem1_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "calM ");
	}
	System::Void WindowsForm::rankToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcM Rank( )");
	}
	System::Void WindowsForm::transposeToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcM Trans( )");
	}
	System::Void WindowsForm::solveLinearSystemToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "calM ( \ )");
	}
	System::Void WindowsForm::determinantToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcM Det( )");
	}
	System::Void WindowsForm::inverseToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcM Inverse( )");
	}
	System::Void WindowsForm::adjointToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcM Adj( )");
	}
	System::Void WindowsForm::eigenValueVectorToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcM Eigen( )");
	}
	System::Void WindowsForm::powerMethodToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcM PM( )");
	}
	System::Void WindowsForm::leastSquareToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Input->Text = Input->Text->Insert(Input->SelectionStart, "funcM leastSquare( , )");
	}

	System::Void WindowsForm::Output_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
	{
		Output->SelectionStart = Output->Text->Length;
		Output->ScrollToCaret();
	}

	System::Void WindowsForm::Input_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//��Input textbox������J���ܮɡA�K�|�i�J���禡

		//�P�_��J�ۤ���'\n'�A�è������r��-1��m
		if (Input->Text->Length - 1 >= 0 && Input->Text[Input->Text->Length - 1] == '\n')
		{
			//���o�V�q���
			std::vector<Vector> vectors = dataManager->GetVectors();
			std::vector<Matrix> matrices = dataManager->GetMatrices();

			//�N�ϥΪ̿�J�r��(�buserInput��)�A�̪ťէ@����
			array<String^> ^userCommand = userInput->Split(' ');
			std::string nameTemp;

			// print Vector
			if (userCommand[0] == "printV")
			{
				try
				{
					MarshalString(userCommand[1], nameTemp);
					// find Matrix index
					int index = dataManager->findVector(nameTemp);
					// Output
					Output->Text += vectors[index].outputStr();
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

			// print Matrix
			else if (userCommand[0] == "printM")
			{
				try
				{
					MarshalString(userCommand[1], nameTemp);
					// find Matrix index
					int index = dataManager->findMatrix(nameTemp);
					// Output
					Output->Text += matrices[index].outputStr();
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

			// calculate Vector
			else if (userCommand[0] == "calV")
			{	
				Generic::List<String^>^ postfixFormula = inToPostfix(userCommand);
#ifdef DEBUG
				Output->Text += "postfix =";
				for (int i = 0; i < postfixFormula->Count; i++)
				{
					Output->Text += " " + postfixFormula[i];
				}
				Output->Text += Environment::NewLine;
#endif // DEBUG
				// store temp Vector
				std::stack<Vector> calStack;
				try
				{
					for (int i = 0; i < postfixFormula->Count; i++)
					{
						// if detect operator
						if (postfixFormula[i] == "+" || postfixFormula[i] == "-" || postfixFormula[i] == "*")
						{
							std::string opTemp = "";
							MarshalString(postfixFormula[i], opTemp);

							// pop two Vector
							Vector Vb = calStack.top();
							calStack.pop();
							Vector Va = calStack.top();
							calStack.pop();

							// Check zero vector first
							if (Va.zeroCheck())
							{
								Va.zeroExpand(Vb.size());
							}
							else if (Vb.zeroCheck())
							{
								Vb.zeroExpand(Va.size());
							}

							// push calculated result
							calStack.push(Vector(opTemp[0], Va, Vb));
						}
						// not operator push vector into stack 
						else
						{
							std::string formulaTemp = "";
							MarshalString(postfixFormula[i], formulaTemp);
							int index = dataManager->findVector(formulaTemp);
							calStack.push(vectors[index]);
						}
					}

					// Avoid empty stack
					if (calStack.empty()) throw "---Formula is empty---";

					// pop final calculate result vector 
					Vector result = calStack.top();
					calStack.pop();

					// output
					MarshalString(userCommand[1], result.Name);
					Output->Text += result.outputStr();
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

			// calculate Matrix
			else if (userCommand[0] == "calM")
			{
				// normalization postfix formula
				Generic::List<String^>^ postfixFormula = inToPostfix(userCommand);
#ifdef DEBUG
				// Output postfix formula
				Output->Text += "postfix =";
				for (int i = 0; i < postfixFormula->Count; i++)
				{
					Output->Text += " " + postfixFormula[i];
				}
				Output->Text += Environment::NewLine;
#endif // DEBUG
				// store temp Matrix
				std::stack<Matrix> calStack;
				try
				{
					for (int i = 0; i < postfixFormula->Count; i++)
					{
						// if detect operator
						if (postfixFormula[i] == "+" || postfixFormula[i] == "-" || postfixFormula[i] == "*" || postfixFormula[i] == "\\")
						{
							std::string opTemp = "";
							MarshalString(postfixFormula[i], opTemp);

							// pop two Matrix
							Matrix Mb = calStack.top();
							calStack.pop();
							Matrix Ma = calStack.top();
							calStack.pop();

							// push calculated result
							calStack.push(Matrix(opTemp[0], Ma, Mb));
						}
						// not operator push matrix into stack 
						else
						{
							std::string formulaTemp = "";
							MarshalString(postfixFormula[i], formulaTemp);
							int index = dataManager->findMatrix(formulaTemp);
							calStack.push(matrices[index]);
						}
					}

					// Avoid empty stack
					if (calStack.empty()) throw "---Formula is empty---";

					// pop final calculate result matrix 
					Matrix result = calStack.top();
					calStack.pop();

					// output
					MarshalString(userCommand[1], result.Name);
					Output->Text += result.outputStr();
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

			// Vector Function
			else if (userCommand[0] == "funcV")
			{
				// normalization the command name and parameter
				Generic::List<String^> ^funcFormula = CmdProcess(userCommand);
				try
				{
					Vector result;
					std::string VarNameTemp = "";
					if (funcFormula->Count == 0) throw "---No Function command---";
					else if (funcFormula->Count == 1) throw "---No parameter---";
					else if (funcFormula->Count == 2)
					{
						// record parameter index of array
						MarshalString(funcFormula[1], VarNameTemp);
						int index = dataManager->findVector(VarNameTemp);

						if (funcFormula[0] == "norm")
						{
							double normValue = vectors[index].Norm();
							result.Data.push_back(normValue);
							result.Name = "Norm(" + vectors[index].Name + ")";
#ifdef DEBUG
							Output->Text += "Norm called" + Environment::NewLine;
#endif // DEBUG
						}
						else if (funcFormula[0] == "normal")
						{
							result = vectors[index].Normal();
							result.Name = "Normal(" + vectors[index].Name + ")";
#ifdef DEBUG
							Output->Text += "Normalization called" + Environment::NewLine;
#endif // DEBUG
						}
						else throw "---Function of unary not exist---";
					}
					else if (funcFormula->Count >= 3)
					{
						// record parameter index of array
						int index, indexA, indexB;

						if (funcFormula[0] == "ob" || funcFormula[0] == "isli")
						{
							// Ob function or isLI function PreProcess
							MarshalString(funcFormula[1], nameTemp);
							index = dataManager->findVector(nameTemp);

							std::vector<Vector> ui;
							ui.push_back(vectors[index]);
							int normal = ui[0].Data.size();
							ui.resize(normal);

							for (int i = 2; i <= normal; i++)
							{
								MarshalString(funcFormula[i], nameTemp);
								index = dataManager->findVector(nameTemp);

								if (vectors[index].dimCheck(ui[0]))
								{
									ui[i - 1] = vectors[index];	//get vector data into ui
								}
							}

							if (funcFormula[0] == "ob")
							{
#ifdef DEBUG
								Output->Text += "Ob called" + Environment::NewLine;
#endif // DEBUG
								Matrix ObResult;
								ObResult = Ob(normal, ui);
								ObResult.Name = "Ob(";
								for (int varIndex = 1; varIndex < funcFormula->Count; varIndex++)
								{
									if (varIndex != 1)
									{
										ObResult.Name += ",";
									}
									MarshalString(funcFormula[varIndex], nameTemp);
									ObResult.Name += nameTemp;
								}
								ObResult.Name += ")";
								Output->Text += ObResult.outputStr();
							}
							else if (funcFormula[0] == "isli")
							{
#ifdef DEBUG
								Output->Text += "isLI called" + Environment::NewLine;
#endif // DEBUG
								result.Name = "isLI(";
								for (int varIndex = 1; varIndex < funcFormula->Count; varIndex++)
								{
									if (varIndex != 1)
									{
										result.Name += ",";
									}
									MarshalString(funcFormula[varIndex], nameTemp);
									result.Name += nameTemp;
								}
								result.Name += ") : ";
								result.Name += (isLI(normal, ui)) ? "Yes" : "No";
							}
						}
						else if (funcFormula->Count == 3)
						{
							MarshalString(funcFormula[1], VarNameTemp);
							indexA = dataManager->findVector(VarNameTemp);
							MarshalString(funcFormula[2], VarNameTemp);
							indexB = dataManager->findVector(VarNameTemp);

							// Check zero vector first
							if (vectors[indexA].zeroCheck())
							{
								vectors[indexA].zeroExpand(vectors[indexB].size());
							}
							else if (vectors[indexB].zeroCheck())
							{
								vectors[indexB].zeroExpand(vectors[indexA].size());
							}

							if (!vectors[indexA].dimCheck(vectors[indexB])) throw "---Dimension not same---";


							if (funcFormula[0] == "isorthogonal")
							{
								result = vectors[indexA] * vectors[indexB];
								result.Name = "isOrthogonal(" + vectors[indexA].Name + "," + vectors[indexB].Name + ")";
								if (result.Data[0] == 0)
								{
									result.Name += " : Yes";
								}
								else
								{
									result.Name += " : No";
								}
#ifdef DEBUG
								Output->Text += "isOrthogonal called" + Environment::NewLine;
#endif // DEBUG
							}
							else if (funcFormula[0] == "angle")
							{
								double angleValue = vectors[indexA].Angle(vectors[indexB]);
								result.Data.push_back(angleValue);
								result.Name = "Angle(" + vectors[indexA].Name + "," + vectors[indexB].Name + ") theta";
#ifdef DEBUG
								Output->Text += "Angle called" + Environment::NewLine;
#endif // DEBUG
							}
							else if (funcFormula[0] == "com")
							{
								double comValue = vectors[indexA].Com(vectors[indexB]);
								result.Data.push_back(comValue);
								result.Name = "Com(" + vectors[indexA].Name + "," + vectors[indexB].Name + ")";
#ifdef DEBUG
								Output->Text += "Com called" + Environment::NewLine;
#endif // DEBUG
							}
							else if (funcFormula[0] == "proj")
							{
								result = vectors[indexA].Proj(vectors[indexB]);
								result.Name = "Proj(" + vectors[indexA].Name + "," + vectors[indexB].Name + ")";
#ifdef DEBUG
								Output->Text += "Proj called" + Environment::NewLine;
#endif // DEBUG
							}
							else if (funcFormula[0] == "cross" || funcFormula[0] == "pn")
							{
								if (vectors[indexA].Data.size() == 3)
								{
									result = vectors[indexA].Cross(vectors[indexB]);
									if (funcFormula[0] == "cross")
									{
										result.Name = "Cross";
									}
									else if (funcFormula[0] == "pn")
									{
										result.Name = "pN";
									}
									result.Name += "(" + vectors[indexA].Name + "," + vectors[indexB].Name + ")";
								}
								else throw "---Cross / pN Dimension error---";
#ifdef DEBUG
								Output->Text += "Cross / pN called" + Environment::NewLine;
#endif // DEBUG
							}
							else if (funcFormula[0] == "isparallel")
							{
								result.Name = "isParallel(" + vectors[indexA].Name + "," + vectors[indexB].Name + ")";
								double angleValue = vectors[indexA].Angle(vectors[indexB]);

								if (angleValue == 0 || angleValue == 180)
								{
									result.Name += " : Yes";
								}
								else
								{
									result.Name += " : No";
								}
#ifdef DEBUG
								Output->Text += "isParallel called" + Environment::NewLine;
#endif // DEBUG
							}
							else if (funcFormula[0] == "area")
							{
								double areaValue = vectors[indexA].Area(vectors[indexB]);
								result.Data.push_back(areaValue);
								result.Name = "Area(" + vectors[indexA].Name + "," + vectors[indexB].Name + ")";
#ifdef DEBUG
								Output->Text += "Area called" + Environment::NewLine;
#endif // DEBUG
							}

							else throw "---Function of binary not exist---";
						}
						else throw  "---Parameter amount error / Function not found---";
					}
					// test version
					Output->Text += result.outputStr();
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

			// Matrix Function
			else if (userCommand[0] == "funcM")
			{
				// normalization the command name and parameter
				Generic::List<String^> ^funcFormula = CmdProcess(userCommand);

				try
				{
					Matrix result;
					std::string VarNameTemp = "";
					std::vector<double> eigenVal;

					if (funcFormula->Count == 0) throw "---No Function command---";
					else if (funcFormula->Count == 1) throw "---No parameter---";
					else
					{
						switch (funcFormula->Count)
						{
							// record parameter index of array
							int index, indexA, indexB;

							// unary parameter function case
						case 2:
							MarshalString(funcFormula[1], VarNameTemp);
							// find matrix
							index = dataManager->findMatrix(VarNameTemp);

							if (funcFormula[0] == "trans")
							{
								result = matrices[index].trans();
								result.Name = "Trans(" + matrices[index].Name + ")";
							}
							else if (funcFormula[0] == "gauss")
							{
								result = matrices[index].gaussian(1, true);
								result.Name = "Gauss(" + matrices[index].Name + ")";
							}
							else if (funcFormula[0] == "rank")
							{
								double rankValue = matrices[index].rank();
								result.Data.resize(1);
								result.Data[0].Data.push_back(rankValue);
								result.Name = "Rank(" + matrices[index].Name + ")";
							}
							else if (funcFormula[0] == "det")
							{
								double detValue = matrices[index].det();
								result.Data.resize(1);
								result.Data[0].Data.push_back(detValue);
								result.Name = "Det(" + matrices[index].Name + ")";
							}
							else if (funcFormula[0] == "inverse")
							{
								result = matrices[index].inverse();
								result.Name = "Inverse(" + matrices[index].Name + ")";
							}
							else if (funcFormula[0] == "adj")
							{
								result = matrices[index].adjoint();
								result.Name = "Adj(" + matrices[index].Name + ")";
							}
							else if (funcFormula[0] == "eigen")
							{
								eigenVal = matrices[index].eigenVal();

								// store eigen Vector
								result = matrices[index].eigenVec(eigenVal);
								result.Name = "eigen Vector(" + matrices[index].Name +")";

								Matrix valResult;
								valResult.Data.resize(eigenVal.size());
								for (int i = 0; i < eigenVal.size(); i++)
								{
									valResult.Data[i].Data.push_back(eigenVal[i]);
								}
								valResult.Name = "eigen Value(" + matrices[index].Name + ")";
								Output->Text += valResult.outputStr();
							}
							else if (funcFormula[0] == "pm")
							{
								eigenVal.push_back(matrices[index].pm());

								// store eigen Vector
								result = matrices[index].eigenVec(eigenVal);
								result.Name = "PM eigen Vector(" + matrices[index].Name + ")";

								Matrix valResult;
								valResult.Data.resize(eigenVal.size());
								for (int i = 0; i < eigenVal.size(); i++)
								{
									valResult.Data[i].Data.push_back(eigenVal[i]);
								}
								valResult.Name = "PM eigen Value(" + matrices[index].Name + ")";
								Output->Text += valResult.outputStr();
							}
							else throw "---Function of binary not exist---";
							break;
						case 3:
							MarshalString(funcFormula[1], VarNameTemp);
							indexA = dataManager->findMatrix(VarNameTemp);
							MarshalString(funcFormula[2], VarNameTemp);
							indexB = dataManager->findMatrix(VarNameTemp);

							if (funcFormula[0] == "leastsquare")
							{
								result = matrices[indexA].leastSquare(matrices[indexB]);
								result.Name = "LeastSquare(" + matrices[indexA].Name + "," + matrices[indexB].Name +")";
							}
							break;
						default:
							throw  "---Parameter amount error / Function not found---";
							break;
						}
					}
					
					// output result
					Output->Text += result.outputStr();
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

			//�Ϥ��h�P�_�䤣����O
			else
			{
				Output->Text += "---Command not found---" + Environment::NewLine;
			}
		}
		else
		{
			//�N�ϥΪ̿�J�r��(�bText box��)�A��'\n'�@����
			array<String^> ^userCommand = Input->Text->Split('\n');

			//�ñN�̫�@��A�@���ثe�ϥΪ̿�J���O
			userInput = userCommand[userCommand->Length - 1];
		}
		Input->SelectionStart = Input->Text->Length;
		Input->ScrollToCaret();
	}
}
