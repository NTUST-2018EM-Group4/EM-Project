#pragma once
#include "DataManager.h"
#include "DotNetUtilities.h"
#include <stack>

#include <stdlib.h>
#include <string.h>
#include <msclr/marshal_cppstd.h>


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

	/// <summary>
	/// WindowsForm ���K�n
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
		/// �M������ϥΤ����귽�C
		/// </summary>
		~WindowsForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip2;
	private: System::Windows::Forms::ToolStripMenuItem^  FileToolStripMenuItem;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::ToolStripMenuItem^  LoadVectorToolStripMenuItem;



	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
	private: System::Windows::Forms::Label^  OutputLabel;
	private: System::Windows::Forms::TextBox^  Output;

	private: System::Windows::Forms::Label^  InputLabel;
	private: System::Windows::Forms::TextBox^  Input;
	private: System::Windows::Forms::Label^  VectorLabel;
	private: System::Windows::Forms::ListBox^  VectorList;



	protected:















	protected:

	private:
		/// <summary>
			DataManager* dataManager;
			String^ userInput;
			int lastInputLength;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
			 /// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
			this->FileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LoadVectorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->InputLabel = (gcnew System::Windows::Forms::Label());
			this->Input = (gcnew System::Windows::Forms::TextBox());
			this->VectorLabel = (gcnew System::Windows::Forms::Label());
			this->VectorList = (gcnew System::Windows::Forms::ListBox());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->OutputLabel = (gcnew System::Windows::Forms::Label());
			this->Output = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip2->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip2
			// 
			this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->FileToolStripMenuItem });
			this->menuStrip2->Location = System::Drawing::Point(0, 0);
			this->menuStrip2->Name = L"menuStrip2";
			this->menuStrip2->Size = System::Drawing::Size(384, 24);
			this->menuStrip2->TabIndex = 1;
			this->menuStrip2->Text = L"menuStrip2";
			// 
			// FileToolStripMenuItem
			// 
			this->FileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->LoadVectorToolStripMenuItem });
			this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
			this->FileToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->FileToolStripMenuItem->Text = L"File";
			// 
			// LoadVectorToolStripMenuItem
			// 
			this->LoadVectorToolStripMenuItem->Name = L"LoadVectorToolStripMenuItem";
			this->LoadVectorToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->LoadVectorToolStripMenuItem->Text = L"Load Vector";
			this->LoadVectorToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::LoadVectorToolStripMenuItem_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel2, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 24);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(384, 338);
			this->tableLayoutPanel1->TabIndex = 2;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->InputLabel);
			this->flowLayoutPanel1->Controls->Add(this->Input);
			this->flowLayoutPanel1->Controls->Add(this->VectorLabel);
			this->flowLayoutPanel1->Controls->Add(this->VectorList);
			this->flowLayoutPanel1->Location = System::Drawing::Point(195, 3);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(186, 332);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// InputLabel
			// 
			this->InputLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->InputLabel->AutoSize = true;
			this->InputLabel->Font = (gcnew System::Drawing::Font(L"�L�n������", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->InputLabel->Location = System::Drawing::Point(3, 0);
			this->InputLabel->Name = L"InputLabel";
			this->InputLabel->Size = System::Drawing::Size(41, 16);
			this->InputLabel->TabIndex = 0;
			this->InputLabel->Text = L"Input";
			// 
			// Input
			// 
			this->Input->Location = System::Drawing::Point(3, 19);
			this->Input->Multiline = true;
			this->Input->Name = L"Input";
			this->Input->Size = System::Drawing::Size(180, 158);
			this->Input->TabIndex = 1;
			this->Input->TextChanged += gcnew System::EventHandler(this, &WindowsForm::Input_TextChanged);
			// 
			// VectorLabel
			// 
			this->VectorLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->VectorLabel->AutoSize = true;
			this->VectorLabel->Font = (gcnew System::Drawing::Font(L"�L�n������", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->VectorLabel->Location = System::Drawing::Point(3, 180);
			this->VectorLabel->Name = L"VectorLabel";
			this->VectorLabel->Size = System::Drawing::Size(47, 16);
			this->VectorLabel->TabIndex = 2;
			this->VectorLabel->Text = L"Vector";
			// 
			// VectorList
			// 
			this->VectorList->FormattingEnabled = true;
			this->VectorList->ItemHeight = 12;
			this->VectorList->Location = System::Drawing::Point(3, 199);
			this->VectorList->Name = L"VectorList";
			this->VectorList->Size = System::Drawing::Size(180, 124);
			this->VectorList->TabIndex = 3;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Controls->Add(this->OutputLabel);
			this->flowLayoutPanel2->Controls->Add(this->Output);
			this->flowLayoutPanel2->Location = System::Drawing::Point(3, 3);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(186, 332);
			this->flowLayoutPanel2->TabIndex = 1;
			// 
			// OutputLabel
			// 
			this->OutputLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->OutputLabel->AutoSize = true;
			this->OutputLabel->Font = (gcnew System::Drawing::Font(L"�L�n������", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->OutputLabel->Location = System::Drawing::Point(3, 0);
			this->OutputLabel->Name = L"OutputLabel";
			this->OutputLabel->Size = System::Drawing::Size(52, 16);
			this->OutputLabel->TabIndex = 0;
			this->OutputLabel->Text = L"Output";
			// 
			// Output
			// 
			this->Output->Font = (gcnew System::Drawing::Font(L"�s�ө���", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Output->Location = System::Drawing::Point(3, 19);
			this->Output->Multiline = true;
			this->Output->Name = L"Output";
			this->Output->ReadOnly = true;
			this->Output->Size = System::Drawing::Size(183, 313);
			this->Output->TabIndex = 1;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WindowsForm::openFileDialog1_FileOk);
			// 
			// WindowsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 362);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->menuStrip2);
			this->Name = L"WindowsForm";
			this->Text = L"VectorExample";
			this->Load += gcnew System::EventHandler(this, &WindowsForm::WindowsForm_Load);
			this->menuStrip2->ResumeLayout(false);
			this->menuStrip2->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void WindowsForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void LoadVectorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	//�}��Dialog
	openFileDialog1->ShowDialog();
}
private: System::Void Input_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	//��Input textbox������J���ܮɡA�K�|�i�J���禡
	//���o�V�q���
	std::vector<Vector> vectors = dataManager->GetVectors();
	//�P�_��J�ۤ���'\n'�A�è������r��-1��m
	if (Input->Text->Length-1 >= 0 &&Input->Text[Input->Text->Length - 1] == '\n')
	{
		//�N�ϥΪ̿�J�r��(�buserInput��)�A�̪ťէ@����
		array<String^> ^userCommand = userInput->Split(' ');
		//�r�����A�Y���O��"print"�����p
		if (userCommand[0] == "print")
		{
			//�w�q��X�Ȧs
			String^ outputTemp = "";
			//�z�Lfor�j��A�q�V�q��Ƥ���X�����ܼ�
			for (unsigned int i = 0; i < vectors.size();i++)
			{
				//�Y�ܼƦW�ٻP���O�ܼƦW�ٲŦX
				if (userCommand[1] == gcnew String(vectors[i].Name.c_str()))
				{
					//�N��X�榡�s�J�Ȧs
					outputTemp += "[";
					//�N��X��Ʀs�J�Ȧs
					for (unsigned int j = 0; j<vectors[i].Data.size(); j++)
					{
						outputTemp += vectors[i].Data[j].ToString();
						if (j != vectors[i].Data.size() - 1)
							outputTemp += ",";
					}
					//�N��X�榡�s�J�Ȧs�A�åB����
					outputTemp += "]" + Environment::NewLine;
					//��X�Ȧs��T 
					Output->Text += gcnew String(vectors[i].Name.c_str()) +" = "+ outputTemp;
					break;
				}
			}
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
			//�N�B�z�����r��̪ťէ@����
			array<String^> ^postfixFormula = postfix->Split(' ');
			
			Vector ans, Va, Vb;
			std::stack<Vector> calStack;
			bool dimFlag, foundFlag;
			for (int i = 0; i < postfixFormula->Length; i++)
			{
				dimFlag = 0;
				foundFlag = 0;
				Va = Vector();
				Vb = Vector();
				if (postfixFormula[i] == "+" || postfixFormula[i] == "-" || postfixFormula[i] == "*")
				{
					std::string temp;
					double scalar;
					//find vector that need to calculate
					//�z�Lfor�j��A�q�V�q��Ƥ���X�����ܼ�
					for (unsigned int j = 0; j < vectors.size(); j++)
					{
						System::String^ Temp = postfixFormula[i - 2];
						temp = msclr::interop::marshal_as<std::string>(Temp);
						if (temp[0] != '$')
						{
							scalar = strtod(temp.c_str(), NULL);
							break;
						}
						//�Y�ܼƦW�ٻP���O�ܼƦW�ٲŦX
						if (postfixFormula[i - 2] == gcnew String(vectors[j].Name.c_str()))
						{
							Va = vectors[j];
							break;
						}
						
					}

					for (unsigned int k = 0; k < vectors.size(); k++)
					{
						System::String^ Temp = postfixFormula[i - 1];
						temp = msclr::interop::marshal_as<std::string>(Temp);
						if (temp[0] != '$')
						{
							scalar = strtod(temp.c_str(), NULL);
							break;
						}
						//�Y�ܼƦW�ٻP���O�ܼƦW�ٲŦX
						if (postfixFormula[i - 1] == gcnew String(vectors[k].Name.c_str()))
						{
							Vb = vectors[k];
							break;
						}
					}

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
							Output->Text += "Addition called" + Environment::NewLine; /*debug*/
							ans = Va + Vb;
						}
						else if (postfixFormula[i] == "-")
						{
							//call Subtraction
							Output->Text += "Subtraction called" + Environment::NewLine; /*debug*/
							ans = Va - Vb;
						}
						else if (postfixFormula[i] == "*")
						{
							//call dot
							Output->Text += "Dot called" + Environment::NewLine; /*debug*/
							ans = Va * Vb;
						}
						//push into calStack
						calStack.push(ans);
					}
					else
					{
						if (Va.Data.empty() || Vb.Data.empty())
						{
							dimFlag = 1;
							foundFlag = 1;
							//call scalar
							Output->Text += "Scalar called" + Environment::NewLine; /*debug*/
							if (Va.Data.empty())
								ans = scalar * Vb;
							else ans = scalar * Va;
							//push into calStack
							calStack.push(ans);
						}
						break;
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
				//�N��X�榡�s�J�Ȧs
				outputTemp += "[";
				//�N��X��Ʀs�J�Ȧs
				ans = calStack.top();
				calStack.pop();
				for (unsigned int j = 0; j < ans.Data.size(); j++)
				{
					outputTemp += ans.Data[j].ToString();
					if (j != ans.Data.size() - 1)
						outputTemp += ",";
				}
				//�N��X�榡�s�J�Ȧs�A�åB����
				outputTemp += "]" + Environment::NewLine;
				//��X�Ȧs��T 
				Output->Text += gcnew String("formula = " + outputTemp);
			}
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
		userInput = userCommand[userCommand->Length-1];
	}

}
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) 
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
			for (unsigned int j = 0; j<vectors[i].Data.size(); j++)
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
};
}

