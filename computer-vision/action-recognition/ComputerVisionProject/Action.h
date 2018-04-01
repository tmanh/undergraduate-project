#pragma once

#include "Libraries\Headers\opencv2\core\core.hpp"
#include "Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "Libraries\Headers\opencv2\imgproc\imgproc.hpp"
#include "Libraries\Headers\opencv2\features2d\features2d.hpp"
#include "Libraries\Headers\opencv2\nonfree\features2d.hpp"
#include "Libraries\Headers\opencv2\flann\flann.hpp"
#include "Libraries\Headers\opencv2\ml\ml.hpp"
#include "Libraries\Headers\opencv2\objdetect\objdetect.hpp"
#include "Libraries\Headers\opencv2\gpu\gpu.hpp"

#include "DepthMapSkt.h"
#include "DepthMapSktBinFileIO.h"

#include <fstream>

using namespace cv;
using namespace std;

#define	dim	3
#define _gesture_thresh 30
#define _depth_gesture_thresh 150
#define _minHessian 600
#define _number_point_thresh 2500
#define _number_point_depth_thresh 2500
#define esilon 2.71828182846
#define PI 3.14159265359
#define Q 0.08726646259f

class Action
{
public:
	Action(void);
	~Action(void);

	int skeframes;	//so frame chua trong file ske
	int skepoints;	//so points chua trong frame cua file ske

	int nofs; //so frame chua trong file depth
	int ncols;
	int nrows;

	void loadDepth(string rbg_fname, string depth_fname, Mat& fMHI, Mat& bMHI);
	Mat load(string rbg_fname, string depth_fname);
	void loadHOG(string rbg_fname, string depth_fname, Mat& HOG);
	
	void readSkeletonFileHeader(ifstream &fin);
	void readSkeleton(ifstream &fin, float** skeleton);
	
	int getGestureRegion(Mat &beforeScene, Mat &afterScene, Mat &result, Mat &depth, int &meanDepthMotion);
	int getGesturDepthRegion(Mat &beforeScene, Mat &afterScene, Mat& MotionRGB, Mat &resultIncrease, Mat &resultDecrease, Mat &depth, int &meanDepthMotion);
	int getGesturDepthRegion2(CDepthMapSkt &beforeScene, CDepthMapSkt &afterScene, Mat& MotionRGB, Mat &resultIncrease, Mat &resultDecrease);

	void getShape(int mean_depth, Mat& depth, Mat& newmotion);

	Rect roiDepth; Rect roiRGB;
	Size size;
private:
	int ipadding;
	float fpadding;

	int max(const int &a, const int &b)
	{
		if(a >= b)
			return a;
		return b;
	}

	//Ham luong hoa
	void quantize(uchar &R)
	{
		R = (R / 128) * 128 + 64;
	}

	//Ham luong hoa
	void quantize(uchar* data, int width, int height)
	{
		int size = width * height;

		for(int i = 0; i < size; i++)
			quantize(data[i]);
	}

	void removeKeyPoint(Mat &depth, vector<KeyPoint> &keyPoint, int meanDepthMotion, bool control);
	int round(float src);
	void quantize(CDepthMapSkt& depthMap, Mat &result, int size);
	float ConvolutionOnePixel(uchar* img, int &width, int &height,
							float** kernel, int m, int n, int x, int y);
	void Convolution(uchar* img, int width, int height,
					float** kernel, int m, int n, float** result);
	void horizontalPrewitt(uchar* img, int width, int height, float** result);
	void verticalPrewitt(uchar* img, int width, int height, float** result);
	void findEdgeDirection(uchar* img, int width, int height,
							float** Gradient, float** Direction);
	void correlogramDirection(int width, int height, int d, int n,
							float** Direction, float* correlogram, float* Histogram);
	void getNeighbor(int width, int height, vector<Point> &neighbor, int &x, int &y, int &d, int &di, int &dj);
	Mat compute(Mat image);
	Mat compute2(Mat image);
};