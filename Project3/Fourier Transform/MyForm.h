#pragma once
#include <iostream>
#include "DataManager.h"
#include "FT.h"

namespace FourierTransform {

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
			fourierTransformMethod = new FT();
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
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
			 System::Windows::Forms::MenuStrip^  menuStrip1;

			 System::Windows::Forms::OpenFileDialog^  openFileDialog1;

			 System::Windows::Forms::GroupBox^  groupBox1;
			 System::Windows::Forms::GroupBox^  groupBox2;
			 System::Windows::Forms::GroupBox^  groupBox3;
			 System::Windows::Forms::GroupBox^  groupBox4;
			 System::Windows::Forms::GroupBox^  groupBox5;
			 System::Windows::Forms::GroupBox^  groupBox6;
			 System::Windows::Forms::GroupBox^  groupBox7;
			 System::Windows::Forms::GroupBox^  groupBox8;

			 System::Windows::Forms::PictureBox^  pictureBox_SourceImage;
			 System::Windows::Forms::PictureBox^  pictureBox_OutputImage;
			 System::Windows::Forms::PictureBox^  pictureBox_FFT;
			 System::Windows::Forms::PictureBox^  pictureBox_IFFT;
			 System::Windows::Forms::PictureBox^  pictureBox_Lowpass;
			 System::Windows::Forms::PictureBox^  pictureBox_InvLowpass;
			 System::Windows::Forms::PictureBox^  pictureBox_Highpass;
			 System::Windows::Forms::PictureBox^  pictureBox_InvHighpass;

			 System::Windows::Forms::ToolStripMenuItem^  loadFileToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  setResultAsInputToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  fastFourierTransformToolStripMenuItem1;
			 System::Windows::Forms::ToolStripMenuItem^  inverseFastFourierTransformToolStripMenuItem1;
			 System::Windows::Forms::ToolStripMenuItem^  lowpassFilterToolStripMenuItem1;
			 System::Windows::Forms::ToolStripMenuItem^  highpassFilterToolStripMenuItem1;
			 System::Windows::Forms::ToolStripMenuItem^  discreteFTToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  inverseDiscreteFTToolStripMenuItem;

	private:
		/// <summary>
		/// </summary>
		DataManager* dataManager;
		FT*	fourierTransformMethod;

	private: System::Windows::Forms::ToolStripMenuItem^  clickHereToolStripMenuItem;

		
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox_Lowpass = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox_InvLowpass = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox_OutputImage = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox_SourceImage = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox_FFT = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox_IFFT = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox_Highpass = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox_InvHighpass = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->loadFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->setResultAsInputToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fastFourierTransformToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->inverseFastFourierTransformToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lowpassFilterToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->highpassFilterToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->discreteFTToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->inverseDiscreteFTToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clickHereToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tableLayoutPanel1->SuspendLayout();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Lowpass))->BeginInit();
			this->groupBox6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_InvLowpass))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_OutputImage))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_SourceImage))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_FFT))->BeginInit();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_IFFT))->BeginInit();
			this->groupBox7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Highpass))->BeginInit();
			this->groupBox8->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_InvHighpass))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->tableLayoutPanel1->ColumnCount = 4;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->Controls->Add(this->groupBox5, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->groupBox6, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->groupBox2, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->groupBox1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->groupBox3, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->groupBox4, 3, 1);
			this->tableLayoutPanel1->Controls->Add(this->groupBox7, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->groupBox8, 3, 2);
			this->tableLayoutPanel1->Controls->Add(this->menuStrip1, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(2);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1179, 644);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// groupBox5
			// 
			this->groupBox5->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->groupBox5->AutoSize = true;
			this->groupBox5->Controls->Add(this->pictureBox_Lowpass);
			this->groupBox5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox5->Location = System::Drawing::Point(3, 337);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(288, 304);
			this->groupBox5->TabIndex = 9;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Lowpass Filter Image";
			// 
			// pictureBox_Lowpass
			// 
			this->pictureBox_Lowpass->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->pictureBox_Lowpass->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox_Lowpass->Location = System::Drawing::Point(3, 19);
			this->pictureBox_Lowpass->Name = L"pictureBox_Lowpass";
			this->pictureBox_Lowpass->Size = System::Drawing::Size(282, 282);
			this->pictureBox_Lowpass->TabIndex = 4;
			this->pictureBox_Lowpass->TabStop = false;
			// 
			// groupBox6
			// 
			this->groupBox6->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->groupBox6->AutoSize = true;
			this->groupBox6->Controls->Add(this->pictureBox_InvLowpass);
			this->groupBox6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox6->Location = System::Drawing::Point(297, 337);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(288, 304);
			this->groupBox6->TabIndex = 8;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Inverse Lowpass Filter Image";
			// 
			// pictureBox_InvLowpass
			// 
			this->pictureBox_InvLowpass->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->pictureBox_InvLowpass->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox_InvLowpass->Location = System::Drawing::Point(3, 19);
			this->pictureBox_InvLowpass->Name = L"pictureBox_InvLowpass";
			this->pictureBox_InvLowpass->Size = System::Drawing::Size(282, 282);
			this->pictureBox_InvLowpass->TabIndex = 4;
			this->pictureBox_InvLowpass->TabStop = false;
			// 
			// groupBox2
			// 
			this->groupBox2->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->groupBox2->AutoSize = true;
			this->groupBox2->Controls->Add(this->pictureBox_OutputImage);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Location = System::Drawing::Point(297, 27);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(288, 304);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Result Image";
			// 
			// pictureBox_OutputImage
			// 
			this->pictureBox_OutputImage->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->pictureBox_OutputImage->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox_OutputImage->Location = System::Drawing::Point(3, 19);
			this->pictureBox_OutputImage->Name = L"pictureBox_OutputImage";
			this->pictureBox_OutputImage->Size = System::Drawing::Size(282, 282);
			this->pictureBox_OutputImage->TabIndex = 3;
			this->pictureBox_OutputImage->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->groupBox1->AutoSize = true;
			this->groupBox1->Controls->Add(this->pictureBox_SourceImage);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->Location = System::Drawing::Point(3, 27);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(288, 304);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Source Image";
			// 
			// pictureBox_SourceImage
			// 
			this->pictureBox_SourceImage->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->pictureBox_SourceImage->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox_SourceImage->Location = System::Drawing::Point(3, 19);
			this->pictureBox_SourceImage->Name = L"pictureBox_SourceImage";
			this->pictureBox_SourceImage->Size = System::Drawing::Size(282, 282);
			this->pictureBox_SourceImage->TabIndex = 2;
			this->pictureBox_SourceImage->TabStop = false;
			// 
			// groupBox3
			// 
			this->groupBox3->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->groupBox3->AutoSize = true;
			this->groupBox3->Controls->Add(this->pictureBox_FFT);
			this->groupBox3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox3->Location = System::Drawing::Point(591, 27);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(288, 304);
			this->groupBox3->TabIndex = 6;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"FFT Image";
			// 
			// pictureBox_FFT
			// 
			this->pictureBox_FFT->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->pictureBox_FFT->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox_FFT->Location = System::Drawing::Point(3, 19);
			this->pictureBox_FFT->Name = L"pictureBox_FFT";
			this->pictureBox_FFT->Size = System::Drawing::Size(282, 282);
			this->pictureBox_FFT->TabIndex = 3;
			this->pictureBox_FFT->TabStop = false;
			// 
			// groupBox4
			// 
			this->groupBox4->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->groupBox4->AutoSize = true;
			this->groupBox4->Controls->Add(this->pictureBox_IFFT);
			this->groupBox4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox4->Location = System::Drawing::Point(885, 27);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(291, 304);
			this->groupBox4->TabIndex = 7;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Inverse FFT Image";
			// 
			// pictureBox_IFFT
			// 
			this->pictureBox_IFFT->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->pictureBox_IFFT->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox_IFFT->Location = System::Drawing::Point(3, 19);
			this->pictureBox_IFFT->Name = L"pictureBox_IFFT";
			this->pictureBox_IFFT->Size = System::Drawing::Size(285, 282);
			this->pictureBox_IFFT->TabIndex = 3;
			this->pictureBox_IFFT->TabStop = false;
			// 
			// groupBox7
			// 
			this->groupBox7->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->groupBox7->Controls->Add(this->pictureBox_Highpass);
			this->groupBox7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox7->Location = System::Drawing::Point(591, 337);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(288, 304);
			this->groupBox7->TabIndex = 6;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Highpass Filter Image";
			// 
			// pictureBox_Highpass
			// 
			this->pictureBox_Highpass->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->pictureBox_Highpass->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox_Highpass->Location = System::Drawing::Point(3, 19);
			this->pictureBox_Highpass->Name = L"pictureBox_Highpass";
			this->pictureBox_Highpass->Size = System::Drawing::Size(282, 282);
			this->pictureBox_Highpass->TabIndex = 3;
			this->pictureBox_Highpass->TabStop = false;
			// 
			// groupBox8
			// 
			this->groupBox8->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->groupBox8->AutoSize = true;
			this->groupBox8->Controls->Add(this->pictureBox_InvHighpass);
			this->groupBox8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox8->Location = System::Drawing::Point(885, 337);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(291, 304);
			this->groupBox8->TabIndex = 10;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"Inverse Highpass Filter Image";
			// 
			// pictureBox_InvHighpass
			// 
			this->pictureBox_InvHighpass->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->pictureBox_InvHighpass->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox_InvHighpass->Location = System::Drawing::Point(3, 19);
			this->pictureBox_InvHighpass->Name = L"pictureBox_InvHighpass";
			this->pictureBox_InvHighpass->Size = System::Drawing::Size(285, 282);
			this->pictureBox_InvHighpass->TabIndex = 3;
			this->pictureBox_InvHighpass->TabStop = false;
			// 
			// menuStrip1
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->menuStrip1, 4);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->loadFileToolStripMenuItem,
					this->setResultAsInputToolStripMenuItem, this->fastFourierTransformToolStripMenuItem1, this->inverseFastFourierTransformToolStripMenuItem1,
					this->lowpassFilterToolStripMenuItem1, this->highpassFilterToolStripMenuItem1, this->discreteFTToolStripMenuItem, this->inverseDiscreteFTToolStripMenuItem,
					this->clickHereToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1179, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// loadFileToolStripMenuItem
			// 
			this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
			this->loadFileToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::L));
			this->loadFileToolStripMenuItem->Size = System::Drawing::Size(70, 20);
			this->loadFileToolStripMenuItem->Text = L"Load File";
			this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadFileToolStripMenuItem_Click);
			// 
			// setResultAsInputToolStripMenuItem
			// 
			this->setResultAsInputToolStripMenuItem->Name = L"setResultAsInputToolStripMenuItem";
			this->setResultAsInputToolStripMenuItem->Size = System::Drawing::Size(132, 20);
			this->setResultAsInputToolStripMenuItem->Text = L"Set Result As Source";
			this->setResultAsInputToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::setResultAsInputToolStripMenuItem_Click);
			// 
			// fastFourierTransformToolStripMenuItem1
			// 
			this->fastFourierTransformToolStripMenuItem1->BackColor = System::Drawing::SystemColors::Info;
			this->fastFourierTransformToolStripMenuItem1->Name = L"fastFourierTransformToolStripMenuItem1";
			this->fastFourierTransformToolStripMenuItem1->Size = System::Drawing::Size(38, 20);
			this->fastFourierTransformToolStripMenuItem1->Text = L"FFT";
			this->fastFourierTransformToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::fastFourierTransformToolStripMenuItem1_Click);
			// 
			// inverseFastFourierTransformToolStripMenuItem1
			// 
			this->inverseFastFourierTransformToolStripMenuItem1->BackColor = System::Drawing::SystemColors::Info;
			this->inverseFastFourierTransformToolStripMenuItem1->Name = L"inverseFastFourierTransformToolStripMenuItem1";
			this->inverseFastFourierTransformToolStripMenuItem1->Size = System::Drawing::Size(80, 20);
			this->inverseFastFourierTransformToolStripMenuItem1->Text = L"Inverse FFT";
			this->inverseFastFourierTransformToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::inverseFastFourierTransformToolStripMenuItem1_Click);
			// 
			// lowpassFilterToolStripMenuItem1
			// 
			this->lowpassFilterToolStripMenuItem1->BackColor = System::Drawing::SystemColors::Info;
			this->lowpassFilterToolStripMenuItem1->Name = L"lowpassFilterToolStripMenuItem1";
			this->lowpassFilterToolStripMenuItem1->Size = System::Drawing::Size(97, 20);
			this->lowpassFilterToolStripMenuItem1->Text = L"Lowpass Filter";
			this->lowpassFilterToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::lowpassFilterToolStripMenuItem1_Click);
			// 
			// highpassFilterToolStripMenuItem1
			// 
			this->highpassFilterToolStripMenuItem1->BackColor = System::Drawing::SystemColors::Info;
			this->highpassFilterToolStripMenuItem1->Name = L"highpassFilterToolStripMenuItem1";
			this->highpassFilterToolStripMenuItem1->Size = System::Drawing::Size(101, 20);
			this->highpassFilterToolStripMenuItem1->Text = L"Highpass Filter";
			this->highpassFilterToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::highpassFilterToolStripMenuItem1_Click);
			// 
			// discreteFTToolStripMenuItem
			// 
			this->discreteFTToolStripMenuItem->Name = L"discreteFTToolStripMenuItem";
			this->discreteFTToolStripMenuItem->Size = System::Drawing::Size(80, 20);
			this->discreteFTToolStripMenuItem->Text = L"Discrete FT";
			this->discreteFTToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::discreteFTToolStripMenuItem_Click);
			// 
			// inverseDiscreteFTToolStripMenuItem
			// 
			this->inverseDiscreteFTToolStripMenuItem->Name = L"inverseDiscreteFTToolStripMenuItem";
			this->inverseDiscreteFTToolStripMenuItem->Size = System::Drawing::Size(122, 20);
			this->inverseDiscreteFTToolStripMenuItem->Text = L"Inverse Discrete FT";
			this->inverseDiscreteFTToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::inverseDiscreteFTToolStripMenuItem_Click);
			// 
			// clickHereToolStripMenuItem
			// 
			this->clickHereToolStripMenuItem->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->clickHereToolStripMenuItem->Name = L"clickHereToolStripMenuItem";
			this->clickHereToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F1;
			this->clickHereToolStripMenuItem->Size = System::Drawing::Size(79, 20);
			this->clickHereToolStripMenuItem->Text = L"Click Here!";
			this->clickHereToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::clickHereToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1179, 644);
			this->Controls->Add(this->tableLayoutPanel1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Fourier Transform";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Lowpass))->EndInit();
			this->groupBox6->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_InvLowpass))->EndInit();
			this->groupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_OutputImage))->EndInit();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_SourceImage))->EndInit();
			this->groupBox3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_FFT))->EndInit();
			this->groupBox4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_IFFT))->EndInit();
			this->groupBox7->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Highpass))->EndInit();
			this->groupBox8->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_InvHighpass))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
			 System::Void loadFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void setResultAsInputToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void fastFourierTransformToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void inverseFastFourierTransformToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void lowpassFilterToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void highpassFilterToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void discreteFTToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void inverseDiscreteFTToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void clickHereToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

			 Bitmap^ printToBox(DataManager& data);
};
}
