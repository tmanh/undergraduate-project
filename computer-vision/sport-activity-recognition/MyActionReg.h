#pragma once

#include "Loader.h"

class MyActionReg
{
public:
	CvSVM SVM;
	CvSVMParams params;
	Loader loader;
	Mat center;

	vector<ObjectInfo> obj;

	MyActionReg(void): center(1, _number_of_word, CV_32FC1)
	{
		// Set up SVM's parameters
		params . svm_type		= CvSVM::C_SVC;
		params . kernel_type	= CvSVM::RBF;
		params . degree			= 3;
		params . gamma			= 75;
		params . coef0			= 0;
		params . C				= 60;
		params . nu				= 0.5;
		params . p				= 0.5;
		params . class_weights	= NULL;
		params . term_crit		= cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);
	};
	~MyActionReg(void);

	//ham save load
	void loadSVM(char* fn);
	void saveSVM(char* fn);
	void load();
	void save();

	//ham doc du lieu
	void readdatatrain(Mat &his);
	void readdatatest(Mat &his);

	//ham tap luyen
	void train(char* folder);
	
	//Phan lop tat ca cac lop
	void predictall(char* folder);

	//Ham xuat tat ca ket qua tinh toan
	//counttrue: mang so ket qua phan lop dung cua tung lop
	//countnum: tong so phan lop co ket qua la i
	//num: tong so phan tu cua lop i
	void showresultall(int counttrue[], int countnum[], int num[]);

	//Ham xuat ket qua
	void showresult(string fxml, string fvideo);

	//lay ten nhan
	string getlabel(float res);
};