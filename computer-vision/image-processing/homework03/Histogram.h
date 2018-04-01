#ifndef _Histogram_
#define _Histogram_

#include "PixelOperators.h"
#include <math.h>

// cân bằng histogram cho ảnh xám
Mat GrayEqualization(Mat image, char* name = "Ham tich luy");
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
void computeEqualization(int data[], int n, int src[]);
//chuan hoa ham tich luy
void ECumulativeDistribution(int data[], int n);
#endif