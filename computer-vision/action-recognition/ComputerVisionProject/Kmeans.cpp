#include "Kmeans.h"


Kmeans::~Kmeans(void)
{
	if(data != NULL)
	{
		for (int ti = 0; ti < size; ti++)
		{
			delete []data[ti];
		}
		delete []data;
	}

}

void Kmeans::setData(uchar** data, int size, int length)
{
	this->data = data;
	this->length = length;
	this->size = size;
}

float Kmeans::_distance(uchar* center1, uchar* center2, int length)
{
	float result = 0;
	for(int i = 0; i < length; i++)
	{
		result += (center1[i] - center2[i]) * (center1[i] - center2[i]);
	}
	return sqrt(result);
}

bool Kmeans::overlap(int* centers, int &iterate, int &index)
{
	for(int i = 0; i < iterate; i++)
		if(centers[i] == index)
			return true;
	return false;
}

float Kmeans::computeErr(uchar** oldCenters, uchar** Centers, int nClusters, float &maxErr)
{
	float err;
	
	ftmp = 0;
	maxErr = MIN_ERROR;

	for (ti = 0; ti < nClusters; ti++)
	{
		for (tj = 0; tj < length; tj++)
		{
			err =	(oldCenters[ti][tj] - Centers[ti][tj]) * 
					(oldCenters[ti][tj] - Centers[ti][tj]);

			ftmp += err;

			if(err > maxErr)
				maxErr = err;
		}
	}

	ftmp /= nClusters;

	return ftmp;
}

void Kmeans::getLabel(int &nClusters, uchar* labels, uchar** Centers)
{
	int label = 0;
	long minDis;

	for (int i = 0; i < size; i++)
	{
		minDis = Distance(Centers[0], data[i]);
		labels[i] = 0;
		for (int j = 1; j < nClusters; j++)
		{
			ltmp = Distance(Centers[j], data[i]);
			if (ltmp < minDis)
			{
				labels[i] = j;
				minDis = ltmp;
			}
		}
	}
}

void Kmeans::initializeCluster(int &nClusters, uchar* labels, uchar** Centers)
{
	int* index_centers = new int[nClusters];
	
	for(ti = 0; ti < nClusters; ti++)
	{
		do
		{
			itmp = rand() % size;
		}
		while(overlap(index_centers, ti, itmp));
		
		index_centers[ti] = itmp;
	}
	
	for (ti = 0; ti < nClusters; ti++)
	{
		for (tj = 0; tj < length; tj++)
		{
			Centers[ti][tj] = data[index_centers[ti]][tj];
		}
	}

	getLabel(nClusters, labels, Centers);

	delete []index_centers;
}

void Kmeans::initializeCluster(int &nClusters, uchar* labels, uchar** Centers, char* fname)
{
	ifstream fin(fname);

	int tmp;

	fin >> tmp;

	for (ti = 0; ti < nClusters; ti++)
	{
		for (tj = 0; tj < length; tj++)
		{
			fin >> tmp;
			Centers[ti][tj] = tmp;
		}
	}

	getLabel(nClusters, labels, Centers);
}

void Kmeans::UpdateCenters(int &nClusters, uchar* labels, uchar** Centers)
{
	int* countData = new int[nClusters];

	int** centers = new int* [size];
	for(int i = 0; i < size; i++)
		centers[i] = new int [length];

	for (ti = 0; ti < nClusters; ti++)
	{
		countData[ti] = 0;

		for (tj = 0; tj < length; tj++)
		{
			centers[ti][tj] = 0;
		}
	}

	for (ti = 0; ti < size; ti++)
	{
		countData[labels[ti]]++;

		for (tj = 0; tj < length; tj++)
		{
			centers[labels[ti]][tj] += data[ti][tj];
		}
	}

	for (ti = 0; ti < nClusters; ti++)
	{
		if(countData[ti] == 0)
		{
			for(int tj = 0; tj < length; tj++)
			{
				int tmp = 0;
				for(int tk = 0; tk < ti; tk++)
					tmp += Centers[tk][tj];
				Centers[ti][tj] = tmp / (ti + 1);
			}
		}
		else
		{
			for (tj = 0; tj < length; tj++)
			{
				Centers[ti][tj] = (uchar)(centers[ti][tj]/countData[ti]);
			}
		}
	}

	for(int i = 0; i < size; i++)
		delete []centers[i];
	delete []centers;

	delete []countData;
}

void Kmeans::cluster(int nClusters, float err, int iterate, uchar* labels, uchar** Centers)
{
	//khoi tao cac bien
	int i, j;
	float t_mse, t_err;

	uchar** oldCenters = new uchar*[nClusters];
	for (ti = 0; ti < nClusters; ti++)
	{
		oldCenters[ti] = new uchar[length];
	}
	
	bool break_status = false;
	int number_iterate = 0;

	//khoi tao trang thai dau
	initializeCluster(nClusters, labels, Centers);

	//vong lap thuc hien viec cap nhat tam cum
	while (break_status == false && number_iterate < iterate)
	{
		number_iterate++;
		for (i = 0; i < nClusters; i++)
		{
			for (j = 0; j < length; j++)
			{
				oldCenters[i][j] = Centers[i][j];
			}
		}
		
		//cap nhat lai diem trung tam cum
		UpdateCenters(nClusters, labels, Centers);
		//cap nhat nhan cac diem du lieu
		getLabel(nClusters, labels, Centers);

		t_mse = computeErr(oldCenters, Centers, nClusters, t_err);

		//kiem tra co su thay doi trong cac cum
		if (t_mse < err)
		{
			break_status = true;
		}
	}

	for (int ti = 0; ti < nClusters; ti++)
	{
		delete []oldCenters[ti];
	}
	delete []oldCenters;
}

void Kmeans::cluster(int nClusters, float err, int iterate, uchar* labels, uchar** Centers, char* fname)
{
	//khoi tao cac bien
	int i, j;
	float t_mse, t_err;

	uchar** oldCenters = new uchar*[nClusters];
	for (ti = 0; ti < nClusters; ti++)
	{
		oldCenters[ti] = new uchar[length];
	}
	
	bool break_status = false;
	int number_iterate = 0;

	//khoi tao trang thai dau
	initializeCluster(nClusters, labels, Centers, fname);

	//vong lap thuc hien viec cap nhat tam cum
	while (break_status == false && number_iterate < iterate)
	{
		number_iterate++;
		for (i = 0; i < nClusters; i++)
		{
			for (j = 0; j < length; j++)
			{
				oldCenters[i][j] = Centers[i][j];
			}
		}
		
		//cap nhat lai diem trung tam cum
		UpdateCenters(nClusters, labels, Centers);
		//cap nhat nhan cac diem du lieu
		getLabel(nClusters, labels, Centers);

		t_mse = computeErr(oldCenters, Centers, nClusters, t_err);

		//kiem tra co su thay doi trong cac cum
		if (t_mse < err)
		{
			break_status = true;
		}
	}

	for (int ti = 0; ti < nClusters; ti++)
	{
		delete []oldCenters[ti];
	}
	delete []oldCenters;
}

