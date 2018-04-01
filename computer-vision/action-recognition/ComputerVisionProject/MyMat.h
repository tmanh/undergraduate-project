#pragma once

#include <iostream>

using namespace std;

class MyMat
{
//function
public:
	MyMat(void);
	MyMat(int rows, int cols);

	~MyMat(void);

	void init();

	MyMat& operator=(const MyMat &src);
//data
public:
	float** data;
	int rows, cols;
};

