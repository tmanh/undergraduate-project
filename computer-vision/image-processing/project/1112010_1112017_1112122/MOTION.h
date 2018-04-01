/*
	THIS IS MADE BY truongminhanh93.it@gmail.com
	YOU CAN USE IT WITH YOUR OWN RESPONSIBILITY
	PLEASE KEEP THIS AUTHOR INFORMATION WHEN SHARING IT
	THANK YOU!
*/

#pragma once

#include <iostream>
#include <cmath>

#include "..\Libraries\Headers\opencv2\core\core.hpp"
#include "..\Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "..\Libraries\Headers\opencv2\imgproc\imgproc.hpp"

#include "GUI.h"

using namespace cv;
using namespace std;

#define	d	5	//maximum distance between two pixel
#define	window_size	3	//maximum size of iterator window
#define	max_mse	5000	//define maximum mse
#define	thresh_mse	2000	//threshold of mse, if lower than it the distance will be accepted
#define max_distance 1000	//threshold of distance, if lower than it, the distance will be accepted
#define thresh_dif	30		//threshold of difference between two pixel, if higher than it, the position will be
							//approved that is two pixel of two object

namespace My1112010_1112017_1112122 {
	ref class MOTION
	{
#pragma region Data
	private:
		GUI^ _gui;
		System::String^ s_video;
		System::String^ s_image1;
		System::String^ s_image2;
#pragma endregion
#pragma region Function
	public:
		//tim max
		//data: mang du lieu
		int round(const float &data)
		{
			return int(data);
		}

		std::string getString(System::String^ x)
		{
			std::string tmp;
			for(int i = 0; i < x->Length; i++)
			tmp += (char)x[i];
			return tmp;
		}

		void getVideo(System::String^ s)
		{
			if(s_video != nullptr)
				delete s_video;
			s_video = s;
		}

		void getImage1(System::String^ s)
		{
			if(s_image1 != nullptr)
				delete s_image1;
			s_image1 = s;
		}

		void getImage2(System::String^ s)
		{
			if(s_image2 != nullptr)
				delete s_image2;
			s_image2 = s;
		}
#pragma endregion
	public:
		void test()
		{
			/*
				Note: Because the motion very small, the result picture very dark
				you can check the result by the qoute code that i provided in
				computeMotion motion function
			*/

			//load two image
			Mat a = imread("Untitled2.png", CV_8UC1);
			Mat b = imread("Untitled3.png", CV_8UC1);

			int** X, **Y;

			//initialize X, Y
			X = new int* [a.rows];
			Y = new int* [a.rows];
			for(int  i = 0; i < a.rows; i++)
			{
				X[i] = new int [a.cols];
				Y[i] = new int [a.cols];
			}

			//compute motion image
			Mat result = computeMotion(a, b, X, Y);

			//show your result
			imshow("vui-1", a);
			imshow("vui-2", b);
			imshow("vui", result);
			waitKey(0);

			//destroy X, Y
			for(int  i = 0; i < a.rows; i++)
			{
				delete []X[i];
				delete []Y[i];
			}
			delete []X;
			delete []Y;
		}

		void showMotion()
		{
			Mat image1 = imread(getString(s_image1));
			Mat image2 = imread(getString(s_image2));

			cvtColor(image1, image1, CV_BGR2GRAY);
			cvtColor(image2, image2, CV_BGR2GRAY);

			imshow("Image1", image1);
			imshow("Image2", image2);
			waitKey(10);

			int** X, **Y;

			//initialize X, Y
			X = new int* [image1.rows];
			Y = new int* [image1.rows];
			for(int  i = 0; i < image1.rows; i++)
			{
				X[i] = new int [image1.cols];
				Y[i] = new int [image1.cols];
			}

			computeMotion(image1, image2, X, Y);

			Mat image3, image4;

			image3 = image1.clone(); image4 = image1.clone();

			uchar* ptr_img3 = (uchar*)image3.data;
			uchar* ptr_img4 = (uchar*)image4.data;

			int k = 0;
			for(int  i = 0; i < image1.rows; i++)
			{
				for(int  j = 0; j < image1.cols; j++)
				{
					ptr_img3[k] = X[i][j];
					ptr_img4[k] = Y[i][j];
					k++;
				}
			}

			imshow("Motion X", image3);
			imshow("Motion Y", image4);

			//destroy X, Y
			for(int  i = 0; i < image1.rows; i++)
			{
				delete []X[i];
				delete []Y[i];
			}
			delete []X;
			delete []Y;
		}

	//the function of compution motion of two image
	//return: the Mat stored distance between two pixel
	//Xmotion: the int** stored distance between two pixel on x-axis
	//Ymotion: the int** stored distance between two pixel on y-axis
	Mat computeMotion(Mat &fisrtScene, Mat &secondScene,
						int** Xmotion, int** Ymotion)
	{
		Mat Result = fisrtScene.clone();
		Mat Mask;

		//initialize Xmotion and Ymotion
		for(int i = 0; i < fisrtScene.rows; i++)
		{
			for(int j = 0; j < fisrtScene.cols; j++)
			{
				Xmotion[i][j] = 0;
				Ymotion[i][j] = 0;
			}
		}

		//initialize iterator
		uchar* Ptr_fisrtScene, *Ptr_secondScene, *Ptr_Result, *Ptr_Mask;
		Ptr_fisrtScene = (uchar*)fisrtScene.data;
		Ptr_secondScene = (uchar*)secondScene.data;
		Ptr_Result = (uchar*)Result.data;

		//initialize variable that stored size of image
		int height, width;
		height = fisrtScene.rows;
		width = fisrtScene.cols;

		//initialize variable that stored index
		int index = 0;

		//compute the mask of procedure
		Mask = computeMask(fisrtScene, secondScene);
		Ptr_Mask = (uchar*)Mask.data;

		//iterate procedure of motion compuation
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				if(Ptr_Mask[index] == 0)
				{
					Ptr_Result[index++] = 0;
					continue;
				}

				Ptr_Result[index] = (uchar)computeDistance(fisrtScene, secondScene,
													  i, j,
													  Ymotion[i][j], Xmotion[i][j]);
				
				/*if(Ptr_Result[index] != 0)
					Ptr_Result[index] = 255;*/

				index++;
			}
		}

		return Result;
	}

		//the function of computation mask
	Mat computeMask(Mat &fisrtScene, Mat &secondScene)
	{
		Mat Result = fisrtScene.clone();

		//initialize iterator
		uchar* Ptr_fisrtScene, *Ptr_secondScene, *Ptr_Result;
		Ptr_fisrtScene = (uchar*)fisrtScene.data;
		Ptr_secondScene = (uchar*)secondScene.data;
		Ptr_Result = (uchar*)Result.data;

		//initialize variable that stored size of image
		int height, width;
		height = fisrtScene.rows;
		width = fisrtScene.cols;

		//initialize variable that stored index
		int index = 0;

		//iterate procedure of mask compuation
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				Ptr_Result[index] = abs(Ptr_fisrtScene[index] - Ptr_secondScene[index]);
				
				if(Ptr_Result[index] < thresh_dif)
				{
					Ptr_Result[index] = 0;
				}
				
				index++;
			}
		}

		return Result;
	}

		//the function of computation distance of motion of pixel (x, y)
	float computeDistance(Mat &fisrtScene, Mat &secondScene, int y, int x,
	  	  	  	  	  	  	int &Ymotion, int &Xmotion)
	{
		//initialize iterator
		uchar* Ptr_fisrtScene, *Ptr_secondScene;
		Ptr_fisrtScene = (uchar*)fisrtScene.data;
		Ptr_secondScene = (uchar*)secondScene.data;

		//initialize variable that stored size of image
		int height, width;
		height = fisrtScene.rows;
		width = fisrtScene.cols;

		//the variable stored minimum mse
		float min_mse = max_mse;

		//the variable stored position of pixel have minimum mse 
		int minx = -1, miny = -1;

		//the variable stored result distance 
		float distance = max_distance;

		//temporary variable
		float tmp_mse;
		float newdistance;

		//iterate procedure of distance compuation
		for(int i = -d; i < d; i++)
		{
			for(int j = -d; j < d; j++)
			{
				if(y+i<0 || x+j<0 || y+i>=height || x+j>=width)
					continue;

				tmp_mse = computeMSE(fisrtScene, secondScene, y, x, y+i, x+j);
			
				if(tmp_mse < min_mse)
				{
					min_mse = tmp_mse;

					minx = x+j;
					miny = y+i;

					//compute distance
					distance = sqrt((float)(minx-x)*(minx-x)+(miny-y)*(miny-y));
				}
				else if(tmp_mse == min_mse)
				{
					//compute distance
					newdistance = sqrt((float)(i*i+j*j));
				
					if(newdistance < distance)
					{
						min_mse = tmp_mse;

						minx = x+j;
						miny = y+i;

						distance = newdistance;
					}
				}

			}
		}

		//if min mse higher than threshold it will be rejected
		if(min_mse > thresh_mse)
		{
			return 0;
		}

		Xmotion = minx - x;
		Ymotion = miny - y;

		return distance;
	}

	//the function of computation mse procedure 
	float computeMSE(Mat &fisrtScene, Mat &secondScene,
						 int y1, int x1, int y2, int x2)
	{
		//variable stored result and number of pixel in window
		float result = 0;
		int count = 0;

		//initialize iterator
		uchar* Ptr_fisrtScene, *Ptr_secondScene;
		Ptr_fisrtScene = (uchar*)fisrtScene.data;
		Ptr_secondScene = (uchar*)secondScene.data;

		//initialize the variable stored size of image
		int height, width, size;

		height = fisrtScene.rows;
		width = fisrtScene.cols;
		size = height * width;

		////initialize variable stored index of pixel
		int index, index2, ty, ty2;

		//iterate to compute mse
		for(int i = -window_size; i < window_size; i++)
		{
			ty = (y1 + i);
			ty2 = (y2 + i);

			for(int j = -window_size; j < window_size; j++)
			{
				index = ty * height + x1 + j;
				index2 = ty2 * height + x2 + j;

				if((index < 0 || index2 < 0) || (index >= size || index2 >= size))
					continue;

				count++;

				result +=	(Ptr_fisrtScene[index] - Ptr_secondScene[index2]) *
							(Ptr_fisrtScene[index] - Ptr_secondScene[index2]);
			}
		}

		if(count != 0)
			result /= count;
		else
			result = max_mse;

		return result;
	}

#pragma region Histogram Motion
	int HistogramMotion(float* motionHistogram, int**X, int**Y, int rows, int cols)
	{
		int edge, count = 0;
		float atan_res;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if((X[i][j] != 0 && Y[i][j] != 0) || (X[i][j] != 0 && Y[i][j] == 0))
				{
					atan_res = atan((float)Y[i][j]/X[i][j]) * 180 /3.14 + 90;
					
					if(X[i][j] < 0)
						atan_res += 180;

					edge = (atan_res)/5;

					motionHistogram[edge] = motionHistogram[edge] + 1;
					count++;
				}
			}
		}
		return count;
	}

	//hien thi motion histogram
		void showMotionHistogram()
		{
			Mat image1 = imread(getString(s_image1));
			Mat image2 = imread(getString(s_image2));

			cvtColor(image1, image1, CV_BGR2GRAY);
			cvtColor(image2, image2, CV_BGR2GRAY);

			imshow("Image1", image1);
			imshow("Image2", image2);
			waitKey(10);

			int** X, **Y;
			
			//initialize X, Y
			X = new int* [image1.rows];
			Y = new int* [image1.rows];
			for(int  i = 0; i < image1.rows; i++)
			{
				X[i] = new int [image1.cols];
				Y[i] = new int [image1.cols];
			}

			float* motionHistogram = new float[72];
			for(int i = 0; i < 72; i++)
				motionHistogram[i] = 0;

			computeMotion(image1, image2, X, Y);

			int count = HistogramMotion(motionHistogram, X, Y, image1.rows, image1.cols);

			for(int i = 0; i < 72; i++)
				motionHistogram[i] /= count;

			_gui->DrawEdgeHistogram(motionHistogram, "Motion Histogram");

			//destroy X, Y
			for(int  i = 0; i < image1.rows; i++)
			{
				delete []X[i];
				delete []Y[i];
			}
			delete []X;
			delete []Y;
			delete []motionHistogram;
		}

		//hien thi motion histogram cho video
		void showVMotionHistogram()
		{
			VideoCapture cap(getString(s_video));

			Mat frameA, frameB;
			cap.read(frameA);

			int rows = frameA.rows;
			int cols = frameA.cols;

			int** X, **Y;
			
			//initialize X, Y
			X = new int* [frameA.rows];
			Y = new int* [frameA.rows];
			for(int  i = 0; i < frameA.rows; i++)
			{
				X[i] = new int [frameA.cols];
				Y[i] = new int [frameA.cols];
			}

			float* motionHistogram = new float[72];
			for(int i = 0; i < 72; i++)
				motionHistogram[i] = 0;
			
			int count = 0, iter = 0;
			bool odd_frame = true;
			while(true)
			{
				if(iter > 170)
					break;
				if(odd_frame == true)
				{
					if(!cap.read(frameB))
						break;
					cvtColor(frameB, frameB, CV_BGR2GRAY);
					
					imshow("video", frameB);
					waitKey(10);

					computeMotion(frameA, frameB, X, Y);
				}
				else
				{
					if(!cap.read(frameA))
						break;
					cvtColor(frameA, frameA, CV_BGR2GRAY);

					imshow("video", frameA);
					waitKey(10);

					computeMotion(frameB, frameA, X, Y);
				}

				odd_frame = !odd_frame;
				count += HistogramMotion(motionHistogram, X, Y, frameA.rows, frameA.cols);
				iter++;
			}

			for(int i = 0; i < 72; i++)
				motionHistogram[i] /= count;

			_gui->DrawEdgeHistogram(motionHistogram, "Motion Histogram");

			//destroy X, Y
			for(int  i = 0; i < frameA.rows; i++)
			{
				delete []X[i];
				delete []Y[i];
			}
			delete []X;
			delete []Y;
			delete []motionHistogram;
		}
#pragma endregion
#pragma region Mean Motion Image
		//hien thi motion histogram cho video
		void showMeanMotion()
		{
			VideoCapture cap(getString(s_video));

			Mat frameA, frameB;
			cap.read(frameA);

			int rows = frameA.rows;
			int cols = frameA.cols;

			int** X, **Y, **OX, **OY;
			
			//initialize X, Y
			X = new int* [frameA.rows];
			Y = new int* [frameA.rows];
			OX = new int* [frameA.rows];
			OY = new int* [frameA.rows];
			for(int  i = 0; i < frameA.rows; i++)
			{
				X[i] = new int [frameA.cols];
				Y[i] = new int [frameA.cols];
				OX[i] = new int [frameA.cols];
				OY[i] = new int [frameA.cols];
			}

			for(int i = 0; i < frameA.rows; i++)
			{
				for(int j = 0; j < frameA.cols; j++)
				{
					OX[i][j] = 0;
					OY[i][j] = 0;
				}
			}
			
			int count = 0, iter = 0;
			bool odd_frame = true;
			while(true)
			{
				if(iter > 70)
					break;
				if(odd_frame == true)
				{
					if(!cap.read(frameB))
						break;
					if(!cap.read(frameB))
						break;
					cvtColor(frameB, frameB, CV_BGR2GRAY);
					
					imshow("video", frameB);
					waitKey(1);

					computeMotion(frameA, frameB, X, Y);
				}
				else
				{
					if(!cap.read(frameA))
						break;
					if(!cap.read(frameA))
						break;
					cvtColor(frameA, frameA, CV_BGR2GRAY);

					imshow("video", frameA);
					waitKey(1);

					computeMotion(frameB, frameA, X, Y);
				}

				for(int i = 0; i < frameA.rows; i++)
				{
					for(int j = 0; j < frameA.cols; j++)
					{
						OX[i][j] += abs(X[i][j]);
						OY[i][j] += abs(Y[i][j]);
					}
				}

				odd_frame = !odd_frame;
				iter++;
			}

			int maxX = findMax(X, frameA.rows, frameA.cols);
			int maxY = findMax(Y, frameA.rows, frameA.cols);
			int tmpX = 256 / maxX * iter;
			int tmpY = 256 / maxY * iter;

			Mat imageX = Mat(frameA.rows, frameA.cols, CV_8UC1);
			Mat imageY = Mat(frameA.rows, frameA.cols, CV_8UC1);

			uchar* ptr_X = (uchar*)imageX.data, *ptr_Y = (uchar*)imageY.data;

			int k = 0;
			for(int i = 0; i < frameA.rows; i++)
			{
				for(int j = 0; j < frameA.cols; j++)
				{
					ptr_X[k] = OX[i][j] * tmpX / iter;
					ptr_Y[k] = OY[i][j] * tmpY / iter;
					k++;
				}
			}

			imshow("X motion", imageX);
			imshow("Y motion", imageY);

			//destroy X, Y
			for(int  i = 0; i < frameA.rows; i++)
			{
				delete []X[i];
				delete []Y[i];
				delete []OX[i];
				delete []OY[i];
			}
			delete []X;
			delete []Y;
			delete []OX;
			delete []OY;
		}

	int findMax(int** X, int rows, int cols)
	{
		int max = 0;

		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				if(X[i][j] > max)
					max = X[i][j];
			}
		}
		
		return max;
	}
#pragma endregion
		//constructor
		MOTION(void)
		{
		}
	};
}