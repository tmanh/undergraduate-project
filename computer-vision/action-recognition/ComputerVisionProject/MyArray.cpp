#include "MyArray.h"


MyArray::MyArray(void)
{
	length = 0;
	data = NULL;
}


MyArray::MyArray(int length)
{
	this->length = length;

	data = new float [length];

	init();
}


MyArray::MyArray(float* raw, int length)
{
	this->length = length;

	data = raw;
}


MyArray::~MyArray(void)
{
	if(data == NULL)
		return;

	delete []data;
}


void MyArray::init()
{
	for(int i = 0; i < length; i++)
		data[i] = 0;
}

MyArray& MyArray::operator=(const MyArray& src)
{
	if(data != NULL)
	{
		delete []data;
	}

	length = src.length;

	int i;

	data = new float [length];
	
	for(i = 0; i < length; i++)
		data[i] = src.data[i];

	return *this;
}

void MyArray::getData(float* src, int length)
{
	if(data != NULL)
		delete []data;

	this->length = length;

	data = src;
}