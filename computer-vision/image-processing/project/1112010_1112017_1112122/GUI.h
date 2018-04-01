#pragma once

#include "..\Libraries\Headers\opencv2\core\core.hpp"
#include "..\Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "..\Libraries\Headers\opencv2\imgproc\imgproc.hpp"

using namespace cv;

namespace My1112010_1112017_1112122 {
	public ref class GUI
	{
	public:
		GUI(void)
		{
		}

		//Hàm hiển thị ảnh
		//image: ảnh cần hiển thị
		//windowName: tên của cửa sổ hiển thị ảnh
		void displayImage( Mat image, char* windowName )
		{
			namedWindow(windowName, CV_WINDOW_AUTOSIZE );// Create a window for display.
			imshow(windowName, image);                   // Show our image inside it.
		}

		//ham ve duong thang
		void MyLine( Mat img, Point start, Point end, int R, int G, int B )
		{
			int thickness = 1;
			int lineType = 8;
			line( img, start, end, Scalar( B, G, R ), thickness, lineType );
		}

		//ham ve histogram day anh
		void DrawHistogram( float* Histogram, int bin, char* window_name)
		{
			float max = 0, tmp;
			int max_bin = bin*bin*bin;
			int R, G, B;
			int range = 256/bin;
			Mat image(400, max_bin*2, CV_8UC3, Scalar(255,255,255));

			for(int i = 0; i < 72; i++)
			{
				if(max < Histogram[i])
				{
					max = Histogram[i];
				}
			}

			tmp = (int)(300 / max);

			Point start, end;
			start.x = 0;
			start.y = 400;

			for(int i = 0; i < max_bin; i++)
			{
				start.x = end.x = 2*i;
				end.y = (int)(400 - tmp * Histogram[i]);

				R = i/(bin*bin);
				G = (i - bin*bin*R)/bin;
				B = i - R*bin*bin - G*bin;

				if(G < 0)
					G = 0;
				if(B < 0)
					B = 0;

				MyLine( image, start, end, R*range + range/2, G*range + range/2, B*range + range/2 );

				start.x = end.x = start.x+1;
				MyLine( image, start, end, R*range + range/2, G*range + range/2, B*range + range/2 );
			}

			displayImage(image, window_name);
		}

		//ham ve histogram day anh
		void DrawEdgeHistogram( float* Histogram, char* window_name)
		{
			float max = 0;
			int tmp;

			int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
			double fontScale = 0.5;
			int thickness = 2;

			for(int i = 0; i < 72; i++)
			{
				if(max < Histogram[i])
				{
					max = Histogram[i];
				}
			}

			tmp = (int)(300 / max);

			Mat image(400, 288, CV_8UC3, Scalar(255,255,255));

			Point start, end, textOrg;
			start.x = 0;
			start.y = 300;

			for(int i = 0; i < 72; i++)
			{
				start.x = end.x = 4*i;
				end.y = start.y - (int)(tmp * Histogram[i]);

				if(i%18 != 0)
					MyLine( image, start, end, 0, 0, 255 );
				else
				{
					MyLine( image, start, end, 255, 0, 0 );
					if(i == 0)
					{
						textOrg.x = 1;
						textOrg.y = 320;
						putText( image, "0", textOrg, fontFace, fontScale,
								 Scalar(0,0,255), thickness, 8);
					}
					else if(i == 18)
					{
						textOrg.x = 61;
						textOrg.y = 320;
						putText( image, "90", textOrg, fontFace, fontScale,
								 Scalar(0,0,255), thickness, 8);
					}
					else if(i == 36)
					{
						textOrg.x = 130;
						textOrg.y = 320;
						putText( image, "180", textOrg, fontFace, fontScale,
								 Scalar(0,0,255), thickness, 8);
					}
					else if(i == 54)
					{
						textOrg.x = 202;
						textOrg.y = 320;
						putText( image, "270", textOrg, fontFace, fontScale,
								 Scalar(0,0,255), thickness, 8);
					}
				}

				start.x = end.x = start.x+1;
				
				if(i%18 != 0)
					MyLine( image, start, end, 0, 0, 255 );
				else
				{
					MyLine( image, start, end, 255, 0, 0 );
				}
			}

			displayImage(image, window_name);
		}

		//ham ve histogram day anh
		void DrawCoherenceVector( float** Vector, int bin )
		{
			int max_bin = bin*bin*bin;
			float max[2] = {0, 0};
			int tmp[2], tmp2;
			int R, G, B;
			int range = 256/bin;
			Mat image(600, max_bin*2, CV_8UC3, Scalar(255,255,255));

			for(int t = 0; t < 2; t++)
			{
				for(int i = 0; i < max_bin; i++)
				{
					if(max[t] < Vector[t][i])
					{
						max[t] = Vector[t][i];
					}
				}

				tmp[t] = (int)(300 / max[t]);
			}

			Point start, end;
			start.x = 0;

			for(int t = 0; t < 2; t++)
			{
				start.y = 300 * (t + 1);

				for(int i = 0; i < max_bin; i++)
				{
					start.x = end.x = 2*i;
					end.y = start.y - (int)(Vector[t][i] * tmp[t]);

					R = i/(bin*bin);
					G = (i - bin*bin*R)/bin;
					B = i - R*bin*bin - G*bin;

					if(G < 0)
						G = 0;
					if(B < 0)
						B = 0;

					MyLine( image, start, end, R*range + range/2, G*range + range/2, B*range + range/2 );

					start.x = end.x = start.x+1;
					MyLine( image, start, end, R*range + range/2, G*range + range/2, B*range + range/2 );
				}
			}

			displayImage(image, "Vector lien ket mau");
		}

		//ham ve histogram day anh
		void DrawCoherenceVector( float** Vector )
		{
			int max_bin = 72;
			float max[2] = {0, 0};
			int tmp[2], tmp2;

			int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
			double fontScale = 0.5;
			int thickness = 2;

			Mat image(600, max_bin*4, CV_8UC3, Scalar(255,255,255));

			for(int t = 0; t < 2; t++)
			{
				for(int i = 0; i < 72; i++)
				{
					if(max[t] < Vector[t][i])
					{
						max[t] = Vector[t][i];
					}
				}

				tmp[t] = (int)(250 / max[t]);
			}

			Point start, end, textOrg;
			start.x = 0;

			for(int t = 0; t < 2; t++)
			{
				start.y = 250 * (t + 1) + 50 * t;

				for(int i = 0; i < 72; i++)
				{
					tmp2 = tmp[t] * Vector[t][i];
					
					start.x = end.x = 4*i;
					end.y = start.y - (int)(tmp2);

					if(i%18 != 0)
						MyLine( image, start, end, 0, 0, 255 );
					else
					{
						MyLine( image, start, end, 255, 0, 0 );
						if(i == 0)
						{
							textOrg.x = 1;
							textOrg.y = 300*t + 270;
							putText( image, "0", textOrg, fontFace, fontScale,
									 Scalar(0,0,255), thickness, 8);
						}
						else if(i == 18)
						{
							textOrg.x = 61;
							textOrg.y = 300*t + 270;
							putText( image, "90", textOrg, fontFace, fontScale,
									 Scalar(0,0,255), thickness, 8);
						}
						else if(i == 36)
						{
							textOrg.x = 130;
							textOrg.y = 300*t + 270;
							putText( image, "180", textOrg, fontFace, fontScale,
									 Scalar(0,0,255), thickness, 8);
						}
						else if(i == 54)
						{
							textOrg.x = 202;
							textOrg.y = 300*t + 270;
							putText( image, "270", textOrg, fontFace, fontScale,
									 Scalar(0,0,255), thickness, 8);
						}
					}

					start.x = end.x = start.x+1;
				
					if(i%18 != 0)
						MyLine( image, start, end, 0, 0, 255 );
					else
					{
						MyLine( image, start, end, 255, 0, 0 );
					}
				}
			}

			displayImage(image, "Luoc do lien ket he so goc");
		}
	};
}