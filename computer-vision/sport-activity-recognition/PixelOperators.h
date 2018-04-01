#ifndef _pixeloperators_
#define _pixeloperators_

#include <iostream>
#include <fstream>

#include "Libraries\Headers\opencv2\core\core.hpp"
#include "Libraries\Headers\opencv2\highgui\highgui.hpp"

using namespace std;
using namespace cv;

#define MAX_N 256
#define MAX_XHIS 256
#define MAX_YHIS 600
#define MAX 255
#define MIN	0

//tim max
//data: mang du lieu
int max(int data[]);

//khoi tao gia tri cho mang
//data: mang du lieu
//n: so phan tu mang
//a: gia tri can khoi tao
void init(int data[], int n, int a);

//khoi tao histogram
//R: histogram kenh mau red
//G: histogram kenh mau green
//B: histogram kenh mau blue
void initHistogram(int R[], int G[], int B[]);

//dem cac gia tri mau trong anh
//R: kenh mau red
//G: kenh mau green
//B: kenh mau blue
void countHistogram(Mat image, int R[], int G[], int B[]);

//dem cac gia tri mau trong anh
//Gray: cuong do xam
void countHistogram(Mat image, int Gray[]);

//tinh histogram cua anh
//R: histogram kenh mau red
//G: histogram kenh mau green
//B: histogram kenh mau blue
void computeHistogram(Mat image, int R[], int G[], int B[]);

//tinh histogram cua anh
//Gray: histogram cuong do xam
void computeHistogram(Mat image, int Gray[]);

//Hàm kiểm Mat rỗng hay không
//image: Mat cần kiểm tra
bool checkMat(Mat image);

//Hàm hiển thị ảnh
//image: ảnh cần hiển thị
//windowName: tên của cửa sổ hiển thị ảnh
void displayImage(Mat image, char* windowName);

//Hàm thay đổi độ sáng cho ảnh màu hoac ảnh xám, cách 1
//image: ảnh gốc
//delta: khoảng tăng thêm hoặc giảm xuống của độ sáng
Mat changePixelIntensity1(Mat image, uchar delta);

//Hàm thay đổi độ sáng cho ảnh màu, cách 2
//image: ảnh gốc
//delta: khoảng tăng thêm hoặc giảm xuống của độ sáng
Mat changePixelIntensity2_color(Mat image, uchar delta);

//Hàm thay đổi độ sáng cho ảnh màu hoặc xám, cách 2
//image: ảnh gốc
//delta: khoảng tăng thêm hoặc giảm xuống của độ sáng
Mat changePixelIntensity2(Mat image, uchar delta);

//Hàm thay đổi độ sáng cho xám, cách 2
//image: ảnh gốc
//delta: khoảng tăng thêm hoặc giảm xuống của độ sáng
Mat changePixelIntensity2_gray(Mat image, uchar delta);

//Hàm tạo ảnh âm bản
//image: ảnh gốc
Mat invertImage(Mat image);

//Hàm tạo ảnh âm bản xam
//image: ảnh gốc
Mat invertGrayImage(Mat image);

//Hàm tạo ảnh âm bản mau
//image: ảnh gốc
Mat invertColorImage(Mat image);

//Hàm tạo ảnh xám từ ảnh màu
//image: ảnh gốc
Mat RGB2GRAY(Mat image);

//Ham tim gia tri cua pixel co cuong do lon nhat
//image: ảnh gốc
void max_min(Mat image, Vec3b &intensity_max, Vec3b &intensity_min);

//Ham tim gia tri cua pixel co cuong do lon nhat
//image: ảnh gốc
void max_min(Mat image, uchar &intensity_max, uchar &intensity_min);

//Hàm tang giam do tuong phan
//image: ảnh gốc
Mat contrast(Mat image, double a);

//Hàm tang giam do tuong phan anh xam
//image: ảnh gốc
Mat contrastGray(Mat image, double a);

//Hàm tang giam do tuong phan anh mau
//image: ảnh gốc
Mat contrastColor(Mat image, double a);

//ham tinh histogram anh mau
//image: anh goc
//R: histogram cua kenh red
//G: histogram cua kenh green
//B: histogram cua kenh blue
void Histogram(Mat image, int R[], int G[], int B[]);

//ham tinh histogram anh xam
//image: anh goc
//Gray: histogram cua cuong do xam
void Histogram(Mat image, int Gray[]);

//ham ve histogram
//R: histogram cua kenh red
//G: histogram cua kenh green
//B: histogram cua kenh blue
//name: ten cua so muon dat
void DrawHistogram(int R[], int G[], int B[], char* name);

//ham ve histogram cua mot anh mau
//image: hinh muon ve histogram
//name: ten cua so muon dat
void DrawHistogram(Mat image, char* name);

//ham ve histogram anh xam
//Gray: histogram cua anh do xam
void DrawHistogram(int Gray[], char* name);

//ham chuyen tu YCbCr sang RGB
Mat YCbCr2RGB(Mat Scr);

//ham chuyen tu RGB sang YCbCr
Mat RGB2YCbCr(Mat Scr);

//ham chuyen tu CYMK sang RGB
Mat CYMK2RGB(Mat Scr);

//ham chuyen tu RGB sang CYMK
Mat RGB2CYMK(Mat Scr);
#endif