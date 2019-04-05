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
			Output->Text += "---Vector datas have been loaded---" + Environment::NewLine;
		}
	}
	System::Void WindowsForm::loadMatrixToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//開啟Dialog
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
			Output->Text += "---Matrix datas have been loaded---" + Environment::NewLine;
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
			if (userCommand[0] == "printV")
			{
				//定義輸出暫存
				String^ outputTemp = "";

				MarshalString(userCommand[1], nameTemp);
				int index = dataManager->findVector(nameTemp);
				if (index != -1)
				{
					outputTemp = printVector(outputTemp, vectors[index]);
					Output->Text += gcnew String(vectors[index].Name.c_str()) + " = " + outputTemp;
				}
				else
					Output->Text += "-Vector not found-" + Environment::NewLine;
			}
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
					// pop final calculate result vector 
					Vector result = calStack.top();
					calStack.pop();

					// output
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
//				Vector ans, Va, Vb;
//				std::stack<Vector> calStack;
//				bool dimFlag, foundFlag;
//				for (int i = 0; i < postfixFormula->Count; i++)
//				{
//					dimFlag = 0;
//					foundFlag = 0;
//					Va = Vector();
//					Vb = Vector();
//					if (postfixFormula[i] == "+" || postfixFormula[i] == "-" || postfixFormula[i] == "*")
//					{
//						std::string temp;
//						double scalar;
//
//						//check scalar or not
//						System::String^ Temp = postfixFormula[i - 2];
//						MarshalString(Temp, temp);
//						if (temp[0] != '$')
//							scalar = strtod(temp.c_str(), NULL);
//
//						Temp = postfixFormula[i - 1];
//						MarshalString(Temp, temp);
//						if (temp[0] != '$')
//							scalar = strtod(temp.c_str(), NULL);
//
//						//find vector to calculate
//						MarshalString(postfixFormula[i - 2], nameTemp);
//						int index = dataManager->findVector(nameTemp);
//						if (index != -1)
//							Va = vectors[index];
//
//						MarshalString(postfixFormula[i - 1], nameTemp);
//						index = dataManager->findVector(nameTemp);
//						if (index != -1)
//							Vb = vectors[index];
//
//						//從算式stack中獲得運算子
//						if (Vb.Name == "" && !calStack.empty())
//						{
//							Vb = calStack.top();
//							calStack.pop();
//						}
//
//						if (Va.Name == "" && !calStack.empty())
//						{
//							Va = calStack.top();
//							calStack.pop();
//						}
//
//						//found check
//						if (!Va.Data.empty() && !Vb.Data.empty())
//							foundFlag = 1;
//						else if (Va.Data.empty() && Vb.Data.empty()) break;
//
//						//dimesion check
//						if (Va.dimCheck(Vb)) {
//							dimFlag = 1;
//
//							if (postfixFormula[i] == "+")
//							{
//								//call Addition
//#ifdef DEBUG
//								Output->Text += "Addition called" + Environment::NewLine;
//#endif // DEBUG
//								ans = Va + Vb;
//							}
//							else if (postfixFormula[i] == "-")
//							{
//								//call Subtraction
//#ifdef DEBUG
//								Output->Text += "Subtraction called" + Environment::NewLine;
//#endif // DEBUG
//								ans = Va - Vb;
//							}
//							else if (postfixFormula[i] == "*")
//							{
//								//call dot
//#ifdef DEBUG
//								Output->Text += "Dot called" + Environment::NewLine;
//#endif // DEBUG
//								ans = Va * Vb;
//							}
//							//push into calStack
//							calStack.push(ans);
//
//							postfixFormula->RemoveAt(i - 2);
//							postfixFormula->RemoveAt(i - 2);
//							i -= 2;
//
//						}
//						else
//						{
//							if (Va.Data.empty() || Vb.Data.empty() || \
//								(!Va.Data.empty() && !Vb.Data.empty()))
//							{
//								if (Va.Data.empty() && postfixFormula[i - 2][0] == '$' || \
//									Vb.Data.empty() && postfixFormula[i - 1][0] == '$')
//									continue;
//								dimFlag = 1;
//								foundFlag = 1;
//								//call scalar
//#ifdef DEBUG
//								Output->Text += "Scalar called" + Environment::NewLine;
//#endif // DEBUG
//								if (Va.Data.size() < Vb.Data.size())
//								{
//									if (!Va.Data.empty())
//										scalar = Va.Data[0];
//									ans = scalar * Vb;
//								}
//								else
//								{
//									if (!Vb.Data.empty())
//										scalar = Vb.Data[0];
//									ans = scalar * Va;
//								}
//								//push into calStack
//								calStack.push(ans);
//								postfixFormula->RemoveAt(i - 2);
//								postfixFormula->RemoveAt(i - 2);
//								i -= 2;
//							}
//							else break;
//						}
//					}
//				}
//
//				if (!foundFlag)
//					Output->Text += "-Vector not found-" + Environment::NewLine;
//				else if (!dimFlag)
//					Output->Text += "-Dimension not same-" + Environment::NewLine;
//				else
//				{
//					//格式無誤，輸出結果
//
//					String^ outputTemp;
//					//將輸出資料存入暫存
//					ans = calStack.top();
//					calStack.pop();
//					outputTemp = printVector(outputTemp, ans);
//					//輸出暫存資訊
//					Output->Text += gcnew String(userCommand[1] + " = " + outputTemp);
//				}
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
					// pop final calculate result matrix 
					Matrix result = calStack.top();
					calStack.pop();

					// output
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
					// TODO: if Count == 0
					if (funcFormula->Count == 1) throw "---No parameter---";
					else
					{
						// TODO: Change rename method
						switch (funcFormula->Count)
						{
							// record parameter index of array
							int index, indexA, indexB;

						// unary parameter function case
						case 2:

							MarshalString(funcFormula[1], VarNameTemp);
							index = dataManager->findVector(VarNameTemp);

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
							break;

						// binary parameter function case
						case 3:

							MarshalString(funcFormula[1], VarNameTemp);
							indexA = dataManager->findVector(VarNameTemp);
							MarshalString(funcFormula[2], VarNameTemp);
							indexB = dataManager->findVector(VarNameTemp);

							if (!vectors[indexA].dimCheck(vectors[indexB])) throw "---Dimension not same---";

							if (funcFormula[0] == "isorthogonal")
							{
								result.Name = "isOrthogonal(" + vectors[indexA].Name + "," + vectors[indexB].Name + ")";
								result = vectors[indexA] * vectors[indexB];
								if (result.Data[0] == 0)
								{
									result.Name = " : Yes";
								}
								else
								{
									result.Name = " : No";
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
									// TODO: Command tolower
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
								result.Name = "Com(" + vectors[indexA].Name + "," + vectors[indexB].Name + ")";
								double angleValue = vectors[indexA].Angle(vectors[indexB]);

								if (angleValue == 0 || angleValue == 180)
								{
									result.Name = " : Yes";
								}
								else
								{
									result.Name = " : No";
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
							break;
						// Ob function or error
						default:

							/*bool*/ /*foundFlag = 0,*/ /*funcFound = 1,*/ /*dimFlag = 0;*/
							MarshalString(/*userCommand[2]*/ funcFormula[1], nameTemp);
							index = dataManager->findVector(nameTemp);
							//foundFlag = 1;
							std::vector<Vector> ui;
							ui.push_back(vectors[index]);
							int normal = ui[0].Data.size();
							ui.resize(normal);
							/*for (int i = 4, j = 1; i <= 2 * normal; i += 2, j++)*/
							for (int i = 2; i <= normal; i++)
							{
								/*MarshalString(userCommand[i], nameTemp);*/
								MarshalString(funcFormula[i], nameTemp);
								index = dataManager->findVector(nameTemp);

								//if (index == -1)
								//{
								//	foundFlag = 0;
								//	break;
								//}
								//if (vectors[index].Data.size() != normal)
								//{
								//	dimFlag = 0;
								//	break;
								//}

								//dimFlag = 1;
								//ui[j] = vectors[index];	//get vector data into ui

								if (vectors[index].dimCheck(ui[0]))
								{
									ui[i-1] = vectors[index];	//get vector data into ui
								}
							}
							// TODO: Ob isLI output not support
							if (funcFormula[0] == "ob")
							{
								//if (dimFlag && foundFlag)
								//	{
#ifdef DEBUG
										Output->Text += "Ob called" + Environment::NewLine;
#endif // DEBUG
										Matrix ans;
										ans = Ob(normal, ui);

										Output->Text += ans.outputStr();
									//}
							}
							else if (funcFormula[0] == "isli")
							{
#ifdef DEBUG
								Output->Text += "isLI called" + Environment::NewLine;
#endif // DEBUG
								String^ outputTemp;
								outputTemp = (isLI(normal, ui)) ? "Yes" : "No";
								Output->Text += outputTemp + Environment::NewLine;
							}
							else throw  "---Parameter amount error / Function not found---";
							break;
						}
					}
					// TODO: Output 
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

//				Vector Va, Vb;
//				bool foundFlag = 0, funcFound = 1, dimFlag = 0;
//				if ((userCommand[1] == "Norm(" || userCommand[1] == "Normal(")\
//					&& userCommand[3] == ")")	//unary "funcName( $v )"
//				{
//					dimFlag = 1;
//					MarshalString(userCommand[2], nameTemp);
//					int index = findVector(nameTemp, vectors);
//					if (index != -1)
//					{
//						foundFlag = 1;
//						Va = vectors[index];
//						if (userCommand[1] == "Norm(")
//						{
//#ifdef DEBUG
//							Output->Text += "Norm called" + Environment::NewLine;
//#endif // DEBUG
//
//							double ans = Va.Norm();
//							Output->Text += "Norm(" + userCommand[2] + ") = " + ans + Environment::NewLine;
//						}
//						else if (userCommand[1] == "Normal(")
//						{
//#ifdef DEBUG
//							Output->Text += "Normalization called" + Environment::NewLine;
//#endif // DEBUG
//							Vector ans = Va.Normal();
//							String^ outputTemp = printVector(outputTemp, ans);
//							Output->Text += "Normal(" + userCommand[2] + ") = " + outputTemp;
//						}
//					}
//				}
//				else if ((userCommand[1] == "isOrthogonal(" || userCommand[1] == "Angle("	\
//					|| userCommand[1] == "Com(" || userCommand[1] == "Proj(")			\
//					|| userCommand[1] == "Cross(" || userCommand[1] == "isParallel("		\
//					|| userCommand[1] == "Area(" || userCommand[1] == "pN("				\
//					|| userCommand[1] == "isLI("	\
//					&& userCommand[3] == ","		&& userCommand[5] == ")")	//binary "funcName( $va , $vb )"
//				{
//					MarshalString(userCommand[2], nameTemp);
//					int indexA = findVector(nameTemp, vectors);
//					MarshalString(userCommand[4], nameTemp);
//					int indexB = findVector(nameTemp, vectors);
//					if (indexA != -1 && indexB != -1)
//					{
//						foundFlag = 1;
//						Va = vectors[indexA];
//						Vb = vectors[indexB];
//						if (Va.dimCheck(Vb))	//dinmension check
//						{
//							dimFlag = 1;
//							if (userCommand[1] == "isOrthogonal(")
//							{
//#ifdef DEBUG
//								Output->Text += "isOrthogonal called" + Environment::NewLine;
//#endif // DEBUG
//								String^ outputTemp = ((Va * Vb) == 0) ? "Yes" : "No";
//								Output->Text += outputTemp + Environment::NewLine;
//
//							}
//							else if (userCommand[1] == "Angle(")
//							{
//#ifdef DEBUG
//								Output->Text += "Angle called" + Environment::NewLine;
//#endif // DEBUG
//								double ans = Va.Angle(Vb);
//								Output->Text += "theta = " + ans + Environment::NewLine;
//							}
//							else if (userCommand[1] == "Com(")
//							{
//#ifdef DEBUG
//								Output->Text += "Com called" + Environment::NewLine;
//#endif // DEBUG
//
//								double ans = Va.Com(Vb);
//								Output->Text += ans + Environment::NewLine;
//							}
//							else if (userCommand[1] == "Proj(")
//							{
//#ifdef DEBUG
//								Output->Text += "Proj called" + Environment::NewLine;
//#endif // DEBUG
//								Vector ans = Va.Proj(Vb);
//								String^ outputTemp = "";
//								for (int i = 1; i <= 5; i++)
//									outputTemp += userCommand[i];
//								outputTemp += " = ";
//								outputTemp = printVector(outputTemp, ans);
//								Output->Text += outputTemp;
//							}
//							else if (userCommand[1] == "Cross(" || userCommand[1] == "pN(")
//							{
//								if (Va.Data.size() == 3)
//								{
//#ifdef DEBUG
//									Output->Text += "Cross / pN called" + Environment::NewLine;
//#endif // DEBUG
//									Vector ans = Va.Cross(Vb);
//									String^ outputTemp = "";
//									for (int i = 1; i <= 5; i++)
//										outputTemp += userCommand[i];
//									outputTemp += " = ";
//									outputTemp = printVector(outputTemp, ans);
//									Output->Text += outputTemp;
//								}
//								else
//									Output->Text += "-Dimension error-" + Environment::NewLine;
//							}
//							else if (userCommand[1] == "isParallel(")
//							{
//#ifdef DEBUG
//								Output->Text += "isParallel called" + Environment::NewLine;
//#endif // DEBUG
//
//								String^ outputTemp;
//								double angle = Va.Angle(Vb);
//								if (angle == 0 || angle == 180)
//									outputTemp = "Yes";
//								else
//									outputTemp = "No";
//								Output->Text += outputTemp + Environment::NewLine;
//							}
//							else if (userCommand[1] == "Area(")
//							{
//#ifdef DEBUG
//								Output->Text += "Area called" + Environment::NewLine;
//#endif // DEBUG
//
//								double ans = Va.Area(Vb);
//								Output->Text += ans + Environment::NewLine;
//							}
//							else if (userCommand[1] == "isLI(")
//							{
//#ifdef DEBUG
//								Output->Text += "isLI called" + Environment::NewLine;
//#endif // DEBUG
//								//todo
//							}
//						}
//					}
//				}

//				else if (userCommand[1] == "Ob(")
//				{
//					MarshalString(userCommand[2], nameTemp);
//					int index = findVector(nameTemp, vectors);
//					if (index != -1)
//					{
//						foundFlag = 1;
//						std::vector<Vector> ui;
//						ui.push_back(vectors[index]);
//						int normal = ui[0].Data.size();
//						std::vector<Vector> Vi(normal);
//						std::vector<Vector> ni(normal);
//						ui.resize(normal);
//						Vi[0] = ui[0];
//						ni[0] = Vi[0].Normal();
//						for (int i = 4, j = 1; i <= 2 * normal; i += 2, j++)
//						{
//							MarshalString(userCommand[i], nameTemp);
//							index = findVector(nameTemp, vectors);
//							if (index == -1)
//							{
//								foundFlag = 0;
//								break;
//							}
//							if (vectors[index].Data.size() != normal)
//							{
//								dimFlag = 0;
//								break;
//							}
//							dimFlag = 1;
//							ui[j] = vectors[index];	//get vector data into ui
//						}
//						if (dimFlag && foundFlag)
//						{
//#ifdef DEBUG
//							Output->Text += "Ob called" + Environment::NewLine;
//#endif // DEBUG
//							//formula from wikipedia "Gram–Schmidt process"
//							for (int i = 1; foundFlag && i < normal; i++)
//							{
//								Vector sum;
//								sum.Data.resize(normal);
//								for (int j = 0; j <= i - 1; j++)
//								{
//									sum = sum + ((ui[i] * ni[j]) * ni[j]);
//								}
//								Vi[i] = ui[i] - sum;
//								ni[i] = Vi[i].Normal();
//							}
//							String^ outputTemp = "";
//							for (int i = 1; i <= normal * 2 + 1; i++)
//								outputTemp += userCommand[i];
//							outputTemp += " :" + Environment::NewLine;
//							for (int i = 0; i < normal; i++)
//							{
//								outputTemp = printVector(outputTemp, ni[i]);
//							}
//							Output->Text += outputTemp;
//						}
//					}
//				}
//				else
//				{
//					funcFound = 0;
//					Output->Text += "-Function not found-" + Environment::NewLine;
//				}
//				if (funcFound && !foundFlag)
//					Output->Text += "-Vector not found-" + Environment::NewLine;
//				else if (funcFound && !dimFlag)
//					Output->Text += "-dimension not same-" + Environment::NewLine;
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
					// TODO: if Count == 0
					if (funcFormula->Count == 1) throw "---No parameter---";
					else
					{
						// TODO: Change rename method
						switch (funcFormula->Count)
						{
							// record parameter index of array
							int index, indexA, indexB;

							// unary parameter function case
						case 2:
							MarshalString(funcFormula[1], VarNameTemp);
							// find matrix
							int index = dataManager->findMatrix(VarNameTemp);

							if (funcFormula[0] == "trans")
							{
								result = matrices[index].trans();
							}
							else if (funcFormula[0] == "gauss")
							{
								result = matrices[index].gaussian();
							}
							else if (funcFormula[0] == "rank")
							{
								double rankValue = matrices[index].rank();
								result.Data.resize(1);
								result.Data[0].Data.push_back(rankValue);
								result.Name = "Rank Value";
							}
							else if (funcFormula[0] == "det")
							{
								double detValue = matrices[index].det();
								result.Data.resize(1);
								result.Data[0].Data.push_back(detValue);
								result.Name = "Determinant Value";
							}
							else if (funcFormula[0] == "inverse")
							{
								result = matrices[index].inverse();
							}
							else if (funcFormula[0] == "adjoint")
							{
								result = matrices[index].adjoint();
							}
							else if (funcFormula[0] == "eigen")
							{
								throw "---Eigen not finished---";
							}
							else if (funcFormula[0] == "pm")
							{
								throw "---PM not finished---";
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
								throw "---LeastSquare not finished---";
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
			//反之則判斷找不到指令
			else
			{
				Output->Text += "---Command not found---" + Environment::NewLine;
			}
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
