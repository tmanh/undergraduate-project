#pragma once

#include "..\Libraries\Headers\opencv2\core\core.hpp"
#include "..\Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "..\Libraries\Headers\opencv2\imgproc\imgproc.hpp"

#include <vector>

using namespace cv;
using namespace std;

#define pi 3.14159265359F
#define THRESHOLD 200

ref class GEOMETRIC
{
public:
#pragma region Data
	System::String^ s_image;

	float Perimeter;
	float Area;
	float MajorAxisLength;
	float MinorAxisLength;
	float BoundingBoxHeight;
	float BoundingBoxWidth;
	float AreaConvexHull;
	float PerimeterConvexHull;
#pragma endregion

#pragma region Initialization
	GEOMETRIC(void);
#pragma endregion

#pragma region Function
	//chuyen tu string^ sang string
	std::string getString(System::String^ x)
	{
		std::string tmp;
		for(int i = 0; i < x->Length; i++)
		tmp += (char)x[i];
		return tmp;
	}

	//lay ten cua hinh
	void getImage(System::String^ s)
	{
		if(s_image != nullptr)
			delete s_image;
		s_image = s;
	}

	//kiem tra diem co nam tren bien hay khong
	bool CheckPixelInBoundary(int &x, int &y, uchar* Image, int &height, int &width)
	{
		int index, ti, tj;
		for(int di = -1; di < 2; di++)
		{
			for(int dj = -1; dj < 2; dj++)
			{
				ti = y+di;
				tj = x+dj;
				//kiem tra xem diem dang xet co nam ngoai ria anh hay khong
				if(ti < 0 || tj < 0 || ti >= height || tj >= width)
					return true;
				index = ti*width + tj;
				//Neu co 1 pixel quanh pixel dang xet co gia tri 0
				//thi diem dang xet la bien
				if(Image[index] < THRESHOLD)
					return true;
			}
		}

		return false;
	}

	//lay danh sach cac diem nam tren bien
	void BoundaryRegion(vector<int> &bpx, vector <int> &bpy, uchar* Image, int& height, int &width)
	{
		int index;

		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				index = i*width + j;
				if(Image[index] < THRESHOLD)	//neu diem dang xet co gia tri 0
					continue;			//thi bo qua
				
				//kiem tra xem diem dang xet co phai bien canh hay ko
				if(CheckPixelInBoundary(j, i, Image, height, width) == false)
					continue;

				//them diem bien canh vao vector ket qua
				bpx.push_back(j);
				bpy.push_back(i);
			}
		}
	}

	//lay danh sach cac diem tren vat the
	void ListRegion(vector<int> &px, vector <int> &py, uchar* Image, int& height, int &width)
	{
		int index;

		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				index = i*width + j;
				if(Image[index] < THRESHOLD)	//neu diem dang xet co gia tri 0
					continue;			//thi bo qua

				//them diem thuoc vat the vao vector ket qua
				px.push_back(j);
				py.push_back(i);
			}
		}
	}

	//tinh chu vi vat the
	void PerimeterRegion(vector<int> &bpx, vector <int> &bpy, uchar* Image, int& height, int &width)
	{
		BoundaryRegion(bpx, bpy, Image, height, width);
		Perimeter = (float)bpx.size();
	}

	//tinh dien tich vat the
	void AreaRegion(vector<int> &px, vector <int> &py, uchar* Image, int& height, int &width)
	{
		ListRegion(px, py, Image, height, width);
		Area = (float)px.size();
	}

	//tim tam vat the
	void findCentroid(vector<int> &px, vector <int> &py, float &xmean, float &ymean)
	{
		int size = px.size();
		xmean = ymean = 0;

		//tinh tong toa do tat ca cac diem
		for (int i = 0; i < size; i++)
		{
			xmean += px[i];
			ymean += py[i];
		}

		//tinh trung binh toa do
		xmean /= size;
		ymean /= size;
	}

	//tim chieu dai 2 truc chinh
	void findAxisLength(vector<int> &px, vector <int> &py)
	{
		float xmean, ymean;
		int size = px.size();
		
		//tim tam vat the
		findCentroid(px, py, xmean, ymean);

		vector<float> dx; vector<float> dy;
		
		//tinh vector tu cac dinh khac den tam
		for(int i = 0; i < size; i++)
		{
			dx.push_back(px[i] - xmean);
			dy.push_back(py[i] - ymean);
		}

		float uxx = 0, uyy = 0, uxy = 0;

		//tinh cac he so trong ma tran seccond moment
		for(int i = 0; i < size; i++)
		{
			uxx += dx[i]*dx[i];
			uyy += dy[i]*dy[i];
			uxy += dx[i]*dy[i];
		}

		//chuan hoa
		uxx /= size; uyy /= size; uxy /= size;
		//tinh he so delta
		float delta = sqrt((uxx - uyy)* (uxx - uyy) + 4*uxy*uxy);

		//tra ve ket qua chieu dai 2 truc
		MajorAxisLength = (float)(2*sqrt(2.0)*sqrt(uxx + uyy + delta));
		MinorAxisLength = (float)(2*sqrt(2.0)*sqrt(uxx + uyy - delta));
	}

	//tim hinh chu nhat nho nhat bao vat the
	void BoundingBox(int &xmin, int &ymin, vector<int> &px, vector <int> &py)
	{
		//khoi tao cac bien
		xmin = -1, ymin = -1;
		int xmax = -1, ymax = -1;
		int size = px.size();

		//duyet tat ca cac diem tren vat the de tim min max toa do
		for (int i = 0; i < size; i++)
		{
			if(xmin == -1 || xmin > px[i])
				xmin = px[i];
			if(ymin == -1 || ymin > py[i])
				ymin = py[i];
			if(xmax == -1 || xmax < px[i])
				xmax = px[i];
			if(ymax == -1 || ymax < py[i])
				ymax = py[i];
		}

		//gan ket qua chieu dai va rong
		if(ymax - ymin > xmax - xmin)
		{
			BoundingBoxHeight = (float)(ymax - ymin);
			BoundingBoxWidth = (float)(xmax - xmin);
		}
		else
		{
			BoundingBoxWidth = (float)(ymax - ymin);
			BoundingBoxHeight = (float)(xmax - xmin);
		}
	}

	//ham tinh khoang cach hai diem
	float Distance(int x1, int y1, int x2, int y2)
	{
		return sqrt((float)(x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	}

	//ham tinh dien tich tam giac theo cong thuc herong
	float TriangleArea(int x1, int y1, int x2, int y2, int x3, int y3)
	{
		float a = Distance(x1, y1, x2, y2);
		float b = Distance(x2, y2, x3, y3);
		float c = Distance(x3, y3, x1, y1);

		return sqrt((a+b+c)*(a-b+c)*(a+-c)*(b+c-a))/4;
	}

	//ham sort cac diem tren bien tang dan theo x
	void sortBoundaryRegion(vector<int> &bpx, vector <int> &bpy)
	{
		int size = bpx.size();
		int tmp;

		//bubble sort
		for(int i = 0; i < size-1; i++)
		{
			for(int j = i+1; j < size; j++)
			{
				if(bpx[i] > bpx[j])
				{
					tmp = bpx[i];
					bpx[i] = bpx[j];
					bpx[j] = tmp;

					tmp = bpy[i];
					bpy[i] = bpy[j];
					bpy[j] = tmp;
				}
				else if(bpx[i] == bpx[j] && bpy[i] > bpy[j])
				{
					tmp = bpy[i];
					bpy[i] = bpy[j];
					bpy[j] = tmp;
				}
			}
		}
	}

	//tinh dien tich bao loi
	void calAreaConvexHull(vector<int> &px_convex, vector<int> &py_convex)
	{
		int size = px_convex.size();
		AreaConvexHull = 0;

		for(int  i = 2; i < size; i++)
		{
			AreaConvexHull += TriangleArea(	px_convex[0], py_convex[0],
											px_convex[i-1], py_convex[i-1], 
											px_convex[i], py_convex[i]);
		}
	}

	//tinh chu vi bao loi
	void calPerimeterConvexHull(vector<int> &px_convex, vector<int> &py_convex)
	{
		int size = px_convex.size();
		PerimeterConvexHull = Distance(	px_convex[0], py_convex[0],
										px_convex[size-1], py_convex[size-1]);

		for(int  i = 1; i < size; i++)
		{
			PerimeterConvexHull += Distance( px_convex[i], py_convex[i],
											 px_convex[i-1], py_convex[i-1]);
		}
	}

	//ham tinh tich co huong cua 2 vector
	int CrossProduct(vector<int> &px_convex, vector<int> &py_convex, int &k, int &x, int &y)
	{
		return	(px_convex[k-1] - x)*(py_convex[k-2] - y) -
				(py_convex[k-1] - y)*(px_convex[k-2] - x);
	}

	//ham tim bao loi
	void ConvexHull(vector<int> &bpx, vector <int> &bpy, vector<int> &px_convex, vector<int> &py_convex)
	{
		//sap xep tang theo x
		sortBoundaryRegion(bpx, bpy);

		int size = bpx.size();
		int k = 0;

		//test
		int thickness = 2;
		int lineType = 0;

		//tim lower hull
		for(int i = 0; i < size; i++)
		{
			while(k >= 2 && CrossProduct(px_convex, py_convex, k, bpx[i], bpy[i]) <= 0)
			{
				px_convex.erase(px_convex.begin() + k - 1);
				py_convex.erase(py_convex.begin() + k - 1);
				k--;
			}

			if(py_convex.size() == k)
			{
				px_convex.push_back(bpx[i]);
				py_convex.push_back(bpy[i]);
			}
			else
			{
				px_convex[k] = bpx[i];
				py_convex[k] = bpy[i];
			}

			k++;
		}

		//tim upper hull
		for(int i = size-2; i > 0; i--)
		{
			while(k >= 2 && CrossProduct(px_convex, py_convex, k, bpx[i], bpy[i]) <= 0)
			{
				px_convex.erase(px_convex.begin() + k - 1);
				py_convex.erase(py_convex.begin() + k - 1);
				k--;
			}

			if(py_convex.size() == k)
			{
				px_convex.push_back(bpx[i]);
				py_convex.push_back(bpy[i]);
			}
			else
			{
				px_convex[k] = bpx[i];
				py_convex[k] = bpy[i];
			}

			k++;
		}
	}

	//tim cac dac trung cua bao loi
	void findConvexHullProperty(vector<int> &bpx, vector <int> &bpy, vector<int> &px_convex, vector<int> &py_convex)
	{
		ConvexHull(bpx, bpy, px_convex, py_convex);
		calAreaConvexHull(px_convex, py_convex);
		calPerimeterConvexHull(px_convex, py_convex);
	}
#pragma endregion

#pragma region VOHUONG
	float Compact()
	{
		float rc = (float)sqrt (Area / pi);
		float pc = 2 * pi * rc;
		return pc/Perimeter;
	}
	float ti_so_truc_chinh()
	{
		return MinorAxisLength/MajorAxisLength;
	}
	float Thon_Dai()
	{
		return BoundingBoxWidth/BoundingBoxHeight;
	}
	float Chu_Nhat()
	{
		float Ar = BoundingBoxWidth*BoundingBoxHeight;
		return Area/Ar;
	}
	float Tinh_Loi()
	{
		return PerimeterConvexHull/Perimeter;
	}
	void ComputeAll()
	{
		vector<int> bpx; vector <int> bpy;
		vector<int> px; vector <int> py;
		vector<int> px_convex; vector <int> py_convex;
		int xmin, ymin;

		Mat image = imread(getString(s_image), CV_8UC1);

		uchar* pixelPtr_image = (uchar*)image.data;	//bien chay

		PerimeterRegion(bpx, bpy, pixelPtr_image, image.rows, image.cols);
		AreaRegion(px, py, pixelPtr_image, image.rows, image.cols);
		findAxisLength(px, py);
		BoundingBox(xmin, ymin, px, py);
		findConvexHullProperty(bpx, bpy, px_convex, py_convex);

		show_convexhull(image, px_convex, py_convex);
	}

	void getAll(float &compact, float &ti_so_truc, float &thon_dai, float &chu_nhat, float &loi)
	{
		compact = Compact();
		ti_so_truc = ti_so_truc_chinh();
		thon_dai = Thon_Dai();
		chu_nhat = Chu_Nhat();
		loi = Tinh_Loi();
	}

	//hien thi convex hull
	void show_convexhull(Mat image, vector<int> &px_convex, vector<int> &py_convex)
	{
		int thickness = 2;
		int lineType = 0;
		int size = px_convex.size();

		Mat img;
		cvtColor(image, img, CV_GRAY2RGB);
		
		for(int i = 1; i < size; i++)
			line(	img,
					Point(px_convex[i], py_convex[i]),
					Point(px_convex[i-1], py_convex[i-1]),
					Scalar( 255, 255, 0 ),
					thickness,
					lineType );

		line(	img,
				Point(px_convex[0], py_convex[0]),
				Point(px_convex[size-1], py_convex[size-1]),
				Scalar( 255, 255, 0 ),
				thickness,
				lineType );

		for(int i = 0; i < size; i++)
			circle(	img,
					Point(px_convex[i], py_convex[i]),
					1,
					Scalar( 255, 0, 255 ),
					thickness,
					lineType );

		imshow(getString(s_image), img);
	}
#pragma endregion
};