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
		case '*': case '/': case'\\': return 2;
		default:            return 0;
		}
	}
	String^ printVector(String^ s, const Vector& v)
	{
		s += "[";
		for (int i = 0; i < v.Data.size(); i++)
		{
			/*不知道怎麼限制6位*/
			s += v.Data[i].ToString();
			if (i != v.Data.size() - 1)
				s += ", ";
		}
		s += "]" + Environment::NewLine;
		return s;
	}

	// TODO: Combine findVar function
	int findVector(std::string name, const std::vector<Vector>& v)
	{
		std::string temp;
		//MarshalString(name, temp);

		//透過for迴圈，從向量資料中找出對應變數
		for (unsigned int i = 0; i < v.size(); i++)
		{
			//若變數名稱與指令變數名稱符合
			if (name == v[i].Name)
				return i;
		}
		return -1;
	}
	int findMatrix(std::string name, const std::vector<Matrix>& m)
	{
		std::string temp;
		//MarshalString(name, temp);

		//透過for迴圈，從向量資料中找出對應變數
		for (unsigned int i = 0; i < m.size(); i++)
		{
			//若變數名稱與指令變數名稱符合
			if (name == m[i].Name)
				return i;
		}
		// error handle
		throw "Varible not found";
		// return -1;
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
				Cmd->Add(CmdArray[i]);
			}
		}
		return Cmd;
	}

	System::Void WindowsForm::loadVectorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//開啟Dialog
		openFileDialog1->ShowDialog();
	}
	System::Void WindowsForm::openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		//在Dialog按下OK便會進入此函式
		//字串轉制string^ to string
		std::string tempFileName;
		MarshalString(openFileDialog1->FileName, tempFileName);
		//將檔案路徑名稱傳入dataManager
		dataManager->SetFileName(tempFileName);
		//從讀取讀取向量資料
		if (dataManager->LoadVectorData())
		{
			//將VectorList中項目先做清除
			VectorList->Items->Clear();
			//取得所有向量資料
			std::vector<Vector> vectors = dataManager->GetVectors();

			for (unsigned int i = 0; i < vectors.size(); i++)
			{
				//將檔案名稱存入暫存
				std::string tempString = vectors[i].Name;
				//將輸出格式存入暫存
				tempString += " [";
				//將輸出資料存入暫存
				for (unsigned int j = 0; j < vectors[i].Data.size(); j++)
				{
					std::string scalarString = std::to_string(vectors[i].Data[j]);
					tempString += scalarString.substr(0, scalarString.size() - 5);
					if (j != vectors[i].Data.size() - 1)
						tempString += ",";
				}
				//將輸出格式存入暫存
				tempString += "]";
				//將項目加入VectorList中
				VectorList->Items->Add(gcnew String(tempString.c_str()));
			}
			Output->Text += "-Vector datas have been loaded-" + Environment::NewLine;
		}
	}
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

	System::Void WindowsForm::Input_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//當Input textbox中的輸入改變時，便會進入此函式
		//取得向量資料
		std::vector<Vector> vectors = dataManager->GetVectors();
		std::vector<Matrix> matrices = dataManager->GetMatrices();
		//判斷輸入自元為'\n'，並防止取到字串-1位置
		if (Input->Text->Length - 1 >= 0 && Input->Text[Input->Text->Length - 1] == '\n')
		{
			//將使用者輸入字串(在userInput中)，依空白作切割
			array<String^> ^userCommand = userInput->Split(' ');
			std::string nameTemp;
			//字串比較，若指令為"print"的情況
			if (userCommand[0] == "print")
			{
				//定義輸出暫存
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

			else if (userCommand[0] == "calV")
			{
				//infix to postfix

				//若運算式中有空格先合併成無空格版
				for (int i = 2; i < userCommand->Length; i++)
				{
					userCommand[1] += userCommand[i];
				}
				//將無空格版處理成空格版
				//定義輸出暫存
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
				//去除最後一個空格
				if (infixTemp[infixTemp->Length - 1] == ' ')
				{
					infixTemp = infixTemp->Remove(infixTemp->Length - 1, 1);
				}
				//將處理完的字串依空白作切割
				array<String^> ^infixFormula = infixTemp->Split(' ');
				String^ stack = " ";

				String^ postfix = "";
				int top = 0;
				for (int i = 0; i < infixFormula->Length; i++)
				{

					if (infixFormula[i] == "(")
					{
						// 運算子堆疊
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
						stack = stack->Insert(++top, infixFormula[i]); // 存入堆疊
					}
					else if (infixFormula[i] == ")")
					{
						while (stack[top] != '(') { // 遇 ) 輸出至 (
							postfix += stack[top--];
							postfix += " ";
						}
						top--;  // 不輸出 (
					}
					else
					{
						// 運算元直接輸出
						postfix += infixFormula[i];
						postfix += " ";
					}
				}
				while (top > 0) {
					postfix += stack[top--];
					postfix += " ";
				}
				//去除最後一個空格
				if (postfix[postfix->Length - 1] == ' ')
				{
					postfix = postfix->Remove(postfix->Length - 1, 1);
				}
				//將處理完的字串(postfix)依空白作切割存到array
				array<String^> ^postfixArray = postfix->Split(' ');

				//將array(postfixArray)轉成List
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

						//從算式stack中獲得運算子
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
					//格式無誤，輸出結果

					String^ outputTemp;
					//將輸出資料存入暫存
					ans = calStack.top();
					calStack.pop();
					outputTemp = printVector(outputTemp, ans);
					//輸出暫存資訊
					Output->Text += gcnew String(userCommand[1] + " = " + outputTemp);
				}
			}
			
			// calculate Matrix
			else if (userCommand[0] == "calM")
			{
				//infix to postfix
				//若運算式中有空格先合併成無空格版
				for (int i = 2; i < userCommand->Length; i++)
				{
					userCommand[1] += userCommand[i];
				}
				//將無空格版處理成空格版
				//定義輸出暫存
				String^ infixTemp = "";
				int begin = 0;
				for (int i = 0; i < userCommand[1]->Length; i++)
				{
					if (userCommand[1][i] == '(' ||
						userCommand[1][i] == ')' ||
						userCommand[1][i] == '+' ||
						userCommand[1][i] == '-' ||
						userCommand[1][i] == '*' || 
						userCommand[1][i] == '\\')
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
				//去除最後一個空格
				if (infixTemp[infixTemp->Length - 1] == ' ')
				{
					infixTemp = infixTemp->Remove(infixTemp->Length - 1, 1);
				}
				//將處理完的字串依空白作切割
				array<String^> ^infixFormula = infixTemp->Split(' ');
				String^ stack = " ";

				String^ postfix = "";
				int top = 0;
				for (int i = 0; i < infixFormula->Length; i++)
				{

					if (infixFormula[i] == "(")
					{
						// 運算子堆疊
						stack = stack->Insert(++top, infixFormula[i]);
					}
					else if (infixFormula[i] == "+" ||
						infixFormula[i] == "-" ||
						infixFormula[i] == "*" ||
						infixFormula[i] == "\\")
					{
						while (priority(stack[top]) >= priority(infixFormula[i][0]))
						{
							postfix += stack[top--];
							postfix += " ";
						}
						stack = stack->Insert(++top, infixFormula[i]); // 存入堆疊
					}
					else if (infixFormula[i] == ")")
					{
						while (stack[top] != '(') { // 遇 ) 輸出至 (
							postfix += stack[top--];
							postfix += " ";
						}
						top--;  // 不輸出 (
					}
					else
					{
						// 運算元直接輸出
						postfix += infixFormula[i];
						postfix += " ";
					}
				}
				while (top > 0) {
					postfix += stack[top--];
					postfix += " ";
				}
				//去除最後一個空格
				if (postfix[postfix->Length - 1] == ' ')
				{
					postfix = postfix->Remove(postfix->Length - 1, 1);
				}
				//將處理完的字串(postfix)依空白作切割存到array
				array<String^> ^postfixArray = postfix->Split(' ');

				//將array(postfixArray)轉成List
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

				Matrix ans, Ma, Mb;
				std::stack<Matrix> calStack;
				bool dimFlag, foundFlag;
				try
				{
					for (int i = 0; i < postfixFormula->Count; i++)
					{
						if (postfixFormula[i] == "+" || postfixFormula[i] == "-" || postfixFormula[i] == "*" || postfixFormula[i] == "\\")
						{
							std::string opTemp = "";
							MarshalString(postfixFormula[i], opTemp);

							Matrix Mb = calStack.top();
							calStack.pop();
							Matrix Ma = calStack.top();
							calStack.pop();

							calStack.push(Matrix(opTemp[0], Ma, Mb));
						}
						else
						{
							std::string formulaTemp = "";
							MarshalString(postfixFormula[i], formulaTemp);
							int index = findMatrix(formulaTemp, matrices);
							calStack.push(matrices[index]);
						}
					}

					Matrix result = calStack.top();
					calStack.pop();

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


				//if (!foundFlag)
				//	Output->Text += "-Vector not found-" + Environment::NewLine;
				//else if (!dimFlag)
				//	Output->Text += "-Dimension not same-" + Environment::NewLine;
				//else
				//{
				//	//格式無誤，輸出結果

				//	String^ outputTemp;
				//	//將輸出資料存入暫存
				//	ans = calStack.top();
				//	calStack.pop();
				//	outputTemp = printVector(outputTemp, ans);
				//	//輸出暫存資訊
				//	Output->Text += gcnew String(userCommand[1] + " = " + outputTemp) + Environment::NewLine;
				//}
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
							Output->Text += "Normal(" + userCommand[2] + ") = " + outputTemp;
						}
					}
				}
				else if ((userCommand[1] == "isOrthogonal(" || userCommand[1] == "Angle("	\
					|| userCommand[1] == "Com("		|| userCommand[1] == "Proj(")			\
					|| userCommand[1] == "Cross("	|| userCommand[1] == "isParallel("		\
					|| userCommand[1] == "Area("	|| userCommand[1] == "pN("				\
					|| userCommand[1] == "isLI("	\
					&& userCommand[3] == ","		&& userCommand[5] == ")")	//binary "funcName( $va , $vb )"
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
								Output->Text += "Angle called" + Environment::NewLine;
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
								Output->Text += "Proj called" + Environment::NewLine;
#endif // DEBUG
								Vector ans = Va.Proj(Vb);
								String^ outputTemp = "";
								for (int i = 1; i <= 5; i++)
									outputTemp += userCommand[i];
								outputTemp += " = ";
								outputTemp = printVector(outputTemp, ans);
								Output->Text += outputTemp;
							}
							else if (userCommand[1] == "Cross(" || userCommand[1] == "pN(")
							{
								if (Va.Data.size() == 3)
								{
#ifdef DEBUG
									Output->Text += "Cross / pN called" + Environment::NewLine;
#endif // DEBUG
									Vector ans = Va.Cross(Vb);
									String^ outputTemp = "";
									for (int i = 1; i <= 5; i++)
										outputTemp += userCommand[i];
									outputTemp += " = ";
									outputTemp = printVector(outputTemp, ans);
									Output->Text += outputTemp;
								}
								else
									Output->Text += "-Dimension error-" + Environment::NewLine;
							}
							else if (userCommand[1] == "isParallel(")
							{
#ifdef DEBUG
								Output->Text += "isParallel called" + Environment::NewLine;
#endif // DEBUG

								String^ outputTemp;
								double angle = Va.Angle(Vb);
								if (angle == 0 || angle == 180)
									outputTemp = "Yes";
								else
									outputTemp = "No";
								Output->Text += outputTemp + Environment::NewLine;
							}
							else if (userCommand[1] == "Area(")
							{
#ifdef DEBUG
								Output->Text += "Area called" + Environment::NewLine;
#endif // DEBUG

								double ans = Va.Area(Vb);
								Output->Text += ans + Environment::NewLine;
							}
							else if (userCommand[1] == "isLI(")
							{
#ifdef DEBUG
								Output->Text += "isLI called" + Environment::NewLine;
#endif // DEBUG
								//todo
							}
						}
					}
				}
				else if (userCommand[1] == "Ob(")
				{
					MarshalString(userCommand[2], nameTemp);
					int index = findVector(nameTemp, vectors);
					if (index != -1)
					{
						foundFlag = 1;
						std::vector<Vector> ui;
						ui.push_back(vectors[index]);
						int normal = ui[0].Data.size();
						std::vector<Vector> Vi(normal);
						std::vector<Vector> ni(normal);
						ui.resize(normal);
						Vi[0] = ui[0];
						ni[0] = Vi[0].Normal();
						for (int i = 4, j = 1; i <= 2 * normal; i += 2, j++)
						{
							MarshalString(userCommand[i], nameTemp);
							index = findVector(nameTemp, vectors);
							if (index == -1)
							{
								foundFlag = 0;
								break;
							}
							if (vectors[index].Data.size() != normal)
							{
								dimFlag = 0;
								break;
							}
							dimFlag = 1;
							ui[j] = vectors[index];	//get vector data into ui
						}
						if (dimFlag && foundFlag)
						{
#ifdef DEBUG
							Output->Text += "Ob called" + Environment::NewLine;
#endif // DEBUG
							//formula from wikipedia "Gram–Schmidt process"
							for (int i = 1; foundFlag && i < normal; i++)
							{
								Vector sum;
								sum.Data.resize(normal);
								for (int j = 0; j <= i - 1; j++)
								{
									sum = sum + ((ui[i] * ni[j]) * ni[j]);
								}
								Vi[i] = ui[i] - sum;
								ni[i] = Vi[i].Normal();
							}
							String^ outputTemp = "";
							for (int i = 1; i <= normal * 2 + 1; i++)
								outputTemp += userCommand[i];
							outputTemp += " :" + Environment::NewLine;
							for (int i = 0; i < normal; i++)
							{
								outputTemp = printVector(outputTemp, ni[i]);
							}
							Output->Text += outputTemp;
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

			// Matrix Function
			else if (userCommand[0] == "funcM")
			{
				Generic::List<String^> ^funcFormula = CmdProcess(userCommand);
				try
				{
					Matrix temp;
					std::string VarNameTemp = "";
					MarshalString(funcFormula[1], VarNameTemp);
					int index = findMatrix(VarNameTemp, matrices);

					if (funcFormula[0] == "trans")
					{
						temp = matrices[index].trans();
					}
					else if (funcFormula[0] == "gauss")
					{
						temp = matrices[index].gaussian();
					}
					else if (funcFormula[0] == "rank")
					{
						double rankValue = matrices[index].rank();
						temp.Data.resize(1);
						temp.Data[0].Data.push_back(rankValue);
						temp.Name = "Rank Value";
					}
					else if (funcFormula[0] == "det")
					{
						double detValue = matrices[index].det();
						temp.Data.resize(1);
						temp.Data[0].Data.push_back(detValue);
						temp.Name = "Determinant Value";
					}
					else if (funcFormula[0] == "inverse")
					{
						temp = matrices[index].inverse();
					}
					else
					{
						throw "---Command not exist---";
					}
					Output->Text += temp.outputStr();
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
			//反之則判斷找不到指令
			else
			{
				Output->Text += "-Command not found-" + Environment::NewLine;
			}
			userInput = "";
		}
		else
		{
			//將使用者輸入字串(在Text box中)，依'\n'作切割
			array<String^> ^userCommand = Input->Text->Split('\n');
			//並將最後一行，作為目前使用者輸入指令
			userInput = userCommand[userCommand->Length - 1];
		}

	}
}
