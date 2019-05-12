#pragma once
//#define DEBUG
#include "DataManager.h"
#include "DotNetUtilities.h"

namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			dataManager = new DataManager();
			lastInputLength = -1;
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

		DataManager* dataManager;
		String^ userInput;
		int lastInputLength;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  loadFileToolStripMenuItem;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  Input;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TextBox^  Variable;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::TextBox^  Output;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->loadFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Input = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->Variable = (gcnew System::Windows::Forms::TextBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->Output = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadFileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(818, 27);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// loadFileToolStripMenuItem
			// 
			this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
			this->loadFileToolStripMenuItem->Size = System::Drawing::Size(84, 23);
			this->loadFileToolStripMenuItem->Text = L"Load File";
			this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadFileToolStripMenuItem_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->groupBox1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->groupBox2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->groupBox3, 0, 2);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 27);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 60)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(818, 685);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// groupBox1
			// 
			this->groupBox1->AutoSize = true;
			this->groupBox1->Controls->Add(this->Input);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox1->Location = System::Drawing::Point(3, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(812, 131);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Input";
			// 
			// Input
			// 
			this->Input->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Input->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Input->Location = System::Drawing::Point(3, 23);
			this->Input->Multiline = true;
			this->Input->Name = L"Input";
			this->Input->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->Input->Size = System::Drawing::Size(806, 105);
			this->Input->TabIndex = 0;
			// 
			// groupBox2
			// 
			this->groupBox2->AutoSize = true;
			this->groupBox2->Controls->Add(this->Variable);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox2->Location = System::Drawing::Point(3, 140);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(812, 131);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Variable";
			// 
			// Variable
			// 
			this->Variable->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Variable->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Variable->Location = System::Drawing::Point(3, 23);
			this->Variable->Multiline = true;
			this->Variable->Name = L"Variable";
			this->Variable->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->Variable->Size = System::Drawing::Size(806, 105);
			this->Variable->TabIndex = 1;
			this->Variable->Text = L"initialPoint [name] [value]\r\ninterval [name] [beginValue] [endValue] \r\n";
			// 
			// groupBox3
			// 
			this->groupBox3->AutoSize = true;
			this->groupBox3->Controls->Add(this->Output);
			this->groupBox3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox3->Location = System::Drawing::Point(3, 277);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(812, 405);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Output";
			// 
			// Output
			// 
			this->Output->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Output->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9));
			this->Output->Location = System::Drawing::Point(3, 23);
			this->Output->Multiline = true;
			this->Output->Name = L"Output";
			this->Output->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->Output->Size = System::Drawing::Size(806, 379);
			this->Output->TabIndex = 2;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(818, 712);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Project2";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void loadFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);

};

	//
	// function
	//
	int priority(String^ op);
	int priority(std::string op);
	Generic::List<String^> ^inToPostfix(array<String^>^ formulaList);
	Generic::List<String^> ^CmdProcess(array<String^>^ CmdList);
}
