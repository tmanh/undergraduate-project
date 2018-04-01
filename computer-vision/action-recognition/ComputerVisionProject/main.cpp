#include "myBOW.h"

#include <time.h>
#include <vector>
#include <fstream>

#include "Action.h"
#include "Kmeans.h"
#include "Cmeans.h"

clock_t start;

using namespace std;
using namespace cv;

#define _minHessian	550

void loadDepthDataSet(char* fname1, char* fname2, char* fname3, char* fname4, int ID, int nData);
float _distance(float* data1, float* data2, int length);
void getVideoHistogramMHI(char* fname1, char* fname2, char* fname3);
void getVideoHistogramF_BMHI(char* fname1, char* fname2, char* fname3, char* fname4, char* fname5);
void getCmeanVideoHistogramMHI(char* fname1, char* fname2, char* fname3);
float classify(char* fname1, char* fname2, int nCluster, int nData1, int nData2);
float classifySVM(char* fname1, char* fname2, int nCluster, int nData1, int nData2);
int ClassifierKNN(float* data, float** histogram, int* _class, int k, int nCluster, int nData);
float _distance(uchar* data1, uchar* data2, int length);
int getCenter(uchar* data, uchar** Centers, int nClusters, int length);
void loadDataSet(char* fname1, char* fname2, char* fname3, int ID, int nData);
void loadKmeans(char* fname1, char* fname2, char* fname3, int nClusters, float err, int iter);
void loadCmeans(char* fname1, char* fname2, char* fname3, int nClusters, float err, int iter);
void loadDepthKmeans(char* fname1, char* fname2, char* fname3, char* fname4, char* fname5, int nClusters, float err, int iter);
void loadDepthKmeans(char* fname1, char* fname2, char* fname3, char* fname4, char* fname5, char* fname6, char* fname7, int nClusters, float err, int iter);

void saveBestClusterF_BMHI(char* fname1, char* fname2);
void saveBestClusterMHI(char* fname1, char* fname2);

float histogram_correlogramMHI(int flag)
{
	int max = 0;
	float res_max = 0;
	float tmp = -1, best_result = 0, best_k = 50, mean;

	//doc k tot nhat
	ifstream fin("bestkmhi.txt");
	fin >> best_k;
	fin.close();

	if(flag == 1)
	{
		loadDataSet("training2.txt", "mhiFeaturesExtract.txt", "HeaderFeaturesExtract.txt", 0, 224);
		loadDataSet("training3.txt", "trainmhiFeaturesExtract.txt", "trainmhiHeaderFeaturesExtract.txt", 0, 160);
		loadDataSet("validation.txt", "valimhiFeaturesExtract.txt", "valiHeaderFeaturesExtract.txt", 0, 64);
		loadDataSet("test.txt", "testmhiFeaturesExtract.txt", "testHeaderFeaturesExtract.txt", 0, 96);
	}

	if(flag == 2)
	{
		for(int k = 50; k <= 120; k += 10 )
		{
			mean = 0;
			for(int i = 0; i < 10; i++)
			{
				loadKmeans("trainmhiFeaturesExtract.txt", "trainmhiHeaderFeaturesExtract.txt", "trainmhiClustering.txt", k, 0.005F, 50);

				getVideoHistogramMHI("trainmhiFeaturesExtract.txt", "trainmhiClustering.txt", "trainmhiHistogram.txt");
				getVideoHistogramMHI("valimhiFeaturesExtract.txt", "trainmhiClustering.txt", "valimhiHistogram.txt");
				tmp = classifySVM("trainmhiHistogram.txt", "valimhiHistogram.txt", k, 160, 64);

				mean += tmp;

				cout << "result[" << k << "][" << i << "]: " << tmp << endl;	
			}

			if(mean > best_result)
			{
				best_k = k;
				best_result = mean;

				ofstream fout("bestkmhi.txt");
				fout << best_k;
				fout.close();

				saveBestClusterMHI("mhiFeaturesExtract.txt", "bestmhiClustering.txt");
			}
		}

		loadKmeans("mhiFeaturesExtract.txt", "HeaderFeaturesExtract.txt", "Clustering.txt", best_k, 0.0005F, 100);
	}

	if(flag == 3)
	{
		getVideoHistogramMHI("mhiFeaturesExtract.txt", "Clustering.txt", "Histogram.txt");
		getVideoHistogramMHI("testmhiFeaturesExtract.txt", "Clustering.txt", "testHistogram.txt");
	}

	if(flag == 4)
		tmp = classifySVM("Histogram.txt", "testHistogram.txt", best_k, 224, 96);

	return tmp;
}

float fbMHI(int flag)
{
	int max = 0;
	float res_max = 0;
	float tmp = -1, best_result = 0, best_k = 70, mean;

	//doc k tot nhat
	ifstream fin("bestkfbmhi.txt");
	fin >> best_k;
	fin.close();

	//thuc hien rut trich dac trung
	if(flag == 1)
	{
		loadDepthDataSet("training2.txt", "fmhiFeaturesExtract.txt", "bmhiFeaturesExtract.txt", "fbmhiHeaderFeaturesExtract.txt", 0, 224);
		loadDepthDataSet("training3.txt", "trainfmhiFeaturesExtract.txt", "trainbmhiFeaturesExtract.txt", "trainHeaderFeaturesExtract.txt", 0, 160);
		loadDepthDataSet("validation.txt", "valifmhiFeaturesExtract.txt", "valibmhiFeaturesExtract.txt", "valiHeaderFeaturesExtract.txt", 0, 64);
		loadDepthDataSet("test.txt", "testfmhiFeaturesExtract.txt", "testbmhiFeaturesExtract.txt", "testfbmhiHeaderFeaturesExtract.txt", 0, 96);
	}

	//thuc hien gom cum
	if(flag == 2)
	{
		for(int k = 50; k <= 120; k += 10 )
		{
			mean = 0;
			for(int i = 0; i < 10; i++)
			{
				loadDepthKmeans("trainfmhiFeaturesExtract.txt", "trainbmhiFeaturesExtract.txt", "trainHeaderFeaturesExtract.txt", "trainfmhiClustering.txt", "trainbmhiClustering.txt", k, 0.005F, 50);

				getVideoHistogramF_BMHI("trainfmhiFeaturesExtract.txt", "trainfmhiClustering.txt", "trainbmhiFeaturesExtract.txt", "trainbmhiClustering.txt", "trainfbmhiHistogram.txt");
				getVideoHistogramF_BMHI("valifmhiFeaturesExtract.txt", "trainfmhiClustering.txt", "valibmhiFeaturesExtract.txt", "trainbmhiClustering.txt", "valifbmhiHistogram.txt");
				tmp = classifySVM("trainfbmhiHistogram.txt", "valifbmhiHistogram.txt", 2 * k, 160, 64);

				mean += tmp;

				cout << "result[" << k << "][" << i << "]: " << tmp << endl;	
			}

			if(mean > best_result)
			{
				best_k = k;
				best_result = mean;

				ofstream fout("bestkfbmhi.txt");
				fout << best_k;
				fout.close();

				saveBestClusterF_BMHI("trainfmhiClustering.txt", "bestfmhiClustering.txt");
				saveBestClusterF_BMHI("trainbmhiClustering.txt", "bestbmhiClustering.txt");
			}
		}

		loadDepthKmeans("fmhiFeaturesExtract.txt", "bmhiFeaturesExtract.txt", "fbmhiHeaderFeaturesExtract.txt", "fmhiClustering.txt", "bmhiClustering.txt", best_k, 0.005F, 50);
	}

	//thuc hien tinh descriptor va phan lop
	if(flag == 3)
	{
		getVideoHistogramF_BMHI("fmhiFeaturesExtract.txt", "fmhiClustering.txt", "bmhiFeaturesExtract.txt", "bmhiClustering.txt", "fbmhiHistogram.txt");
		getVideoHistogramF_BMHI("testfmhiFeaturesExtract.txt", "fmhiClustering.txt", "testbmhiFeaturesExtract.txt", "bmhiClustering.txt", "testfbmhiHistogram.txt");
	}

	if(flag == 4)
		tmp = classifySVM("fbmhiHistogram.txt", "testfbmhiHistogram.txt", 2 * best_k, 224, 96);

	return tmp;
}

void main()
{
	/*VideoCapture cap("C:\\Users\\dell\\Desktop\\capture-1.avi");

	Mat frameA;

	while(cap.read(frameA))
	{
		imshow("vui", frameA);
		waitKey();
	}*/

	int choice, flag;
	float result;
	
	while(true)
	{
		system("cls");

		cout << "Chon 1 trong 2 lua chon de kiem tra ket qua cua 2 huong tiep can" << endl;

		cout << "Nhap lua chon: " << endl;
		cout << "\t1. Histogram of MHG + Correlogram of MHG" << endl;
		cout << "\t2. Forward MHG Histogram + Backward MHG Histogram" << endl;
		cout << "\t3. Exit" << endl;
		cout << "Lua chon: ";
	
		cin >> choice;

		if(choice == 3)
			return;
		else if(choice <= 0 || choice > 3)
		{
			cout << "Lenh vua nhap khong hop le!!! Vui long nhap lai.";
			system("pause");
			continue;
		}
		else
		{
			system("cls");

			if(choice == 1)
				cout << "Histogram of MHG + Correlogram of MHG" << endl;
			else
				cout << "Forward MHG Histogram + Backward MHG Histogram" << endl;

			cout << "Nhap lua chon: " << endl;
			cout << "\t1. Rut trich dac trung" << endl;
			cout << "\t2. Gom nhom tu" << endl;
			cout << "\t3. Tinh histogram of word" << endl;
			cout << "\t4. Phan lop" << endl;
			cout << "\t5. Back" << endl;

			cout << "Thuc hien chon lua chon 4 de xem ket qua hien tai cua nhom" << endl;

			cout << "Lua chon: ";

			cin >> flag;

			if(flag == 5)
				continue;

			if(choice == 1)
				result = histogram_correlogramMHI(flag);
			else
				result = fbMHI(flag);

			if(result > 0)
			{
				cout << "Ket qua: " << result << endl;
			}

			system("pause");
		}
	}
}

//fname1: ten file can luu
//fname2: ten file khi luu
void saveBestClusterF_BMHI(char* fname1, char* fname2)
{
	int tmp, nClusters;

	ifstream fin(fname1);
	ofstream fout(fname2);

	fin >> nClusters;
	fout << nClusters << endl;

	for(int i = 0; i < nClusters; i++)
	{
		for(int j = 0; j < 144; j++)
		{
			fin >> tmp;
			fout << tmp << " ";
		}
		fout << endl;
	}

	fin.close();
	fout.close();
}

//fname1: ten file can luu
//fname2: ten file khi luu
void saveBestClusterMHI(char* fname1, char* fname2)
{
	int tmp, nClusters;

	ifstream fin(fname1);
	ofstream fout(fname2);

	fin >> nClusters;
	fout << nClusters << endl;

	for(int i = 0; i < nClusters; i++)
	{
		for(int j = 0; j < 144; j++)
		{
			fin >> tmp;
			fout << tmp << " ";
		}
		fout << endl;
	}

	fin.close();
	fout.close();
}

//fname1: file chua thong tin data
//fname2: file luu features
//fname3: file luu header features
void loadDataSet(char* fname1, char* fname2, char* fname3, int ID, int nData)
{
	string fn1, fn2;
	int _class, all_rows = 0;
	Action act;

	ifstream fin(fname1);
	ofstream fout(fname2);
	ofstream fout2(fname3);

	fout << nData << endl;

	for(int k = 0; k < nData; k++)
	{
		fin >> fn1;
		fin >> _class;
		fin >> fn2;
		fin >> _class;
		Mat descrip_frame;

		if(ID == 0)
		{
			descrip_frame = act.load(fn2, fn1);
		}

		int rows = descrip_frame.rows;
		int cols = descrip_frame.cols;
		int steps = descrip_frame.step;
		int index; 
		all_rows += rows;

		cout << fn1 << " - " << fn2 << " - " << _class << endl;
		fout << _class << " " << rows << " " << cols << endl;

		uchar* ptr_descrip = (uchar*)descrip_frame.data;
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				index = i * steps + j;
				fout << (int)ptr_descrip[index] << " "; 
			}
			fout << endl;
		}

		fout << endl;
	}

	fout2 << all_rows << endl;

	fout2.close();
	fout.close();
	fin.close();
}

//tinh dac trung f-MHI, b-MHI
//fname1: file chua thong tin data
//fname2: file luu fMHI features
//fname3: file luu bMHI features
//fname4: file luu header features
void loadDepthDataSet(char* fname1, char* fname2, char* fname3, char* fname4, int ID, int nData)
{
	string fn1, fn2;
	int _class, all_rows1 = 0, all_rows2 = 0;
	Action act;

	ifstream fin(fname1);
	ofstream fout(fname2);
	ofstream fout2(fname3);
	ofstream fout3(fname4);

	fout << nData << endl;
	fout2 << nData << endl;

	for(int k = 0; k < nData; k++)
	{
		fin >> fn1;
		fin >> _class;
		fin >> fn2;
		fin >> _class;
		Mat descrip_frame1, descrip_frame2;

		if(ID == 0)
		{
			act.loadDepth(fn2, fn1, descrip_frame1, descrip_frame2);
		}

		int rows = descrip_frame1.rows;
		int cols = descrip_frame1.cols;
		int steps = descrip_frame1.step;
		int index;

		all_rows1 += descrip_frame1.rows;
		all_rows2 += descrip_frame2.rows;

		cout << fn1 << " - " << fn2 << " - " << _class << endl;
		fout << _class << " " << rows << " " << cols << endl;
		fout2 << _class << " " << rows << " " << cols << endl;

		uchar* ptr_descrip1 = (uchar*)descrip_frame1.data;
		uchar* ptr_descrip2 = (uchar*)descrip_frame2.data;

		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				index = i * steps + j;
				fout << (int)ptr_descrip1[index] << " ";
				fout2 << (int)ptr_descrip2[index] << " "; 
			}
			fout << endl;
			fout2 << endl;
		}

		fout << endl;
		fout2 << endl;
	}

	fout3 << all_rows1 << " " << all_rows2 << endl;

	fout3.close();
	fout2.close();
	fout.close();
	fin.close();
}

//fname1: File data
//fname2: Header
//fname3: file ket qua
void loadKmeans(char* fname1, char* fname2, char* fname3, int nClusters, float err, int iter)
{
	int _class, all_rows, rows, tmp, nData;

	ifstream fin(fname1);
	ifstream fin2(fname2);
	ofstream fout(fname3);

	fin >> nData;
	fin2 >> all_rows;

	uchar** data = new uchar* [all_rows];
	for(int i = 0; i < all_rows; i++)
		data[i] = new uchar [144];

	int index = 0, max_index;
	for(int k = 0; k < nData; k++)
	{
		fin >> _class;
		fin >> rows;
		fin >> tmp;

		max_index = index + rows;

		for(int i = index; i < max_index; i++)
		{
			for(int j = 0; j < 144; j++)
			{
				fin >> tmp;
				data[i][j] = tmp; 
			}
		}

		index = max_index;
	}

	Kmeans kmean;
	uchar* labels = new uchar[all_rows];

	uchar** centers = new uchar* [nClusters];
	for(int i = 0; i < nClusters; i++)
		centers[i] = new uchar [144];

	kmean.setData(data, all_rows, 144);
	kmean.cluster(nClusters, err, iter, labels, centers);

	fout << nClusters << endl;
	for(int i = 0; i < nClusters; i++)
	{
		for(int j = 0; j < 144; j++)
		{
			fout << (int)centers[i][j] << " ";
		}
		fout << endl;
	}

	for(int i = 0; i < nClusters; i++)
		delete []centers[i];
	delete []centers;

	delete []labels;

	fout.close();
	fin.close();
	fin2.close();
}

//fname1: File data
//fname2: File data
//fname3: Header
//fname4: file ket qua(fmhi)
//fname5: file ket qua(bmhi)
void loadDepthKmeans(char* fname1, char* fname2, char* fname3, char* fname4, char* fname5, int nClusters, float err, int iter)
{
	int number = 72;
	int _class, all_rows1, all_rows2, rows, tmp, nData;

	ifstream fin(fname1);
	ifstream fin2(fname2);
	ifstream fin3(fname3);
	ofstream fout(fname4);
	ofstream fout2(fname5);

	fin >> nData;
	fin3 >> all_rows1;
	fin3 >> all_rows2;

	uchar** data = new uchar* [all_rows1];
	for(int i = 0; i < all_rows1; i++)
		data[i] = new uchar [number];

	int index = 0, max_index;
	for(int k = 0; k < nData; k++)
	{
		fin >> _class;
		fin >> rows;
		fin >> tmp;

		max_index = index + rows;

		for(int i = index; i < max_index; i++)
		{
			for(int j = 0; j < number; j++)
			{
				fin >> tmp;
				data[i][j] = tmp; 
			}
		}

		index = max_index;
	}

	Kmeans kmean;
	uchar* labels = new uchar[all_rows1];

	uchar** centers = new uchar* [nClusters];
	for(int i = 0; i < nClusters; i++)
		centers[i] = new uchar [number];

	kmean.setData(data, all_rows1, number);
	kmean.cluster(nClusters, err, iter, labels, centers);

	fout << nClusters << endl;
	for(int i = 0; i < nClusters; i++)
	{
		for(int j = 0; j < number; j++)
		{
			fout << (int)centers[i][j] << " ";
		}
		fout << endl;
	}
	//////////////////////

	fin2 >> nData;
	index = 0, max_index;
	for(int k = 0; k < nData; k++)
	{
		fin2 >> _class;
		fin2 >> rows;
		fin2 >> tmp;

		max_index = index + rows;

		for(int i = index; i < max_index; i++)
		{
			for(int j = 0; j < number; j++)
			{
				fin2 >> tmp;
				data[i][j] = tmp; 
			}
		}

		index = max_index;
	}

	kmean.setData(data, all_rows2, number);
	kmean.cluster(nClusters, err, iter, labels, centers);

	fout2 << nClusters << endl;
	for(int i = 0; i < nClusters; i++)
	{
		for(int j = 0; j < number; j++)
		{
			fout2 << (int)centers[i][j] << " ";
		}
		fout2 << endl;
	}

	for(int i = 0; i < nClusters; i++)
		delete []centers[i];
	delete []centers;

	delete []labels;

	fout2.close();
	fout.close();
	fin.close();
	fin2.close();
	fin3.close();
}

//fname1: File data
//fname2: File data
//fname3: Header
//fname4: file ket qua(fmhi)
//fname5: file ket qua(bmhi)
//fname6: file best fmhi
//fname7: file best bmhi
void loadDepthKmeans(char* fname1, char* fname2, char* fname3, char* fname4, char* fname5, char* fname6, char* fname7, int nClusters, float err, int iter)
{
	int number = 72;
	int _class, all_rows1, all_rows2, rows, tmp, nData;

	ifstream fin(fname1);
	ifstream fin2(fname2);
	ifstream fin3(fname3);
	ofstream fout(fname4);
	ofstream fout2(fname5);

	fin >> nData;
	fin3 >> all_rows1;
	fin3 >> all_rows2;

	uchar** data = new uchar* [all_rows1];
	for(int i = 0; i < all_rows1; i++)
		data[i] = new uchar [number];

	int index = 0, max_index;
	for(int k = 0; k < nData; k++)
	{
		fin >> _class;
		fin >> rows;
		fin >> tmp;

		max_index = index + rows;

		for(int i = index; i < max_index; i++)
		{
			for(int j = 0; j < number; j++)
			{
				fin >> tmp;
				data[i][j] = tmp; 
			}
		}

		index = max_index;
	}

	Kmeans kmean;
	uchar* labels = new uchar[all_rows1];

	uchar** centers = new uchar* [nClusters];
	for(int i = 0; i < nClusters; i++)
		centers[i] = new uchar [number];

	kmean.setData(data, all_rows1, number);
	kmean.cluster(nClusters, err, iter, labels, centers, fname6);

	fout << nClusters << endl;
	for(int i = 0; i < nClusters; i++)
	{
		for(int j = 0; j < number; j++)
		{
			fout << (int)centers[i][j] << " ";
		}
		fout << endl;
	}
	//////////////////////

	fin2 >> nData;
	index = 0, max_index;
	for(int k = 0; k < nData; k++)
	{
		fin2 >> _class;
		fin2 >> rows;
		fin2 >> tmp;

		max_index = index + rows;

		for(int i = index; i < max_index; i++)
		{
			for(int j = 0; j < number; j++)
			{
				fin2 >> tmp;
				data[i][j] = tmp; 
			}
		}

		index = max_index;
	}

	kmean.setData(data, all_rows2, number);
	kmean.cluster(nClusters, err, iter, labels, centers, fname7);

	fout2 << nClusters << endl;
	for(int i = 0; i < nClusters; i++)
	{
		for(int j = 0; j < number; j++)
		{
			fout2 << (int)centers[i][j] << " ";
		}
		fout2 << endl;
	}

	for(int i = 0; i < nClusters; i++)
		delete []centers[i];
	delete []centers;

	delete []labels;

	fout2.close();
	fout.close();
	fin.close();
	fin2.close();
	fin3.close();
}

//fname1: File data
//fname2: Header
//fname3: file ket qua
void loadCmeans(char* fname1, char* fname2, char* fname3, int nClusters, float err, int iter)
{
	int _class, all_rows, rows, tmp, nData;

	ifstream fin(fname1);
	ifstream fin2(fname2);
	ofstream fout(fname3);

	fin >> nData;
	fin2 >> all_rows;

	uchar** data = new uchar* [all_rows];
	for(int i = 0; i < all_rows; i++)
		data[i] = new uchar [144];

	int index = 0, max_index;
	for(int k = 0; k < nData; k++)
	{
		fin >> _class;
		fin >> rows;
		fin >> tmp;

		max_index = index + rows;

		for(int i = index; i < max_index; i++)
		{
			for(int j = 0; j < 144; j++)
			{
				fin >> tmp;
				data[i][j] = tmp; 
			}
		}

		index = max_index;
	}

	Cmeans cmeans;
	uchar** degree = new uchar*[all_rows];
	for(int i = 0; i < all_rows; i++)
		degree[i] = new uchar [nClusters];

	uchar** centers = new uchar* [nClusters];
	for(int i = 0; i < nClusters; i++)
		centers[i] = new uchar [144];

	cmeans.setData(data, all_rows, 144);
	cmeans.cluster(nClusters, err, iter, degree, centers);

	fout << nClusters << endl;
	for(int i = 0; i < nClusters; i++)
	{
		for(int j = 0; j < 144; j++)
		{
			fout << (int)centers[i][j] << " ";
		}
		fout << endl;
	}

	for(int i = 0; i < nClusters; i++)
		delete []centers[i];
	delete []centers;

	for(int i = 0; i < all_rows; i++)
		delete []degree[i];
	delete []degree;

	fout.close();
	fin.close();
	fin2.close();
}

//fname1: data
//fname2: cluster
//fname3: file ket qua
void getVideoHistogramMHI(char* fname1, char* fname2, char* fname3)
{
	int _class, nClusters, tmp, rows, nData;

	ifstream fin(fname1);
	ifstream fin2(fname2);
	ofstream fout(fname3);

	fin >> nData;
	fin2 >> nClusters;

	uchar** centers = new uchar* [nClusters];
	for(int i = 0; i < nClusters; i++)
		centers[i] = new uchar [144];

	for(int i = 0; i < nClusters; i++)
	{
		for(int j = 0; j < 144; j++)
		{
			fin2 >> tmp;
			centers[i][j] = tmp;
		}
	}

	float* Histogram = new float [nClusters];

	for(int k = 0; k < nData; k++)
	{
		fin >> _class;
		fin >> rows;
		fin >> tmp;

		if(rows == 0)
			cout << _class << " - " << k << endl;

		uchar** data = new uchar* [rows];
		for(int i = 0; i < rows; i++)
			data[i] = new uchar [144];

		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < 144; j++)
			{
				fin >> tmp;
				data[i][j] = tmp;
			}
		}

		for(int i = 0; i < nClusters; i++)
		{
			Histogram[i] = 0;
		}
		
		for(int i = 0; i < rows; i++)
			Histogram[getCenter(data[i],centers,nClusters,144)]++;

		fout << _class << " ";
		for(int i = 0; i < nClusters; i++)
		{
			if(rows != 0)
				Histogram[i] /= rows;
			fout << Histogram[i] << " ";
		}
		fout << endl;

		for(int i = 0; i < rows; i++)
		{
			delete []data[i];
		}
		delete []data;
	}

	delete []Histogram;

	for(int i = 0; i < nClusters; i++)
	{
		delete []centers[i];
	}
	delete []centers;
}

//fname1: data
//fname2: cluster
//fname3: data 2
//fname4: cluster 2
//fname5: file ket qua
void getVideoHistogramF_BMHI(char* fname1, char* fname2, char* fname3, char* fname4, char* fname5)
{
	int number = 72;
	int _class, tmp, rows, _class2, tmp2, rows2, nClusters1, nClusters2, nData1, nData2;

	ifstream fin(fname1);
	ifstream fin2(fname2);
	ifstream fin3(fname3);
	ifstream fin4(fname4);
	ofstream fout(fname5);

	////////////////////////////////////
	fin >> nData1;
	fin2 >> nClusters1;
	fin3 >> nData2;
	fin4 >> nClusters2;

	//read center form fmhi
	uchar** centers = new uchar* [nClusters1];
	for(int i = 0; i < nClusters1; i++)
		centers[i] = new uchar [number];

	for(int i = 0; i < nClusters1; i++)
	{
		for(int j = 0; j < number; j++)
		{
			fin2 >> tmp;
			centers[i][j] = tmp;
		}
	}

	//read center form bmhi
	uchar** centers2 = new uchar* [nClusters2];
	for(int i = 0; i < nClusters2; i++)
		centers2[i] = new uchar [number];

	for(int i = 0; i < nClusters2; i++)
	{
		for(int j = 0; j < number; j++)
		{
			fin4 >> tmp;
			centers2[i][j] = tmp;
		}
	}

	/////////////////
	//write numbers of total column
	//fout << (nClusters2 + nClusters1) << endl;

	float* Histogram1 = new float [nClusters1];
	float* Histogram2 = new float [nClusters1];

	for(int k = 0; k < nData1; k++)
	{
		/////read data form fmhi-features
		fin >> _class;
		fin >> rows;
		fin >> tmp;

		if(rows == 0)
			cout << _class << " - " << k << endl;

		uchar** data = new uchar* [rows];
		for(int i = 0; i < rows; i++)
			data[i] = new uchar [number];

		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < number; j++)
			{
				fin >> tmp;
				data[i][j] = tmp;
			}
		}

		/////read data form bmhi-features
		fin3 >> _class2;
		fin3 >> rows2;
		fin3 >> tmp2;

		uchar** data2 = new uchar* [rows2];
		for(int i = 0; i < rows2; i++)
			data2[i] = new uchar [number];

		for(int i = 0; i < rows2; i++)
		{
			for(int j = 0; j < number; j++)
			{
				fin3 >> tmp2;
				data2[i][j] = tmp2;
			}
		}

		////////////
		//initialize histogram
		for(int i = 0; i < nClusters1; i++)
		{
			Histogram1[i] = 0;
		}

		for(int i = 0; i < nClusters2; i++)
		{
			Histogram2[i] = 0;
		}
		
		//cluster
		for(int i = 0; i < rows; i++)
			Histogram1[getCenter(data[i],centers,nClusters1,number)]++;
		
		for(int i = 0; i < rows; i++)
			Histogram2[getCenter(data2[i],centers2,nClusters2,number)]++;

		//write file
		fout << _class << " ";
		for(int i = 0; i < nClusters1; i++)
		{
			if(rows != 0)
				Histogram1[i] /= rows;
			fout << Histogram1[i] << " ";
		}
		for(int i = 0; i < nClusters2; i++)
		{
			if(rows2 != 0)
				Histogram2[i] /= rows2;
			fout << Histogram2[i] << " ";
		}
		fout << endl;

		for(int i = 0; i < rows; i++)
		{
			delete []data[i];
		}
		delete []data;

		for(int i = 0; i < rows2; i++)
		{
			delete []data2[i];
		}
		delete []data2;
	}

	delete []Histogram1;
	delete []Histogram2;

	for(int i = 0; i < nClusters1; i++)
	{
		delete []centers[i];
	}
	delete []centers;

	for(int i = 0; i < nClusters2; i++)
	{
		delete []centers2[i];
	}
	delete []centers2;
}

//fname1: data
//fname2: cluster
//fname3: file ket qua
void getCmeanVideoHistogramMHI(char* fname1, char* fname2, char* fname3)
{
	int _class, nClusters, tmp, rows, nData;

	ifstream fin(fname1);
	ifstream fin2(fname2);
	ofstream fout(fname3);

	fin >> nData;
	fin2 >> nClusters;

	uchar** centers = new uchar* [nClusters];
	for(int i = 0; i < nClusters; i++)
		centers[i] = new uchar [144];

	for(int i = 0; i < nClusters; i++)
	{
		for(int j = 0; j < 144; j++)
		{
			fin2 >> tmp;
			centers[i][j] = tmp;
		}
	}

	float* Histogram = new float [nClusters];
	float* distance_set = new float [nClusters];
	int sum_distance;
	float distance_tmp;

	for(int k = 0; k < nData; k++)
	{
		fin >> _class;
		fin >> rows;
		fin >> tmp;

		if(rows == 0)
			cout << _class << " - " << k << endl;

		uchar** data = new uchar* [rows];
		for(int i = 0; i < rows; i++)
			data[i] = new uchar [144];

		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < 144; j++)
			{
				fin >> tmp;
				data[i][j] = tmp;
			}
		}

		for(int i = 0; i < nClusters; i++)
		{
			Histogram[i] = 0;
		}
		
		for(int i = 0; i < rows; i++)
		{
			sum_distance = 0;
			for(int j = 0; j < nClusters; j++)
			{
				distance_set[j] = _distance(data[i], centers[j], 144);
				sum_distance += distance_set[j];
			}

			for(int j = 0; j < nClusters; j++)
			{
				distance_tmp = 0;

				for(int tk = 0; tk < nClusters; tk++)
					distance_tmp += pow((distance_set[j]/distance_set[tk]), 2);
				
				distance_tmp = 1 / distance_tmp;

				if(distance_tmp > 0.02)
					Histogram[j] += distance_tmp;
			}
		}

		fout << _class << " ";
		for(int i = 0; i < nClusters; i++)
		{
			if(rows != 0)
				Histogram[i] /= rows;
			fout << Histogram[i] << " ";
		}
		fout << endl;

		for(int i = 0; i < rows; i++)
		{
			delete []data[i];
		}
		delete []data;
	}

	delete []Histogram;
	delete []distance_set;

	for(int i = 0; i < nClusters; i++)
	{
		delete []centers[i];
	}
	delete []centers;
}

//fname1: traning
//fname2: test
float classify(char* fname1, char* fname2, int nCluster, int nData1, int nData2)
{
	ifstream fin1(fname1);
	ifstream fin2(fname2);

	int* _class1 = new int [nData1];
	int* _class2 = new int [nData1];

	float** histogram1 = new float* [nData1];
	for(int i = 0; i < nData1; i++)
		histogram1[i] = new float [nCluster];

	float** histogram2 = new float* [nData2];
	for(int i = 0; i < nData2; i++)
		histogram2[i] = new float [nCluster];

	int tmp2;
	float tmp;

	for(int i = 0; i < nData1; i++)
	{
		fin1 >> tmp2;
		_class1[i] = tmp2;
		for(int j = 0; j < nCluster; j++)
		{
			fin1 >> tmp;
			histogram1[i][j] = tmp;
		}
	}

	for(int i = 0; i < nData2; i++)
	{
		fin2 >> tmp2;
		_class2[i] = tmp2;
		for(int j = 0; j < nCluster; j++)
		{
			fin2 >> tmp;
			histogram2[i][j] = tmp;
		}
	}

	float percent = 0;
	int classify;
	for(int i = 0; i < nData2; i++)
	{
		classify = ClassifierKNN(histogram2[i], histogram1, _class2, 5, nCluster, nData2);
		cout << classify << " " << (int)_class2[i] << endl;
		if(classify == (int)_class2[i])
			percent++;
	}

	cout << "Ket qua: " << percent / nData2 << endl;

	delete []_class1;
	delete []_class2;

	for(int i = 0; i < nData1; i++)
		delete []histogram1[i];
	delete []histogram1;

	for(int i = 0; i < nData2; i++)
		delete []histogram2[i];
	delete []histogram2;

	return percent / nData2;
}

float classifySVM(char* fname1, char* fname2, int nCluster, int nData1, int nData2)
{
	ifstream fin1(fname1);
	ifstream fin2(fname2);

	int* _class1 = new int [nData1];
	int* _class2 = new int [nData1];

	float** histogram1 = new float* [nData1];
	for(int i = 0; i < nData1; i++)
		histogram1[i] = new float [nCluster];

	float** histogram2 = new float* [nData2];
	for(int i = 0; i < nData2; i++)
		histogram2[i] = new float [nCluster];

	int tmp2, k;
	float tmp;

	for(int i = 0; i < nData1; i++)
	{
		fin1 >> tmp2;
		_class1[i] = tmp2;
		for(int j = 0; j < nCluster; j++)
		{
			fin1 >> tmp;
			histogram1[i][j] = tmp;
		}
	}

	for(int i = 0; i < nData2; i++)
	{
		fin2 >> tmp2;
		_class2[i] = tmp2;
		for(int j = 0; j < nCluster; j++)
		{
			fin2 >> tmp;
			histogram2[i][j] = tmp;
		}
	}

    // Set up training data
    Mat labelsMat(nData1, 1, CV_32FC1);

	float* ptr = (float*)labelsMat.data;
	for(int i = 0; i < nData1; i++)
		ptr[i]  = _class1[i];

    Mat trainingDataMat(nData1, nCluster, CV_32FC1);

	k = 0;
	ptr = (float*)trainingDataMat.data;
	for(int i = 0; i < nData1; i++)
	{
		for(int j = 0; j < nCluster; j++)
		{
			ptr[k] = histogram1[i][j];
			k++;
		}
	}

	Mat testDataMat(nData2, nCluster, CV_32FC1);
	k = 0;
	ptr = (float*)testDataMat.data;
	for(int i = 0; i < nData2; i++)
	{
		for(int j = 0; j < nCluster; j++)
		{
			ptr[k] = histogram2[i][j];
			k++;
		}
	}

	Mat result;

    // Set up SVM's parameters
    CvSVMParams params;
    /*params.svm_type    = CvSVM::C_SVC;
    params.kernel_type = CvSVM::LINEAR;
    params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100, 0.5);*/
	params . svm_type		= CvSVM::C_SVC;
	params . kernel_type	= CvSVM::RBF;
	params . degree			= 2;
	params . gamma			= 15;
	params . coef0			= 0;
	params . C				= 60;
	params . nu				= 0.5;
	params . p				= 0.5;
	params . class_weights	= NULL;
	params . term_crit		= cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-1);

    // Train the SVM
    CvSVM SVM;
    SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);

	float percent = 0;

	SVM.predict(testDataMat, result);

	ptr = (float*)result.data;

	for(int i = 0; i < nData2; i++)
	{
		if((int)ptr[i] == (int)_class2[i])
			percent++;
	}

	delete []_class1;
	delete []_class2;

	for(int i = 0; i < nData1; i++)
		delete []histogram1[i];
	delete []histogram1;

	for(int i = 0; i < nData2; i++)
		delete []histogram2[i];
	delete []histogram2;

	return percent / nData2;
}

//k: so k trong K-NN
int ClassifierKNN(float* data, float** histogram, int* _class, int k, int nCluster, int nData)
{
	float tmp;

	int* listIndex = new int [k];
	float* listDistance = new float [k];

	for(int i = 0; i < k; i++)
	{
		listIndex[i] = 0;
		listDistance[i] = 9999;
	}

	for(int i = 1; i < nData; i++)
	{
		tmp = _distance(data, histogram[i], nCluster);
		for(int j = 0; j < k; j++)
		{
			if(tmp < listDistance[j])
			{
				for(int h = k - 1; h > j; h--)
				{
					listDistance[h] = listDistance[h - 1];
					listIndex[h] = listIndex[h - 1];
				}

				listDistance[j] = tmp;
				listIndex[j] = i;
				break;
			}
		}
	}

	vector<int> listNumberIndex;
	vector<int> listClassMin;

	int flag = false;
	for(int i = 0; i < k; i++)
	{
		for(int j = 0; j < listClassMin.size(); j++)
		{
			if(listClassMin[j] == _class[listIndex[i]])
			{
				listNumberIndex[j]++;
				flag = true;
				break;
			}
		}
		if(flag == false)
		{
			listNumberIndex.push_back(1);
			listClassMin.push_back(_class[listIndex[i]]);
		}
	}

	int maxIndex = 0;
	for(int i = 0; i < listClassMin.size(); i++)
	{
		if(listNumberIndex[i] > listNumberIndex[maxIndex])
			maxIndex = i;
	}

	return listClassMin[maxIndex];
}

int getCenter(uchar* data, uchar** Centers, int nClusters, int length)
{
	int minIndex = 0;
	int minDistance = _distance(data, Centers[0], length);
	int tmp;

	for(int i = 1; i < nClusters; i++)
	{
		tmp = _distance(data, Centers[i], length);
		if(tmp < minDistance)
		{
			minDistance = tmp;
			minIndex = i;
		}
	}
	return minIndex;
}

float _distance(uchar* data1, uchar* data2, int length)
{
	float result = 0;
	for(int i = 0; i < length; i++)
		result += (data1[i] - data2[i]) * (data1[i] - data2[i]);
	return (int)sqrt(result);
}

float _distance(float* data1, float* data2, int length)
{
	float result = 0;
	for(int i = 0; i < length; i++)
		result += (data1[i] - data2[i]) * (data1[i] - data2[i]);
	return sqrt(result);
}