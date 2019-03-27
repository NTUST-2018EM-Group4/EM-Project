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
	int priority(char op)
	{
		switch (op) {
		case '+': case '-': return 1;
		case '*': case '/': return 2;
		default:            return 0;
		}
	}
	String^ printVector(String^ s, const Vector& v)
	{
		s += "[";
		for (int i = 0; i < v.Data.size(); i++)
		{
			/*�����D��򭭨�6��*/
			s += v.Data[i].ToString();
			if (i != v.Data.size() - 1)
				s += ", ";
		}
		s += "]" + Environment::NewLine;
		return s;
	}
	int findVector(std::string name, const std::vector<Vector>& v)
	{
		std::string temp;
		//MarshalString(name, temp);

		//�z�Lfor�j��A�q�V�q��Ƥ���X�����ܼ�
		for (unsigned int i = 0; i < v.size(); i++)
		{
			//�Y�ܼƦW�ٻP���O�ܼƦW�ٲŦX
			if (name == v[i].Name)
				return i;
		}
		return -1;
	}

	System::Void WindowsForm::loadVectorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//�}��Dialog
		openFileDialog1->ShowDialog();
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
			Output->Text += "-Vector datas have been loaded-" + Environment::NewLine;
		}
	}
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

	System::Void WindowsForm::Input_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//��Input textbox������J���ܮɡA�K�|�i�J���禡
		//���o�V�q���
		std::vector<Vector> vectors = dataManager->GetVectors();
		//�P�_��J�ۤ���'\n'�A�è������r��-1��m
		if (Input->Text->Length - 1 >= 0 && Input->Text[Input->Text->Length - 1] == '\n')
		{
			//�N�ϥΪ̿�J�r��(�buserInput��)�A�̪ťէ@����
			array<String^> ^userCommand = userInput->Split(' ');
			std::string nameTemp;
			//�r�����A�Y���O��"print"�����p
			if (userCommand[0] == "print")
			{
				//�w�q��X�Ȧs
				String^ outputTemp = "";

				MarshalString(userCommand[1], nameTemp);
				int index = findVector(nameTemp, vectors);
				if (index != -1)
				{
					outputTemp = printVector(outputTemp, vectors[index]);
					Output->Text += gcnew String(vectors[index].Name.c_str()) + " = " + outputTemp;
				}
				else
					Output->Text += "-Vector not found-" + Environment::NewLine;
			}

			else if (userCommand[0] == "cal")
			{
				//infix to postfix

				//�Y�B�⦡�����Ů���X�֦��L�Ů檩
				for (int i = 2; i < userCommand->Length; i++)
				{
					userCommand[1] += userCommand[i];
				}
				//�N�L�Ů檩�B�z���Ů檩
				//�w�q��X�Ȧs
				String^ infixTemp = "";
				int begin = 0;
				for (int i = 0; i < userCommand[1]->Length; i++)
				{
					if (userCommand[1][i] == '(' ||
						userCommand[1][i] == ')' ||
						userCommand[1][i] == '+' ||
						userCommand[1][i] == '-' ||
						userCommand[1][i] == '*')
					{
						if (i - 1 >= 0)
						{
							infixTemp += userCommand[1]->Substring(begin, (i - 1 - begin + 1));
							infixTemp += " ";
						}
						infixTemp += userCommand[1]->Substring(i, 1);
						infixTemp += " ";
						begin = i + 1;
					}
					else if (i == userCommand[1]->Length - 1)
					{
						infixTemp += userCommand[1]->Substring(begin, (i - begin + 1));
						infixTemp += " ";
					}
				}
				//�h���̫�@�ӪŮ�
				if (infixTemp[infixTemp->Length - 1] == ' ')
				{
					infixTemp = infixTemp->Remove(infixTemp->Length - 1, 1);
				}
				//�N�B�z�����r��̪ťէ@����
				array<String^> ^infixFormula = infixTemp->Split(' ');
				String^ stack = " ";

				String^ postfix = "";
				int top = 0;
				for (int i = 0; i < infixFormula->Length; i++)
				{

					if (infixFormula[i] == "(")
					{
						// �B��l���|
						stack = stack->Insert(++top, infixFormula[i]);
					}
					else if (infixFormula[i] == "+" ||
						infixFormula[i] == "-" ||
						infixFormula[i] == "*")
					{
						while (priority(stack[top]) >= priority(infixFormula[i][0]))
						{
							postfix += stack[top--];
							postfix += " ";
						}
						stack = stack->Insert(++top, infixFormula[i]); // �s�J���|
					}
					else if (infixFormula[i] == ")")
					{
						while (stack[top] != '(') { // �J ) ��X�� (
							postfix += stack[top--];
							postfix += " ";
						}
						top--;  // ����X (
					}
					else
					{
						// �B�⤸������X
						postfix += infixFormula[i];
						postfix += " ";
					}
				}
				while (top > 0) {
					postfix += stack[top--];
					postfix += " ";
				}
				//�h���̫�@�ӪŮ�
				if (postfix[postfix->Length - 1] == ' ')
				{
					postfix = postfix->Remove(postfix->Length - 1, 1);
				}
				//�N�B�z�����r��(postfix)�̪ťէ@���Φs��array
				array<String^> ^postfixArray = postfix->Split(' ');

				//�Narray(postfixArray)�নList
				Generic::List<String^> ^postfixFormula = gcnew Generic::List<String^>();
				for (int i = 0; i < postfixArray->Length; i++)
				{
					//Avoid " " bug
					if (postfixArray[i] != "")
					{
						postfixFormula->Add(postfixArray[i]);
					}
				}

#ifdef DEBUG
				Output->Text += "postfix = " + postfix + Environment::NewLine;
#endif // DEBUG

				Vector ans, Va, Vb;
				std::stack<Vector> calStack;
				bool dimFlag, foundFlag;
				for (int i = 0; i < postfixFormula->Count; i++)
				{
					dimFlag = 0;
					foundFlag = 0;
					Va = Vector();
					Vb = Vector();
					if (postfixFormula[i] == "+" || postfixFormula[i] == "-" || postfixFormula[i] == "*")
					{
						std::string temp;
						double scalar;

						//check scalar or not
						System::String^ Temp = postfixFormula[i - 2];
						MarshalString(Temp, temp);
						if (temp[0] != '$')
							scalar = strtod(temp.c_str(), NULL);

						Temp = postfixFormula[i - 1];
						MarshalString(Temp, temp);
						if (temp[0] != '$')
							scalar = strtod(temp.c_str(), NULL);

						//find vector to calculate
						MarshalString(postfixFormula[i - 2], nameTemp);
						int index = findVector(nameTemp, vectors);
						if (index != -1)
							Va = vectors[index];

						MarshalString(postfixFormula[i - 1], nameTemp);
						index = findVector(nameTemp, vectors);
						if (index != -1)
							Vb = vectors[index];

						//�q�⦡stack����o�B��l
						if (Vb.Name == "" && !calStack.empty())
						{
							Vb = calStack.top();
							calStack.pop();
						}

						if (Va.Name == "" && !calStack.empty())
						{
							Va = calStack.top();
							calStack.pop();
						}

						//found check
						if (!Va.Data.empty() && !Vb.Data.empty())
							foundFlag = 1;
						else if (Va.Data.empty() && Vb.Data.empty()) break;

						//dimesion check
						if (Va.dimCheck(Vb)) {
							dimFlag = 1;

							if (postfixFormula[i] == "+")
							{
								//call Addition
#ifdef DEBUG
								Output->Text += "Addition called" + Environment::NewLine;
#endif // DEBUG
								ans = Va + Vb;
							}
							else if (postfixFormula[i] == "-")
							{
								//call Subtraction
#ifdef DEBUG
								Output->Text += "Subtraction called" + Environment::NewLine;
#endif // DEBUG
								ans = Va - Vb;
							}
							else if (postfixFormula[i] == "*")
							{
								//call dot
#ifdef DEBUG
								Output->Text += "Dot called" + Environment::NewLine;
#endif // DEBUG
								ans = Va * Vb;
							}
							//push into calStack
							calStack.push(ans);

							postfixFormula->RemoveAt(i - 2);
							postfixFormula->RemoveAt(i - 2);
							i -= 2;

						}
						else
						{
							if (Va.Data.empty() || Vb.Data.empty() || \
								(!Va.Data.empty() && !Vb.Data.empty()))
							{
								if (Va.Data.empty() && postfixFormula[i - 2][0] == '$' || \
									Vb.Data.empty() && postfixFormula[i - 1][0] == '$')
									continue;
								dimFlag = 1;
								foundFlag = 1;
								//call scalar
#ifdef DEBUG
								Output->Text += "Scalar called" + Environment::NewLine;
#endif // DEBUG
								if (Va.Data.size() < Vb.Data.size())
								{
									if (!Va.Data.empty())
										scalar = Va.Data[0];
									ans = scalar * Vb;
								}
								else
								{
									if (!Vb.Data.empty())
										scalar = Vb.Data[0];
									ans = scalar * Va;
								}
								//push into calStack
								calStack.push(ans);
								postfixFormula->RemoveAt(i - 2);
								postfixFormula->RemoveAt(i - 2);
								i -= 2;
							}
							else break;
						}
					}
				}

				if (!foundFlag)
					Output->Text += "-Vector not found-" + Environment::NewLine;
				else if (!dimFlag)
					Output->Text += "-Dimension not same-" + Environment::NewLine;
				else
				{
					//�榡�L�~�A��X���G

					String^ outputTemp;
					//�N��X��Ʀs�J�Ȧs
					ans = calStack.top();
					calStack.pop();
					outputTemp = printVector(outputTemp, ans);
					//��X�Ȧs��T
					Output->Text += gcnew String(userCommand[1] + " = " + outputTemp) + Environment::NewLine;
				}
			}

			else if (userCommand[0] == "func")
			{
				Vector Va, Vb;
				bool foundFlag = 0, funcFound = 1, dimFlag = 0;
				if ((userCommand[1] == "Norm(" || userCommand[1] == "Normal(")\
					&& userCommand[3] == ")")	//unary "funcName( $v )"
				{
					dimFlag = 1;
					MarshalString(userCommand[2], nameTemp);
					int index = findVector(nameTemp, vectors);
					if (index != -1)
					{
						foundFlag = 1;
						Va = vectors[index];
						if (userCommand[1] == "Norm(")
						{
#ifdef DEBUG
							Output->Text += "Norm called" + Environment::NewLine;
#endif // DEBUG
							double ans = Va.Norm();
							Output->Text += "Norm(" + userCommand[2] + ") = " + ans + Environment::NewLine;
						}
						else if (userCommand[1] == "Normal(")
						{
#ifdef DEBUG
							Output->Text += "Normalization called" + Environment::NewLine;
#endif // DEBUG
							Vector ans = Va.Normal();
							String^ outputTemp = printVector(outputTemp, ans);
							Output->Text += "Normal(" + userCommand[2] + ") = " + outputTemp + Environment::NewLine;
						}
					}
				}
				else if ((userCommand[1] == "isOrthogonal(" || userCommand[1] == "angle(" \
					|| userCommand[1] == "Com(" || userCommand[1] == "Proj(") \
					&& userCommand[3] == "," && userCommand[5] == ")")	//binary "funcName( $va , $vb )"
				{
					MarshalString(userCommand[2], nameTemp);
					int indexA = findVector(nameTemp, vectors);
					MarshalString(userCommand[4], nameTemp);
					int indexB = findVector(nameTemp, vectors);
					if (indexA != -1 && indexB != -1)
					{
						foundFlag = 1;
						Va = vectors[indexA];
						Vb = vectors[indexB];
						if (Va.dimCheck(Vb))	//dinmension check
						{
							dimFlag = 1;
							if (userCommand[1] == "isOrthogonal(")
							{
#ifdef DEBUG
								Output->Text += "isOrthogonal called" + Environment::NewLine;
#endif // DEBUG
								String^ outputTemp = ((Va * Vb) == 0) ? "Yes" : "No";
								Output->Text += outputTemp + Environment::NewLine;

							}
							else if (userCommand[1] == "Angle(")
							{
#ifdef DEBUG
								Output->Text = "Angle called" + Environment::NewLine;
#endif // DEBUG
								double ans = Va.Angle(Vb);
								Output->Text += "theta = " + ans + Environment::NewLine;
							}
							else if (userCommand[1] == "Com(")
							{
#ifdef DEBUG
								Output->Text += "Com called" + Environment::NewLine;
#endif // DEBUG

								double ans = Va.Com(Vb);
								Output->Text += ans + Environment::NewLine;
							}
							else if (userCommand[1] == "Proj(")
							{
#ifdef DEBUG
								Output->Text += "Proj call" + Environment::NewLine;
#endif // DEBUG
								Vector ans = Va.Proj(Vb);
								String^ outputTemp = "";
								for (int i = 1; i <= 5; i++)
									outputTemp += userCommand[i];
								outputTemp += " = ";
								outputTemp = printVector(outputTemp, ans);
								Output->Text += outputTemp + Environment::NewLine;
							}
						}
					}
				}
				else
				{
					funcFound = 0;
					Output->Text += "-Function not found-" + Environment::NewLine;
				}
				if (funcFound && !foundFlag)
					Output->Text += "-Vector not found-" + Environment::NewLine;
				else if (funcFound && !dimFlag)
					Output->Text += "-dimension not same-" + Environment::NewLine;
			}
			//�Ϥ��h�P�_�䤣����O
			else
			{
				Output->Text += "-Command not found-" + Environment::NewLine;
			}
			userInput = "";
		}
		else
		{
			//�N�ϥΪ̿�J�r��(�bText box��)�A��'\n'�@����
			array<String^> ^userCommand = Input->Text->Split('\n');
			//�ñN�̫�@��A�@���ثe�ϥΪ̿�J���O
			userInput = userCommand[userCommand->Length - 1];
		}

	}
}
