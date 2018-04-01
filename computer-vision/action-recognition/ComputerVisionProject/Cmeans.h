#pragma once

#include "Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "Libraries\Headers\opencv2\core\core.hpp"
#include "Libraries\Headers\opencv2\imgproc\imgproc.hpp"

#include <iostream>
#include <time.h>

using namespace std;
using namespace cv;

#define delta 0.1
#define MIN_ERROR 0
#define m_factor 2.0

class Cmeans
{
public:
	Cmeans(void)
	{
		data = NULL;
		length = size = 0;
		power = 2 / (m_factor - 1);

		srand(time(NULL));
	}

	~Cmeans(void);
private:
	int ti, tj, tk;
	long ltmp;
	int itmp;
	float ftmp;

protected:
	float power;
	int length, size;
	uchar** data;
private:
	float Distance(uchar* a, uchar* b) //ham tinh khoang cach 2 diem
	{
		float result = 0;

		//vong lap tinh tong ket qua
		for(ti = 0; ti < length; ti++)
		{
			ftmp = (a[ti] - b[ti]);
			result += ftmp * ftmp;
		}

		return sqrt(result);
	};

	//kiem tra trung
	bool overlap(int* centers, int &iterate, int &index);

	//tinh so thay doi
	float computeErr(uchar** oldCenters, uchar**Centers, int nClusters, float &maxErr);

	//ham khoi tao cac cluster
	//nCluster: so cum
	//degreeMembership : nhan cua cac diem du lieu
	//Centers: cac tam cum
	void initializeCluster(int &nClusters, uchar** degreeMembership , uchar** Centers);

	//ham cap nhat cac cluster
	//nCluster: so cum
	//degreeMembership : nhan cua cac diem du lieu
	//Centers: cac tam cum
	void UpdateCenters(int &nClusters, uchar** degreeMembership , uchar** Centers);

	//gan nhan cho cac diem du lieu
	//nCluster: so cum
	//degreeMembership : nhan cua cac diem du lieu
	//Centers: cac tam cum
	void getDegree(int &nClusters, uchar** degreeMembership , uchar** Centers);
public:
	//ham gom cum
	//nCluster: so cum
	//err: nguong loi
	//iterate: so lan lap
	//degreeMembership : nhan cua cac diem du lieu
	//Centers: cac tam cum
	void cluster(int nClusters, float err, int iterate, uchar** degreeMembership , uchar** Centers);

	// Ham gan du lieu
	void setData(uchar** &data, int size, int length);
};