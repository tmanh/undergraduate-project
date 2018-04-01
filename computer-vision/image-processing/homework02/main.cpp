#include "PixelOperators.h"
#include "Histogram.h"

int main(int argc, char* argv[])
{
	Mat image, gray, result;

	if (argc < 3)
	{
		cout<<"Khong du tham so de chay" << endl;
		return -1;
	}

	image = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	if(checkMat(image))
		return -1;

	if(strcmp(argv[2],"hq-gray") == 0)
	{
		result = GrayEqualization(image, "Ham tich luy Gray");

		DrawHistogram(result, "result");
		displayImage(result,"Gray Image Result");
	}
	if(strcmp(argv[2],"hq-rgb") == 0 || strcmp(argv[2],"hq-color") == 0)
	{
		result = RGBEqualization(image);
		
		DrawHistogram(result, "result");
		displayImage(result,"RGB Image Result");
	}
	if(strcmp(argv[2],"hq-hsv") == 0 || strcmp(argv[2],"hq-color") == 0)
	{
		result = HSVEqualization(image);
		
		displayImage(result,"HSV Image Result");
	}
	if(strcmp(argv[2],"hq-hls") == 0 || strcmp(argv[2],"hq-color") == 0)
	{
		result = HLSEqualization(image);
		
		DrawHistogram(result, "HLS result");
		displayImage(result,"Image Result");
	}
	if(strcmp(argv[2],"hq-ycbcr") == 0 || strcmp(argv[2],"hq-color") == 0)
	{
		result = YCbCrEqualization(image);
		
		DrawHistogram(result, "result");
		displayImage(result,"YCbCr Image Result");
	}
	if(strcmp(argv[2],"hq-lab") == 0 || strcmp(argv[2],"hq-color") == 0)
	{
		result = LabEqualization(image);
		
		DrawHistogram(result, "result");
		displayImage(result,"Lab Image Result");
	}
	if(strcmp(argv[2],"hq-luv") == 0 || strcmp(argv[2],"hq-color") == 0)
	{
		result = LuvEqualization(image);
		
		DrawHistogram(result, "result");
		displayImage(result,"Luv Image Result");
	}
	if(strcmp(argv[2],"hq-cymk") == 0 || strcmp(argv[2],"hq-color") == 0)
	{
		result = CYMKEqualization(image);
		
		DrawHistogram(result, "result");
		displayImage(result,"Cymk Image Result");
	}
	if(strcmp(argv[2],"hq-yuv") == 0 || strcmp(argv[2],"hq-color") == 0)
	{
		result = YUVEqualization(image);
		
		DrawHistogram(result, "result");
		displayImage(result,"Yuv Image Result");
	}
	cvWaitKey(0);
}