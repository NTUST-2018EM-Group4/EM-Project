#pragma once
//#define DEBUG
#include "DataManager.h"
#include "DotNetUtilities.h"
#include "Equation.h"


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
			 System::Windows::Forms::ToolStripMenuItem^  loadFileToolStripMenuItem;
			 System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
			 System::Windows::Forms::GroupBox^  groupBox2;
			 System::Windows::Forms::OpenFileDialog^  openFileDialog1;
			 System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
			 System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
			 System::Windows::Forms::RadioButton^  Powell;
			 System::Windows::Forms::RadioButton^  Newton;
			 System::Windows::Forms::RadioButton^  Step;
			 System::Windows::Forms::RadioButton^  Quasi;
			 System::Windows::Forms::RadioButton^  Conjuate;
			 System::Windows::Forms::GroupBox^  groupBox4;
			 System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
			 System::Windows::Forms::Label^  label1;
			 System::Windows::Forms::GroupBox^  groupBox6;
			 System::Windows::Forms::Label^  label2;
			 System::Windows::Forms::GroupBox^  groupBox5;
			 System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
			 System::Windows::Forms::Label^  label4;
			 System::Windows::Forms::Label^  label5;
			 System::Windows::Forms::Label^  label6;
			 System::Windows::Forms::TextBox^  yInitial;
			 System::Windows::Forms::TextBox^  yBegin;
			 System::Windows::Forms::TextBox^  yEnd;
			 System::Windows::Forms::Label^  label3;
			 System::Windows::Forms::TextBox^  xInitial;
			 System::Windows::Forms::TextBox^  xBegin;
			 System::Windows::Forms::TextBox^  xEnd;
			 System::Windows::Forms::GroupBox^  groupBox1;
			 System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
			 System::Windows::Forms::Button^  EnterBtn;
			 System::Windows::Forms::ComboBox^  Input;
			 System::Windows::Forms::GroupBox^  groupBox3;
			 System::Windows::Forms::TextBox^  Output;
			 System::Windows::Forms::ToolStripMenuItem^  clearOutputToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  resetXToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  resetYToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  outputResultToolStripMenuItem;

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
			this->clearOutputToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetXToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetYToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->EnterBtn = (gcnew System::Windows::Forms::Button());
			this->Input = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->Output = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->yInitial = (gcnew System::Windows::Forms::TextBox());
			this->yBegin = (gcnew System::Windows::Forms::TextBox());
			this->yEnd = (gcnew System::Windows::Forms::TextBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->xInitial = (gcnew System::Windows::Forms::TextBox());
			this->xBegin = (gcnew System::Windows::Forms::TextBox());
			this->xEnd = (gcnew System::Windows::Forms::TextBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->Powell = (gcnew System::Windows::Forms::RadioButton());
			this->Newton = (gcnew System::Windows::Forms::RadioButton());
			this->Step = (gcnew System::Windows::Forms::RadioButton());
			this->Quasi = (gcnew System::Windows::Forms::RadioButton());
			this->Conjuate = (gcnew System::Windows::Forms::RadioButton());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->outputResultToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->loadFileToolStripMenuItem,
					this->clearOutputToolStripMenuItem, this->resetXToolStripMenuItem, this->resetYToolStripMenuItem, this->outputResultToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(928, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// loadFileToolStripMenuItem
			// 
			this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
			this->loadFileToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->loadFileToolStripMenuItem->Size = System::Drawing::Size(84, 23);
			this->loadFileToolStripMenuItem->Text = L"Load File";
			this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadFileToolStripMenuItem_Click);
			// 
			// clearOutputToolStripMenuItem
			// 
			this->clearOutputToolStripMenuItem->Name = L"clearOutputToolStripMenuItem";
			this->clearOutputToolStripMenuItem->Size = System::Drawing::Size(110, 23);
			this->clearOutputToolStripMenuItem->Text = L"Clear Output";
			this->clearOutputToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::clearOutputToolStripMenuItem_Click);
			// 
			// resetXToolStripMenuItem
			// 
			this->resetXToolStripMenuItem->Name = L"resetXToolStripMenuItem";
			this->resetXToolStripMenuItem->Size = System::Drawing::Size(73, 23);
			this->resetXToolStripMenuItem->Text = L"Reset X";
			this->resetXToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::resetXToolStripMenuItem_Click);
			// 
			// resetYToolStripMenuItem
			// 
			this->resetYToolStripMenuItem->Name = L"resetYToolStripMenuItem";
			this->resetYToolStripMenuItem->Size = System::Drawing::Size(72, 23);
			this->resetYToolStripMenuItem->Text = L"Reset Y";
			this->resetYToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::resetYToolStripMenuItem_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->groupBox1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->groupBox3, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->groupBox2, 0, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 28);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 70)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(928, 684);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// groupBox1
			// 
			this->groupBox1->AutoSize = true;
			this->groupBox1->Controls->Add(this->tableLayoutPanel5);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox1->Location = System::Drawing::Point(3, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(922, 62);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Input";
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 2;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				90)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel5->Controls->Add(this->EnterBtn, 1, 0);
			this->tableLayoutPanel5->Controls->Add(this->Input, 0, 0);
			this->tableLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel5->Location = System::Drawing::Point(3, 23);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 1;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(916, 36);
			this->tableLayoutPanel5->TabIndex = 0;
			// 
			// EnterBtn
			// 
			this->EnterBtn->Dock = System::Windows::Forms::DockStyle::Top;
			this->EnterBtn->Location = System::Drawing::Point(827, 3);
			this->EnterBtn->Name = L"EnterBtn";
			this->EnterBtn->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->EnterBtn->Size = System::Drawing::Size(86, 27);
			this->EnterBtn->TabIndex = 1;
			this->EnterBtn->Text = L"Enter";
			this->EnterBtn->UseVisualStyleBackColor = true;
			this->EnterBtn->Click += gcnew System::EventHandler(this, &MyForm::EnterBtn_Click);
			// 
			// Input
			// 
			this->Input->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Input->FormattingEnabled = true;
			this->Input->Location = System::Drawing::Point(3, 3);
			this->Input->Name = L"Input";
			this->Input->Size = System::Drawing::Size(818, 27);
			this->Input->TabIndex = 2;
			// 
			// groupBox3
			// 
			this->groupBox3->AutoSize = true;
			this->groupBox3->Controls->Add(this->Output);
			this->groupBox3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox3->Location = System::Drawing::Point(3, 207);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(922, 474);
			this->groupBox3->TabIndex = 3;
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
			this->Output->Size = System::Drawing::Size(916, 448);
			this->Output->TabIndex = 2;
			// 
			// groupBox2
			// 
			this->groupBox2->AutoSize = true;
			this->groupBox2->Controls->Add(this->tableLayoutPanel2);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox2->Location = System::Drawing::Point(3, 71);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(922, 130);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Setting";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 3;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				30)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				30)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40)));
			this->tableLayoutPanel2->Controls->Add(this->groupBox5, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->groupBox4, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->groupBox6, 2, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 23);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(916, 104);
			this->tableLayoutPanel2->TabIndex = 0;
			// 
			// groupBox5
			// 
			this->groupBox5->AutoSize = true;
			this->groupBox5->Controls->Add(this->tableLayoutPanel4);
			this->groupBox5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox5->Location = System::Drawing::Point(277, 3);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(268, 98);
			this->groupBox5->TabIndex = 3;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Y side";
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 4;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel4->Controls->Add(this->label4, 2, 1);
			this->tableLayoutPanel4->Controls->Add(this->label5, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->label6, 0, 1);
			this->tableLayoutPanel4->Controls->Add(this->yInitial, 1, 0);
			this->tableLayoutPanel4->Controls->Add(this->yBegin, 1, 1);
			this->tableLayoutPanel4->Controls->Add(this->yEnd, 3, 1);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 23);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 2;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(262, 72);
			this->tableLayoutPanel4->TabIndex = 0;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label4->Location = System::Drawing::Point(172, 36);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(20, 36);
			this->label4->TabIndex = 6;
			this->label4->Text = L"~";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label5->Location = System::Drawing::Point(3, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(98, 36);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Initial";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label6->Location = System::Drawing::Point(3, 36);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(98, 36);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Interval";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// yInitial
			// 
			this->tableLayoutPanel4->SetColumnSpan(this->yInitial, 3);
			this->yInitial->Dock = System::Windows::Forms::DockStyle::Fill;
			this->yInitial->Location = System::Drawing::Point(107, 3);
			this->yInitial->Name = L"yInitial";
			this->yInitial->Size = System::Drawing::Size(152, 27);
			this->yInitial->TabIndex = 3;
			this->yInitial->Text = L"NULL";
			// 
			// yBegin
			// 
			this->yBegin->Dock = System::Windows::Forms::DockStyle::Fill;
			this->yBegin->Location = System::Drawing::Point(107, 39);
			this->yBegin->Name = L"yBegin";
			this->yBegin->Size = System::Drawing::Size(59, 27);
			this->yBegin->TabIndex = 4;
			this->yBegin->Text = L"0";
			// 
			// yEnd
			// 
			this->yEnd->Dock = System::Windows::Forms::DockStyle::Fill;
			this->yEnd->Location = System::Drawing::Point(198, 39);
			this->yEnd->Name = L"yEnd";
			this->yEnd->Size = System::Drawing::Size(61, 27);
			this->yEnd->TabIndex = 5;
			this->yEnd->Text = L"0";
			// 
			// groupBox4
			// 
			this->groupBox4->AutoSize = true;
			this->groupBox4->Controls->Add(this->tableLayoutPanel3);
			this->groupBox4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox4->Location = System::Drawing::Point(3, 3);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(268, 98);
			this->groupBox4->TabIndex = 0;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"X side";
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 4;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel3->Controls->Add(this->label3, 2, 1);
			this->tableLayoutPanel3->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->label2, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->xInitial, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->xBegin, 1, 1);
			this->tableLayoutPanel3->Controls->Add(this->xEnd, 3, 1);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 23);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 2;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(262, 72);
			this->tableLayoutPanel3->TabIndex = 0;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label3->Location = System::Drawing::Point(172, 36);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(20, 36);
			this->label3->TabIndex = 6;
			this->label3->Text = L"~";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(98, 36);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Initial";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Location = System::Drawing::Point(3, 36);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(98, 36);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Interval";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// xInitial
			// 
			this->tableLayoutPanel3->SetColumnSpan(this->xInitial, 3);
			this->xInitial->Dock = System::Windows::Forms::DockStyle::Fill;
			this->xInitial->Location = System::Drawing::Point(107, 3);
			this->xInitial->Name = L"xInitial";
			this->xInitial->Size = System::Drawing::Size(152, 27);
			this->xInitial->TabIndex = 3;
			this->xInitial->Text = L"NULL";
			// 
			// xBegin
			// 
			this->xBegin->Dock = System::Windows::Forms::DockStyle::Fill;
			this->xBegin->Location = System::Drawing::Point(107, 39);
			this->xBegin->Name = L"xBegin";
			this->xBegin->Size = System::Drawing::Size(59, 27);
			this->xBegin->TabIndex = 4;
			this->xBegin->Text = L"0";
			// 
			// xEnd
			// 
			this->xEnd->Dock = System::Windows::Forms::DockStyle::Fill;
			this->xEnd->Location = System::Drawing::Point(198, 39);
			this->xEnd->Name = L"xEnd";
			this->xEnd->Size = System::Drawing::Size(61, 27);
			this->xEnd->TabIndex = 5;
			this->xEnd->Text = L"0";
			// 
			// groupBox6
			// 
			this->groupBox6->AutoSize = true;
			this->groupBox6->Controls->Add(this->flowLayoutPanel1);
			this->groupBox6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox6->Location = System::Drawing::Point(551, 3);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(362, 98);
			this->groupBox6->TabIndex = 2;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Method";
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->AutoSize = true;
			this->flowLayoutPanel1->Controls->Add(this->Powell);
			this->flowLayoutPanel1->Controls->Add(this->Newton);
			this->flowLayoutPanel1->Controls->Add(this->Step);
			this->flowLayoutPanel1->Controls->Add(this->Quasi);
			this->flowLayoutPanel1->Controls->Add(this->Conjuate);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(3, 23);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Padding = System::Windows::Forms::Padding(2);
			this->flowLayoutPanel1->Size = System::Drawing::Size(356, 72);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// Powell
			// 
			this->Powell->AutoSize = true;
			this->Powell->Checked = true;
			this->Powell->Location = System::Drawing::Point(5, 5);
			this->Powell->Name = L"Powell";
			this->Powell->Size = System::Drawing::Size(78, 23);
			this->Powell->TabIndex = 0;
			this->Powell->TabStop = true;
			this->Powell->Text = L"Powell";
			this->Powell->UseVisualStyleBackColor = true;
			// 
			// Newton
			// 
			this->Newton->AutoSize = true;
			this->Newton->Location = System::Drawing::Point(89, 5);
			this->Newton->Name = L"Newton";
			this->Newton->Size = System::Drawing::Size(88, 23);
			this->Newton->TabIndex = 1;
			this->Newton->Text = L"Newton";
			this->Newton->UseVisualStyleBackColor = true;
			// 
			// Step
			// 
			this->Step->AutoSize = true;
			this->Step->Location = System::Drawing::Point(183, 5);
			this->Step->Name = L"Step";
			this->Step->Size = System::Drawing::Size(137, 23);
			this->Step->TabIndex = 2;
			this->Step->Text = L"Steep Descent";
			this->Step->UseVisualStyleBackColor = true;
			// 
			// Quasi
			// 
			this->Quasi->AutoSize = true;
			this->Quasi->Location = System::Drawing::Point(5, 34);
			this->Quasi->Name = L"Quasi";
			this->Quasi->Size = System::Drawing::Size(135, 23);
			this->Quasi->TabIndex = 3;
			this->Quasi->Text = L"Quasi-Newton";
			this->Quasi->UseVisualStyleBackColor = true;
			// 
			// Conjuate
			// 
			this->Conjuate->AutoSize = true;
			this->Conjuate->Location = System::Drawing::Point(146, 34);
			this->Conjuate->Name = L"Conjuate";
			this->Conjuate->Size = System::Drawing::Size(162, 23);
			this->Conjuate->TabIndex = 4;
			this->Conjuate->Text = L"Conjuate Gradient";
			this->Conjuate->UseVisualStyleBackColor = true;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// outputResultToolStripMenuItem
			// 
			this->outputResultToolStripMenuItem->Name = L"outputResultToolStripMenuItem";
			this->outputResultToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->outputResultToolStripMenuItem->Size = System::Drawing::Size(117, 24);
			this->outputResultToolStripMenuItem->Text = L"Output Result";
			this->outputResultToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::outputResultToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(928, 712);
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
			this->tableLayoutPanel5->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void loadFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
			 System::Void EnterBtn_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void clearOutputToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void resetXToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void resetYToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void outputResultToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
};
}
