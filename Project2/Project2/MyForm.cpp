#include "MyForm.h"
#include <stack>

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
		//若運算式中有空格先合併成無空格版
		for (int i = 2; i < formulaList->Length; i++)
		{
			formulaList[1] += formulaList[i];
		}

		// infix formula (blank ver)
		String^ infixTemp = "";

		//將無空格版處理成空格版
		for (int i = 0; i < formulaList[1]->Length; i++)
		{
			if (formulaList[1][i] == '(' || \
				formulaList[1][i] == ')' || \
				formulaList[1][i] == '+' || \
				formulaList[1][i] == '-' || \
				formulaList[1][i] == '*' || \
				formulaList[1][i] == '/' || \
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
				// 運算子堆疊
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
				opStack.push(stdStringTemp); // 存入堆疊
			}
			else if (infixArray[i] == ")")
			{
				while (opStack.top() != "(")
				{
					// 遇 ) 輸出至 (
					String^ formStringTemp = gcnew String(opStack.top().c_str());
					postfixArray->Add(formStringTemp);
					opStack.pop();
				}
				opStack.pop();  // 不輸出 (
			}
			else
			{
				// 運算元直接輸出
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
		//若運算式中有空格先合併成無空格版
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

		//將array(CmdArray)轉成List
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
	System::Void MyForm::loadFileToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		openFileDialog1->ShowDialog();
	}

	System::Void MyForm::openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string FilePath;
		MarshalString(openFileDialog1->FileName, FilePath);

		std::fstream fin;
		fin.open(FilePath, std::ios::in);

		std::string tempString;
		
		while (!fin.eof())
		{
			fin >> tempString;
			Input->Text += gcnew System::String(tempString.c_str()) + Environment::NewLine;
		}
	}
}