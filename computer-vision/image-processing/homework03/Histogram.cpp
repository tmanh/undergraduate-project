/*
THIS IS MADE BY ddkhoa@fit.hcmus.edu.vn
YOU CAN USE IT WITH YOUR OWN RESPONSIBILITY
PLEASE KEEP THIS AUTHOR INFORMATION WHEN SHARING IT
THANK YOU!
*/

#include "Histogram.h"

//tinh ham tich luy
void countCumulativeDistribution(int data[], int n, int src[])
{
	data[0] = src[0];
	for(int i = 1; i < n; i++)
	{
		data[i] = data[i-1] + src[i];
	}
}

//tinh ham chuan hoa
void computeEqualization(int data[], int n, int src[])
{
	int maxCD;				// max ham tich luy
	maxCD = src[MAX];		//lay gia tri max cua ham tich luy

	for(int i = 0; i < n; i++)
	{
		data[i] = (int)((float)src[i]*255/maxCD + 0.5);
	}
}

// cân bằng histogram cho ảnh xám
Mat GrayEqualization(Mat image, char* name)
{
	int original[256];
	int CumulativeDistribution[256];	//mảng cộng dồn điềm ảnh
	int Equalization[256];				// mảng chuẩn hóa

	init(original, MAX, 0);
	countHistogram(image, original);
	countCumulativeDistribution(CumulativeDistribution, MAX_N, original);
	computeEqualization(Equalization, MAX_N, CumulativeDistribution);

	// tạo ảnh mới mà có số điểm ảnh cân bằng--
	Mat result(image.rows, image.cols,image.type());

	uchar* pixelPtr_image = (uchar*)image.data;
	uchar* pixelPtr_mat = (uchar*)result.data;

	int rowIndex;
	for(int i = 0; i < image.rows; i++)
	{
		rowIndex = i * image.step;
		for(int j = 0; j < image.cols; j++)
		{	
			pixelPtr_mat[rowIndex + j] = Equalization[pixelPtr_image[rowIndex + j]];
		}
	}

	ECumulativeDistribution(CumulativeDistribution, MAX_N);
	DrawHistogram(CumulativeDistribution, name);

	return result;
}

// cân bằng histogram cho ảnh RGB
Mat RGBEqualization(Mat image)
{
	Mat Color[3], result;
	split(image, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy RGB - R");
	Color[1] = GrayEqualization(Color[1], "Ham tich luy RGB - B");
	Color[2] = GrayEqualization(Color[2], "Ham tich luy RGB - G");

	merge(Color, 3, result);
	return result;
}

// cân bằng histogram cho ảnh HSV
Mat HSVEqualization(Mat image)
{
	Mat Color[3], result;
	cvtColor(image, result, CV_RGB2HSV);
	split(result, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy HSV - H");

	merge(Color, 3, result);
	cvtColor(result, result, CV_HSV2RGB);
	return result;
}

// cân bằng histogram cho ảnh HLS
Mat HLSEqualization(Mat image)
{
	Mat Color[3], result;
	cvtColor(image, result, CV_RGB2HLS);
	split(result, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy HLS - H");

	merge(Color, 3, result);
	cvtColor(result, result, CV_HLS2RGB);
	return result;
}

// cân bằng histogram cho ảnh ycbcr
Mat YCbCrEqualization(Mat image)
{
	Mat Color[3], result;
	result = RGB2YCbCr(image);
	split(result, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy YCbCr - Y");

	merge(Color, 3, result);
	result = YCbCr2RGB(result);
	return result;
}

// cân bằng histogram cho ảnh Lab
Mat LabEqualization(Mat image)
{
	Mat Color[3], result;
	cvtColor(image, result, CV_RGB2Lab);
	split(result, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy Lab - L");

	merge(Color, 3, result);
	cvtColor(result, result, CV_Lab2RGB);
	return result;
}

// cân bằng histogram cho ảnh Luv
Mat LuvEqualization(Mat image)
{
	Mat Color[3], result;
	cvtColor(image, result, CV_RGB2Luv);
	split(result, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy L");

	merge(Color, 3, result);
	cvtColor(result, result, CV_Luv2RGB);
	return result;
}

// cân bằng histogram cho ảnh CYMK
Mat CYMKEqualization(Mat image)
{
	Mat Color[4], result;
	result = RGB2CYMK(image);
	split(result, Color);

	Color[3] = GrayEqualization(Color[3], "Ham tich luy CYMK - K");

	merge(Color, 4, result);
	result = CYMK2RGB(result);
	return result;
}

// cân bằng histogram cho ảnh YUV
Mat YUVEqualization(Mat image)
{
	Mat Color[3], result;
	cvtColor(image, result, CV_RGB2YUV);
	split(result, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy YUV - Y");

	merge(Color, 3, result);
	cvtColor(result, result, CV_YUV2RGB);
	return result;
}

//chuan hoa ham tich luy
void ECumulativeDistribution(int data[], int n)
{
	int max_CD = data[MAX];

	for(int i = 0; i < n; i++)
		data[i] = 199 * data[i] / max_CD;
}