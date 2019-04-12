#pragma once
#define DEBUG
#include "DataManager.h"
#include "DotNetUtilities.h"

namespace WindowsFormsApplication_cpp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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

		/// <summary>
			DataManager* dataManager;
			String^ userInput;
			int lastInputLength;
	private: System::Windows::Forms::MenuStrip^  menuStrip2;
			 System::Windows::Forms::ToolStripMenuItem^  loadVectorToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  loadMatrixToolStripMenuItem;
			 System::Windows::Forms::OpenFileDialog^  openFileDialog1;
			 System::Windows::Forms::OpenFileDialog^  openFileDialog2;
			 System::Windows::Forms::GroupBox^  groupBox2;
			 System::Windows::Forms::TextBox^  Output;
			 System::Windows::Forms::GroupBox^  groupBox1;

			 System::Windows::Forms::ListBox^  VectorList;
			 System::Windows::Forms::ListBox^  MatrixList;
			 System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
			 System::Windows::Forms::GroupBox^  groupBox3;
			 System::Windows::Forms::GroupBox^  groupBox4;
			 System::Windows::Forms::ToolStripMenuItem^  clearInputToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  clearOutputToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  loadVectorToolStripMenuItem1;
			 System::Windows::Forms::ToolStripMenuItem^  calculateToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  loadMatrixToolStripMenuItem1;
			 System::Windows::Forms::ToolStripMenuItem^  calculateToolStripMenuItem1;
			 System::Windows::Forms::ToolStripMenuItem^  rankToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  transposeToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  solveLinearSystemToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  determinantToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  inverseToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  adjointToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  eigenValueVectorToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  powerMethodToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  leastSquareToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  normToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  normalToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  crossToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  componentToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  projectionToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  triangleAreaToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  parallelToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  orthogonalToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  angleToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  planeToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  linearIndependentToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  gramschmidtToolStripMenuItem;
			 System::Windows::Forms::ToolStripMenuItem^  printVectorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  printMatrixToolStripMenuItem;
	private: System::Windows::Forms::ComboBox^  Input;

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
			this->loadVectorToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->printVectorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->calculateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->normToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->normalToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->crossToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->componentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->projectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->triangleAreaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->parallelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->orthogonalToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->angleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->planeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->linearIndependentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gramschmidtToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadMatrixToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadMatrixToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->printMatrixToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->calculateToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rankToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->transposeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->solveLinearSystemToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->determinantToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->inverseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->adjointToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->eigenValueVectorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->powerMethodToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->leastSquareToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearInputToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearOutputToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->Output = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->VectorList = (gcnew System::Windows::Forms::ListBox());
			this->MatrixList = (gcnew System::Windows::Forms::ListBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->Input = (gcnew System::Windows::Forms::ComboBox());
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
			this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->loadVectorToolStripMenuItem,
					this->loadMatrixToolStripMenuItem, this->clearInputToolStripMenuItem, this->clearOutputToolStripMenuItem, this->helpToolStripMenuItem
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
			this->loadVectorToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(15) {
				this->loadVectorToolStripMenuItem1,
					this->printVectorToolStripMenuItem, this->calculateToolStripMenuItem, this->normToolStripMenuItem, this->normalToolStripMenuItem,
					this->crossToolStripMenuItem, this->componentToolStripMenuItem, this->projectionToolStripMenuItem, this->triangleAreaToolStripMenuItem,
					this->parallelToolStripMenuItem, this->orthogonalToolStripMenuItem, this->angleToolStripMenuItem, this->planeToolStripMenuItem,
					this->linearIndependentToolStripMenuItem, this->gramschmidtToolStripMenuItem
			});
			this->loadVectorToolStripMenuItem->Name = L"loadVectorToolStripMenuItem";
			this->loadVectorToolStripMenuItem->Size = System::Drawing::Size(66, 23);
			this->loadVectorToolStripMenuItem->Text = L"Vector";
			// 
			// loadVectorToolStripMenuItem1
			// 
			this->loadVectorToolStripMenuItem1->Name = L"loadVectorToolStripMenuItem1";
			this->loadVectorToolStripMenuItem1->Size = System::Drawing::Size(220, 26);
			this->loadVectorToolStripMenuItem1->Text = L"Load Vector";
			this->loadVectorToolStripMenuItem1->Click += gcnew System::EventHandler(this, &WindowsForm::loadVectorToolStripMenuItem1_Click);
			// 
			// printVectorToolStripMenuItem
			// 
			this->printVectorToolStripMenuItem->Name = L"printVectorToolStripMenuItem";
			this->printVectorToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->printVectorToolStripMenuItem->Text = L"Print Vector";
			this->printVectorToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::printVectorToolStripMenuItem_Click);
			// 
			// calculateToolStripMenuItem
			// 
			this->calculateToolStripMenuItem->Name = L"calculateToolStripMenuItem";
			this->calculateToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->calculateToolStripMenuItem->Text = L"Calculate";
			this->calculateToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::calculateToolStripMenuItem_Click);
			// 
			// normToolStripMenuItem
			// 
			this->normToolStripMenuItem->Name = L"normToolStripMenuItem";
			this->normToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->normToolStripMenuItem->Text = L"Norm";
			this->normToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::normToolStripMenuItem_Click);
			// 
			// normalToolStripMenuItem
			// 
			this->normalToolStripMenuItem->Name = L"normalToolStripMenuItem";
			this->normalToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->normalToolStripMenuItem->Text = L"Normalization";
			this->normalToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::normalToolStripMenuItem_Click);
			// 
			// crossToolStripMenuItem
			// 
			this->crossToolStripMenuItem->Name = L"crossToolStripMenuItem";
			this->crossToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->crossToolStripMenuItem->Text = L"Cross";
			this->crossToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::crossToolStripMenuItem_Click);
			// 
			// componentToolStripMenuItem
			// 
			this->componentToolStripMenuItem->Name = L"componentToolStripMenuItem";
			this->componentToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->componentToolStripMenuItem->Text = L"Component";
			this->componentToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::componentToolStripMenuItem_Click);
			// 
			// projectionToolStripMenuItem
			// 
			this->projectionToolStripMenuItem->Name = L"projectionToolStripMenuItem";
			this->projectionToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->projectionToolStripMenuItem->Text = L"Projection";
			this->projectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::projectionToolStripMenuItem_Click);
			// 
			// triangleAreaToolStripMenuItem
			// 
			this->triangleAreaToolStripMenuItem->Name = L"triangleAreaToolStripMenuItem";
			this->triangleAreaToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->triangleAreaToolStripMenuItem->Text = L"Triangle area";
			this->triangleAreaToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::triangleAreaToolStripMenuItem_Click);
			// 
			// parallelToolStripMenuItem
			// 
			this->parallelToolStripMenuItem->Name = L"parallelToolStripMenuItem";
			this->parallelToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->parallelToolStripMenuItem->Text = L"Parallel";
			this->parallelToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::parallelToolStripMenuItem_Click);
			// 
			// orthogonalToolStripMenuItem
			// 
			this->orthogonalToolStripMenuItem->Name = L"orthogonalToolStripMenuItem";
			this->orthogonalToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->orthogonalToolStripMenuItem->Text = L"Orthogonal";
			this->orthogonalToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::orthogonalToolStripMenuItem_Click);
			// 
			// angleToolStripMenuItem
			// 
			this->angleToolStripMenuItem->Name = L"angleToolStripMenuItem";
			this->angleToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->angleToolStripMenuItem->Text = L"Angle";
			this->angleToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::angleToolStripMenuItem_Click);
			// 
			// planeToolStripMenuItem
			// 
			this->planeToolStripMenuItem->Name = L"planeToolStripMenuItem";
			this->planeToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->planeToolStripMenuItem->Text = L"Plane Normal";
			this->planeToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::planeToolStripMenuItem_Click);
			// 
			// linearIndependentToolStripMenuItem
			// 
			this->linearIndependentToolStripMenuItem->Name = L"linearIndependentToolStripMenuItem";
			this->linearIndependentToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->linearIndependentToolStripMenuItem->Text = L"Linear independent";
			this->linearIndependentToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::linearIndependentToolStripMenuItem_Click);
			// 
			// gramschmidtToolStripMenuItem
			// 
			this->gramschmidtToolStripMenuItem->Name = L"gramschmidtToolStripMenuItem";
			this->gramschmidtToolStripMenuItem->Size = System::Drawing::Size(220, 26);
			this->gramschmidtToolStripMenuItem->Text = L"Gram-schmidt";
			this->gramschmidtToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::gramschmidtToolStripMenuItem_Click);
			// 
			// loadMatrixToolStripMenuItem
			// 
			this->loadMatrixToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(12) {
				this->loadMatrixToolStripMenuItem1,
					this->printMatrixToolStripMenuItem, this->calculateToolStripMenuItem1, this->rankToolStripMenuItem, this->transposeToolStripMenuItem,
					this->solveLinearSystemToolStripMenuItem, this->determinantToolStripMenuItem, this->inverseToolStripMenuItem, this->adjointToolStripMenuItem,
					this->eigenValueVectorToolStripMenuItem, this->powerMethodToolStripMenuItem, this->leastSquareToolStripMenuItem
			});
			this->loadMatrixToolStripMenuItem->Name = L"loadMatrixToolStripMenuItem";
			this->loadMatrixToolStripMenuItem->Size = System::Drawing::Size(65, 23);
			this->loadMatrixToolStripMenuItem->Text = L"Matrix";
			// 
			// loadMatrixToolStripMenuItem1
			// 
			this->loadMatrixToolStripMenuItem1->Name = L"loadMatrixToolStripMenuItem1";
			this->loadMatrixToolStripMenuItem1->Size = System::Drawing::Size(224, 26);
			this->loadMatrixToolStripMenuItem1->Text = L"Load Matrix";
			this->loadMatrixToolStripMenuItem1->Click += gcnew System::EventHandler(this, &WindowsForm::loadMatrixToolStripMenuItem1_Click);
			// 
			// printMatrixToolStripMenuItem
			// 
			this->printMatrixToolStripMenuItem->Name = L"printMatrixToolStripMenuItem";
			this->printMatrixToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->printMatrixToolStripMenuItem->Text = L"Print Matrix";
			this->printMatrixToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::printMatrixToolStripMenuItem_Click);
			// 
			// calculateToolStripMenuItem1
			// 
			this->calculateToolStripMenuItem1->Name = L"calculateToolStripMenuItem1";
			this->calculateToolStripMenuItem1->Size = System::Drawing::Size(224, 26);
			this->calculateToolStripMenuItem1->Text = L"Calculate";
			this->calculateToolStripMenuItem1->Click += gcnew System::EventHandler(this, &WindowsForm::calculateToolStripMenuItem1_Click);
			// 
			// rankToolStripMenuItem
			// 
			this->rankToolStripMenuItem->Name = L"rankToolStripMenuItem";
			this->rankToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->rankToolStripMenuItem->Text = L"Rank";
			this->rankToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::rankToolStripMenuItem_Click);
			// 
			// transposeToolStripMenuItem
			// 
			this->transposeToolStripMenuItem->Name = L"transposeToolStripMenuItem";
			this->transposeToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->transposeToolStripMenuItem->Text = L"Transpose";
			this->transposeToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::transposeToolStripMenuItem_Click);
			// 
			// solveLinearSystemToolStripMenuItem
			// 
			this->solveLinearSystemToolStripMenuItem->Name = L"solveLinearSystemToolStripMenuItem";
			this->solveLinearSystemToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->solveLinearSystemToolStripMenuItem->Text = L"Solve Linear System";
			this->solveLinearSystemToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::solveLinearSystemToolStripMenuItem_Click);
			// 
			// determinantToolStripMenuItem
			// 
			this->determinantToolStripMenuItem->Name = L"determinantToolStripMenuItem";
			this->determinantToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->determinantToolStripMenuItem->Text = L"Determinants";
			this->determinantToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::determinantToolStripMenuItem_Click);
			// 
			// inverseToolStripMenuItem
			// 
			this->inverseToolStripMenuItem->Name = L"inverseToolStripMenuItem";
			this->inverseToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->inverseToolStripMenuItem->Text = L"Inverse";
			this->inverseToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::inverseToolStripMenuItem_Click);
			// 
			// adjointToolStripMenuItem
			// 
			this->adjointToolStripMenuItem->Name = L"adjointToolStripMenuItem";
			this->adjointToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->adjointToolStripMenuItem->Text = L"Adjoint";
			this->adjointToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::adjointToolStripMenuItem_Click);
			// 
			// eigenValueVectorToolStripMenuItem
			// 
			this->eigenValueVectorToolStripMenuItem->Name = L"eigenValueVectorToolStripMenuItem";
			this->eigenValueVectorToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->eigenValueVectorToolStripMenuItem->Text = L"Eigen Value Vector";
			this->eigenValueVectorToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::eigenValueVectorToolStripMenuItem_Click);
			// 
			// powerMethodToolStripMenuItem
			// 
			this->powerMethodToolStripMenuItem->Name = L"powerMethodToolStripMenuItem";
			this->powerMethodToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->powerMethodToolStripMenuItem->Text = L"Power Method";
			this->powerMethodToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::powerMethodToolStripMenuItem_Click);
			// 
			// leastSquareToolStripMenuItem
			// 
			this->leastSquareToolStripMenuItem->Name = L"leastSquareToolStripMenuItem";
			this->leastSquareToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->leastSquareToolStripMenuItem->Text = L"Least Square";
			this->leastSquareToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::leastSquareToolStripMenuItem_Click);
			// 
			// clearInputToolStripMenuItem
			// 
			this->clearInputToolStripMenuItem->Name = L"clearInputToolStripMenuItem";
			this->clearInputToolStripMenuItem->Size = System::Drawing::Size(97, 23);
			this->clearInputToolStripMenuItem->Text = L"Clear Input";
			this->clearInputToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::clearInputToolStripMenuItem_Click);
			// 
			// clearOutputToolStripMenuItem
			// 
			this->clearOutputToolStripMenuItem->Name = L"clearOutputToolStripMenuItem";
			this->clearOutputToolStripMenuItem->Size = System::Drawing::Size(110, 23);
			this->clearOutputToolStripMenuItem->Text = L"Clear Output";
			this->clearOutputToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::clearOutputToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(53, 23);
			this->helpToolStripMenuItem->Text = L"Help";
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
			this->Output->ScrollBars = System::Windows::Forms::ScrollBars::Both;
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
			// VectorList
			// 
			this->VectorList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->VectorList->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->VectorList->FormattingEnabled = true;
			this->VectorList->HorizontalScrollbar = true;
			this->VectorList->ItemHeight = 19;
			this->VectorList->Location = System::Drawing::Point(3, 23);
			this->VectorList->Margin = System::Windows::Forms::Padding(4);
			this->VectorList->Name = L"VectorList";
			this->VectorList->Size = System::Drawing::Size(867, 124);
			this->VectorList->TabIndex = 3;
			this->VectorList->DoubleClick += gcnew System::EventHandler(this, &WindowsForm::VectorList_DoubleClick);
			// 
			// MatrixList
			// 
			this->MatrixList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->MatrixList->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->MatrixList->FormattingEnabled = true;
			this->MatrixList->HorizontalScrollbar = true;
			this->MatrixList->ItemHeight = 19;
			this->MatrixList->Location = System::Drawing::Point(3, 23);
			this->MatrixList->Margin = System::Windows::Forms::Padding(4);
			this->MatrixList->Name = L"MatrixList";
			this->MatrixList->Size = System::Drawing::Size(867, 125);
			this->MatrixList->TabIndex = 0;
			this->MatrixList->DoubleClick += gcnew System::EventHandler(this, &WindowsForm::MatrixList_DoubleClick);
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
			// Input
			// 
			this->Input->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Input->FormattingEnabled = true;
			this->Input->Location = System::Drawing::Point(3, 23);
			this->Input->Name = L"Input";
			this->Input->Size = System::Drawing::Size(867, 27);
			this->Input->TabIndex = 0;
			this->Input->TextChanged += gcnew System::EventHandler(this, &WindowsForm::Input_TextChanged);
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
			this->Text = L"Project1";
			this->Load += gcnew System::EventHandler(this, &WindowsForm::WindowsForm_Load);
			this->menuStrip2->ResumeLayout(false);
			this->menuStrip2->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		System::Void WindowsForm_Load(System::Object^  sender, System::EventArgs^  e) {}

		System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
		System::Void openFileDialog2_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);


		System::Void loadVectorToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void loadMatrixToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void clearInputToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void clearOutputToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void Input_TextChanged(System::Object^  sender, System::EventArgs^  e);

		System::Void VectorList_DoubleClick(System::Object^  sender, System::EventArgs^  e);
		System::Void MatrixList_DoubleClick(System::Object^  sender, System::EventArgs^  e);
		System::Void printVectorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void calculateToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void normToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void normalToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void crossToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void componentToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void projectionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void triangleAreaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void parallelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void orthogonalToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void angleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void planeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void linearIndependentToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void gramschmidtToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void printMatrixToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void calculateToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void rankToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void transposeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void solveLinearSystemToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void determinantToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void inverseToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void adjointToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void eigenValueVectorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void powerMethodToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void leastSquareToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

};

	//
	// function
	//
	int priority(String^ op);
	int priority(std::string op);
	String^ printVector(String^ s, const Vector& v);
	//int findVector(std::string name, const std::vector<Vector>& v);
	//int findMatrix(std::string name, const std::vector<Matrix>& m);
	Generic::List<String^> ^inToPostfix(array<String^>^ formulaList);
	Generic::List<String^> ^CmdProcess(array<String^>^ CmdList);
}
