#pragma once

#include "COLOR_FEATURES.h"
#include "GEOMETRIC.h"
#include "TAMURA_TEXTURE.h"
#include "MOTION.h"
#include "SHAPE_FEATURES.h"

#include <cmath>

namespace My1112010_1112017_1112122 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
#pragma region Declare
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	public:
		float compact1; float ti_so_truc1; float thon_dai1; 
		float chu_nhat1; float loi1;
	public:
		float compact2; float ti_so_truc2; float thon_dai2; 
		float chu_nhat2; float loi2;
	public:
		float Coarseness1, Contrast1, Directionality1;
		float Line_likeness1, Regularity1, Roughness1;
	public:
		float Coarseness2, Contrast2, Directionality2;
		float Line_likeness2, Regularity2, Roughness2;
	private:
		System::String^ File1;
		System::String^ File2;
		/// <summary>
		/// Required designer variable.
		/// </summary>
			 System::ComponentModel::Container ^components;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openImageMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  closeMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openPicDlg;
	private: System::Windows::Forms::ToolStripMenuItem^  openVideoMenuItem;
	private: System::Windows::Forms::TextBox^  txtBox_result;
	private: System::Windows::Forms::Label^  lbl_result;
	private: System::Windows::Forms::ToolStripMenuItem^  openImage2ToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  txtBox_result2;
	private: System::Windows::Forms::Label^  lbl_err;
	private: System::Windows::Forms::TextBox^  txtBox_err;
	private: System::Windows::Forms::Button^  btn_compute;
	private: System::Windows::Forms::RadioButton^  rd_Tamura;
	private: System::Windows::Forms::RadioButton^  rd_Geometry;


	private: System::Windows::Forms::RadioButton^  rd_histogram;
	private: System::Windows::Forms::RadioButton^  rd_coherence;
	private: System::Windows::Forms::RadioButton^  rd_meancolor;
	private: System::Windows::Forms::RadioButton^  rd_corrlogram;
	private: System::Windows::Forms::Label^  lbl_para1;
	private: System::Windows::Forms::TextBox^  txt_para1;
	private: System::Windows::Forms::TrackBar^  trb_para1;
	private: System::Windows::Forms::TrackBar^  trb_para2;
	private: System::Windows::Forms::TextBox^  txt_para2;
	private: System::Windows::Forms::Label^  lbl_para2;
	private: System::Windows::Forms::TrackBar^  trb_para3;
	private: System::Windows::Forms::TextBox^  txt_para3;
	private: System::Windows::Forms::Label^  lbl_para3;
	private: System::Windows::Forms::TrackBar^  trb_para4;
	private: System::Windows::Forms::TextBox^  txt_para4;
	private: System::Windows::Forms::Label^  lbl_para4;
	private: System::Windows::Forms::TrackBar^  trb_para5;
	private: System::Windows::Forms::TextBox^  txt_para5;
	private: System::Windows::Forms::Label^  lbl_para5;
	private: System::Windows::Forms::TrackBar^  trb_para6;
	private: System::Windows::Forms::TextBox^  txt_para6;
	private: System::Windows::Forms::Label^  lbl_para6;
	private: System::Windows::Forms::RadioButton^  rd_EdgeHistogram;
	private: System::Windows::Forms::RadioButton^  rd_Motion;
	private: System::Windows::Forms::RadioButton^  rd_MeanMotion;
	private: System::Windows::Forms::RadioButton^  rd_moment;
	private: System::Windows::Forms::RadioButton^  rd_motionHistogram;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::RadioButton^  rd_SIFT;
	private: System::Windows::Forms::RadioButton^  rd_directionCoherence;
	private: System::Windows::Forms::OpenFileDialog^  openVidDlg;
#pragma endregion
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openImageMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openImage2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openVideoMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openPicDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openVidDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->txtBox_result = (gcnew System::Windows::Forms::TextBox());
			this->lbl_result = (gcnew System::Windows::Forms::Label());
			this->txtBox_result2 = (gcnew System::Windows::Forms::TextBox());
			this->lbl_err = (gcnew System::Windows::Forms::Label());
			this->txtBox_err = (gcnew System::Windows::Forms::TextBox());
			this->btn_compute = (gcnew System::Windows::Forms::Button());
			this->rd_Tamura = (gcnew System::Windows::Forms::RadioButton());
			this->rd_Geometry = (gcnew System::Windows::Forms::RadioButton());
			this->rd_histogram = (gcnew System::Windows::Forms::RadioButton());
			this->rd_coherence = (gcnew System::Windows::Forms::RadioButton());
			this->rd_meancolor = (gcnew System::Windows::Forms::RadioButton());
			this->rd_corrlogram = (gcnew System::Windows::Forms::RadioButton());
			this->lbl_para1 = (gcnew System::Windows::Forms::Label());
			this->txt_para1 = (gcnew System::Windows::Forms::TextBox());
			this->trb_para1 = (gcnew System::Windows::Forms::TrackBar());
			this->trb_para2 = (gcnew System::Windows::Forms::TrackBar());
			this->txt_para2 = (gcnew System::Windows::Forms::TextBox());
			this->lbl_para2 = (gcnew System::Windows::Forms::Label());
			this->trb_para3 = (gcnew System::Windows::Forms::TrackBar());
			this->txt_para3 = (gcnew System::Windows::Forms::TextBox());
			this->lbl_para3 = (gcnew System::Windows::Forms::Label());
			this->trb_para4 = (gcnew System::Windows::Forms::TrackBar());
			this->txt_para4 = (gcnew System::Windows::Forms::TextBox());
			this->lbl_para4 = (gcnew System::Windows::Forms::Label());
			this->trb_para5 = (gcnew System::Windows::Forms::TrackBar());
			this->txt_para5 = (gcnew System::Windows::Forms::TextBox());
			this->lbl_para5 = (gcnew System::Windows::Forms::Label());
			this->trb_para6 = (gcnew System::Windows::Forms::TrackBar());
			this->txt_para6 = (gcnew System::Windows::Forms::TextBox());
			this->lbl_para6 = (gcnew System::Windows::Forms::Label());
			this->rd_EdgeHistogram = (gcnew System::Windows::Forms::RadioButton());
			this->rd_Motion = (gcnew System::Windows::Forms::RadioButton());
			this->rd_MeanMotion = (gcnew System::Windows::Forms::RadioButton());
			this->rd_moment = (gcnew System::Windows::Forms::RadioButton());
			this->rd_motionHistogram = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->rd_SIFT = (gcnew System::Windows::Forms::RadioButton());
			this->rd_directionCoherence = (gcnew System::Windows::Forms::RadioButton());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para6))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->fileMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(899, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileMenuItem
			// 
			this->fileMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->openImageMenuItem, 
				this->openImage2ToolStripMenuItem, this->openVideoMenuItem, this->closeMenuItem});
			this->fileMenuItem->Name = L"fileMenuItem";
			this->fileMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileMenuItem->Text = L"File";
			// 
			// openImageMenuItem
			// 
			this->openImageMenuItem->Name = L"openImageMenuItem";
			this->openImageMenuItem->Size = System::Drawing::Size(148, 22);
			this->openImageMenuItem->Text = L"Open Image 1";
			this->openImageMenuItem->Click += gcnew System::EventHandler(this, &Form1::openImageMenuItem_Click);
			// 
			// openImage2ToolStripMenuItem
			// 
			this->openImage2ToolStripMenuItem->Name = L"openImage2ToolStripMenuItem";
			this->openImage2ToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->openImage2ToolStripMenuItem->Text = L"Open Image 2";
			this->openImage2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openImage2ToolStripMenuItem_Click);
			// 
			// openVideoMenuItem
			// 
			this->openVideoMenuItem->Name = L"openVideoMenuItem";
			this->openVideoMenuItem->Size = System::Drawing::Size(148, 22);
			this->openVideoMenuItem->Text = L"Open Video";
			this->openVideoMenuItem->Click += gcnew System::EventHandler(this, &Form1::openVideoMenuItem_Click);
			// 
			// closeMenuItem
			// 
			this->closeMenuItem->Name = L"closeMenuItem";
			this->closeMenuItem->Size = System::Drawing::Size(148, 22);
			this->closeMenuItem->Text = L"Close";
			this->closeMenuItem->Click += gcnew System::EventHandler(this, &Form1::closeMenuItem_Click);
			// 
			// openPicDlg
			// 
			this->openPicDlg->Filter = L"\"image files (*.png, *.jpg, *.bmp)|*.png; *.jpg; *.bmp";
			// 
			// openVidDlg
			// 
			this->openVidDlg->Filter = L"\"video files (*.mp4, *.flv, *.avi *.mkv)|*.mp4; *.flv; *.avi; *.mkv";
			// 
			// txtBox_result
			// 
			this->txtBox_result->Location = System::Drawing::Point(64, 27);
			this->txtBox_result->Multiline = true;
			this->txtBox_result->Name = L"txtBox_result";
			this->txtBox_result->Size = System::Drawing::Size(200, 109);
			this->txtBox_result->TabIndex = 2;
			// 
			// lbl_result
			// 
			this->lbl_result->AutoSize = true;
			this->lbl_result->Location = System::Drawing::Point(12, 30);
			this->lbl_result->Name = L"lbl_result";
			this->lbl_result->Size = System::Drawing::Size(46, 13);
			this->lbl_result->TabIndex = 3;
			this->lbl_result->Text = L"Kết Quả";
			// 
			// txtBox_result2
			// 
			this->txtBox_result2->Location = System::Drawing::Point(270, 27);
			this->txtBox_result2->Multiline = true;
			this->txtBox_result2->Name = L"txtBox_result2";
			this->txtBox_result2->Size = System::Drawing::Size(200, 109);
			this->txtBox_result2->TabIndex = 4;
			// 
			// lbl_err
			// 
			this->lbl_err->AutoSize = true;
			this->lbl_err->Location = System::Drawing::Point(24, 148);
			this->lbl_err->Name = L"lbl_err";
			this->lbl_err->Size = System::Drawing::Size(34, 13);
			this->lbl_err->TabIndex = 5;
			this->lbl_err->Text = L"Độ lỗi";
			// 
			// txtBox_err
			// 
			this->txtBox_err->Location = System::Drawing::Point(55, 145);
			this->txtBox_err->Name = L"txtBox_err";
			this->txtBox_err->Size = System::Drawing::Size(287, 20);
			this->txtBox_err->TabIndex = 6;
			// 
			// btn_compute
			// 
			this->btn_compute->Location = System::Drawing::Point(348, 145);
			this->btn_compute->Name = L"btn_compute";
			this->btn_compute->Size = System::Drawing::Size(75, 20);
			this->btn_compute->TabIndex = 7;
			this->btn_compute->Text = L"Compute";
			this->btn_compute->UseVisualStyleBackColor = true;
			this->btn_compute->Click += gcnew System::EventHandler(this, &Form1::btn_compute_Click);
			// 
			// rd_Tamura
			// 
			this->rd_Tamura->AutoSize = true;
			this->rd_Tamura->Checked = true;
			this->rd_Tamura->Location = System::Drawing::Point(6, 19);
			this->rd_Tamura->Name = L"rd_Tamura";
			this->rd_Tamura->Size = System::Drawing::Size(100, 17);
			this->rd_Tamura->TabIndex = 8;
			this->rd_Tamura->TabStop = true;
			this->rd_Tamura->Text = L"Tamura Texture";
			this->rd_Tamura->UseVisualStyleBackColor = true;
			this->rd_Tamura->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_Tamura_CheckedChanged);
			// 
			// rd_Geometry
			// 
			this->rd_Geometry->AutoSize = true;
			this->rd_Geometry->Location = System::Drawing::Point(6, 65);
			this->rd_Geometry->Name = L"rd_Geometry";
			this->rd_Geometry->Size = System::Drawing::Size(70, 17);
			this->rd_Geometry->TabIndex = 9;
			this->rd_Geometry->Text = L"Geometry";
			this->rd_Geometry->UseVisualStyleBackColor = true;
			this->rd_Geometry->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_Geometry_CheckedChanged);
			// 
			// rd_histogram
			// 
			this->rd_histogram->AutoSize = true;
			this->rd_histogram->Location = System::Drawing::Point(6, 19);
			this->rd_histogram->Name = L"rd_histogram";
			this->rd_histogram->Size = System::Drawing::Size(99, 17);
			this->rd_histogram->TabIndex = 12;
			this->rd_histogram->Text = L"Color Histogram";
			this->rd_histogram->UseVisualStyleBackColor = true;
			this->rd_histogram->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_histogram_CheckedChanged);
			// 
			// rd_coherence
			// 
			this->rd_coherence->AutoSize = true;
			this->rd_coherence->Location = System::Drawing::Point(118, 42);
			this->rd_coherence->Name = L"rd_coherence";
			this->rd_coherence->Size = System::Drawing::Size(111, 17);
			this->rd_coherence->TabIndex = 13;
			this->rd_coherence->TabStop = true;
			this->rd_coherence->Text = L"Coherence Vector";
			this->rd_coherence->UseVisualStyleBackColor = true;
			this->rd_coherence->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_coherence_CheckedChanged);
			// 
			// rd_meancolor
			// 
			this->rd_meancolor->AutoSize = true;
			this->rd_meancolor->Location = System::Drawing::Point(6, 19);
			this->rd_meancolor->Name = L"rd_meancolor";
			this->rd_meancolor->Size = System::Drawing::Size(111, 17);
			this->rd_meancolor->TabIndex = 14;
			this->rd_meancolor->TabStop = true;
			this->rd_meancolor->Text = L"Mean Color Image";
			this->rd_meancolor->UseVisualStyleBackColor = true;
			this->rd_meancolor->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_meancolor_CheckedChanged);
			// 
			// rd_corrlogram
			// 
			this->rd_corrlogram->AutoSize = true;
			this->rd_corrlogram->Location = System::Drawing::Point(6, 42);
			this->rd_corrlogram->Name = L"rd_corrlogram";
			this->rd_corrlogram->Size = System::Drawing::Size(106, 17);
			this->rd_corrlogram->TabIndex = 15;
			this->rd_corrlogram->TabStop = true;
			this->rd_corrlogram->Text = L"Auto-Correlogram";
			this->rd_corrlogram->UseVisualStyleBackColor = true;
			this->rd_corrlogram->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_corrlogram_CheckedChanged);
			// 
			// lbl_para1
			// 
			this->lbl_para1->AutoSize = true;
			this->lbl_para1->Location = System::Drawing::Point(476, 24);
			this->lbl_para1->Name = L"lbl_para1";
			this->lbl_para1->Size = System::Drawing::Size(35, 13);
			this->lbl_para1->TabIndex = 16;
			this->lbl_para1->Text = L"label1";
			// 
			// txt_para1
			// 
			this->txt_para1->Location = System::Drawing::Point(572, 24);
			this->txt_para1->Name = L"txt_para1";
			this->txt_para1->ReadOnly = true;
			this->txt_para1->Size = System::Drawing::Size(33, 20);
			this->txt_para1->TabIndex = 17;
			// 
			// trb_para1
			// 
			this->trb_para1->Location = System::Drawing::Point(616, 24);
			this->trb_para1->Name = L"trb_para1";
			this->trb_para1->Size = System::Drawing::Size(271, 45);
			this->trb_para1->TabIndex = 18;
			this->trb_para1->Scroll += gcnew System::EventHandler(this, &Form1::trb_para1_Scroll);
			// 
			// trb_para2
			// 
			this->trb_para2->Location = System::Drawing::Point(616, 75);
			this->trb_para2->Name = L"trb_para2";
			this->trb_para2->Size = System::Drawing::Size(271, 45);
			this->trb_para2->TabIndex = 21;
			this->trb_para2->Scroll += gcnew System::EventHandler(this, &Form1::trb_para2_Scroll);
			// 
			// txt_para2
			// 
			this->txt_para2->Location = System::Drawing::Point(572, 75);
			this->txt_para2->Name = L"txt_para2";
			this->txt_para2->ReadOnly = true;
			this->txt_para2->Size = System::Drawing::Size(33, 20);
			this->txt_para2->TabIndex = 20;
			// 
			// lbl_para2
			// 
			this->lbl_para2->AutoSize = true;
			this->lbl_para2->Location = System::Drawing::Point(476, 75);
			this->lbl_para2->Name = L"lbl_para2";
			this->lbl_para2->Size = System::Drawing::Size(35, 13);
			this->lbl_para2->TabIndex = 19;
			this->lbl_para2->Text = L"label1";
			// 
			// trb_para3
			// 
			this->trb_para3->Location = System::Drawing::Point(616, 126);
			this->trb_para3->Name = L"trb_para3";
			this->trb_para3->Size = System::Drawing::Size(271, 45);
			this->trb_para3->TabIndex = 24;
			this->trb_para3->Scroll += gcnew System::EventHandler(this, &Form1::trb_para3_Scroll);
			// 
			// txt_para3
			// 
			this->txt_para3->Location = System::Drawing::Point(572, 126);
			this->txt_para3->Name = L"txt_para3";
			this->txt_para3->ReadOnly = true;
			this->txt_para3->Size = System::Drawing::Size(33, 20);
			this->txt_para3->TabIndex = 23;
			// 
			// lbl_para3
			// 
			this->lbl_para3->AutoSize = true;
			this->lbl_para3->Location = System::Drawing::Point(476, 126);
			this->lbl_para3->Name = L"lbl_para3";
			this->lbl_para3->Size = System::Drawing::Size(35, 13);
			this->lbl_para3->TabIndex = 22;
			this->lbl_para3->Text = L"label1";
			// 
			// trb_para4
			// 
			this->trb_para4->Location = System::Drawing::Point(616, 177);
			this->trb_para4->Name = L"trb_para4";
			this->trb_para4->Size = System::Drawing::Size(271, 45);
			this->trb_para4->TabIndex = 27;
			this->trb_para4->Scroll += gcnew System::EventHandler(this, &Form1::trb_para4_Scroll);
			// 
			// txt_para4
			// 
			this->txt_para4->Location = System::Drawing::Point(572, 177);
			this->txt_para4->Name = L"txt_para4";
			this->txt_para4->ReadOnly = true;
			this->txt_para4->Size = System::Drawing::Size(33, 20);
			this->txt_para4->TabIndex = 26;
			// 
			// lbl_para4
			// 
			this->lbl_para4->AutoSize = true;
			this->lbl_para4->Location = System::Drawing::Point(476, 177);
			this->lbl_para4->Name = L"lbl_para4";
			this->lbl_para4->Size = System::Drawing::Size(35, 13);
			this->lbl_para4->TabIndex = 25;
			this->lbl_para4->Text = L"label1";
			// 
			// trb_para5
			// 
			this->trb_para5->Location = System::Drawing::Point(616, 228);
			this->trb_para5->Name = L"trb_para5";
			this->trb_para5->Size = System::Drawing::Size(271, 45);
			this->trb_para5->TabIndex = 30;
			this->trb_para5->Scroll += gcnew System::EventHandler(this, &Form1::trb_para5_Scroll);
			// 
			// txt_para5
			// 
			this->txt_para5->Location = System::Drawing::Point(572, 228);
			this->txt_para5->Name = L"txt_para5";
			this->txt_para5->ReadOnly = true;
			this->txt_para5->Size = System::Drawing::Size(33, 20);
			this->txt_para5->TabIndex = 29;
			// 
			// lbl_para5
			// 
			this->lbl_para5->AutoSize = true;
			this->lbl_para5->Location = System::Drawing::Point(476, 228);
			this->lbl_para5->Name = L"lbl_para5";
			this->lbl_para5->Size = System::Drawing::Size(35, 13);
			this->lbl_para5->TabIndex = 28;
			this->lbl_para5->Text = L"label1";
			// 
			// trb_para6
			// 
			this->trb_para6->Location = System::Drawing::Point(616, 279);
			this->trb_para6->Name = L"trb_para6";
			this->trb_para6->Size = System::Drawing::Size(271, 45);
			this->trb_para6->TabIndex = 33;
			this->trb_para6->Scroll += gcnew System::EventHandler(this, &Form1::trb_para6_Scroll);
			// 
			// txt_para6
			// 
			this->txt_para6->Location = System::Drawing::Point(572, 279);
			this->txt_para6->Name = L"txt_para6";
			this->txt_para6->ReadOnly = true;
			this->txt_para6->Size = System::Drawing::Size(33, 20);
			this->txt_para6->TabIndex = 32;
			// 
			// lbl_para6
			// 
			this->lbl_para6->AutoSize = true;
			this->lbl_para6->Location = System::Drawing::Point(476, 279);
			this->lbl_para6->Name = L"lbl_para6";
			this->lbl_para6->Size = System::Drawing::Size(35, 13);
			this->lbl_para6->TabIndex = 31;
			this->lbl_para6->Text = L"label1";
			// 
			// rd_EdgeHistogram
			// 
			this->rd_EdgeHistogram->AutoSize = true;
			this->rd_EdgeHistogram->Location = System::Drawing::Point(82, 65);
			this->rd_EdgeHistogram->Name = L"rd_EdgeHistogram";
			this->rd_EdgeHistogram->Size = System::Drawing::Size(145, 17);
			this->rd_EdgeHistogram->TabIndex = 34;
			this->rd_EdgeHistogram->TabStop = true;
			this->rd_EdgeHistogram->Text = L"Edge Direction Histogram";
			this->rd_EdgeHistogram->UseVisualStyleBackColor = true;
			this->rd_EdgeHistogram->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_EdgeHistogram_CheckedChanged);
			// 
			// rd_Motion
			// 
			this->rd_Motion->AutoSize = true;
			this->rd_Motion->Location = System::Drawing::Point(6, 88);
			this->rd_Motion->Name = L"rd_Motion";
			this->rd_Motion->Size = System::Drawing::Size(89, 17);
			this->rd_Motion->TabIndex = 35;
			this->rd_Motion->TabStop = true;
			this->rd_Motion->Text = L"Motion Image";
			this->rd_Motion->UseVisualStyleBackColor = true;
			this->rd_Motion->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_Motion_CheckedChanged);
			// 
			// rd_MeanMotion
			// 
			this->rd_MeanMotion->AutoSize = true;
			this->rd_MeanMotion->Location = System::Drawing::Point(123, 19);
			this->rd_MeanMotion->Name = L"rd_MeanMotion";
			this->rd_MeanMotion->Size = System::Drawing::Size(171, 17);
			this->rd_MeanMotion->TabIndex = 36;
			this->rd_MeanMotion->TabStop = true;
			this->rd_MeanMotion->Text = L"Mean Motion Sequence Image";
			this->rd_MeanMotion->UseVisualStyleBackColor = true;
			this->rd_MeanMotion->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_MeanMotion_CheckedChanged);
			// 
			// rd_moment
			// 
			this->rd_moment->AutoSize = true;
			this->rd_moment->Location = System::Drawing::Point(235, 42);
			this->rd_moment->Name = L"rd_moment";
			this->rd_moment->Size = System::Drawing::Size(124, 17);
			this->rd_moment->TabIndex = 37;
			this->rd_moment->TabStop = true;
			this->rd_moment->Text = L"Color Vector Moment";
			this->rd_moment->UseVisualStyleBackColor = true;
			this->rd_moment->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_moment_CheckedChanged);
			// 
			// rd_motionHistogram
			// 
			this->rd_motionHistogram->AutoSize = true;
			this->rd_motionHistogram->Location = System::Drawing::Point(111, 19);
			this->rd_motionHistogram->Name = L"rd_motionHistogram";
			this->rd_motionHistogram->Size = System::Drawing::Size(107, 17);
			this->rd_motionHistogram->TabIndex = 38;
			this->rd_motionHistogram->TabStop = true;
			this->rd_motionHistogram->Text = L"Motion Histogram";
			this->rd_motionHistogram->UseVisualStyleBackColor = true;
			this->rd_motionHistogram->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_motionHistogram_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rd_motionHistogram);
			this->groupBox1->Controls->Add(this->rd_histogram);
			this->groupBox1->Location = System::Drawing::Point(31, 302);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(236, 49);
			this->groupBox1->TabIndex = 46;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Image and Video";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->rd_meancolor);
			this->groupBox2->Controls->Add(this->rd_MeanMotion);
			this->groupBox2->Location = System::Drawing::Point(31, 357);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(311, 41);
			this->groupBox2->TabIndex = 47;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Video";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->rd_directionCoherence);
			this->groupBox3->Controls->Add(this->rd_SIFT);
			this->groupBox3->Controls->Add(this->rd_Tamura);
			this->groupBox3->Controls->Add(this->rd_Motion);
			this->groupBox3->Controls->Add(this->rd_EdgeHistogram);
			this->groupBox3->Controls->Add(this->rd_moment);
			this->groupBox3->Controls->Add(this->rd_Geometry);
			this->groupBox3->Controls->Add(this->rd_coherence);
			this->groupBox3->Controls->Add(this->rd_corrlogram);
			this->groupBox3->Location = System::Drawing::Point(31, 171);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(404, 125);
			this->groupBox3->TabIndex = 48;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Image";
			// 
			// rd_SIFT
			// 
			this->rd_SIFT->AutoSize = true;
			this->rd_SIFT->Location = System::Drawing::Point(234, 65);
			this->rd_SIFT->Name = L"rd_SIFT";
			this->rd_SIFT->Size = System::Drawing::Size(48, 17);
			this->rd_SIFT->TabIndex = 38;
			this->rd_SIFT->TabStop = true;
			this->rd_SIFT->Text = L"SIFT";
			this->rd_SIFT->UseVisualStyleBackColor = true;
			this->rd_SIFT->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_SIFT_CheckedChanged);
			// 
			// rd_directionCoherence
			// 
			this->rd_directionCoherence->AutoSize = true;
			this->rd_directionCoherence->Location = System::Drawing::Point(101, 88);
			this->rd_directionCoherence->Name = L"rd_directionCoherence";
			this->rd_directionCoherence->Size = System::Drawing::Size(184, 17);
			this->rd_directionCoherence->TabIndex = 39;
			this->rd_directionCoherence->TabStop = true;
			this->rd_directionCoherence->Text = L"Edge Direction Coherence Vector";
			this->rd_directionCoherence->UseVisualStyleBackColor = true;
			this->rd_directionCoherence->CheckedChanged += gcnew System::EventHandler(this, &Form1::rd_directionCoherence_CheckedChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(899, 421);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->trb_para6);
			this->Controls->Add(this->txt_para6);
			this->Controls->Add(this->lbl_para6);
			this->Controls->Add(this->trb_para5);
			this->Controls->Add(this->txt_para5);
			this->Controls->Add(this->lbl_para5);
			this->Controls->Add(this->trb_para4);
			this->Controls->Add(this->txt_para4);
			this->Controls->Add(this->lbl_para4);
			this->Controls->Add(this->trb_para3);
			this->Controls->Add(this->txt_para3);
			this->Controls->Add(this->lbl_para3);
			this->Controls->Add(this->trb_para2);
			this->Controls->Add(this->txt_para2);
			this->Controls->Add(this->lbl_para2);
			this->Controls->Add(this->trb_para1);
			this->Controls->Add(this->txt_para1);
			this->Controls->Add(this->lbl_para1);
			this->Controls->Add(this->btn_compute);
			this->Controls->Add(this->txtBox_err);
			this->Controls->Add(this->lbl_err);
			this->Controls->Add(this->txtBox_result2);
			this->Controls->Add(this->lbl_result);
			this->Controls->Add(this->txtBox_result);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Test";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trb_para6))->EndInit();
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
#pragma region MenuTrip
	private: System::Void openImageMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				if(openPicDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					if(rd_Geometry->Checked == true)
					{
						float compact; float ti_so_truc; float thon_dai; 
						float chu_nhat; float loi;

						computeGeometric(compact, ti_so_truc, thon_dai, chu_nhat, loi);
						
						compact1 = compact; 
						ti_so_truc1 = ti_so_truc;
						thon_dai1 = thon_dai;
						chu_nhat1 = chu_nhat;
						loi1 = loi;

						showGeometric(compact, ti_so_truc, thon_dai, chu_nhat, loi, txtBox_result);
					}
					else if(rd_Tamura->Checked == true)
					{
						float Coarseness, Contrast, Directionality;
						float Line_likeness, Regularity, Roughness;

						computeTamura(Coarseness, Contrast, Directionality,
									  Line_likeness, Regularity, Roughness);
						
						Coarseness1 = Coarseness; Contrast1 = Contrast; Directionality1 = Directionality;
						Line_likeness1 = Line_likeness; Regularity1 = Regularity; Roughness1 = Roughness;
						
						showTamura(Coarseness, Contrast, Directionality,
								   Line_likeness, Regularity, Roughness, txtBox_result);
					}
					else if(rd_coherence->Checked == true)
					{
						ColorFeatures color;

						color.getImage(openPicDlg->FileName);
						color.showCoherenceVector(Convert::ToInt32(txt_para1->Text));
					}
					else if(rd_histogram->Checked == true)
					{
						ColorFeatures color;

						color.getImage(openPicDlg->FileName);
						color.ColorHistogram(Convert::ToInt32(txt_para1->Text),
											 Convert::ToInt32(txt_para1->Text),
											 Convert::ToInt32(txt_para1->Text));
					}
					else if(rd_corrlogram->Checked == true)
					{
						ColorFeatures color;

						color.getImage(openPicDlg->FileName);
						color.ColorCorrelogram(Convert::ToInt32(txt_para1->Text),
											   Convert::ToInt32(txt_para2->Text));
					}
					else if(rd_EdgeHistogram->Checked == true)
					{
						SHAPE_FEATURES shape_feature;
						shape_feature.getImage(openPicDlg->FileName);

						shape_feature.showHistogramEdgeDirection(Convert::ToInt32(txt_para1->Text));
					}
					else if(rd_Motion->Checked == true || rd_motionHistogram->Checked == true ||
						    rd_SIFT->Checked == true)
					{
						File1 = openPicDlg->FileName;
					}
					else if(rd_moment->Checked == true)
					{
						ColorFeatures color;
						int Moment[3][3];

						color.getImage(openPicDlg->FileName);

						color.VectorMomentColor(Moment[0], Moment[1], Moment[2]);
						showColorMoment(Moment, txtBox_result);
					}
					else if(rd_directionCoherence->Checked == true)
					{
						SHAPE_FEATURES shape_feature;
						shape_feature.getImage(openPicDlg->FileName);

						shape_feature.showCoherenceVector();
					}

					/*MOTION a;

					a.test();*/
				}
			 }
	private: System::Void openImage2ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					if(openPicDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
					{
						if(rd_Geometry->Checked == true)
						{
							float compact; float ti_so_truc; float thon_dai; 
							float chu_nhat; float loi;

							computeGeometric(compact, ti_so_truc, thon_dai, chu_nhat, loi);
						
							compact2 = compact; 
							ti_so_truc2 = ti_so_truc;
							thon_dai2 = thon_dai;
							chu_nhat2 = chu_nhat;
							loi2 = loi;

							showGeometric(compact, ti_so_truc, thon_dai, chu_nhat, loi, txtBox_result2);
						}
						else if(rd_Tamura->Checked == true)
						{
							float Coarseness, Contrast, Directionality;
							float Line_likeness, Regularity, Roughness;

							computeTamura(Coarseness, Contrast, Directionality,
										  Line_likeness, Regularity, Roughness);
						
							Coarseness2 = Coarseness; Contrast2 = Contrast; Directionality2 = Directionality;
							Line_likeness2 = Line_likeness; Regularity2 = Regularity; Roughness2 = Roughness;
						
							showTamura(Coarseness, Contrast, Directionality,
									   Line_likeness, Regularity, Roughness, txtBox_result2);
						}
						else if(rd_coherence->Checked == true)
						{
							ColorFeatures color;

							color.getImage(openPicDlg->FileName);
							color.showCoherenceVector(Convert::ToInt32(txt_para1->Text));
						}
						else if(rd_histogram->Checked == true)
						{
							ColorFeatures color;

							color.getImage(openPicDlg->FileName);
							color.ColorHistogram(Convert::ToInt32(txt_para1->Text),
												 Convert::ToInt32(txt_para1->Text),
												 Convert::ToInt32(txt_para1->Text));
						}
						else if(rd_corrlogram->Checked == true)
						{
							ColorFeatures color;

							color.getImage(openPicDlg->FileName);
							color.ColorCorrelogram(Convert::ToInt32(txt_para1->Text),
												   Convert::ToInt32(txt_para2->Text));
						}
						else if(rd_EdgeHistogram->Checked == true)
						{
							SHAPE_FEATURES shape_feature;
							shape_feature.getImage(openPicDlg->FileName);

							shape_feature.showHistogramEdgeDirection(Convert::ToInt32(txt_para1->Text));
						}
						else if(rd_Motion->Checked == true || rd_motionHistogram->Checked == true ||
						        rd_SIFT->Checked == true)
						{
							File2 = openPicDlg->FileName;
						}
						else if(rd_moment->Checked == true)
						{
							ColorFeatures color;
							int Moment[3][3];

							color.getImage(openPicDlg->FileName);

							color.VectorMomentColor(Moment[0], Moment[1], Moment[2]);
							showColorMoment(Moment, txtBox_result2);
						}
						else if(rd_directionCoherence->Checked == true)
						{
							SHAPE_FEATURES shape_feature;
							shape_feature.getImage(openPicDlg->FileName);

							shape_feature.showCoherenceVector();
						}
					}
			 }
	private: System::Void btn_compute_Click(System::Object^  sender, System::EventArgs^  e) {
				 float err;
				 if(rd_Geometry->Checked == true)
				 {
					 err =  (compact2 - compact1)*(compact2 - compact1) + 
							(ti_so_truc2 - ti_so_truc1)*(ti_so_truc2 - ti_so_truc1) + 
							(thon_dai2 - thon_dai1)*(thon_dai2 - thon_dai1) +
							(chu_nhat2 - chu_nhat1)*(chu_nhat2 - chu_nhat1) +
							(loi2 - loi1)*(loi2 - loi1);
					 err /= 5;
					 txtBox_err->Text = "\t" + err;
				 }
				 else if(rd_Tamura->Checked == true)
				 {
				 	 err = (Coarseness2 - Coarseness1) * (Coarseness2 - Coarseness1) +
						   (Contrast2 - Contrast1) * (Contrast2 - Contrast1) +
						   (Directionality2 - Directionality1) * (Directionality2 - Directionality1) +
						   (Line_likeness2 - Line_likeness1) * (Line_likeness2 - Line_likeness1) +
						   (Regularity2 - Regularity1) * (Regularity2 - Regularity1) +
						   (Roughness2 - Roughness1) * (Roughness2 - Roughness1);
					 err /= 6;
					 txtBox_err->Text = "\t" + err;
				 }
				 else if(rd_Motion->Checked == true)
				 {
					 MOTION motion;

					 motion.getImage2(File2);
					 motion.getImage1(File1);

					 motion.showMotion();
				 }
				 else if(rd_motionHistogram->Checked == true)
				 {
					 MOTION motion;

					 motion.getImage2(File2);
					 motion.getImage1(File1);

					 motion.showMotionHistogram();
				 }
				 else if(rd_SIFT->Checked == true)
				 {
					 SHAPE_FEATURES shape_feature;
					 
					 shape_feature.getImage(File1);
					 shape_feature.getImage2(File2);

					 shape_feature.showSIFT(Convert::ToInt32(txt_para1->Text));
				 }
			 }
	private: System::Void openVideoMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(openVidDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 if(rd_histogram->Checked == true)
					 {
						 ColorFeatures color;

						 color.getVideo(openVidDlg->FileName);
						 color.DrawVHistogram(Convert::ToInt32(txt_para1->Text));
					 }
					 else if(rd_meancolor->Checked == true)
					 {
						 ColorFeatures color;

						 color.getVideo(openVidDlg->FileName);
						 color.showMeanColorImage();
					 }
					 else if(rd_motionHistogram->Checked == true)
					 {
						 MOTION motion;

						 motion.getVideo(openVidDlg->FileName);

						 motion.showVMotionHistogram();
					 }
					 else if(rd_MeanMotion->Checked == true)
					 {
						 MOTION motion;

						 motion.getVideo(openVidDlg->FileName);

						 motion.showMeanMotion();
					 }
				}
			 }
	private: System::Void closeMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				this->Close();
			 }
#pragma endregion
#pragma region Function
	void computeGeometric(float &compact, float& ti_so_truc, float &thon_dai,
						  float &chu_nhat, float &loi)
	{
		GEOMETRIC geo;
		geo.getImage(openPicDlg->FileName);
		geo.ComputeAll();

		geo.getAll(compact, ti_so_truc, thon_dai, chu_nhat, loi);
	}
	
	void computeTamura(float &Coarseness, float &Contrast, float &Directionality,
					   float &Line_likeness, float &Regularity, float &Roughness)
	{
		TAMURA_TEXTURE tamura;

		tamura.getImage(openPicDlg->FileName);

		tamura.getAll(Coarseness, Contrast, Directionality, Line_likeness,
					  Regularity, Roughness, Convert::ToInt32(txt_para1->Text),
					  Convert::ToInt32(txt_para2->Text),
					  Convert::ToInt32(txt_para3->Text),
					  Convert::ToDouble(txt_para4->Text),
					  Convert::ToInt32(txt_para5->Text),
					  Convert::ToDouble(txt_para6->Text));
	}

	void showTamura(float &Coarseness, float &Contrast, float &Directionality,
					float &Line_likeness, float &Regularity, float &Roughness,
					System::Windows::Forms::TextBox^ txtBox)
	{
		txtBox->Text =	"Tinh Coarseness\t: " + Coarseness + "\r\n" +
						"Tinh Contrast\t: " + Contrast + "\r\n" +
						"Tinh Directionality\t: " + Directionality + "\r\n" +
						"Tinh Line-likeness\t: " + Line_likeness + "\r\n" + 
						"Tinh Regularity\t: " + Regularity + "\r\n" +
						"Tinh Roughness\t: " + Roughness + "\r\n";
	}

	void showGeometric(float &compact, float& ti_so_truc, float &thon_dai,
					   float &chu_nhat, float &loi, System::Windows::Forms::TextBox^ txtBox)
	{
		txtBox->Text =	"Tinh compact\t: " + compact + "\r\n" +
						"Ti so truc chinh\t: " + ti_so_truc + "\r\n" +
						"Tinh thon dai\t: " + thon_dai + "\r\n" +
						"Tinh chu nhat\t: " + chu_nhat + "\r\n" + 
						"Tinh loi\t\t: " + loi;
	}
	void showColorMoment(int Moment[][3], System::Windows::Forms::TextBox^ txtBox)
	{
		txtBox->Text =  "Moment #1: {" + Moment[0][0] + "," + Moment[0][1] + "," + Moment[0][2] + "}" + "\r\n" +
						"Moment #2: {" + Moment[1][0] + "," + Moment[1][1] + "," + Moment[1][2] + "}" + "\r\n" +
						"Moment #3: {" + Moment[2][0] + "," + Moment[2][1] + "," + Moment[2][2] + "}" + "\r\n";
	}
#pragma endregion
#pragma region trackbar event
private: System::Void trb_para1_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_Tamura->Checked == true)
				 txt_para4->Text = (1.0F / trb_para1->Value).ToString();
			 txt_para1->Text = trb_para1->Value.ToString();
		 }
private: System::Void trb_para2_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_corrlogram->Checked == true)
				 txt_para2->Text = (trb_para2->Value * 2 + 1).ToString();
			 else
				 txt_para2->Text = trb_para2->Value.ToString();
		 }
private: System::Void trb_para3_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 txt_para3->Text = trb_para3->Value.ToString();
		 }
private: System::Void trb_para4_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 txt_para4->Text = trb_para4->Value.ToString();
		 }
private: System::Void trb_para5_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 txt_para5->Text = trb_para5->Value.ToString();
		 }
private: System::Void trb_para6_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_Tamura->Checked == true)
				 txt_para6->Text = (trb_para6->Value * 0.25).ToString();
			 else
				 txt_para6->Text = trb_para6->Value.ToString();
		 }
#pragma endregion
#pragma region initialize
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 setTamuraPara();
		 }
private: System::Void setTamuraPara()
		 {
			 trb_para1->Visible = true;
			 trb_para2->Visible = true;
			 trb_para3->Visible = true;
			 trb_para4->Visible = true;
			 trb_para5->Visible = true;
			 trb_para6->Visible = true;

			 txt_para1->Visible = true;
			 txt_para2->Visible = true;
			 txt_para3->Visible = true;
			 txt_para4->Visible = true;
			 txt_para5->Visible = true;
			 txt_para6->Visible = true;

			 lbl_para1->Visible = true;
			 lbl_para2->Visible = true;
			 lbl_para3->Visible = true;
			 lbl_para4->Visible = true;
			 lbl_para5->Visible = true;
			 lbl_para6->Visible = true;

			 trb_para1->Maximum = 64; trb_para1->Minimum = 4; trb_para1->SmallChange = 2;
			 trb_para2->Maximum = 32; trb_para1->Minimum = 2; trb_para1->SmallChange = 1;
			 trb_para3->Maximum = 180; trb_para1->Minimum = 20; trb_para1->SmallChange = 1;
			 trb_para4->Visible = false;
			 trb_para5->Maximum = 8; trb_para5->Minimum = 1; trb_para5->SmallChange = 1;
			 trb_para6->Maximum = 10; trb_para6->Minimum = 1; trb_para6->SmallChange = 1;

			 trb_para1-> Value = 32; trb_para2-> Value = 8;
			 trb_para3-> Value = 30; trb_para5-> Value = 1;
			 trb_para6-> Value = 1;

			 txt_para1->Text = trb_para1->Value.ToString();
			 txt_para2->Text = trb_para2->Value.ToString();
			 txt_para3->Text = trb_para3->Value.ToString();
			 txt_para4->Text = (1.0F / trb_para1->Value).ToString();
			 txt_para5->Text = trb_para5->Value.ToString();
			 txt_para6->Text = (trb_para6->Value * 0.25).ToString();

			 lbl_para1->Text = "So bin mau\r\n(Tren 1 kenh mau)";
			 lbl_para2->Text = "Bac contrast";
			 lbl_para3->Text = "Nguong do lon\r\nbien canh";
			 lbl_para4->Text = "He so chuan hoa\r\nhuu huong";
			 lbl_para5->Text = "Khoang cach d\r\n(Linelikeness)";
			 lbl_para6->Text = "He so chuan hoa\r\ntinh quy luat";
		 }
private: System::Void setHistogramPara()
		 {
			 trb_para1->Visible = true;
			 trb_para2->Visible = false;
			 trb_para3->Visible = false;
			 trb_para4->Visible = false;
			 trb_para5->Visible = false;
			 trb_para6->Visible = false;

			 txt_para1->Visible = true;
			 txt_para2->Visible = false;
			 txt_para3->Visible = false;
			 txt_para4->Visible = false;
			 txt_para5->Visible = false;
			 txt_para6->Visible = false;

			 lbl_para1->Visible = true;
			 lbl_para2->Visible = false;
			 lbl_para3->Visible = false;
			 lbl_para4->Visible = false;
			 lbl_para5->Visible = false;
			 lbl_para6->Visible = false;

			 trb_para1->Maximum = 16; trb_para1->Minimum = 2; trb_para1->SmallChange = 1;

			 trb_para1-> Value = 8;

			 txt_para1->Text = trb_para1->Value.ToString();

			 lbl_para1->Text = "So bin mau\r\n(Tren 1 kenh)";
		 }
private: System::Void setCoherencePara()
		 {
			 trb_para1->Visible = true;
			 trb_para2->Visible = false;
			 trb_para3->Visible = false;
			 trb_para4->Visible = false;
			 trb_para5->Visible = false;
			 trb_para6->Visible = false;

			 txt_para1->Visible = true;
			 txt_para2->Visible = false;
			 txt_para3->Visible = false;
			 txt_para4->Visible = false;
			 txt_para5->Visible = false;
			 txt_para6->Visible = false;

			 lbl_para1->Visible = true;
			 lbl_para2->Visible = false;
			 lbl_para3->Visible = false;
			 lbl_para4->Visible = false;
			 lbl_para5->Visible = false;
			 lbl_para6->Visible = false;

			 trb_para1->Maximum = 16; trb_para1->Minimum = 2; trb_para1->SmallChange = 1;

			 trb_para1-> Value = 8;

			 txt_para1->Text = trb_para1->Value.ToString();

			 lbl_para1->Text = "So bin mau\r\n(Tren 1 kenh)";
		 }
private: System::Void setCorrelogramPara()
		 {
			 trb_para1->Visible = true;
			 trb_para2->Visible = true;
			 trb_para3->Visible = false;
			 trb_para4->Visible = false;
			 trb_para5->Visible = false;
			 trb_para6->Visible = false;

			 txt_para1->Visible = true;
			 txt_para2->Visible = true;
			 txt_para3->Visible = false;
			 txt_para4->Visible = false;
			 txt_para5->Visible = false;
			 txt_para6->Visible = false;

			 lbl_para1->Visible = true;
			 lbl_para2->Visible = true;
			 lbl_para3->Visible = false;
			 lbl_para4->Visible = false;
			 lbl_para5->Visible = false;
			 lbl_para6->Visible = false;

			 trb_para1->Maximum = 16; trb_para1->Minimum = 2; trb_para1->SmallChange = 1;
			 trb_para2->Maximum = 4; trb_para2->Minimum = 0; trb_para2->SmallChange = 1;

			 trb_para1-> Value = 8; trb_para2-> Value = 1;

			 txt_para1->Text = trb_para1->Value.ToString();
			 txt_para2->Text = (trb_para2->Value * 2 + 1).ToString();

			 lbl_para1->Text = "So bin mau\r\n(Tren 1 kenh)";
			 lbl_para2->Text = "Khoang cach d";
		 }
private: System::Void setEdgeDirectionPara()
		 {
			 trb_para1->Visible = true;
			 trb_para2->Visible = false;
			 trb_para3->Visible = false;
			 trb_para4->Visible = false;
			 trb_para5->Visible = false;
			 trb_para6->Visible = false;

			 txt_para1->Visible = true;
			 txt_para2->Visible = false;
			 txt_para3->Visible = false;
			 txt_para4->Visible = false;
			 txt_para5->Visible = false;
			 txt_para6->Visible = false;

			 lbl_para1->Visible = true;
			 lbl_para2->Visible = false;
			 lbl_para3->Visible = false;
			 lbl_para4->Visible = false;
			 lbl_para5->Visible = false;
			 lbl_para6->Visible = false;

			 trb_para1->Maximum = 100; trb_para1->Minimum = 1; trb_para1->SmallChange = 1;

			 trb_para1-> Value = 30;

			 txt_para1->Text = trb_para1->Value.ToString();

			 lbl_para1->Text = "Nguong T";
		 }
private: System::Void setDefaultPara()
		 {
			 trb_para1->Visible = false;
			 trb_para2->Visible = false;
			 trb_para3->Visible = false;
			 trb_para4->Visible = false;
			 trb_para5->Visible = false;
			 trb_para6->Visible = false;

			 txt_para1->Visible = false;
			 txt_para2->Visible = false;
			 txt_para3->Visible = false;
			 txt_para4->Visible = false;
			 txt_para5->Visible = false;
			 txt_para6->Visible = false;

			 lbl_para1->Visible = false;
			 lbl_para2->Visible = false;
			 lbl_para3->Visible = false;
			 lbl_para4->Visible = false;
			 lbl_para5->Visible = false;
			 lbl_para6->Visible = false;
		 }
private: System::Void setSIFTPara()
		 {
			 trb_para1->Visible = true;
			 trb_para2->Visible = false;
			 trb_para3->Visible = false;
			 trb_para4->Visible = false;
			 trb_para5->Visible = false;
			 trb_para6->Visible = false;

			 txt_para1->Visible = true;
			 txt_para2->Visible = false;
			 txt_para3->Visible = false;
			 txt_para4->Visible = false;
			 txt_para5->Visible = false;
			 txt_para6->Visible = false;

			 lbl_para1->Visible = true;
			 lbl_para2->Visible = false;
			 lbl_para3->Visible = false;
			 lbl_para4->Visible = false;
			 lbl_para5->Visible = false;
			 lbl_para6->Visible = false;

			 trb_para1->Maximum = 10; trb_para1->Minimum = 1; trb_para1->SmallChange = 1;

			 trb_para1-> Value = 2;

			 txt_para1->Text = trb_para1->Value.ToString();

			 lbl_para1->Text = "He so alpha: ";
		 }
private: void setFalseImageGroup()
	{
		rd_Tamura->Checked = false;
		rd_coherence->Checked = false;
		rd_moment->Checked = false;
		rd_Geometry->Checked = false;
		rd_corrlogram->Checked = false;
		rd_EdgeHistogram->Checked = false;
		rd_Motion->Checked = false;
		rd_directionCoherence->Checked = false;
	}
private: void setFalseVideoGroup()
	{
		rd_meancolor->Checked = false; 
		rd_MeanMotion->Checked = false;
	}
private: void setFalseHybridGroup()
	{
		rd_histogram->Checked = false;
		rd_motionHistogram->Checked = false;
	}
#pragma endregion
#pragma region radio button
private: System::Void rd_Geometry_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_Geometry->Checked == false)
				 return;
			 setFalseVideoGroup();
			 setFalseHybridGroup();
			 setDefaultPara();
		 }
private: System::Void rd_Tamura_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_Tamura->Checked == false)
				 return;
			 setFalseVideoGroup();
			 setFalseHybridGroup();
			 setTamuraPara();
		 }
private: System::Void rd_meancolor_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_meancolor->Checked == false)
				 return;
			 setFalseImageGroup();
			 setFalseHybridGroup();
			 setDefaultPara();
		 }
private: System::Void rd_histogram_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_histogram->Checked == false)
				 return;
			 setFalseImageGroup();
			 setFalseVideoGroup();
			 setHistogramPara();
		 }
private: System::Void rd_coherence_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_coherence->Checked == false)
				 return;
			 setFalseVideoGroup();
			 setFalseHybridGroup();
			 setCoherencePara();
		 }
private: System::Void rd_corrlogram_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_corrlogram->Checked == false)
				 return;
			 setFalseVideoGroup();
			 setFalseHybridGroup();
			 setCorrelogramPara();
		 }
private: System::Void rd_EdgeHistogram_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_EdgeHistogram->Checked == false)
				 return;
			 setFalseVideoGroup();
			 setFalseHybridGroup();
			 setEdgeDirectionPara();
		 }
private: System::Void rd_Motion_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_Motion->Checked == false)
				 return;
			 setFalseVideoGroup();
			 setFalseHybridGroup();
			 setDefaultPara();
		 }
private: System::Void rd_moment_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_moment->Checked == false)
				 return;
			 setFalseVideoGroup();
			 setFalseHybridGroup();
			 setDefaultPara();
		 }
private: System::Void rd_motionHistogram_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_motionHistogram->Checked == false)
				 return;
			 setFalseImageGroup();
			 setFalseVideoGroup();
			 setDefaultPara();
		 }
private: System::Void rd_MeanMotion_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_MeanMotion->Checked == false)
				 return;
			 setFalseImageGroup();
			 setFalseHybridGroup();
			 setDefaultPara();
		 }
private: System::Void rd_SIFT_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_SIFT->Checked == false)
				 return;
			 setFalseVideoGroup();
			 setFalseHybridGroup();
			 setSIFTPara();
		 }
private: System::Void rd_directionCoherence_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(rd_directionCoherence->Checked == false)
				 return;
			 setFalseVideoGroup();
			 setFalseHybridGroup();
			 setDefaultPara();
		 }
#pragma endregion
};
}