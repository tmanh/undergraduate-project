#include "Cmeans.h"


Cmeans::~Cmeans(void)
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

void Cmeans::setData(uchar** &data, int size, int length)
{
	this->data = data;
	this->length = length;
	this->size = size;
}

bool Cmeans::overlap(int* centers, int &iterate, int &index)
{
	for(int i = 0; i < iterate; i++)
		if(centers[i] == index)
			return true;
	return false;
}

float Cmeans::computeErr(uchar** oldCenters, uchar** Centers, int nClusters, float &maxErr)
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

void Cmeans::getDegree(int &nClusters, uchar** degreeMembership , uchar** Centers)
{
	int label = 0;

	float totalDeg;

	float* dis = new float [nClusters];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < nClusters; j++)
		{
			dis[j] = Distance(Centers[j], data[i]);
		}

		for (int j = 0; j < nClusters; j++)
		{
			totalDeg = 0;
			for(tk = 0; tk < nClusters; tk++)
				totalDeg += pow((dis[j]/dis[tk]), power);
			totalDeg = 1 / totalDeg;

			degreeMembership[i][j] = totalDeg * 255;
		}
	}

	delete []dis;
}

void Cmeans::initializeCluster(int &nClusters, uchar** degreeMembership , uchar** Centers)
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

	getDegree(nClusters, degreeMembership , Centers);

	delete []index_centers;
}

void Cmeans::UpdateCenters(int &nClusters, uchar** degreeMembership , uchar** Centers)
{
	float* countData = new float[nClusters];

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

	for (tk = 0; tk < nClusters; tk++)
	{
		for (ti = 0; ti < size; ti++)
		{
			ftmp = degreeMembership[ti][tk] / 255.0F;
			countData[tk] += ftmp;

			for (tj = 0; tj < length; tj++)
			{
				centers[tk][tj] += (uchar)(ftmp * data[ti][tj]);
			}
		}
	}

	for (ti = 0; ti < nClusters; ti++)
	{
		for (tj = 0; tj < length; tj++)
		{
			Centers[ti][tj] = (uchar)(centers[ti][tj]/countData[ti]);
		}
	}

	for(int i = 0; i < size; i++)
		delete []centers[i];
	delete []centers;

	delete []countData;
}

void Cmeans::cluster(int nClusters, float err, int iterate, uchar** degreeMembership , uchar** Centers)
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
	initializeCluster(nClusters, degreeMembership , Centers);

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
		UpdateCenters(nClusters, degreeMembership , Centers);
		//cap nhat nhan cac diem du lieu
		getDegree(nClusters, degreeMembership , Centers);

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