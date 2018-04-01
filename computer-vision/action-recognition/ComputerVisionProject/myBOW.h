#pragma once

#include "MyMat.h"
#include "MyArray.h"

class myBOW
{
#pragma region Data Declaration
public:
	int number_of_word;

	MyArray raw_data;
	MyArray label_data;
	MyArray word;
#pragma endregion
#pragma region Function Declaration
public:
	myBOW(void);
	~myBOW(void);

	//ham luu du lieu
	void getData(float* srcData, int length, MyArray srcLabel);
	//ham luu word
	void calWord();
	//ham tinh descriptor video
	MyArray getWord();

private:
	//ham tinh cluster mot tu thuoc ve
	int computeCluster(int index, int length);

#pragma endregion
};

