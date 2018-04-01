#include "myBOW.h"


myBOW::myBOW(void)
{
	number_of_word = 0;
}


myBOW::~myBOW(void)
{
}

void myBOW::getData(float* srcData, int length, MyArray srcLabel)
{
	raw_data.getData(srcData, length);
	label_data = srcLabel;
}


MyArray myBOW::getWord()
{
	MyArray Histogram(number_of_word);

	//duyet toan bo du lieu
	int i, j, k = 0;
	for(i = 0; i < label_data.length; i++)
	{
		for(j = 0; j < label_data.data[i]; j++)
		{
			Histogram.data[computeCluster( i , j )]++;
		}
	}

	return Histogram;
}

int myBOW::computeCluster(int index, int length)
{
	return 1;
}