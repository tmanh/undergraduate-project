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
void computeEqualization(int data[], int n, int src[], int maxN)
{
	int maxCD;				// max ham tich luy
	maxCD = src[MAX];		//lay gia tri max cua ham tich luy

	int tmp;
	for(int i = 0; i < n; i++)
	{
		tmp = (int)((float)src[i]*maxN/maxCD + 0.5);
		if(tmp <= maxN)
			data[i] = tmp;
		else
			data[i] = maxN;
	}
}

//ve histogram truoc
void DrawHistogramBefore(int data[], char* his_name)
{
	char tmp[255];

	strcpy(tmp, his_name);
	strcat(tmp, " before");
	ECumulativeDistribution(data, MAX_N);
	DrawHistogram(data, tmp);
}

//ve histogram sau
void DrawHistogramAfter(int data[], char* his_name)
{
	char tmp[255];

	strcpy(tmp, his_name);
	strcat(tmp, " after");
	ECumulativeDistribution(data, MAX_N);
	DrawHistogram(data, tmp);
}

//tao anh moi da duoc can bang
Mat createEqualizationImage(Mat image, int equalization[])
{
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
			pixelPtr_mat[rowIndex + j] = equalization[pixelPtr_image[rowIndex + j]];
		}
	}

	return result;
}

//khoi tao cac gia tri cho ham can bang
void initEqualization(	Mat image, char* his_name, int maxN,
						int original[], int CumulativeDistribution[],
						int Equalization[])
{
	initTable(original, MAX, 0);
	countHistogram(image, original);
	DrawHistogramBefore(original, his_name);

	countCumulativeDistribution(CumulativeDistribution, MAX_N, original);
	computeEqualization(Equalization, MAX_N, CumulativeDistribution, maxN);
}

//xuat ket qua cho ham can bang
void printEqualization(	Mat image, char* name, char* his_name, int maxN,
						int original[], int CumulativeDistribution[],
						int Equalization[])
{
	ECumulativeDistribution(CumulativeDistribution, MAX_N);
	DrawHistogramBefore(CumulativeDistribution, name);
	DrawHistogramAfter(Equalization, name);

	initTable(original, MAX, 0);
	countHistogram(image, original);
	DrawHistogramAfter(original, his_name);
}

// cân bằng histogram cho ảnh xám
Mat GrayEqualization(Mat image, char* name, char* his_name, int maxN)
{
	int original[256];
	int CumulativeDistribution[256];	//mảng cộng dồn điềm ảnh
	int Equalization[256];				// mảng chuẩn hóa

	initEqualization(	image, his_name, maxN, original,
						CumulativeDistribution, Equalization);

	Mat result = createEqualizationImage(image, Equalization);

	printEqualization(	image, name, his_name, maxN, original,
						CumulativeDistribution, Equalization);

	return result;
}

// cân bằng histogram cho ảnh RGB
Mat RGBEqualization(Mat image)
{
	Mat Color[3], result;
	split(image, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy RGB - R", "Histogram - R");
	Color[1] = GrayEqualization(Color[1], "Ham tich luy RGB - G", "Histogram - G");
	Color[2] = GrayEqualization(Color[2], "Ham tich luy RGB - B", "Histogram - B");

	merge(Color, 3, result);
	return result;
}

// cân bằng histogram cho ảnh HSV
Mat HSVEqualization(Mat image)
{
	Mat Color[3], result;
	cvtColor(image, result, CV_RGB2HSV);
	split(result, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy HSV - H", "Histogram - H", 179);

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

	Color[0] = GrayEqualization(Color[0], "Ham tich luy HLS - H", "Histogram - H", 179);

	merge(Color, 3, result);
	cvtColor(result, result, CV_HLS2RGB);
	return result;
}

// cân bằng histogram cho ảnh ycbcr
Mat YCbCrEqualization(Mat image)
{
	Mat Color[3], result;
	cvtColor(image, result, CV_RGB2YCrCb);
	split(result, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy YCbCr - Y", "Histogram - Y");

	merge(Color, 3, result);
	cvtColor(result, result, CV_YCrCb2RGB);
	return result;
}

// cân bằng histogram cho ảnh Lab
Mat LabEqualization(Mat image)
{
	Mat Color[3], result;
	cvtColor(image, result, CV_RGB2Lab);
	split(result, Color);

	Color[0] = GrayEqualization(Color[0], "Ham tich luy Lab - L", "Histogram - L");

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

	Color[0] = GrayEqualization(Color[0], "Ham tich luy L", "Histogram - L");

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

	Color[3] = GrayEqualization(Color[3], "Ham tich luy CYMK - K", "Histogram - K");

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

	Color[0] = GrayEqualization(Color[0], "Ham tich luy YUV - Y", "Histogram - Y");

	merge(Color, 3, result);
	cvtColor(result, result, CV_YUV2RGB);
	return result;
}

//chuan hoa ham tich luy
void ECumulativeDistribution(int data[], int n)
{
	int max_CD = max(data);

	for(int i = 0; i < n; i++)
		data[i] = 199 * data[i] / max_CD;
}