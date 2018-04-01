#include "Libraries\Headers\opencv2\core\core.hpp"
#include "Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "Libraries\Headers\opencv2\objdetect\objdetect.hpp"
#include "Libraries\Headers\opencv2\gpu\gpu.hpp"
#include "Libraries\Headers\opencv2\imgproc\imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;


Mat get_hogdescriptor_visual_image(Mat& origImg, 
	vector<float>& descriptorValues,
	Size winSize,
	Size cellSize,
	int scaleFactor,
	double viz_factor)
{
	Mat visual_image;
	resize(origImg, visual_image, Size(origImg.cols*scaleFactor, origImg.rows*scaleFactor));

	int gradientBinSize = 9;

	float radRangeForOneBin = 3.14 / (float)gradientBinSize;

	int cells_in_x_dir = winSize.width / cellSize.width;
	int cells_in_y_dir = winSize.height / cellSize.height;
	int totalnrofcells = cells_in_x_dir * cells_in_y_dir;
	float*** gradientStrengths = new float**[cells_in_y_dir];
	int** cellUpdateCounter = new int*[cells_in_y_dir];
	for (int y = 0; y<cells_in_y_dir; y++)
	{
		gradientStrengths[y] = new float*[cells_in_x_dir];
		cellUpdateCounter[y] = new int[cells_in_x_dir];
		for (int x = 0; x<cells_in_x_dir; x++)
		{
			gradientStrengths[y][x] = new float[gradientBinSize];
			cellUpdateCounter[y][x] = 0;

			for (int bin = 0; bin<gradientBinSize; bin++)
				gradientStrengths[y][x][bin] = 0.0;
		}
	}

	int blocks_in_x_dir = cells_in_x_dir - 1;
	int blocks_in_y_dir = cells_in_y_dir - 1;

	int descriptorDataIdx = 0;
	int cellx = 0;
	int celly = 0;

	for (int blockx = 0; blockx<blocks_in_x_dir; blockx++)
	{
		for (int blocky = 0; blocky<blocks_in_y_dir; blocky++)
		{
			for (int cellNr = 0; cellNr<4; cellNr++)
			{
				int cellx = blockx;
				int celly = blocky;
				if (cellNr == 1) celly++;
				if (cellNr == 2) cellx++;
				if (cellNr == 3)
				{
					cellx++;
					celly++;
				}

				for (int bin = 0; bin<gradientBinSize; bin++)
				{
					float gradientStrength = descriptorValues[descriptorDataIdx];
					descriptorDataIdx++;

					gradientStrengths[celly][cellx][bin] += gradientStrength;
				} 

				cellUpdateCounter[celly][cellx]++;

			} 


		} 
	} 

	for (int celly = 0; celly<cells_in_y_dir; celly++)
	{
		for (int cellx = 0; cellx<cells_in_x_dir; cellx++)
		{

			float NrUpdatesForThisCell = (float)cellUpdateCounter[celly][cellx];

			for (int bin = 0; bin<gradientBinSize; bin++)
			{
				gradientStrengths[celly][cellx][bin] /= NrUpdatesForThisCell;
			}
		}
	}


	cout << "descriptorDataIdx = " << descriptorDataIdx << endl;

	for (int celly = 0; celly<cells_in_y_dir; celly++)
	{
		for (int cellx = 0; cellx<cells_in_x_dir; cellx++)
		{
			int drawX = cellx * cellSize.width;
			int drawY = celly * cellSize.height;

			int mx = drawX + cellSize.width / 2;
			int my = drawY + cellSize.height / 2;

			rectangle(visual_image,
				Point(drawX*scaleFactor, drawY*scaleFactor),
				Point((drawX + cellSize.width)*scaleFactor,
				(drawY + cellSize.height)*scaleFactor),
				CV_RGB(100, 100, 100),
				1);

			for (int bin = 0; bin<gradientBinSize; bin++)
			{
				float currentGradStrength = gradientStrengths[celly][cellx][bin];

				if (currentGradStrength == 0)
					continue;

				float currRad = bin * radRangeForOneBin + radRangeForOneBin / 2;

				float dirVecX = cos(currRad);
				float dirVecY = sin(currRad);
				float maxVecLen = cellSize.width / 2;
				float scale = viz_factor;

				float x1 = mx - dirVecX * currentGradStrength * maxVecLen * scale;
				float y1 = my - dirVecY * currentGradStrength * maxVecLen * scale;
				float x2 = mx + dirVecX * currentGradStrength * maxVecLen * scale;
				float y2 = my + dirVecY * currentGradStrength * maxVecLen * scale;

				line(visual_image,
					Point(x1*scaleFactor, y1*scaleFactor),
					Point(x2*scaleFactor, y2*scaleFactor),
					CV_RGB(0, 0, 255),
					1);

			} 

		}
	} 

	for (int y = 0; y<cells_in_y_dir; y++)
	{
		for (int x = 0; x<cells_in_x_dir; x++)
		{
			delete[] gradientStrengths[y][x];
		}
		delete[] gradientStrengths[y];
		delete[] cellUpdateCounter[y];
	}
	delete[] gradientStrengths;
	delete[] cellUpdateCounter;

	return visual_image;

}
int main(int argc, const char * argv[])
{
	if(argc != 2)
	{
		cout << "Vui long thu lai!!!" << endl;
	}
	else
	{
		Mat img_raw1 = imread(argv[1], 1); 
		namedWindow("original");
		imshow("original", img_raw1);

		Mat img_raw;
		resize(img_raw1, img_raw, Size(64, 128));

		Mat img;
		cvtColor(img_raw, img, CV_RGB2GRAY);

		HOGDescriptor d;

		vector<float> descriptorsValues;
		vector<Point> locations;
		d.compute(img, descriptorsValues, Size(0, 0), Size(0, 0), locations);

		cout << "HOG descriptor size is " << d.getDescriptorSize() << endl;
		cout << "img dimensions: " << img.cols << " width x " << img.rows << "height" << endl;
		cout << "Found " << descriptorsValues.size() << " descriptor values" << endl;
		cout << "Nr of locations specified : " << locations.size() << endl;

		FILE* f = fopen("HOGDescriptor.csv", "w");
		for (int i = 0; i < descriptorsValues.size(); ++i)
			fprintf(f, "%f\n", descriptorsValues[i]);
		fclose(f);

		Mat res = get_hogdescriptor_visual_image(img_raw, descriptorsValues, Size(64, 128), Size(8, 8), 4, 3);
		resize(res, res, img_raw1.size());
		namedWindow("HOG");
		imshow("HOG", res);

		waitKey();
	}
}