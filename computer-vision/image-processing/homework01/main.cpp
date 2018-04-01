#include "PixelOperators.h"

int main(int argc, char* argv[])
{
	Mat image, gray, result;

	if (argc < 3)
	{
		cout<<"Khong du tham so de chay";
		return -1;
	}

	//Thay đổi độ tương phản cho ảnh
	else if (strcmp(argv[2],"-c") == 0)
	{
		image = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
		if(checkMat(image))
			return -1;

		DrawHistogram(image, "original");
		displayImage(image,"Original Image");

		result = contrast(image, atof(argv[3]));

		DrawHistogram(result, "result");
		displayImage(result,"Changing Constrast Image");
		cvWaitKey(0);
	}

	//Tạo ảnh âm bản cho ảnh
	else if (strcmp(argv[2],"-i") == 0)
	{
		image = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
		if(checkMat(image))
			return -1;

		DrawHistogram(image, "original");
		displayImage(image,"Original Image");

		result = invertImage(image);
		
		DrawHistogram(result, "result");
		displayImage(result,"Invert Image");
		cvWaitKey(0);
	}
	
	//Thay đổi độ sáng cho ảnh xám
	if (strcmp(argv[2],"-b") == 0)
	{
		image = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
		if(checkMat(image))
			return -1;

		DrawHistogram(image, "original");
		displayImage(image,"Original Image");

		//result = changePixelIntensity2(image,atoi(argv[3]));
		//bilateralFilter(image,image,1,1,1);
		
		//DrawHistogram(image, "result");
		//displayImage(image,"Changing Brightness Gray Image");
		cvWaitKey(0);
	}

	return 1;
}