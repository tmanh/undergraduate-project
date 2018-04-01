#include "PixelOperators.h"
#include "Histogram.h"
#include "Filter.h"
#include <time.h>

using namespace std;

#define MIN_SIZE	3

int main(int argc, char* argv[])
{
	Mat image, gray, result;
	int n = -1, s = 0;
	int **mask;

	if (argc < 3)
	{
		cout<<"Khong du tham so de chay" << endl;
		return -1;
	}

	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if(checkMat(image))
		return -1;

	DrawHistogram(image, "original");
	displayImage(image,"Original Image");

	if(strcmp(argv[2],"filtmedian") == 0)
	{
		result = median(image, MIN_SIZE);
	}
	if(strcmp(argv[2],"filtlowpass") == 0)
	{
		s = read(argv[3], mask, n);
		if(n > 0)
			result = cvl(image, mask, n, s);
	}
	if(strcmp(argv[2],"filtroberts") == 0)
	{
		result = filthighroberts(image, MIN_SIZE);
	}
	if(strcmp(argv[2],"filtprewitt") == 0)
	{
		result = filthighprewitt(image, MIN_SIZE);
	}
	if(strcmp(argv[2],"filtsobel") == 0)
	{
		result = filthighsobel(image, MIN_SIZE);
	}
	if(strcmp(argv[2],"filthighboost") == 0)
	{
		result = filthighavg(image, MIN_SIZE, atoi(argv[3]));
	}
	if(strcmp(argv[2],"filthighavg") == 0)
	{
		result = filthighavg(image, 3, 1);
	}

	if(n > 0)
	{
		for(int i = 0; i < n; i++)
			delete []mask[i];
		delete []mask;
	}

	DrawHistogram(result, "Result");
	displayImage(result,"Result Image");
	cvWaitKey(0);
}