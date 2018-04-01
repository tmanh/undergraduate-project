#include "MyMat.h"


MyMat::MyMat(void)
{
	rows = cols = 0;
	data = NULL;
}


MyMat::MyMat(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	data = new float* [rows];
	for(int i = 0; i < cols; i++)
		data[i] = new float [cols];

	init();
}

MyMat::~MyMat(void)
{
	if(data == NULL)
		return;

	for(int i = 0; i < cols; i++)
		delete []data[i];
	delete []data;
	
}

void MyMat::init()
{
	int i, j;
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			data[i][j] = 0;
}

MyMat& MyMat::operator=(const MyMat &src)
{
	if(data != NULL)
	{
		for(int i = 0; i < cols; i++)
			delete []data[i];
		delete []data;
	}

	rows = src.rows;
	cols = src.cols;

	int i, j;

	data = new float* [rows];
	for(i = 0; i < cols; i++)
		data[i] = new float [cols];
	
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			data[i][j] = src.data[i][j];

	return *this;
}