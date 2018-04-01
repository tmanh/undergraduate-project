#pragma once

#include "..\Libraries\Headers\opencv2\core\core.hpp"
#include "..\Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "..\Libraries\Headers\opencv2\imgproc\imgproc.hpp"

using namespace cv;
using namespace std;

#define PI 3.14159265359F
#define EPSILON 0.05F

ref class TAMURA_TEXTURE
{
private:
	System::String^ s_image;

	float coarseness;
	float contrast;
	float directionality;
	float line_likeness;
	float regularity;
	float roughness;
public:
	TAMURA_TEXTURE(void);

public:
	//bin: so bin mau
	//n: bac cua contrast
	//t: nguong bien canh
	//r: he so chuan hoa
	//r2: he so chuan hoa tinh quy luat
	void ComputeAll(int bin, int n, int t, float r, float d, float r2)
	{
		Mat image = imread(getString(s_image), CV_8UC1);

		uchar* pixelPtr_image = (uchar*)image.data;	//bien chay
		computeCoarseness(pixelPtr_image, image.cols, image.rows);

		pixelPtr_image = (uchar*)image.data;	//bien chay
		computeContrast(pixelPtr_image, image.cols, image.rows, bin, n);

		computeDirectionality( pixelPtr_image, image.cols, image.rows,
								t, bin, r);
	
		computeLine_likeness(pixelPtr_image, image.cols, image.rows, t, bin, d);
	
		computeRegularity(r);

		computeRoughness();
	}

	//ham tinh coarseness
	void computeCoarseness(uchar* img, int width, int height)
	{
		float **avg[6];
		
		for(int i = 0; i < 6; i++)
		{
			avg[i] = new float* [height];
			for(int j = 0; j < height; j++)
				avg[i][j] = new float [width];
		}

		float E_k[6];
		int t = 0;
		int S_max = 0, S;
		coarseness = 0;

		findAllAverageMatrix(img, avg, width, height);

		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
			{
				findE_k(avg, width, height, E_k, i, j);
				t = find_max_index(E_k);
				S = (int)pow((float)2, t);
				if(S > S_max)
					S_max = S;
				coarseness += S;
			}

		coarseness /= (width * height * S_max);

		for(int i = 0; i < 6; i++)
		{
			for(int j = 0; j < height; j++)
				delete []avg[i][j];
			delete []avg[i];
		}
	}

	//tinh contrast
	//k: so bin luong hoa muc xam
	//n: bac cua contrast
	void computeContrast(uchar* img, int width, int height, int k, int n)
	{
		contrast = 0;
		float mean, var, kur, alpha;

		float* _Histogram = new float[k];

		Histogram(img, _Histogram, width, height, k);
		mean = meanIntensity(_Histogram, k);
		var = momentIntensity(_Histogram, k, 2, mean);
		kur = momentIntensity(_Histogram, k, 4, mean);
		alpha = kur/pow(var, 2);

		contrast = sqrt(var) / pow(alpha, n);

		delete []_Histogram;
	}

	//tinh tinh co huong
	//t: nguong cua bien do canh
	//nbin: so bin chuan hoa
	//r: he so chuan hoa
	void computeDirectionality(	uchar* img, int width, int height,
								int t, int nbin, float r)
	{
		//khai bao du lieu
		int length, i, j, d;

		vector<int> listMaxima;
		vector<int> listLeftMinima;
		vector<int> listRightMinima;

		float** Gradient, **Oriented;

		Gradient = new float* [height];
		Oriented = new float* [height];
		for(int i = 0; i < height; i++)
		{
			Gradient[i] = new float [width];
			Oriented[i] = new float [width];
		}

		float* Histogram = new float [nbin];

		//thu thi tinh toan
		findEdgeAndOriented(img, width, height, Gradient, Oriented);
		HistogramEdgeOriented(width, height, t, nbin, Gradient, Oriented, Histogram);
		listRealMaxima(Histogram, nbin, listMaxima, listLeftMinima, listRightMinima);

		directionality = 0; length = listMaxima.size();
		for(i = 0; i < length; i++)
		{
			j = listLeftMinima[i];
			while(true)
			{
				d = cirDistance(j, listMaxima[i], nbin);
				directionality += r*length*d*d*Histogram[j];

				if(j == listMaxima[i])
					break;
				j++;
				if(j == nbin)
					j = 0;
			}
			
			j = listMaxima[i];
			while(true)
			{
				d = cirDistance(listMaxima[i], j, nbin);
				directionality += r*length*d*d*Histogram[j];
				
				if(j == listRightMinima[i])
					break;
				j++;
				if(j == nbin)
					j = 0;
			}
		}
		directionality = 1 - directionality;

		//Huy du lieu da xin cap phat
		delete []Histogram;

		for(int i = 0; i < height; i++)
		{
			delete []Gradient[i];
			delete []Oriented[i];
		}
		delete []Gradient;
		delete []Oriented;
	}

	void computeLine_likeness(uchar* img, int width, int height,
							  int t, int nbin, float d)
	{
		int tmp1, tmp2;

		float** P = new float* [nbin];
		for(int i = 0; i < nbin; i++)
			P[i] = new float[nbin];

		for(int i = 0; i < nbin; i++)
			for(int j = 0; j < nbin; j++)
				P[i][j] = 0;

		float** Gradient, **Oriented;

		Gradient = new float* [height];
		Oriented = new float* [height];
		for(int i = 0; i < height; i++)
		{
			Gradient[i] = new float [width];
			Oriented[i] = new float [width];
		}

		findEdgeAndOriented(img, width, height, Gradient, Oriented);

		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				if(Gradient[i][j] < t)
					continue;
				for(int dx = -(int)d; dx <= d; dx++)
				{
					for(int dy = -(int)d; dy <= d; dy++)
					{
						if(dx == 0 && dy == 0)
							continue;
						if(!(i+dx<0 || i+dx>=height || j+dy<0 || j+dy>= width))
						{
							if(Distance(i,j,i+dx,j+dy) >= d-EPSILON && Distance(i,j,i+dx,j+dy) <= d+EPSILON)
							{
								tmp1 = (int)ceil(nbin*Oriented[i][j]/PI-2) + nbin;
								tmp2 = (int)ceil(nbin*Oriented[i+dx][j+dy]/PI-2) + nbin;

								tmp1 = tmp1%nbin;
								tmp2 = tmp2%nbin;

								P[tmp1][tmp2]++;
							}
						}
					}
				}

			}
		}

		float sum = 0;
		line_likeness = 0;

		for(int i = 0; i < nbin; i++)
		{
			for(int j = 0; j < nbin; j++)
			{
				line_likeness += P[i][j]*cos((i-j)*2*PI/nbin);
				sum += P[i][j];
			}
		}

		line_likeness /= sum;

		for(int i = 0; i < height; i++)
		{
			delete []Gradient[i];
			delete []Oriented[i];
		}
		delete []Gradient;
		delete []Oriented;

		for(int i = 0; i < nbin; i++)
			delete []P[i];
		delete []P;
	}

	void computeRegularity(float r)
	{
		regularity = 1 - r*(coarseness + contrast + directionality + line_likeness);
	}

	void computeRoughness()
	{
		roughness = (coarseness + contrast);
	}

	//bin: so bin mau
	//n: bac cua contrast
	//t: nguong bien canh
	//r: he so chuan hoa
	//r2: he so chuan hoa tinh quy luat
	//d: khoang cach trong luoc do tuong quan goc canh
	void getAll(float &Coarseness, float &Contrast, float &Directionality,
				float&Line_likeness, float &Regularity, float &Roughness,
				int bin, int n, int t, float r, float d, float r2)
	{
		ComputeAll(bin, n, t, r, d, r2);

		Coarseness = coarseness;
		Contrast = contrast;
		Directionality = directionality;
		Line_likeness = line_likeness;
		Regularity = regularity;
		Roughness = roughness;
	}

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

	//ham tinh khoang cach hai diem
	float Distance(int x1, int y1, int x2, int y2)
	{
		return sqrt((float)(x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	}

	//ham tinh khoang cach hai diem
	int cirDistance(int x, int y, int max)
	{
		if(x == y)
			return 0;
		int d = 0;
		while(true)
		{
			x++;
			d++;
			if(x == max)
				x = 0;
			if(x == y)
				return d;
		}
	}

	int find_max_index(float E_k[])
	{
		int max = 0;
		for(int i = 0; i < 6; i++)
			if(E_k[i] > E_k[max])
				max = i;
		return max;
	}

	//tim ma tran trung binh do xam diem anh
	void findAverageMatrix(uchar* img, float** result, int &width, int &height, int &k)
	{
		int start = -k/2;
		int end = k/2;
		int ptr_img;
		int count;

		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
			{
				result[i][j] = 0;
			}

		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				count = 0;
				for(int dx = start; dx <= end; dx++)
				{
					for(int dy = start; dy <= end; dy++)
					{
						if(i+dx < 0 || i+dx >= height || j+dy < 0 || j+dy >= width)
							continue;
						count++;
						ptr_img = (i + dx) * width + j + dy;
						result[i][j] += img[ptr_img];
					}
				}
				result[i][j] /= count;
			}

		}
	}

	//tim day ma tran trung binh do xam diem anh
	void findAllAverageMatrix(uchar* img, float** result[], int &width, int &height)
	{
		for(int i = 0; i < 6; i++)
			findAverageMatrix(img, result[i], width, height, i);
	}

	//tim vector gia tri E-k cua diem anh
	void findE_k(float** avg[], int &width, int &height, float E_k[], int &x, int &y)
	{
		float E_hk, E_vk;
		int index1, index2;

		for(int i = 0; i < 6; i++)
		{
			index1 = (int)floor(x + pow((float)2,i-1));
			index2 = (int)ceil(x - pow((float)2,i-1));
			if(index1 >= height || index2 < 0)
			{
				E_hk = -1;
			}
			else
			{
				E_hk = abs(avg[i][index1][y] - avg[i][index2][y]);
			}

			index1 = (int)floor(y + pow((float)2,i-1));
			index2 = (int)ceil(y - pow((float)2,i-1));
			if(index1 >= width || index2 < 0)
			{
				E_vk = -1;
			}
			else
			{
				E_vk = abs(avg[i][x][index1] - avg[i][x][index2]);
			}

			E_k[i] = max(E_hk, E_vk);
		}
	}

	//ham lam tron so
	int round(float data)
	{
		return int(data);
	}

	//ham luong hoa
	int quantize(int G, int bin)
	{
		return round((float)G/256*bin);
	}

	//tinh histogram muc xam
	void Histogram(uchar* img, float* result, int width, int height, int k)
	{
		int size = width*height;

		for(int i = 0; i < k; i++)
			result[i] = 0;

		int index = 0;
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				index = i * width + j;
				result[quantize(img[index], k)]++;
			}
		}

		for(int i = 0; i < k; i++)
			result[i] /= size;
	}

	//tinh gia tri trung binh do xam diem anh
	//k: so bin muc xam luong hoa
	float meanIntensity(float* histogram, int k)
	{
		float mean = 0;

		for(int i = 0; i < k; i++)
			mean += i * histogram[i];

		return mean;
	}

	//tinh gia tri moment do xam diem anh
	//n: so bin mau luong hoa
	//k: bac cua contrast
	float momentIntensity(float* histogram, int n, int k, float mean)
	{
		float moment = 0;

		for(int i = 0; i < n; i++)
			moment += pow((float)(i - mean), k) * histogram[i];

		return moment;
	}

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

		result /= count;

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
	//Gradient, Oriented: bien do, huong canh
	void findEdgeAndOriented(uchar* img, int width, int height,
							 float** Gradient, float** Oriented)
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
					Oriented[i][j] = PI/2;
				}
				else
				{
					Oriented[i][j] = atan(Vertical[i][j]/Horizontal[i][j]) + PI/2;
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
	void HistogramEdgeOriented(int width, int height, int t, int n,
							   float** Gradient, float** Oriented, float* Histogram)
	{
		for(int i = 0; i < n; i++)
			Histogram[i] = 0;

		int count = 0, tmp;

		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				if(Gradient[i][j] > t)
				{
					tmp = int(ceil(n*Oriented[i][j]/PI-1/2)) % n;
					Histogram[tmp]++;
					count++;
				}
			}
		}

		for(int i = 0; i < n; i++)
			Histogram[i] /= count;
	}

	//kiem tra cuc tieu va cuc dai
	//h: gia tri can kiem tra
	//h1, h2: 2 gia tri lien ke
	int checkExtrema(const float &h, const float &h1, const float &h2)
	{
		if(((h - h1) < 0 && (h - h2) <= 0) ||
		   ((h - h1) <= 0 && (h - h2) < 0))
		{
			return -1;
		}
		else if(((h - h1) > 0 && (h - h2) >= 0) ||
				((h - h1) >= 0 && (h - h2) > 0))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	//tim danh sach diem cuc tri
	//listExtrema: vi tri cuc tri
	//listLabel: luu lai nhan cua cuc tri (cuc dai: 1, cuc tieu: -1)
	void findExtrema(float* Histogram, int n, vector<int> &listExtrema, vector<int> &listLabel)
	{
		int tmp;
		tmp = checkExtrema(Histogram[0], Histogram[n-1], Histogram[1]);

		if(tmp != 0)
		{
			listExtrema.push_back(0);
			listLabel.push_back(tmp);
		}

		for(int i = 1; i < n - 2; i++)
		{
			tmp = checkExtrema(Histogram[i], Histogram[i-1], Histogram[i+1]);

			if(tmp != 0)
			{
				listExtrema.push_back(i);
				listLabel.push_back(tmp);
			}
		}

		tmp = checkExtrema(Histogram[n-1], Histogram[n-2], Histogram[0]);

		if(tmp != 0)
		{
			listExtrema.push_back(n-1);
			listLabel.push_back(tmp);
		}
	}

	//tim cac diem thuc su la cuc dai
	void listRealMaxima(float* Histogram, int n, vector<int> &listMaxima,
						vector<int> &listLeftMinima, vector<int> &listRightMinima)
	{
		//neu chi co 1 gia tri luong hoa
		if(n < 2)
			return;

		vector<int> lExtrema;
		vector<int> lLabel;
		
		findExtrema(Histogram, n, lExtrema, lLabel);
		int length = lExtrema.size();

		if(length < 2)
			return;

		if(lLabel[0] == 1)
		{
			if(Histogram[lExtrema[length-1]]/Histogram[0] < 0.5 &&
				Histogram[lExtrema[1]]/Histogram[0] < 0.5)
			{
				listMaxima.push_back(lExtrema[0]);
				listLeftMinima.push_back(lExtrema[length-1]);
				listRightMinima.push_back(lExtrema[1]);
			}
		}

		for(int i = 1; i < length - 2; i++)
		{
			if(lLabel[i] == 1)
			{
				if(Histogram[lExtrema[i-1]]/Histogram[i] < 0.5 &&
					Histogram[lExtrema[i+1]]/Histogram[i] < 0.5)
				{
					listMaxima.push_back(lExtrema[i]);
					listLeftMinima.push_back(lExtrema[i-1]);
					listRightMinima.push_back(lExtrema[i+1]);
				}
			}
		}

		if(lLabel[length-1] == 1)
		{
			if(Histogram[lExtrema[length-2]]/Histogram[length-1] < 0.5 &&
				Histogram[lExtrema[0]]/Histogram[length-1] < 0.5)
			{
				listMaxima.push_back(lExtrema[length-1]);
				listLeftMinima.push_back(lExtrema[length-2]);
				listRightMinima.push_back(lExtrema[0]);
			}
		}
	}

	
};

