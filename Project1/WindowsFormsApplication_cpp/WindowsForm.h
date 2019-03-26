#pragma once
#define DEBUG
#include "DataManager.h"
#include "DotNetUtilities.h"
#include <stack>

namespace WindowsFormsApplication_cpp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	int priority(char op) {
		switch (op) {
		case '+': case '-': return 1;
		case '*': case '/': return 2;
		default:            return 0;
		}
	}

	String^ printVector(String^ s , const Vector& v)
	{
		s += "[";
		for (int i = 0; i < v.Data.size(); i++)
		{
			s += v.Data[i].ToString();
			if (i != v.Data.size() - 1)
				s += ",";
		}
		s += "]" + Environment::NewLine;
		return s;
	}

	int findVector( std::string name, const std::vector<Vector>& v)
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

	/// <summary>
	/// WindowsForm 的摘要
	/// </summary>
	public ref class WindowsForm : public System::Windows::Forms::Form
	{
	public:
		WindowsForm(void)
		{
			InitializeComponent();
			dataManager = new DataManager();
			lastInputLength = -1;
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~WindowsForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip2;

	private: System::Windows::Forms::ToolStripMenuItem^  loadVectorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadMatrixToolStripMenuItem;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog2;

	protected:

	private:
		/// <summary>
			DataManager* dataManager;
			String^ userInput;
			int lastInputLength;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TextBox^  Output;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  Input;
	private: System::Windows::Forms::ListBox^  VectorList;
	private: System::Windows::Forms::ListBox^  MatrixList;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBox4;



			/// </summary>
			System::ComponentModel::Container ^components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
			this->loadVectorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadMatrixToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->Output = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Input = (gcnew System::Windows::Forms::TextBox());
			this->VectorList = (gcnew System::Windows::Forms::ListBox());
			this->MatrixList = (gcnew System::Windows::Forms::ListBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->menuStrip2->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
			//
			// menuStrip2
			//
			this->menuStrip2->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->loadVectorToolStripMenuItem,
					this->loadMatrixToolStripMenuItem
			});
			this->menuStrip2->Location = System::Drawing::Point(0, 0);
			this->menuStrip2->Name = L"menuStrip2";
			this->menuStrip2->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			this->menuStrip2->Size = System::Drawing::Size(879, 27);
			this->menuStrip2->TabIndex = 1;
			this->menuStrip2->Text = L"menuStrip2";
			//
			// loadVectorToolStripMenuItem
			//
			this->loadVectorToolStripMenuItem->Name = L"loadVectorToolStripMenuItem";
			this->loadVectorToolStripMenuItem->Size = System::Drawing::Size(105, 23);
			this->loadVectorToolStripMenuItem->Text = L"Load Vector";
			this->loadVectorToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::loadVectorToolStripMenuItem_Click);
			//
			// loadMatrixToolStripMenuItem
			//
			this->loadMatrixToolStripMenuItem->Name = L"loadMatrixToolStripMenuItem";
			this->loadMatrixToolStripMenuItem->Size = System::Drawing::Size(104, 23);
			this->loadMatrixToolStripMenuItem->Text = L"Load Matrix";
			this->loadMatrixToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::loadMatrixToolStripMenuItem_Click);
			//
			// openFileDialog1
			//
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WindowsForm::openFileDialog1_FileOk);
			//
			// openFileDialog2
			//
			this->openFileDialog2->FileName = L"openFileDialog1";
			this->openFileDialog2->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WindowsForm::openFileDialog2_FileOk);
			//
			// groupBox2
			//
			this->groupBox2->Controls->Add(this->Output);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox2->Location = System::Drawing::Point(3, 81);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(873, 150);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Output";
			//
			// Output
			//
			this->Output->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Output->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Output->Location = System::Drawing::Point(3, 23);
			this->Output->Margin = System::Windows::Forms::Padding(4);
			this->Output->Multiline = true;
			this->Output->Name = L"Output";
			this->Output->ReadOnly = true;
			this->Output->Size = System::Drawing::Size(867, 124);
			this->Output->TabIndex = 1;
			//
			// groupBox1
			//
			this->groupBox1->Controls->Add(this->Input);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold));
			this->groupBox1->Location = System::Drawing::Point(3, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(873, 72);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Input";
			//
			// Input
			//
			this->Input->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Input->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Input->Location = System::Drawing::Point(3, 23);
			this->Input->Margin = System::Windows::Forms::Padding(4);
			this->Input->Multiline = true;
			this->Input->Name = L"Input";
			this->Input->Size = System::Drawing::Size(867, 46);
			this->Input->TabIndex = 1;
			this->Input->TextChanged += gcnew System::EventHandler(this, &WindowsForm::Input_TextChanged);
			//
			// VectorList
			//
			this->VectorList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->VectorList->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->VectorList->FormattingEnabled = true;
			this->VectorList->ItemHeight = 19;
			this->VectorList->Location = System::Drawing::Point(3, 23);
			this->VectorList->Margin = System::Windows::Forms::Padding(4);
			this->VectorList->Name = L"VectorList";
			this->VectorList->Size = System::Drawing::Size(867, 124);
			this->VectorList->TabIndex = 3;
			//
			// MatrixList
			//
			this->MatrixList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->MatrixList->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->MatrixList->FormattingEnabled = true;
			this->MatrixList->ItemHeight = 19;
			this->MatrixList->Location = System::Drawing::Point(3, 23);
			this->MatrixList->Margin = System::Windows::Forms::Padding(4);
			this->MatrixList->Name = L"MatrixList";
			this->MatrixList->Size = System::Drawing::Size(867, 125);
			this->MatrixList->TabIndex = 0;
			//
			// tableLayoutPanel1
			//
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->groupBox1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->groupBox2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->groupBox3, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->groupBox4, 0, 3);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 27);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(4);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 4;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 28.57143F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 28.57143F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 28.57143F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(879, 547);
			this->tableLayoutPanel1->TabIndex = 2;
			//
			// groupBox3
			//
			this->groupBox3->Controls->Add(this->VectorList);
			this->groupBox3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox3->Location = System::Drawing::Point(3, 237);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(873, 150);
			this->groupBox3->TabIndex = 6;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Vector";
			//
			// groupBox4
			//
			this->groupBox4->Controls->Add(this->MatrixList);
			this->groupBox4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox4->Location = System::Drawing::Point(3, 393);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(873, 151);
			this->groupBox4->TabIndex = 7;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Matrix";
			//
			// WindowsForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(879, 574);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->menuStrip2);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"WindowsForm";
			this->Text = L"VectorExample";
			this->Load += gcnew System::EventHandler(this, &WindowsForm::WindowsForm_Load);
			this->menuStrip2->ResumeLayout(false);
			this->menuStrip2->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void WindowsForm_Load(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void Input_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	//當Input textbox中的輸入改變時，便會進入此函式
	//取得向量資料
	std::vector<Vector> vectors = dataManager->GetVectors();
	//判斷輸入自元為'\n'，並防止取到字串-1位置
	if (Input->Text->Length-1 >= 0 &&Input->Text[Input->Text->Length - 1] == '\n')
	{
		//將使用者輸入字串(在userInput中)，依空白作切割
		array<String^> ^userCommand = userInput->Split(' ');
		//字串比較，若指令為"print"的情況
		if (userCommand[0] == "print")
		{
			//定義輸出暫存
			String^ outputTemp = "";
			std::string nameTemp;
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
			Generic::List<String^> ^postfixFormula = gcnew Generic::List<String^> ();
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
					std::string nameTemp;
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
				Output->Text += gcnew String(userCommand[1] + " = " + outputTemp) + Environment::NewLine;
			}
		}

		else if (userCommand[0] == "func")
		{
			Vector Va, Vb;
			bool foundFlag = 0;
			if (userCommand[1] == "Norm\(" && userCommand[3] == ")")
			{
#ifdef DEBUG
				Output->Text += "Norm called" + Environment::NewLine;
#endif // DEBUG
				for (unsigned int i = 0; i < vectors.size(); i++)
				{
					if (userCommand[2] == gcnew String(vectors[i].Name.c_str()))
					{
						Va = vectors[i];
						foundFlag = 1;
						break;
					}
				}
				if (foundFlag)
				{
					double ans = Va.Norm();
					Output->Text += "Norm(" + userCommand[2] + ") = " + ans + Environment::NewLine;
				}
			}
			else if (userCommand[1] == "Normal(" && userCommand[3] == ")")
			{
#ifdef DEBUG
				Output->Text += "Normalization called" + Environment::NewLine;
#endif // DEBUG
				for (unsigned int i = 0; i < vectors.size(); i++)
				{
					if (userCommand[2] == gcnew String(vectors[i].Name.c_str()))
					{
						Va = vectors[i];
						foundFlag = 1;
						break;
					}
				}
				if (foundFlag)
				{
					Vector ans = Va.Normal();
					Output->Text += "Normal(" + userCommand[2] + ") = ";
					//call print
				}
			}
			else
				Output->Text += "-Function not found-" + Environment::NewLine;

			if (!foundFlag)
				Output->Text += "-Vector not found-" + Environment::NewLine;
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
		userInput = userCommand[userCommand->Length-1];
	}

}
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
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
			for (unsigned int j = 0; j<vectors[i].Data.size(); j++)
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

private: System::Void loadVectorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	//開啟Dialog
	openFileDialog1->ShowDialog();
}

private:
	System::Void loadMatrixToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void openFileDialog2_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);


};
}
