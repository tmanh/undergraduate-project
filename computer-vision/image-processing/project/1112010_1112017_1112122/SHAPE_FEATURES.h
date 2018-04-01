#pragma once

#include "..\Libraries\Headers\opencv2\core\core.hpp"
#include "..\Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "..\Libraries\Headers\opencv2\imgproc\imgproc.hpp"
#include "..\Libraries\Headers\opencv2\features2d\features2d.hpp"
#include "..\Libraries\Headers\opencv2\nonfree\nonfree.hpp"

#include "GUI.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <fstream>

using namespace cv;
using namespace std;

#define PI 3.14159265359F
#define Q 0.08726646259f

namespace My1112010_1112017_1112122 {
	ref class SHAPE_FEATURES
	{
	private:
		System::String^ s_image;
		System::String^ s_image2;
		GUI^ _gui;
	public:
		SHAPE_FEATURES(void)
		{
		}
	#pragma region Function
		std::string getString(System::String^ x)
		{
			std::string tmp;
			for(int i = 0; i < x->Length; i++)
			tmp += (char)x[i];
			return tmp;
		}

		void getImage(System::String^ s)
		{
			if(s_image != nullptr)
				delete s_image;
			s_image = s;
		}

		void getImage2(System::String^ s)
		{
			if(s_image2 != nullptr)
				delete s_image2;
			s_image2 = s;
		}
	#pragma endregion
	#pragma region Quantization
		//Ham luong hoa
		int quantize(uchar &R, uchar &G, uchar &B, const int &bin)
		{
			return (int)((float)R/256*bin)*bin*bin + (int)((float)G/256*bin)*bin + (int)((float)B/256*bin);
		}
	#pragma endregion
	#pragma region Edge Direction Histogram
		//Convolution cua 1 pixel
		//m,n: kich thuoc cua kernel (mxn)
		float ConvolutionOnePixel(uchar* img, int &width, int &height,
								 float** kernel, int m, int n, int x, int y)
		{
			float result = 0;
			int count = 0;

			int cols = n/2;
			int rows = m/2;
			int index;
			int px, py;

			for(int i = -rows; i <= rows; i++)
			{
				for(int j = -cols; j <= cols; j++)
				{
					px = i+x;
					py = j+y;
					if(px < 0 || py < 0 || px >= height || py >= width)
						continue;

					index = px * width + py;

					count++;
					result += img[index] * kernel[rows-i][cols-j];
				}
			}

			return result;
		}

		//Convolution
		//m,n: kich thuoc cua kernel (mxn)
		//result: ma tran ket qua tich chap
		void Convolution(uchar* img, int width, int height,
						 float** kernel, int m, int n, float** result)
		{
			for(int i = 0; i < height; i++)
				for(int j = 0; j < width; j++)
					result[i][j] = (float)ConvolutionOnePixel(img, width, height, kernel, m, n, i, j);
		}

		//tinh dao ham theo phuong doc
		void horizontalPrewitt(uchar* img, int width, int height, float** result)
		{
			float** H = new float* [3];
			for(int i = 0; i < 3; i++)
				H[i] = new float [3];

			H[0][0] = H[1][0] = H[2][0] = -1;
			H[0][1] = H[1][1] = H[2][1] = 0;
			H[0][2] = H[1][2] = H[2][2] = 1;

			Convolution(img, width, height, H, 3, 3, result);

			for(int i = 0; i < 3; i++)
				delete []H[i];
			delete []H;
		}

		//tinh dao ham theo phuong ngang
		void verticalPrewitt(uchar* img, int width, int height, float** result)
		{
			float** H = new float* [3];
			for(int i = 0; i < 3; i++)
				H[i] = new float [3];

			H[0][0] = H[0][1] = H[0][2] = -1;
			H[1][0] = H[1][1] = H[1][2] = 0;
			H[2][0] = H[2][1] = H[2][2] = 1;

			Convolution(img, width, height, H, 3, 3, result);

			for(int i = 0; i < 3; i++)
				delete []H[i];
			delete []H;
		}

		//tim ma tran luu bien canh va huong
		//Gradient, Direction: bien do, huong canh
		void findEdgeDirection(uchar* img, int width, int height,
								 float** Gradient, float** Direction)
		{
			//khai bao ma tran chua dao ham doc va ngang
			float** Horizontal, **Vertical;

			Horizontal = new float* [height];
			Vertical = new float* [height];

			for(int i = 0; i < height; i++)
			{
				Horizontal[i] = new float [width];
				Vertical[i] = new float [width];
			}

			//tinh dao ham ngang va doc
			horizontalPrewitt(img, width, height, Horizontal);
			verticalPrewitt(img, width, height, Vertical);

			//tinh gradient va oriented
			for(int i = 0; i < height; i++)
				for(int j = 0; j < width; j++)
				{
					Gradient[i][j] = (abs(Horizontal[i][j]) + abs(Vertical[i][j])) / 2;
				
					if(Horizontal[i][j] == 0)
					{
						if(Vertical[i][j] == 0)
							Direction[i][j] = -1;
						else
							Direction[i][j] = PI/2;
					}
					else
					{
						if(Horizontal[i][j] > 0 && Vertical[i][j] >= 0)
							Direction[i][j] = atan(Vertical[i][j]/Horizontal[i][j]);
						else if(Horizontal[i][j] > 0 && Vertical[i][j] < 0)
							Direction[i][j] = atan(Vertical[i][j]/Horizontal[i][j]) + PI;
						else if(Horizontal[i][j] < 0 && Vertical[i][j] < 0)
							Direction[i][j] = atan(Vertical[i][j]/Horizontal[i][j]) + PI;
						else
							Direction[i][j] = atan(Vertical[i][j]/Horizontal[i][j]) + 2 * PI;
					}
				}

			//huy du lieu
			for(int i = 0; i < height; i++)
			{
				delete []Horizontal[i];
				delete []Vertical[i];
			}
			delete []Horizontal;
			delete []Vertical;
		}

		//tim luoc do huong canh
		//Gradient, Oriented: bien do, huong canh
		//Histogram: luoc do ket qua
		int HistogramEdgeDirection(int width, int height, int t, int n,
								   float** Gradient, float** Direction, float* Histogram)
		{
			for(int i = 0; i < n; i++)
				Histogram[i] = 0;

			int count = 0, tmp;
			int size = width * height;

			for(int i = 0; i < height; i++)
			{
				for(int j = 0; j < width; j++)
				{
					if(Gradient[i][j] > t && Direction[i][j] != -1)
					{
						tmp = (int)(Direction[i][j]/Q);
						Histogram[tmp]++;
						count++;
					}
				}
			}

			for(int i = 0; i < n; i++)
				Histogram[i] /= size;
			Histogram[72] = ((float)size - count) / size;
			return count;
		}

		void showHistogramEdgeDirection(int t)
		{
			Mat image = imread(getString(s_image), CV_8UC1);

			imshow("Image", image);
			waitKey(10);

			float** Gradient, **Direction;

			Gradient = new float* [image.rows];
			Direction = new float* [image.rows];
			for(int i = 0; i < image.rows; i++)
			{
				Gradient[i] = new float [image.cols];
				Direction[i] = new float [image.cols];
			}

			//khai bao mang luu ket qua vector lien ket mau
			float* EdgeDirection = new float[73];

			for(int i = 0; i < 73; i++)
				EdgeDirection[i] = 0;

			uchar* img = (uchar*)image.data;

			findEdgeDirection(img, image.cols, image.rows,
							  Gradient, Direction);

			//goi ham tinh vector lien ket mau
			HistogramEdgeDirection(image.cols, image.rows, t, 73,
								   Gradient, Direction, EdgeDirection);
			_gui->DrawEdgeHistogram(EdgeDirection, strdup(getString("Luoc do he so goc: " + s_image).c_str()));

			//Huy du lieu da xin cap phat
			delete []EdgeDirection;

			for(int i = 0; i < image.rows; i++)
			{
				delete []Gradient[i];
				delete []Direction[i];
			}
			delete []Gradient;
			delete []Direction;
		}
	#pragma endregion
	#pragma region Edge Direction Coherence Vector
	public:
	//0: coherence
	//1: incoherence
	void showCoherenceVector()
	{
		Mat image = imread(getString(s_image), CV_8UC1);

		imshow("Image", image);
		waitKey(10);

		float** Gradient, **Direction;

		Gradient = new float* [image.rows];
		Direction = new float* [image.rows];
		for(int i = 0; i < image.rows; i++)
		{
			Gradient[i] = new float [image.cols];
			Direction[i] = new float [image.cols];
		}

		uchar* img = (uchar*)image.data;

		findEdgeDirection(img, image.cols, image.rows,
						  Gradient, Direction);

		float* EdgeDirection = new float[73];

		for(int i = 0; i < 73; i++)
			EdgeDirection[i] = 0;

		//goi ham tinh vector lien ket mau
		int one_size = HistogramEdgeDirection(image.cols, image.rows, 0, 73,
							   Gradient, Direction, EdgeDirection);

		//khai bao mang luu ket qua vector lien ket mau
		float** CoherenceVector = new float* [2];
		for(int i = 0; i < 2; i++)
			CoherenceVector[i] = new float [72];

		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 72; j++)
				CoherenceVector[i][j] = 0;

		one_size = image.cols * image.rows / 1000;

		//goi ham tinh vector lien ket mau
		computeCoherenceVector(one_size, Direction, image.cols, image.rows, CoherenceVector);
		_gui->DrawCoherenceVector(CoherenceVector);

		//Huy du lieu da xin cap phat
		delete []EdgeDirection;

		for(int i = 0; i < 2; i++)
			delete []CoherenceVector[i];
		delete []CoherenceVector;

		for(int i = 0; i < image.rows; i++)
		{
			delete []Gradient[i];
			delete []Direction[i];
		}
		delete []Gradient;
		delete []Direction;
	}

	public:
	void computeCoherenceVector(int one_size, float** Direction, int width, int height, float** CoherenceVector)
	{
		int k, size = width * height;
		float tmp;

		//khai bao mang luu lich su duyet hinh
		bool **checkMat = new bool* [height];
		for(int i = 0; i < height; i++)
			checkMat[i] = new bool [width];

		//khoi gan gia tri cho checkMat
		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
				checkMat[i][j] = 0;

		//duyet anh frame
		for(int i = 0; i <height; i++)
		{
			for(int j = 0; j < width; j++)
			{	
				if(checkMat[i][j] == 1)
					continue;

				checkMat[i][j] = 1;

				k = 0;
				tmp = Direction[i][j] / Q;
				if(tmp >= 0)
				{
					if(checkCoherence( Direction, width, height,
									   i, j, checkMat, k, one_size,
									   tmp))
					{
						CoherenceVector[0][(int)(Direction[i][j] / Q)] += k;
					}
					else
					{
						CoherenceVector[1][(int)(Direction[i][j] / Q)] += k;
					}
				}
			}
		}

		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 72; j++)
				CoherenceVector[i][j] /= size;

		for(int i = 0; i < height; i++)
			delete []checkMat[i];
		delete []checkMat;
	}

	public:
	bool checkCoherence(float** Direction, int &width, int &height,
						int i, int j, bool** checkMat, int &k,
						int &size, float &quanti)
	{
		queue <int>qi;
		queue <int>qj;

		//khai bao bien
		int ti, tj;

		qi.push(i);
		qj.push(j);

		while(!qi.empty())
		{
			ti = qi.front(); tj = qj.front();
			qi.pop(); qj.pop();

			k++;

			//vong lap duyet kiem tra cac diem tuong dong mau hay khong
			for(int ki = -1; ki < 2; ki++)
			{
				for(int kj = -1; kj < 2; kj++)
				{
					//neu da duoc duyet thi se bo qua
					if(ti + ki < 0 || tj + kj < 0)
						continue;
					if(ti + ki >= height || tj + kj >= width)
						continue;
					if(checkMat[ti + ki][tj + kj] == 1)
						continue;

					if( (int)Direction[ti + ki][tj + kj] / Q == (int)quanti)
					{
						checkMat[ti + ki][tj + kj] = 1;

						qi.push(ti + ki);
						qj.push(tj + kj);
					}
				}
			}
		}

		if(k > size)
			return true;
		return false;
	}
	#pragma endregion
	#pragma region SIFT
	public:
		void showSIFT(int alpha)
		{
			Mat image = imread(getString(s_image));
			cvtColor(image, image, CV_BGR2GRAY);
			Mat image2 = imread(getString(s_image2));
			cvtColor(image2, image2, CV_BGR2GRAY);

			SiftFeatureDetector _detector;
			SiftDescriptorExtractor _extractor; 

			//Sift for Image one (Detector + Descripter)
			vector<KeyPoint> key_points_1;
			vector<KeyPoint> key_points_2;

			Mat descriptors_1; Mat descriptors_2;

			_detector.detect(image, key_points_1);
			_extractor.compute(image, key_points_1, descriptors_1);
			
			_detector.detect(image2, key_points_2);
			_extractor.compute(image2, key_points_2, descriptors_2);

			//Matching
			BFMatcher matcher(NORM_L2);
			vector< DMatch > matches;
			matcher.match( descriptors_1, descriptors_2, matches );
			
			//find min distance
			int min_distance = 9999;

			for(int i = 0; i < matches.size(); i++)
			{
				if(min_distance > matches[i].distance)
					min_distance = matches[i].distance;
			}

			//remove bad match
			for(int i = 0; i < matches.size(); i++)
			{
				if(matches[i].distance > alpha * min_distance)
				{
					matches.erase(matches.begin() + i);
					i--;
				}
			}

			//Draw matches
			Mat img_matches;
			drawMatches( image, key_points_1, image2, key_points_2, matches, img_matches );
			
			//Show KeyPoint of Image one and Image two.
			Mat output_img_1, output_img_2;
			
			drawKeypoints(image, key_points_1, output_img_1);
			drawKeypoints(image2, key_points_2, output_img_2);
			
			imshow("Output_1", output_img_1);
			imshow("Output_2",output_img_2);
			
			imshow("Matching",img_matches);

			waitKey(0);
		}
	#pragma endregion
	};
}
