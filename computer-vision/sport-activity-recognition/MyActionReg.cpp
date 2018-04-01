#include "MyActionReg.h"


MyActionReg::~MyActionReg(void)
{
}

void MyActionReg::loadSVM(char* fn)
{
	SVM.load(fn);
}

void MyActionReg::saveSVM(char* fn)
{
	SVM.save(fn);
}

//Ham load du lieu
void MyActionReg::load()
{
	//Write svm to file
	SVM.load("svm_data.xml");

	cv::FileStorage file("center.xml", cv::FileStorage::READ);

	// Read from file!
	file["center"] >> center;
}

//Ham save du lieu
void MyActionReg::save()
{
	//Write svm to file
	//-----------------
	SVM.save("svm_data.xml");

	cv::FileStorage file("center.xml", cv::FileStorage::WRITE);
	//-----------------
	// Write to file!
	file << "center" << center;
	file.release();
}

//Ham doc data trainning
void MyActionReg::readdatatrain(Mat &his)
{
	loader.LoadAll(center, obj, his);
}

//Ham doc data test
void MyActionReg::readdatatest(Mat &his)
{
	//Xoa vector object va vector histogram
	//-----------------
	obj.clear();
	his.release();
	//-----------------
	//Doc du lieu toan bo du lieu test
	loader.LoadAllTest(obj, his, center);
}

//ham huan luyen tap
void MyActionReg::train(char* folder)
{
	Mat his;
	readdatatrain(his);
	// Set up training data
	//-----------------
	int k = 0, size = his.rows;

	Mat labelsMat(0, 0, CV_32FC1);

	for(int i = 0; i < size; i++)
		labelsMat.push_back((int)obj[i].bbox[0].label);
	//-----------------
	//tranning by svm
	//-----------------
	SVM.train(his, labelsMat, Mat(), Mat(), params);

	cout << "finished train" << endl;
	//-----------------
	//save result of tranning
	//-----------------
	save();
}

//Phan lop tat ca cac lop
void MyActionReg::predictall(char* folder)
{
	Mat his;
	readdatatest(his);
	//Khoi tao cac bien
	//-----------------
	int counttrue[9], countnum[9], num[9];
	int alltrue = 0;

	for(int i = 0; i < 9; i++)
		counttrue[i] = countnum[i] = num[i] = 0;

	float response = 0;

	Mat tmp(1, _number_of_word, CV_32FC1);

	int k = 0;
	float *x = (float*)his.data;
	float *t = (float*)tmp.data;
	//-----------------
	//Phan lop cho tat ca du lieu
	//-----------------
	for(int i = 0; i < his.rows; i++)
	{
		//trich BOW descriptor thu i tu mang BOW descriptor
		//-----------------
		for(int j = 0; j < _number_of_word; j++)
		{
			t[j] = x[k++];
		}
		//-----------------
		//phan lop
		//-----------------
		response = SVM.predict(tmp);
		//-----------------
		//tinh ket qua
		//-----------------
		num[(int)obj[i].bbox[0].label]++;

		if(response >= 0 && response < 9)
		{
			countnum[(int)response]++;

			if((int)response == (int)obj[i].bbox[0].label)
			{
				counttrue[(int)response]++;
				alltrue++;
			}
		}
	}
	//-----------------
	//xuat tat ca ket qua ra man hinh
	//-----------------
	showresultall(counttrue, countnum, num);
	cout << "Tong do chinh xac: " << (float)alltrue / his.rows * 100 << "%" << endl;
}

//Ham xuat tat ca ket qua tinh toan
//counttrue: mang so ket qua phan lop dung cua tung lop
//countnum: tong so phan lop co ket qua la i
//num: tong so phan tu cua lop i
void MyActionReg::showresultall(int counttrue[], int countnum[], int num[])
{
	float precision, recall, allprecision;
	for(int i = 0; i < 9; i++)
	{
		//tinh do chinh xac va do phu
		//-----------------
		std::cout.precision(4);
		precision = (float)counttrue[i] / (countnum[i]);
		recall = (float)counttrue[i] / num[i];
		allprecision += precision;
		//-----------------
		//xuat do chinh xac va do phu
		//-----------------
		cout << "Doi tuong " <<i << ":" << endl;
		cout << "Precision:\t" << precision * 100 << "%" << endl;
		cout << "Recall:\t\t" << recall * 100 << "%" << endl;
	}
}

//ham show video
void MyActionReg::showresult(string fxml, string fvideo)
{
	//Khai bao bien
	//-----------------
	obj.clear();
	Mat his;
	VideoCapture cap(fvideo);
	//-----------------
	if(!cap.isOpened())  // check if we succeeded
        return;

	loader.LoadOne(fxml, fvideo, obj, his, center);

	vector<float> response; //luu ket qua phan lop

	Mat tmp(1, _number_of_word, CV_32FC1);

	int k = 0;
	float *x = (float*)his.data;
	float *t = (float*)tmp.data;

	cout << "Ket qua: " << endl;
	//Phan lop cho tat ca du lieu
	for(int i = 0; i < his.rows; i++)
	{
		//trich BOW descriptor thu i tu mang BOW descriptor
		for(int j = 0; j < _number_of_word; j++)
		{
			t[j] = x[k++];
		}
		
		//phan lop
		response.push_back(SVM.predict(tmp));
		cout << "Doi tuong thu " << i << ": " << getlabel(response[i]) << endl;
	}

	Mat frame;

	for(int i = 0; ; i++)
    {
		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
			break;

		Rect rct;

		//Tim descriptor tat ca cac frame trong video cua doi tuong
		for(int j = 0; j < obj.size(); j++)
		{
			for(k = 0; k < obj[j].bbox.size(); k++)
			{
				if(i >= obj[j].bbox[k].begin_frame && i <= obj[j].bbox[k].end_frame)
				{
					//xac dinh vi tri doi tuong
					rct.height = obj[j].bbox[k].height;
					rct.width = obj[j].bbox[k].width;
					rct.x = obj[j].bbox[k].x;
					rct.y = obj[j].bbox[k].y;
					
					if(rct.height + rct.y >= frame.rows)
						rct.height = frame.rows - rct.y;
					if(rct.width + rct.x >= frame.cols)
						rct.width = frame.cols - rct.x;
					rectangle(frame, rct, Scalar(0,0,255), 2);
					putText(frame,getlabel(response[j]),Point(rct.x,rct.y),0,0.5,Scalar(0,0,0),2);
				}
			}

			//Hien thi anh tren cua so "Result"
			namedWindow("Result", CV_WINDOW_AUTOSIZE );// Create a window for display.
			displayImage(frame, "Result");
		}
	}
	//Huy cua so hien thi
	destroyWindow("Result");
}

//Lay nhan tuong ung
string MyActionReg::getlabel(float res)
{
	if(res == 0)
		return "basketball shooting";
	if(res == 1.0)
		return "biking";
	if(res == 2.0)
		return "diving";
	if(res == 3.0)
		return "golf swing";
	if(res == 4.0)
		return "horse riding";
	if(res == 5.0)
		return "soccer juggling";
	if(res == 6.0)
		return "tennis swing";
	if(res == 7.0)
		return "trampoline jumping";
	return "walking";
}