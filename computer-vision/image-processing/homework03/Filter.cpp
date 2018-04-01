#include "Filter.h"

//Doc mask tu file
//Input:
//	fn	:	ten file can mo
//	mask:	mat na can tai len
//	n	:	so dong (cot) cua mask
//Output:	he so cua mask
int read(char* fn, int **&mask, int &n)
{
	int s = 0;

	ifstream fin(fn);

	if(fin == NULL)
		return -1;

	fin >> n;

	mask = new int* [n];
	for(int i = 0; i < n; i++)
		mask[i] = new int [n];

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
		{
			fin >> mask[i][j];
			s += mask[i][j];
		}

	fin.close();

	return s;
}

//Tinh tich chap giua mat na va anh tai vi tri x,y
//Input:
//	img: anh goc
//	x,y: toa do cua mot pixel tren anh goc,  noi se dat tam cua mat na thuc hien
//	mask: mat na, mac dinh 3x3
//Output:
//	gia tri moi cua pixel vi tri x,y
int cvl(Mat &img, int x, int y, int** mask, const int &size)
{
	float s = 0;
	int t = 0;

	int tx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int ty[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(x + tx[i] < 0 || x + tx[i] >= img.rows)
				continue;
			if(y + ty[j] < 0 || y + ty[j] >= img.cols)
				continue;

			//lay gia tri pixel trong anh o tung vi tri tuong ung mask
			t = img.data[(x + tx[i]) * img.step + y + ty[j]];

			//nhan voi gia tri cua mask[i][j] va cong don vao ket qua
			s += mask[i][j] * t;
		}
	}
	return (int)s;
}

//Tinh tich chap giua mat na va anh
//Input:
//	img: anh goc
//	mask: mat na, mac dinh 3x3
//Output:
//	anh moi
Mat cvl(Mat &img, int** mask, const int &size, const int &sum)
{
	Mat result(img.rows, img.cols, img.type());

	for(int i = 0; i < img.rows; i++)
		for(int j = 0; j < img.cols; j++)
		{
			uchar &intensity_result = result.at<uchar>(i, j);

			if(sum != 0)
				intensity_result = cvl(img, i, j, mask, size) / sum;
			else
				intensity_result = cvl(img, i, j, mask, size);
		}

	return result;
}

//Ham loc tong quat
//Input
//	img: anh goc
//	mask1, mask2: 2 bo loc doc va ngang
//	size: kich thuoc bo loc
//Output
//	anh sau khi da duoc xu ly
Mat doDerivativeConv(Mat img, int** mask1, int** mask2, int size, const int& sum1, const int& sum2)
{
	//tao anh ket qua
	Mat result(img.rows, img.cols, img.type());
	float fGradient1, fGradient2;

	for(int i = 0; i < img.rows; i++)
		for(int j = 0; j < img.cols; j++)
		{
			if(sum1 != 0)
				fGradient1 = cvl(img, i, j, mask1, size) / sum1;
			else
				fGradient1 = cvl(img, i, j, mask1, size);
			if(sum2 != 0)
				fGradient2 = cvl(img, i, j, mask2, size) / sum2;
			else
				fGradient2 = cvl(img, i, j, mask2, size);

			uchar &intensity_result = result.at<uchar>(i, j);

			intensity_result = (int)sqrt(fGradient1 * fGradient1 + fGradient2 * fGradient2);
		}

	return result;
}

//Ham khoi tao mask
//Input:
//	mask: mat na
void initavgmask(int **&mask, const int &size)
{
	mask = new int* [size];
	for(int i = 0; i < size; i++)
		mask[i] = new int [size];

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			mask[i][j]= 1;
}

//Ham khoi tao mask
//Input:
//	mask1, mask2: mat na
void initrobertsmask(int **&mask1, int **&mask2, const int &size)
{
	mask1 = new int* [size];
	for(int i = 0; i < size; i++)
		mask1[i] = new int [size];

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			mask1[i][j]= 0;

	mask2 = new int* [size];
	for(int i = 0; i < size; i++)
		mask2[i] = new int [size];

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			mask2[i][j]= 0;

	mask1[size/2][size/2] = 1;
	mask1[size/2][size/2 + 1] = -1;
	mask2[size/2][size/2] = 1;
	mask2[size/2 + 1][size/2] = -1;
}

//Ham khoi tao mask
//Input:
//	mask1, mask2: mat na
void initprewittmask(int **&mask1, int **&mask2)
{
	mask1 = new int* [3];
	for(int i = 0; i < 3; i++)
		mask1[i] = new int [3];

	mask1[0][0] = mask1[0][1] = mask1[0][2] = -1;
	mask1[1][0] = mask1[1][1] = mask1[1][2] = 0;
	mask1[2][0] = mask1[2][1] = mask1[2][2] = 1;

	mask2 = new int* [3];
	for(int i = 0; i < 3; i++)
		mask2[i] = new int [3];

	mask2[0][0] = mask2[1][0] = mask2[2][0] = -1;
	mask2[0][1] = mask2[1][1] = mask2[2][1] = 0;
	mask2[0][2] = mask2[1][2] = mask2[2][2] = 1;
}

//Ham khoi tao mask
//Input:
//	mask1, mask2: mat na
void initsobelmask(int **&mask1, int **&mask2)
{
	mask1 = new int* [3];
	for(int i = 0; i < 3; i++)
		mask1[i] = new int [3];

	mask1[0][0] = mask1[0][2] = -1;
	mask1[0][1] = -2;
	mask1[1][0] = mask1[1][1] = mask1[1][2] = 0;
	mask1[2][0] = mask1[2][2] = 1;
	mask1[2][1] = 2;

	mask2 = new int* [3];
	for(int i = 0; i < 3; i++)
		mask2[i] = new int [3];

	mask2[0][0] = mask2[2][0] = -1;
	mask2[1][0] = -2;
	mask2[0][1] = mask2[1][1] = mask2[2][1] = 0;
	mask2[0][2] = mask2[2][2] = 1;
	mask2[1][2] = 2;
}

//Ham loc cao trung binh
//Input:
//	img: anh goc
//Output:
//	anh moi
Mat filthighavg(Mat &img, const int &size, float alpha)
{
	int** mask;
	int size2 = size * size, tmp1 = 0, tmp2 = 0;
	Mat result(img.rows, img.cols, img.type());

	initavgmask(mask, size);

	for(int i = 0; i < img.rows; i++)
		for(int j = 0; j < img.cols; j++)
		{
			uchar &intensity_result = result.at<uchar>(i, j);
			uchar &intensity_image = img.at<uchar>(i, j);
			tmp1 = alpha * intensity_image;
			tmp2 = cvl(img, i, j, mask, size) / size2;
			intensity_result = saturate_cast<uchar>(tmp1 - tmp2);
		}

	for(int i = 0; i < size; i++)
		delete []mask[i];
	delete []mask;

	return result;
}

//Ham loc cao roberts
//Input:
//	img: anh goc
//Output:
//	anh moi
Mat filthighroberts(Mat &img, const int &size)
{
	int** mask1, **mask2;
	int size2 = size * size, s1, s2;
	initrobertsmask(mask1, mask2, size);
	Mat result(img.rows, img.cols, img.type());

	for(int i = 1; i < img.rows; i++)
		for(int j = 1; j < img.cols; j++)
		{
			uchar &iresult = result.at<uchar>(i, j);

			s1 = (cvl(img, i, j, mask1, size)) * (cvl(img, i, j, mask1, size));
			s2 = (cvl(img, i, j, mask2, size)) * (cvl(img, i, j, mask2, size));
			iresult = sqrt(float(s1 + s2));
		}

	for(int i = 0; i < size; i++)
	{
		delete []mask1[i];
		delete []mask2[i];
	}
	delete []mask1;
	delete []mask2;

	return result;
}

//Ham loc cao prewitt
//Input:
//	img: anh goc
//Output:
//	anh moi
Mat filthighprewitt(Mat &img, const int &size)
{
	int** mask1, **mask2;
	int size2 = size * size, s1, s2;
	initprewittmask(mask1, mask2);
	Mat result(img.rows, img.cols, img.type());

	for(int i = 1; i < img.rows; i++)
		for(int j = 1; j < img.cols; j++)
		{
			uchar &iresult = result.at<uchar>(i, j);

			s1 = (cvl(img, i, j, mask1, size) * cvl(img, i, j, mask1, size));
			s2 = (cvl(img, i, j, mask2, size) * cvl(img, i, j, mask2, size));
			iresult = sqrt(float(s1 + s2));
		}

	for(int i = 0; i < size; i++)
	{
		delete []mask1[i];
		delete []mask2[i];
	}
	delete []mask1;
	delete []mask2;

	return result;
}

//Ham loc cao prewitt
//Input:
//	img: anh goc
//Output:
//	anh moi
Mat filthighsobel(Mat &img, const int &size)
{
	int** mask1, **mask2;
	int size2 = size * size, s1, s2;
	initsobelmask(mask1, mask2);
	Mat result(img.rows, img.cols, img.type());

	for(int i = 1; i < img.rows; i++)
		for(int j = 1; j < img.cols; j++)
		{
			uchar &iresult = result.at<uchar>(i, j);

			s1 = (cvl(img, i, j, mask1, size) * cvl(img, i, j, mask1, size));
			s2 = (cvl(img, i, j, mask2, size) * cvl(img, i, j, mask2, size));
			iresult = sqrt(float(s1 + s2));
		}

	for(int i = 0; i < size; i++)
	{
		delete []mask1[i];
		delete []mask2[i];
	}
	delete []mask1;
	delete []mask2;

	return result;
}

//Loc trung vi
//Input:
//	img: anh goc
//	size: kich thuoc bo loc
//Output:
//	anh moi
Mat median(Mat img, int size)
{
	size *= size;

	Mat result(img.rows, img.cols, img.type());

	int tx[9] = {-img.step, -img.step, -img.step, 0, 0, 0, img.step, img.step, img.step};
	int tsx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int ty[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

	for(int i = 0; i < img.rows; i++)
		for(int j = 0; j < img.cols; j++)
		{
			uchar &intensity_result = result.at<uchar>(i, j);

			intensity_result = median(img, i, j, size, tsx, tx, ty);
		}

	return result;
}

//Tinh trung vi tai vi tri x, y
//Input:
//	img: anh goc
//	size: kich thuoc bo loc
//Output:
//	anh moi
int median(const Mat &img, int &x, int &y, const int &size, int tsx[] , int tx[], int ty[])
{
	int tmp, count = 0, sx = x * img.step;

	int t[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

	int i, j;

	for(i = 0; i < size; i++)
	{
		if(x + tsx[i] < 0 || x + tsx[i] >= img.rows)
			continue;
		if(y + ty[i] < 0 || y + ty[i] >= img.cols)
			continue;

		//lay gia tri pixel trong anh o tung vi tri tuong ung mask
		t[count] = img.data[sx + tx[i] + y + ty[i]];

		//dem so o chua du lieu
		count++;
	}

	for(i = 0; i < count; i++)
		for(j = i; j < count; j++)
			if(t[i] > t[j])
			{
				tmp = t[i];
				t[i] = t[j];
				t[j] = tmp;
			}

	if(count % 2 == 0)
		return t[count / 2];
	else
		return t[count / 2 + 1];
}