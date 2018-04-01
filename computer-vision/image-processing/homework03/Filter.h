#include "PixelOperators.h"

//Doc mask tu file
//Input:
//	fn: ten file can mo
//	mask: mat na can tai len
//Output: so dong (cot) cua mask
int read(char* fn, int **&mask, int &n);

//Tinh tich chap giua mat na va anh tai vi tri x,y
//Input:
//	img: anh goc
//	x,y: toa do cua mot pixel tren anh goc,  noi se dat tam cua mat na thuc hien
//	mask: mat na, mac dinh 3x3
//Output:
//	gia tri moi cua pixel vi tri x,y
int cvl(Mat &img, int x, int y, int** mask, const int &size);

//Tinh tich chap giua mat na va anh
//Input:
//	img: anh goc
//	mask: mat na, mac dinh 3x3
//Output:
//	anh moi
Mat cvl(Mat &img, int** mask, const int &size, const int &sum);

//Ham lo tong quat
//Input
//	img: anh goc
//	mask: bo loc
//	size: kich thuoc bo loc
//Output
//	anh sau khi da duoc xu ly
Mat doDerivativeConv(Mat img, float** mask, const int &size);

//Ham khoi tao mask
//Input:
//	mask: mat na
void initavgmask(int **&mask, const int &size);

//Ham khoi tao mask
//Input:
//	mask1, mask2: mat na
void initrobertsmask(int **&mask1, int **&mask2, const int &size);

//Ham khoi tao mask
//Input:
//	mask1, mask2: mat na
void initprewittmask(int **&mask1, int **&mask2);

//Ham khoi tao mask
//Input:
//	mask1, mask2: mat na
void initsobelmask(int **&mask1, int **&mask2);

//Ham loc cao trung binh
//Input:
//	img: anh goc
//Output:
//	anh moi
Mat filthighavg(Mat &img, const int &size, float alpha);

//Ham loc cao roberts
//Input:
//	img: anh goc
//Output:
//	anh moi
Mat filthighroberts(Mat &img, const int &size);

//Ham loc cao prewitt
//Input:
//	img: anh goc
//Output:
//	anh moi
Mat filthighprewitt(Mat &img, const int &size);

//Ham loc cao prewitt
//Input:
//	img: anh goc
//Output:
//	anh moi
Mat filthighsobel(Mat &img, const int &size);

//Loc trung vi
//Input:
//	img: anh goc
//	size: kich thuoc bo loc
//Output:
//	anh moi
Mat median(Mat img, int size);

//Tinh trung vi tai vi tri x, y
//Input:
//	img: anh goc
//	size: kich thuoc bo loc
//Output:
//	anh moi
int median(const Mat &img, int &x, int &y, const int &size, int tsx[], int tx[], int ty[]);