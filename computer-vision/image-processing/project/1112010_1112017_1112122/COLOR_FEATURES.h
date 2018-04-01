// MyOpencvLibrary.h

#pragma once

#include "..\Libraries\Headers\opencv2\core\core.hpp"
#include "..\Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "..\Libraries\Headers\opencv2\imgproc\imgproc.hpp"

#include "GUI.h"

#include <queue>
#include <iostream>

using namespace System;
using namespace cv;
using namespace std;

#define SCALE_OF_HIST  2

namespace My1112010_1112017_1112122 {
	public ref class ColorFeatures
	{
#pragma region Data
	private:
		GUI^ _gui;
		System::String^ s_video;
		System::String^ s_image;
#pragma endregion
#pragma region Initialization
public:
	ColorFeatures()
	{
		_gui = gcnew GUI();
		s_video = nullptr;
		s_image = nullptr;
	}

	~ColorFeatures()
	{
		delete _gui;

		if(s_video != nullptr)
			delete s_video;
		s_video = nullptr;
	}
#pragma endregion
#pragma region Function
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

	void getImage(System::String^ s)
	{
		if(s_image != nullptr)
			delete s_image;
		s_image = s;
	}

	int Distance(int x1, int y1, int x2, int y2)
	{
		return (int)sqrt((float)((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
	}

#pragma endregion
#pragma region Quantization
	//Ham luong hoa
	int quantize(uchar &R, uchar &G, uchar &B, const int &bin)
	{
		return (int)((float)R/256*bin)*bin*bin + round((float)G/256*bin)*bin + round((float)B/256*bin);
	}
#pragma endregion
#pragma region Histogram
	//tinh histogram cua day anh
	public:
#pragma region BAO_FUNCTION
	void displayImage(Mat img, char* windowName)
	{
		namedWindow(windowName);
		imshow(windowName, img);

		waitKey(10);
	}
	void computeHSVColorHistogram(const Mat src, int* hist, int numBin_H, int numBin_S, int numBin_V)
	{
		uchar* pixelPtr_image = (uchar*)src.data; // data của ảnh
		int rowIndex, colIndex, nChannels = src.channels(); //nChannels==1 ảnh xám, nChannels==3 ảnh 3 kênh màu
		float R, G, B; //Giá trị 3 kênh màu Red, Green, Blue đã chuẩn hóa về [0,1]
		float H, S, V; //Giá trị 3 kênh màu Hue, Sarturation, Value
		float Cmax, Cmin; //Mac, min của (R, G, B)
		float Delta; // Delta = Cmax - Cmin
		float hStep, sStep, vStep;//Độ lớn mỗi bin
		int index, index1, index2, index3; // chỉ số của mảng H

		hStep = (float)360 / numBin_H;
		sStep = (float)1 / numBin_S;
		vStep = (float)1 / numBin_V;
		index1 = numBin_S*numBin_V;
		index2 = numBin_V;
		index3 = 1;

		// Duyệt từng pixel: Cộng dồn tương ứng
		for (int i = 0; i < src.rows; i++)
		{
			rowIndex = i*src.step;
			for (int j = 0; j < src.cols; j++)
			{
				colIndex = j*nChannels;
				B = (float)pixelPtr_image[rowIndex + colIndex];
				G = (float)pixelPtr_image[rowIndex + colIndex + 1];
				R = (float)pixelPtr_image[rowIndex + colIndex + 2];

				R /= 255; G /= 255; B /= 255;

				Cmax = B;
				if (G > Cmax)
					Cmax = G;
				if (R > Cmax)
					Cmax = R;
				Cmin = B;
				if (G < Cmin)
					Cmin = G;
				if (R < Cmin)
					Cmin = R;
				
				Delta = Cmax - Cmin;

				V = Cmax;

				if (V == 0)
				{
					H = 0;
					S = 0;
				}
				else
				{
					S = Delta / Cmax;

					if(S == 0)
					{
						H = 0;
					}
					else
					{
						if (Cmax = R)
							H = 60 * (G - B) / Delta;
						else if (Cmax == G)
							H = 120 + 60 * (R - G) / Delta;
						else
							H = 240 + 60 * (R - G) / Delta;
					}
				}
			
				index = index1*(int)(H / hStep) + index2*(int)(S / sStep) + index3*(int)(V / vStep);

				hist[index]++;
			}
		}
	}

	void HSVtoRGB(float h, float s, float v, float &r, float &g, float &b)
	{
		int i;
		float f, p, q, t;
		if (s == 0) 
		{
			r = g = b = v;
			return;
		}
		h /= 60;			
		i = floor(h);
		f = h - i;			
		p = v * (1 - s);
		q = v * (1 - s * f);
		t = v * (1 - s * (1 - f));
		switch (i) 
		{
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		default:		

			r = v;
			g = p;
			b = q;
			break;
		}
	}

	Mat drawColorHistogram(int* hist, int numBin_H, int numBin_S, int numBin_V)
	{
		int flag = 0; // Cờ để tìm giá trị màu lớn nhất cho từng kênh màu

		int size = numBin_H * numBin_S * numBin_V;

		// Tìm giá trị max
		for (int i = 0; i< size; ++i)
		{
			cout << hist[i] << " ";
			if (hist[i] > flag)
				flag = hist[i];
		}

		// Quy về giá trị max tương ứng 100%
		float scale = (float)100 / flag;

		int nRows = 100 * SCALE_OF_HIST + 7, nCols = size * SCALE_OF_HIST;

		// Tạo ảnh để vẽ histogram có màu trắng
		Mat img_hist(nRows, nCols, CV_8UC3);
		img_hist.setTo(Scalar(255, 255, 255));

		cout << endl << "-------------------HSV2RGB---------------" << endl;
		// Vẽ histogram cho từng kênh màu
		for (int i = 0; i < size; i++)
		{
			float H = int(i / (numBin_S*numBin_V)) * 360 / numBin_H;
			float S = float(int((i % (numBin_S*numBin_V)) / numBin_V)) / numBin_S;
			float V = float((i % (numBin_S*numBin_V)) % numBin_V) / numBin_V;

			//cout << "(" << H << " " << S << " " << V << "), ";ze

			float fR, fG, fB;
			HSVtoRGB(H, S, V, fR, fG, fB);

			int R = fR * 255;
			int G = fG * 255;
			int B = fB * 255;
			cout << "(" << R << " " << G << " " << B << "), ";
			rectangle(img_hist, Point2i(i*SCALE_OF_HIST, 7), Point2i(SCALE_OF_HIST*(i + 1), (SCALE_OF_HIST*hist[i] * scale) + 7), Scalar(B, G, R), CV_FILLED);
			rectangle(img_hist, Point2i(i*SCALE_OF_HIST, 0), Point2i(SCALE_OF_HIST*(i + 1), 4), Scalar(B, G, R), CV_FILLED);

		}

		flip(img_hist, img_hist, 0); // 
		return img_hist;
	}
	void drawHistogram(Mat image, int numBin_H, int numBin_S, int numBin_V)
	{
		// Nếu số kênh màu là 3 thì vẽ histogram cho ảnh màu, ngược lại vẽ cho ảnh xám
		if (image.channels() == 3)
		{
			int n = numBin_H*numBin_S*numBin_V;
			int* hist = new int[n];
			for (int i = 0; i < n; ++i)
				hist[i] = 0;
			computeHSVColorHistogram(image, hist, numBin_H, numBin_S, numBin_V);
			Mat original_hisst = drawColorHistogram(hist, numBin_H, numBin_S, numBin_V);
			displayImage(original_hisst, "Histogram of original image");
		}
	}
	void ColorHistogram(int nHue, int nSar, int nValue)
	{
		Mat image = imread(getString(s_image));

		imshow("Image", image);
		waitKey(10);

		//Mat img_HSV;
		//cvtColor(image, img_HSV, CV_BGR2HSV);
		//displayImage(img_HSV, "HSV image");

		drawHistogram(image, nHue, nSar, nValue);
		waitKey(10);
	}
#pragma endregion
	void computeVHistogram(int bin, float* Histogram)
	{
		VideoCapture segment(getString(s_video));

		//Khai bao bien
		int t = 0;	//bien dem so frame
		int rowIndex, colIndex, index; //bien chay
		int cols, rows;	//luu kich thuoc anh
		int cn;		//bien luu tru so kenh mau
		int max_bin = bin*bin*bin;

		uchar* pixelPtr_image;	//bien chay

		for(int i = 0; i < max_bin; i++)
			Histogram[i] = 0;

		Mat frame;

		while(segment.read(frame) && t < 120)
		{
			imshow("Video",frame);
			waitKey(40);

			//gan pixelPtr_image vao frame de tien hanh duyet
			pixelPtr_image = (uchar*)frame.data;

			cn = frame.channels();

			rows = frame.rows;
			cols = frame.cols;

			//duyet anh frame
			for(int i = 0; i < rows; i++)
			{
				rowIndex = i * frame.step;
				for(int j = 0; j < cols; j++)
				{	
					colIndex = j * cn;
					index = rowIndex + colIndex;
					Histogram[quantize(pixelPtr_image[index+2],
									pixelPtr_image[index+1],
									pixelPtr_image[index],
									bin)]++;
				}
			}

			t++;
		}

		int w = t * rows * cols; //he so chuan hoa

		for(int i = 0; i < max_bin; i++)
			Histogram[i] /= w;
	}

	void DrawVHistogram(int bin)
	{
		float* his = NULL;
		his = new float [bin*bin*bin];

		computeVHistogram(bin, his);
		_gui->DrawHistogram(his, bin, strdup(getString("Luoc do mau day anh: " + s_video).c_str()));

		if(his != NULL)
			delete []his;
	}
#pragma endregion
#pragma region Auto-Correlogram 
	// lấy các điểm lân cận điểm (x, y) theo khoảng cách d
	// imgage: Ảnh thao tác
	// neigh: lưu tọa độ các điểm lấy được
	void getNeighbor(Mat image, vector<Point> &neighbor, int &x, int &y, int &d, int &di, int &dj)
	{
		di = -d;
		if(x + di >= 0)
		{
			for(int dj = -d; dj <= d; dj++)
				if(y + dj >= 0 && y + dj < image.rows)
					neighbor.push_back(Point(x+di,y+dj));
		}
		
		di = d;
		if(x + di < image.cols)
		{
			for(dj = -d; dj <= d; dj++)
				if(y + dj >= 0 && y + dj < image.rows)
					neighbor.push_back(Point(x+di,y+dj));
		}

		dj = -d;
		if(y + dj >= 0)
		{
			for(di = -d+1; di < d; di++)
				if(x + di >= 0 && x + di < image.cols)
					neighbor.push_back(Point(x+di,y+dj));
		}
		
		dj = d;
		if(y + dj < image.rows)
		{
			for(di = -d+1; di < d; di++)
				if(x + di >= 0 && x + di < image.cols)
					neighbor.push_back(Point(x+di,y+dj));
		}
	}
	
	// Hàm tính lược độ tương quan màu
	// image: Ảnh cần tính
	// d: Khoảng cách d trong công thức
	// bin: so bin mau luong hoa trên 1 kênh
	void computeColorCorrelogram(Mat image, int &d, int &bin, float* Correlogram)
	{
		int max_bin = bin*bin*bin;
		int rowIndex, colIndex, nChannels = image.channels(); //nChannels==1 ảnh xám, nChannels==3 ảnh 3 kênh màu
		uchar* pixelPtr_image = (uchar*)image.data; // data của ảnh
		uchar red, green, blue; // Lưu các giá trị màu tại một pixel trong image
		uchar t_red, t_green, t_blue; // Lưu các giá trị màu tại một pixel trong image
		int index1, index2, color_index;
		int di, dj;
		
		vector<Point> neigh;
		int *Histogram = new int [max_bin];

		// Gán các giá trị = 0 để chuẩn bị cộng dồn
		for (int i = 0; i < max_bin; ++i)
		{
			Correlogram[i] = 0;
			Histogram[i] = 0;
		}
	
		for (int i = 0; i < image.rows; i++)
		{
			rowIndex = i * image.step;
			for (int j = 0; j < image.cols; j++)
			{
				//tinh index
				colIndex = j * nChannels;
				index1 = rowIndex + colIndex;

				//gan kenh mau
				blue = pixelPtr_image[index1];
				green = pixelPtr_image[index1 + 1];
				red = pixelPtr_image[index1 + 2];

				//tang histogram mau Q(I(x,y))
				color_index = quantize(red, green, blue, bin);
				Histogram[color_index]++;

				//lay toa do cac diem lang gieng
				neigh.clear();
				getNeighbor(image, neigh, j, i, d, di, dj);

				//dem so diem trung mau
				for (unsigned int k = 0; k < neigh.size(); ++k)
				{
					//tinh index
					index2 = neigh[k].y * image.step + neigh[k].x * nChannels;
					
					//gan kenh mau
					t_blue = pixelPtr_image[index2];
					t_green = pixelPtr_image[index2 + 1];
					t_red = pixelPtr_image[index2 + 2];

					if(quantize(t_red, t_green, t_blue, bin) == color_index)
						Correlogram[color_index]++;
				}
			}
		}

		//normalize
		int d8 = 8 * d; //he so chuan hoa
		for (int i = 0; i < max_bin; ++i)
		{
			if(Histogram[i] > 0)
				Correlogram[i] /= (Histogram[i] * d8);
		}
		
		delete []Histogram;
	}

	void ColorCorrelogram(int bin, int d)
	{
		Mat image = imread(getString(s_image));

		imshow("Image", image);

		//khai bao bien
		int max_bin = bin*bin*bin;		//so bin mau toi da

		float* corr = new float [bin*bin*bin];

		computeColorCorrelogram(image, d, bin, corr);
		_gui->DrawHistogram(corr, bin, strdup(getString("Luoc do tu tuong quan mau: " + s_image).c_str()));

		delete []corr;
	}
#pragma endregion
#pragma region mean_color_image
	Mat computeMeanColorImage()
	{
		VideoCapture segment(getString(s_video));

		//Khai bao bien
		int t = 0;	//bien dem so frame
		int i; //bien chay
		int max_index;	//luu kich thuoc anh

		uchar* pixelPtr_image;	//bien chay

		Mat frame, result;
		float* tmp;

		while(segment.read(frame) && t < 120)
		{
			imshow("Video",frame);
			waitKey(40);

			if(t == 0)
			{
				max_index = 3 * frame.rows * frame.cols;
				tmp = new float [max_index];

				for(int i = 0; i < max_index; i++)
					tmp[i] = 0;

				result = Mat(frame.rows, frame.cols, CV_8UC3, Scalar(0,0,0));
			}

			//gan pixelPtr_image vao frame de tien hanh duyet
			pixelPtr_image = (uchar*)frame.data;

			//duyet anh frame
			for(i = 0; i < max_index; i++)
			{
				tmp[i] += pixelPtr_image[i];
			}

			t++;
		}

		//duyet anh frame
		pixelPtr_image = (uchar*)result.data;

		for(i = 0; i < max_index; i++)
		{
			pixelPtr_image[i] = (uchar)(tmp[i]/t);
		}

		delete []tmp;
		return result;
	}

	void showMeanColorImage()
	{
		_gui->displayImage(computeMeanColorImage(), "Anh trung binh mau day anh");
	}
#pragma endregion
#pragma region Color Coherence Vector
	public:
	void showCoherenceVector(int bin)
	{
		Mat image = imread(getString(s_image));

		imshow("Image", image);
		waitKey(10);

		//khai bao bien
		int max_bin = bin*bin*bin;		//so bin mau toi da

		//khai bao mang luu ket qua vector lien ket mau
		float** CoherenceVector = new float* [2];
		for(int i = 0; i < 2; i++)
			CoherenceVector[i] = new float [max_bin];

		for(int i = 0; i < 2; i++)
			for(int j = 0; j < max_bin; j++)
				CoherenceVector[i][j] = 0;

		//goi ham tinh vector lien ket mau
		computeCoherenceVector(bin, CoherenceVector);
		_gui->DrawCoherenceVector(CoherenceVector, bin);

		//don du lieu da duoc khai bao
		for(int i = 0; i < 2; i++)
			delete []CoherenceVector[i];
		delete []CoherenceVector;
	}

	void computeCoherenceVector(int bin, float** CoherenceVector)
	{
		Mat image = imread(getString(s_image));

		//Khai bao bien
		int cn = image.channels();					//bien luu tru so kenh mau
		int one_size = image.rows*image.cols/100;	//luu thuoc cua 1% anh
		int size = image.rows*image.cols;	//luu thuoc cua anh
		int step = image.step;
		int max_bin = bin*bin*bin;
		int quanti, k;
		int rowIndex, colIndex, index; //bien chay
		uchar* pixelPtr_image = (uchar*)image.data;	//bien chay

		//khai bao mang luu lich su duyet hinh
		bool **checkMat = new bool* [image.rows];
		for(int i = 0; i < image.rows; i++)
			checkMat[i] = new bool [image.cols];

		//khoi gan gia tri cho checkMat
		for(int i = 0; i < image.rows; i++)
			for(int j = 0; j < image.cols; j++)
				checkMat[i][j] = 0;

		//duyet anh frame
		for(int i = 0; i < image.rows; i++)
		{
			rowIndex = i * image.step;
			for(int j = 0; j < image.cols; j++)
			{	
				colIndex = j * cn;
				index = rowIndex + colIndex;

				if(checkMat[i][j] == 1)
					continue;

				checkMat[i][j] = 1;

				quanti = quantize(	pixelPtr_image[index+2],
									pixelPtr_image[index+1],
									pixelPtr_image[index],
									bin
								 );
				k = 0;

				if(checkCoherence( pixelPtr_image, bin, image.cols, image.rows, cn, step,
								i, j, checkMat, k, one_size,
								quanti))
				{
					CoherenceVector[0][quanti] += k;
				}
				else
				{
					CoherenceVector[1][quanti] += k;
				}
			}
		}

		for(int i = 0; i < 2; i++)
			for(int j = 0; j < max_bin; j++)
				CoherenceVector[i][j] /= size;

		for(int i = 0; i < image.rows; i++)
			delete []checkMat[i];
		delete []checkMat;
	}

	bool checkCoherence(uchar* img, int &bin, int &width, int &height, int &cn, int &step,
						int i, int j, bool** checkMat, int &k,
						int &size, int &quanti)
	{
		queue <int>qi;
		queue <int>qj;

		//khai bao bien
		int l_rowIndex, l_colIndex, l_index; //bien chay
		int ti, tj;

		qi.push(i);
		qj.push(j);

		while(!qi.empty())
		{
			ti = qi.front(); tj = qj.front();
			qi.pop(); qj.pop();

			k++;

			//vong lap duyet kiem tra cac diem tuong dong mau hay khong
			for(int pi = -1; pi < 2; pi++)
			{
				for(int pj = -1; pj < 2; pj++)
				{
					//neu da duoc duyet thi se bo qua
					if(ti + pi < 0 || tj + pj < 0)
						continue;
					if(ti + pi >= height || tj + pj >= width)
						continue;
					if(checkMat[ti + pi][tj + pj] == 1)
						continue;

					l_rowIndex = (ti + pi) * step;
					l_colIndex = (tj + pj) * cn;
					l_index = l_rowIndex + l_colIndex;

					if( quantize(img[l_index+2], img[l_index+1], img[l_index], bin) == quanti)
					{
						checkMat[ti + pi][tj + pj] = 1;

						qi.push(ti + pi);
						qj.push(tj + pj);
					}
				}
			}
		}

		if(k > size)
			return true;
		return false;
	}
#pragma endregion
#pragma region Color Vector Moment
// ghi chu thich
// ghi input output
void VectorMomentColor(int Moment1[3], int Moment2[3], int Moment3[3])
{
	Mat image = imread(getString(s_image));

	//initialize moment 1, 2 and 3
	Moment1[0] = Moment1[1] = Moment1[2] = 0;
	Moment2[0] = Moment2[1] = Moment2[2] = 0;
	Moment3[0] = Moment3[1] = Moment3[2] = 0;

	uchar* ptr_image = (uchar*)image.data;
	int nChannels = image.channels();
	int step = image.step;
	int rows = image.rows; int cols = image.cols;

	mean(ptr_image, nChannels, step, rows, cols, Moment1);
	momentK(ptr_image, nChannels, step, rows, cols, Moment1, 2, Moment2);
	momentK(ptr_image, nChannels, step, rows, cols, Moment1, 3, Moment3);
}

//compute moment I
void mean(uchar* image, int nChannels, int step, int rows, int cols, int Mean[])
{
	int rowIndex, colIndex;
	int size = rows * cols;

	for(int i = 0; i < rows; i++)
	{
		rowIndex = i * step;
		for(int j = 0; j < cols; j++)
		{	
			colIndex = j * nChannels;
			for (int k = 0 ; k < nChannels ; k++) //k=0 Blue; k=1 Green; k=2 Red
				Mean[k] += image[rowIndex + colIndex + k];
		}
	}

	for(int i = 0; i < 3; i++)
		Mean[i] /= size;
}

//t: bac cua moment
void momentK(uchar* image, int nChannels, int step, int rows, int cols, int Mean[], int t, int Moment[])
{
	int rowIndex, colIndex, Index;
	int size = rows * cols;

	for(int i = 0; i < rows; i++)
	{
		rowIndex = i * step;
		for(int j = 0; j < cols; j++)
		{	
			colIndex = j * nChannels;
			Index = rowIndex + colIndex;

			for (int k = 0 ; k < nChannels ; k++) //k=0 Blue; k=1 Green; k=2 Red
			{
				Moment[k] += (int)pow((float)(image[Index + k] - Mean[k]),t);
			}
		}
	}

	int sign[3];
	for (int i = 0; i < 3; i++)
	{
		if(Moment[i] <0)
			sign[i] = -1;
		else
			sign[i] = 1;
	}

	for(int i = 0; i < 3; i++)
		Moment[i] = (sign[i] * pow(Moment[i] * sign[i] / size, 1.0F / t));
}

#pragma endregion
	};
}
