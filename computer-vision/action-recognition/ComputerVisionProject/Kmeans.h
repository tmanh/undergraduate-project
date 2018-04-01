#pragma once

#include "Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "Libraries\Headers\opencv2\core\core.hpp"
#include "Libraries\Headers\opencv2\imgproc\imgproc.hpp"

#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;
using namespace cv;

#define delta 0.1
#define MIN_ERROR 0

class Kmeans
{
public:
	Kmeans(void)
	{
		data = NULL;
		length = size = 0;

		srand(time(NULL));
	}

	~Kmeans(void);
private:
	int ti, tj;
	long ltmp;
	int itmp;
	float ftmp;

protected:
	int length, size;
	uchar** data;
private:
	long Distance(uchar* a, uchar* b) //ham tinh khoang cach 2 diem
	{
		long result = 0;

		//vong lap tinh tong ket qua
		for(ti = 0; ti < length; ti++)
		{
			ltmp = (a[ti] - b[ti]);
			result += ltmp * ltmp;
		}

		return result;
	};

	//kiem tra trung
	bool overlap(int* centers, int &iterate, int &index);

	//tinh so thay doi
	float computeErr(uchar** oldCenters, uchar**Centers, int nClusters, float &maxErr);

	//ham cap nhat cac cluster
	//nCluster: so cum
	//labels: nhan cua cac diem du lieu
	//Centers: cac tam cum
	void UpdateCenters(int &nClusters, uchar* labels, uchar** Centers);
public:
	// Ham gan du lieu
	void setData(uchar** data, int size, int length);

	//ham khoi tao cac cluster
	//nCluster: so cum
	//labels: nhan cua cac diem du lieu
	//Centers: cac tam cum
	void initializeCluster(int &nClusters, uchar* labels, uchar** Centers);

	//ham khoi tao cac cluster
	//nCluster: so cum
	//labels: nhan cua cac diem du lieu
	//Centers: cac tam cum
	void initializeCluster(int &nClusters, uchar* labels, uchar** Centers, char* fname);

	//gan nhan cho cac diem du lieu
	//nCluster: so cum
	//labels: nhan cua cac diem du lieu
	//Centers: cac tam cum
	void getLabel(int &nClusters, uchar* labels, uchar** Centers);

	float _distance(uchar* center1, uchar* center2, int length);
public:
	//ham gom cum
	//nCluster: so cum
	//err: nguong loi
	//iterate: so lan lap
	//labels: nhan cua cac diem du lieu
	//Centers: cac tam cum
	void cluster(int nClusters, float err, int iterate, uchar* labels, uchar** Centers);

	//ham gom cum
	//nCluster: so cum
	//err: nguong loi
	//iterate: so lan lap
	//labels: nhan cua cac diem du lieu
	//Centers: cac tam cum
	//fname: file khoi tao tam cum
	void Kmeans::cluster(int nClusters, float err, int iterate, uchar* labels, uchar** Centers, char* fname);
};

