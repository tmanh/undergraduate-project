/*
THIS IS MADE BY ddkhoa@fit.hcmus.edu.vn
YOU CAN USE IT WITH YOUR OWN RESPONSIBILITY
PLEASE KEEP THIS AUTHOR INFORMATION WHEN SHARING IT
THANK YOU!
*/

#include "PixelOperators.h"

//tim max
//data: mang du lieu
int max(int data[])
{
	int max = 0;
	for(int i = 0; i < MAX_N; i++)
		if(data[max] < data[i])
			max = i;

	return data[max];
}

//khoi tao gia tri cho mang
void initTable(int data[], int n, int a)
{
	for(int i = 0; i <= n; i++)
		data[i] = a;
}

//dem cac gia tri mau trong anh
//R: kenh mau red
//G: kenh mau green
//B: kenh mau blue
void countHistogram(Mat image, int R[], int G[], int B[])
{
	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			Vec3b &intensity_image = image.at<Vec3b>(i, j);

			B[intensity_image.val[0]]++;
			G[intensity_image.val[1]]++;
			R[intensity_image.val[2]]++;
		}
	}
}

//dem cac gia tri mau trong anh
//Gray: cuong do xam
void countHistogram(Mat image, int Gray[])
{
	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			uchar &intensity_image = image.at<uchar>(i, j);

			Gray[intensity_image]++;
		}
	}
}

//tinh histogram cua anh
//R: histogram kenh mau red
//G: histogram kenh mau green
//B: histogram kenh mau blue
void computeHistogram(Mat image, int R[], int G[], int B[])
{
	int max_r, max_g, max_b;

	max_r = max(R);
	max_g = max(G);
	max_b = max(B);

	for(int i = 0; i < 256; i++)
	{
		B[i] *= 200;
		G[i] *= 200;
		R[i] *= 200;

		B[i] /= max_b;
		G[i] /= max_g;
		R[i] /= max_r;
	}
}

//tinh histogram cua anh
//Gray: histogram cuong do xam
void computeHistogram(Mat image, int Gray[])
{
	int max_gray = max(Gray);

	for(int i = 0; i < 256; i++)
	{
		Gray[i] *= 200;
		Gray[i] /= max_gray;
	}
}

//khoi tao histogram
//R: histogram kenh mau red
//G: histogram kenh mau green
//B: histogram kenh mau blue
void initHistogram(int R[], int G[], int B[])
{
	initTable(R,MAX,0);
	initTable(G,MAX,0);
	initTable(B,MAX,0);
}

//Hàm kiểm Mat rỗng hay không
//image: Mat cần kiểm tra
bool checkMat(Mat image)
{
	if(!image.data)
	{
		return 1;
	}
	return 0;
}

//Hàm hiển thị ảnh
//image: ảnh cần hiển thị
//windowName: tên của cửa sổ hiển thị ảnh
void displayImage(Mat image, char* windowName)
{
    namedWindow(windowName, CV_WINDOW_AUTOSIZE );// Create a window for display.
	imshow(windowName, image);                   // Show our image inside it.
	//cvWaitKey(0);								// wait until enter something
}

//Hàm thay đổi độ sáng cho ảnh màu hoặc ảnh xám, cách 1
//image: ảnh gốc
//delta: khoảng tăng thêm hoặc giảm xuống của độ sáng
Mat changePixelIntensity1(Mat image, uchar delta)
{
	Mat result(image.rows, image.cols,image.type());

	uchar* pixelPtr_image = (uchar*)image.data;
	uchar* pixelPtr_mat = (uchar*)result.data;

	int rowIndex, colIndex, nChannels = image.channels(); //nChannels==1 ảnh xám, nChannels==3 ảnh 3 kênh màu

	int cn = image.channels();
	for(int i = 0; i < image.rows; i++)
	{
		rowIndex = i*image.step;
		for(int j = 0; j < image.cols; j++)
		{	
			colIndex = j*cn;
			for (int k = 0 ; k < nChannels ; k++) //k=0 Blue; k=1 Green; k=2 Red
				pixelPtr_mat[rowIndex + colIndex + k] = saturate_cast<uchar>(pixelPtr_image[rowIndex + colIndex + k] + delta);
		}
	}
	return result;
}

//Hàm thay đổi độ sáng cho ảnh màu, cách 2
//image: ảnh gốc
//delta: khoảng tăng thêm hoặc giảm xuống của độ sáng
Mat changePixelIntensity2_colors(Mat image, uchar delta)
{
	Mat result(image.rows, image.cols,image.type());

	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			Vec3b &intensity_image = image.at<Vec3b>(i, j);
			Vec3b &intensity_result = result.at<Vec3b>(i,j);

			for(int k = 0; k < image.channels(); k++) 
				intensity_result.val[k] = saturate_cast<uchar>(intensity_image.val[k] + delta);
		 }
	}
	return result;
}

//Hàm thay đổi độ sáng cho xám, cách 2
//image: ảnh gốc
//delta: khoảng tăng thêm hoặc giảm xuống của độ sáng
Mat changePixelIntensity2_gray(Mat image, uchar delta)
{
	Mat result(image.rows, image.cols,image.type());

	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			uchar &intensity_image = image.at<uchar>(i, j);
			uchar &intensity_result = result.at<uchar>(i,j);

			intensity_result = saturate_cast<uchar>(intensity_image + delta);
		 }
	}
	return result;
}

//Hàm thay đổi độ sáng cho ảnh màu hoặc xám, cách 2
//image: ảnh gốc
//delta: khoảng tăng thêm hoặc giảm xuống của độ sáng
Mat changePixelIntensity2(Mat image, uchar delta)
{
	if(image.channels() == 1)
		return changePixelIntensity2_gray(image, delta);
	else
		return changePixelIntensity2_colors(image, delta);
}

//Hàm tạo ảnh âm bản mau
//image: ảnh gốc
Mat invertColorImage(Mat image)
{
	Mat result(image.rows, image.cols,image.type());

	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			Vec3b &intensity_image = image.at<Vec3b>(i, j);
			Vec3b &intensity_result = result.at<Vec3b>(i,j);

			for(int k = 0; k < image.channels(); k++) 
				intensity_result.val[k] = MAX - intensity_image.val[k];
		 }
	}

	return result;
}

//Hàm tạo ảnh âm bản xam
//image: ảnh gốc
Mat invertGrayImage(Mat image)
{
	Mat result(image.rows, image.cols,image.type());

	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			uchar &intensity_image = image.at<uchar>(i, j);
			uchar &intensity_result = result.at<uchar>(i,j);

			intensity_result = MAX - intensity_image;
		 }
	}

	return result;
}

//Hàm tạo ảnh âm bản
//image: ảnh gốc
Mat invertImage(Mat image)
{
	if(image.channels() == 1)
		return invertGrayImage(image);
	else
		return invertColorImage(image);
}

//Hàm tạo ảnh xám từ ảnh màu
//image: ảnh gốc
Mat RGB2GRAY(Mat image)
{
	Mat result(image.rows, image.cols, CV_8UC3 );
	uchar tmp;

	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			Vec3b &intensity_image = image.at<Vec3b>(i, j);
			Vec3b &intensity_result = result.at<Vec3b>(i,j);

			tmp =	0.11 * intensity_image.val[0] +
					0.59 * intensity_image.val[1] + 
					0.3 * intensity_image.val[2];

			for(int k = 0; k < image.channels(); k++)
				intensity_result.val[k] = tmp;
		 }
	}

	return result;
}

//Ham tim gia tri cua pixel co cuong do lon nhat
//image: ảnh gốc
void max_min(Mat image, Vec3b &intensity_max, Vec3b &intensity_min)
{
	intensity_max = image.at<Vec3b>(0, 0);
	intensity_min = image.at<Vec3b>(0, 0);

	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			Vec3b &intensity_image = image.at<Vec3b>(i, j);

			for(int k = 0; k < image.channels(); k++)
			{
				if(intensity_max.val[k] < intensity_image.val[k])
					intensity_max.val[k] = intensity_image.val[k];

				if(intensity_min.val[k] > intensity_image.val[k])
					intensity_min.val[k] = intensity_image.val[k];
			}
		}
	}
}

//Ham tim gia tri cua pixel co cuong do lon nhat
//image: ảnh gốc
void max_min(Mat image, uchar &intensity_max, uchar &intensity_min)
{
	intensity_max = intensity_min = 0;

	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			uchar &intensity_image = image.at<uchar>(i, j);

			if(intensity_max < intensity_image)
				intensity_max = intensity_image;

			if(intensity_min > intensity_image)
				intensity_min = intensity_image;
		}
	}
}

//Hàm tang giam do tuong phan anh xam
//image: ảnh gốc
Mat contrastGray(Mat image, double a)
{
	Mat result(image.rows, image.cols, image.type());
	uchar intensity_max, intensity_min, intensity_mean;

	max_min(image, intensity_max, intensity_min);

	intensity_mean = image.at<uchar>(0, 0);
	
	intensity_mean = (intensity_max + intensity_min) / 2;
	
	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			uchar &intensity_image = image.at<uchar>(i, j);
			uchar &intensity_result = result.at<uchar>(i,j);

			intensity_result = saturate_cast<uchar>(intensity_mean + 
							   a * (intensity_image - intensity_mean));
		 }
	}

	return result;
}

//Hàm tang giam do tuong phan anh mau
//image: ảnh gốc
Mat contrastColor(Mat image, double a)
{
	Mat result(image.rows, image.cols, image.type());
	Vec3b intensity_max, intensity_min, intensity_mean;

	max_min(image, intensity_max, intensity_min);

	intensity_mean = image.at<Vec3b>(0, 0);
	
	for(int k = 0; k < image.channels(); k++)
		intensity_mean.val[k] = (intensity_max.val[k] + intensity_min.val[k]) / 2;
	
	for (int i = 0; i < image.rows; i++) 
	{
		for (int j = 0; j < image.cols; j++) 
		{
			Vec3b &intensity_image = image.at<Vec3b>(i, j);
			Vec3b &intensity_result = result.at<Vec3b>(i,j);

			for(int k = 0; k < image.channels(); k++)
			{
				intensity_result.val[k] = saturate_cast<uchar>(intensity_mean.val[k] + 
					  a * (intensity_image.val[k] - intensity_mean.val[k]));
			}
		 }
	}

	return result;
}

//Hàm tang giam do tuong phan
//image: ảnh gốc
Mat contrast(Mat image, double a)
{
	if(image.channels() == 1)
		return contrastGray(image, a);
	else
		return contrastColor(image, a);
}

//ham tinh histogram anh mau
//image: anh goc
//R: histogram cua kenh red
//G: histogram cua kenh green
//B: histogram cua kenh blue
void Histogram(Mat image, int R[], int G[], int B[])
{
	initHistogram(R, G, B);
	countHistogram(image, R, G, B);
	computeHistogram(image, R, G, B);
}

//ham tinh histogram anh xam
//image: anh goc
//Gray: histogram cua cuong do xam
void Histogram(Mat image, int Gray[])
{
	initTable(Gray, MAX, 0);
	countHistogram(image, Gray);
	computeHistogram(image, Gray);
}

//ham ve histogram anh mau
//R: histogram cua kenh red
//G: histogram cua kenh green
//B: histogram cua kenh blue
void DrawHistogram(int R[], int G[], int B[], char* name)
{
	Mat image(MAX_YHIS, MAX_XHIS, CV_8UC3, Scalar(MAX,MAX,MAX));

	int max_xhis = MAX_XHIS * 3;

	for(int i = 0; i < MAX_XHIS; i += 1)
	{
		for(int j = 199; j >= 200 - R[i]; j--)
		{
			image.data[j * max_xhis + i * 3 + 1] = 0;
			image.data[j * max_xhis + i * 3 + 0] = 0;
		}

		for(int j = 399; j >= 400 - G[i]; j--)
		{
			image.data[j * max_xhis + i * 3 + 2] = 0;
			image.data[j * max_xhis + i * 3 + 0] = 0;
		}

		for(int j = 599; j >= 600 - B[i]; j--)
		{
			image.data[j * max_xhis + i * 3 + 2] = 0;
			image.data[j * max_xhis + i * 3 + 1] = 0;
		}
	}

	displayImage(image, name);
}

//ham ve histogram anh xam
//Gray: histogram cua anh do xam
void DrawHistogram(int Gray[], char* name)
{
	Mat image(MAX_YHIS / 3, MAX_XHIS, CV_8UC1, Scalar(MAX));

	for(int i = 0; i < MAX_XHIS; i += 1)
	{
		for(int j = 199; j >= 200 - Gray[i]; j--)
		{
			image.data[j * MAX_XHIS + i] = 0;
		}
	}

	displayImage(image, name);
}

//ham ve histogram cua mot anh mau
//image: hinh muon ve histogram
//name: ten cua so muon dat
void DrawHistogram(Mat image, char* name)
{
	int R[256], G[256], B[256], Gray[256];

	if(image.type() == CV_8UC1)
	{
		Histogram(image, Gray);
		DrawHistogram(Gray, name);
	}
	else
	{
		Histogram(image, R, G, B);
		DrawHistogram(R, G, B, name);
	}
}

//ham chuyen tu YCbCr sang RGB
Mat YCbCr2RGB(Mat Scr)
{
	Mat result(Scr.rows, Scr.cols, Scr.type());
	
	for (int i = 0; i < Scr.rows; i++) 
	{
		for (int j = 0; j < Scr.cols; j++) 
		{
			Vec3b &intensity_image = Scr.at<Vec3b>(i, j);
			Vec3b &intensity_result = result.at<Vec3b>(i,j);

			intensity_result.val[0] =	intensity_image.val[0] +
										1.403 * (intensity_image.val[2] - 128);
			intensity_result.val[1] =	intensity_image.val[0] -
										0.344 * (intensity_image.val[1] - 128) -
										0.714 * (intensity_image.val[2] - 128);
			intensity_result.val[2] =	intensity_image.val[0] +
										1.77 * (intensity_image.val[1] - 128);
		 }
	}

	return result;
}

//ham chuyen tu RGB sang YCbCr
Mat RGB2YCbCr(Mat Scr){
    Mat result(Scr.rows, Scr.cols, Scr.type());
	
	for (int i = 0; i < Scr.rows; i++) 
	{
		for (int j = 0; j < Scr.cols; j++) 
		{
			Vec3b &intensity_image = Scr.at<Vec3b>(i, j);
			Vec3b &intensity_result = result.at<Vec3b>(i,j);

			intensity_result.val[0] =	0.299 * intensity_image.val[0] +
										0.587 * intensity_image.val[1] +
										0.114 * intensity_image.val[2];
			intensity_result.val[1] =	-0.1687 * intensity_image.val[0] -
										0.3313 * intensity_image.val[1] +
										0.5 * intensity_image.val[2] + 128;
			intensity_result.val[2] =	0.5 * intensity_image.val[0] -
										0.4187 * intensity_image.val[1] -
										0.0813 * intensity_image.val[2] + 128;
		 }
	}

	return result;
}

//ham chuyen tu CYMK sang RGB
Mat RGB2CYMK(Mat Scr)
{
	Mat result(Scr.rows, Scr.cols, CV_8UC4);

	float compute[3], minCYM;

	for (int i = 0; i < Scr.rows; i++) 
	{
		for (int j = 0; j < Scr.cols; j++) 
		{
			Vec3b &intensity_image = Scr.at<Vec3b>(i, j);
			Vec4b &intensity_result = result.at<Vec4b>(i,j);

			for(int i = 0; i < 3; i++)
				compute[i] = 1 - ((float)intensity_image.val[i] / 255);

			minCYM = min(compute[0], min(compute[1], compute[2]));

			for(int i = 0; i < 3; i++)
				compute[i] = (compute[i] - minCYM) / (1 - minCYM);

			intensity_result.val[0] =	255 * compute[0];
			intensity_result.val[1] =	255 * compute[1];
			intensity_result.val[2] =	255 * compute[2];
			intensity_result.val[3] =	255 * minCYM;
		 }
	}

	return result;
}

//ham chuyen tu RGB sang CYMK
Mat CYMK2RGB(Mat Scr)
{
	Mat result(Scr.rows, Scr.cols, CV_8UC3);

	for (int i = 0; i < Scr.rows; i++) 
	{
		for (int j = 0; j < Scr.cols; j++) 
		{
			Vec4b &intensity_image = Scr.at<Vec4b>(i, j);
			Vec3b &intensity_result = result.at<Vec3b>(i,j);

			uchar minCYM = intensity_image.val[3];

			for(int k = 0; k < 3; k++)
				intensity_result.val[k] =	255 - intensity_image.val[k] * (255 - minCYM) / 255 - minCYM;
		 }
	}

	return result;
}