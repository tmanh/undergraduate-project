#pragma once

#include <iostream>

using namespace std;

class MyArray
{
//function
public:
	MyArray(void);
	MyArray(int length);
	MyArray(float* raw, int length);

	~MyArray(void);

	void init();

	MyArray& operator=(const MyArray& src);

	void getData(float* src, int length);
//data
public:
	float* data;
	int length;
};

