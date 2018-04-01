#ifndef _Histogram_
#define _Histogram_

#include "PixelOperators.h"
#include <math.h>

// cân bằng histogram cho ảnh xám
Mat GrayEqualization(Mat image, char* name = "Ham tich luy", char* his_name = "Histogram", int maxN = 255);
// cân bằng histogram cho ảnh RGB
Mat RGBEqualization(Mat image);
// cân bằng histogram cho ảnh HSV
Mat HSVEqualization(Mat image);
// cân bằng histogram cho ảnh HLS
Mat HLSEqualization(Mat image);
// cân bằng histogram cho ảnh YCbCr
Mat YCbCrEqualization(Mat image);
// cân bằng histogram cho ảnh Lab
Mat LabEqualization(Mat image);
// cân bằng histogram cho ảnh Luv
Mat LuvEqualization(Mat image);
// cân bằng histogram cho ảnh CYMK
Mat CYMKEqualization(Mat image);
// cân bằng histogram cho ảnh YUV
Mat YUVEqualization(Mat image);

//tinh ham tich luy
void countCumulativeDistribution(int data[], int n, int src[]);
//tinh ham chuan hoa
void computeEqualization(int data[], int n, int src[], int maxN = 255);
//chuan hoa ham tich luy
void ECumulativeDistribution(int data[], int n);
//ve histogram truoc
void DrawHistogramBefore(int data[], char* his_name);
//ve histogram sau
void DrawHistogramAfter(int data[], char* his_name);
//tao anh moi da duoc can bang
Mat createEqualizationImage(Mat image, int equalization[]);
//khoi tao cac gia tri cho ham can bang
void initEqualization(	Mat image, char* his_name, int maxN,
						int original[], int CumulativeDistribution[],
						int Equalization[]);
//xuat ket qua cho ham can bang
void printEqualization(	Mat image, char* name, char* his_name, int maxN,
						int original[], int CumulativeDistribution[],
						int Equalization[]);
#endif