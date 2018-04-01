#include "Action.h"


Action::Action(void)
{
	skeframes = skepoints = nofs = ncols = nrows = 0;
	fpadding = 0;
	ipadding = 0;
	roiDepth = cv::Rect(0,0, 240,240);
	roiRGB = cv::Rect(30,31, 445,435);
	size = Size(240, 240);
}


Action::~Action(void)
{
}

//doc header cua file chua skeleton
void Action::readSkeletonFileHeader(ifstream &fin)
{
	fin >> skeframes;
	fin >> skepoints;
}

//doc frame chua skeleton
void Action::readSkeleton(ifstream &fin, float** skeleton)
{
	fin >> ipadding;

	for(int j = 0; j < skepoints; j++)
	{
		fin >> ipadding >> fpadding >> fpadding >> fpadding;

		fin >> ipadding >> skeleton[j][0] >> skeleton[j][1] >> skeleton[j][2];
	}
}

//tim descriptor
//Mat Action::load(string rbg_fname, string depth_fname)
//{
//	int numberGesturePixel = 0, numberFrame = 1, meanDepthMotion = 0, tmp_meanDepth;
//	double max_dist; double min_dist;
//
//	SurfFeatureDetector detector( _minHessian );
//	SurfDescriptorExtractor extractor;
//
//	BFMatcher matcher;
//	std::vector< DMatch > matches;
//	std::vector< DMatch > good_matches;
//
//	VideoCapture cap(rbg_fname);
//	FILE * fp = fopen(strdup(depth_fname.c_str()), "rb");	//khai bao bien doc file tt do sau
//
//	ReadDepthMapSktBinFileHeader(fp, nofs, ncols, nrows);	//doc thong tin file depth
//
//	Mat motionRGB, motionDepth;
//	Mat depthMatA, depthMatB;
//	Mat frameA, frameB;	//khai bao bien duyet frame grayscale
//	Mat depthA, depthB, imageA, imageB, oldDescrip;
//	Mat descrip, result;
//
//	vector<KeyPoint> keyPoint;
//	vector<KeyPoint> old_keyPoint;
//
//	bool odd_frame = true;
//
//	CDepthMapSkt depthMapA, depthMapB;	//khai bao bien duyet frame depth
//	depthMapA.SetSize(nrows, ncols);	//it allocates space
//	depthMapB.SetSize(nrows, ncols);
//
//	//read first frame
//	cap.read(frameA);
//	imageA = frameA(roiRGB);
//	cv::resize(imageA, imageA, size);
//	cvtColor(imageA, imageA, CV_BGR2GRAY);
//
//	ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapA);
//
//	depthMatA = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);
//	depthMatB = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);
//
//	quantize(depthMapA, depthMatA, depthMapA.m_nrows * depthMapA.m_ncols);
//	depthA = depthMatA(roiDepth);
//
//	detector.detect(imageA, old_keyPoint);
//	removeKeyPoint(depthA, old_keyPoint, meanDepthMotion, true);
//	extractor.compute(imageA, old_keyPoint, oldDescrip);
//
//	//clone to initialize motionRGB and motionDepth
//	motionRGB = Mat(roiDepth.height, roiDepth.width, CV_8UC1);
//	motionDepth = depthMatA.clone();
//
//	while(true)
//	{
//		if(odd_frame == true)
//		{
//			if(!cap.read(frameB))
//				break;
//			imageB = frameB(roiRGB);
//			cv::resize(imageB, imageB, size);
//			cvtColor(imageB, imageB, CV_BGR2GRAY);
//
//			//the data will be stored in <depthMap>
//			ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapB);
//			quantize(depthMapB, depthMatB, depthMapB.m_nrows * depthMapB.m_ncols);
//			depthB = depthMatB(roiDepth);
//
//			tmp_meanDepth = 0;
//			numberGesturePixel += getGestureRegion(imageA, imageB, motionRGB, depthB, tmp_meanDepth);
//			meanDepthMotion += tmp_meanDepth;
//		}
//		else
//		{
//			if(!cap.read(frameA))
//				break;
//			imageA = frameA(roiRGB);
//			cv::resize(imageA, imageA, size);
//			cvtColor(imageA, imageA, CV_BGR2GRAY);
//
//			//the data will be stored in <depthMap>
//			ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapA);
//			quantize(depthMapA, depthMatA, depthMapA.m_nrows * depthMapA.m_ncols);
//			depthA = depthMatA(roiDepth);
//
//			tmp_meanDepth = 0;
//			numberGesturePixel += getGestureRegion(imageB, imageA, motionRGB, depthA, tmp_meanDepth);
//			meanDepthMotion += tmp_meanDepth;
//		}
//
//		cout << numberGesturePixel << " ";
//
//		if(numberGesturePixel > _number_point_thresh * pow(esilon, - numberFrame * numberFrame / 700) ||
//			numberFrame > 20)
//		{
//			//chuan hoa do sau trung binh cua chuyen dong
//			meanDepthMotion /= numberFrame;
//
//			if(odd_frame == true)
//			{
//				detector.detect(imageB, keyPoint);
//				if(numberFrame > 20)
//					removeKeyPoint(depthB, keyPoint, meanDepthMotion, false);
//				else
//					removeKeyPoint(depthB, keyPoint, meanDepthMotion, true);
//				extractor.compute(imageB, keyPoint, descrip);
//			}
//			else
//			{
//				detector.detect(imageA, keyPoint);
//				if(numberFrame > 20)
//					removeKeyPoint(depthB, keyPoint, meanDepthMotion, false);
//				else
//					removeKeyPoint(depthB, keyPoint, meanDepthMotion, true);
//				extractor.compute(imageA, keyPoint, descrip);
//			}
//
//			for(int i = 0; i < keyPoint.size(); i++)
//			{
//				circle(imageA, keyPoint[i].pt,1,Scalar(0,0,0));
//			}
//			imshow("vui",imageA);
//			waitKey(0);
//
//			if(oldDescrip.rows != 0)
//			{
//				matcher.match(descrip, oldDescrip, matches );
//				max_dist = 0; min_dist = 100;
//
//				double dist;
//				//-- Quick calculation of max and min distances between keypoints
//				for( int i = 0; i < descrip.rows; i++ )
//				{ 
//					dist = matches[i].distance;
//					if( dist < min_dist ) 
//						min_dist = dist;
//					if( dist > max_dist ) 
//						max_dist = dist;
//				}
//
//				good_matches.clear();
//				for( int i = 0; i < descrip.rows; i++ )
//				{ 
//					if( matches[i].distance <= max(0.02, 2 * min_dist) )
//					{ 
//						good_matches.push_back( matches[i]); 
//					}
//				}
//
//				for(int i = 0; i < good_matches.size(); i++)
//				{
//					circle(imageA, keyPoint[good_matches[i].queryIdx].pt,1,Scalar(255,255,0));
//				}
//				imshow("vui2",imageA);
//				waitKey(0);
//
//				oldDescrip = descrip.clone();
//				old_keyPoint = keyPoint;
//
//				for(int i = 0; i < good_matches.size(); i++)
//					result.push_back(descrip.row(good_matches[i].queryIdx));
//			}
//			else
//			{
//				result.push_back(descrip);
//				oldDescrip = descrip.clone();
//				old_keyPoint = keyPoint;
//			}
//			
//			//gan cac tham so = 0
//			numberGesturePixel = 0;
//			meanDepthMotion = 0;
//			numberFrame = 0;
//		}
//
//		odd_frame = !odd_frame;
//		numberFrame++;
//	}
//	return result;
//}

//tim descriptor(MHI)
Mat Action::load(string rbg_fname, string depth_fname)
{
	int numberGesturePixel = 0, numberFrame = 1, meanDepthMotion = 0, tmp_meanDepth;
	int sizeHistory;

	VideoCapture cap(rbg_fname);
	FILE * fp = fopen(strdup(depth_fname.c_str()), "rb");	//khai bao bien doc file tt do sau

	ReadDepthMapSktBinFileHeader(fp, nofs, ncols, nrows);	//doc thong tin file depth

	Mat motionRGB, motionDepth, motionRGBHistory;
	Mat depthMatA, depthMatB;
	Mat frameA, frameB;	//khai bao bien duyet frame grayscale
	Mat depthA, depthB, imageA, imageB, oldDescrip;
	Mat descrip, result;

	vector<KeyPoint> keyPoint;
	vector<KeyPoint> old_keyPoint;

	bool odd_frame = true;

	CDepthMapSkt depthMapA, depthMapB;	//khai bao bien duyet frame depth
	depthMapA.SetSize(nrows, ncols);	//it allocates space
	depthMapB.SetSize(nrows, ncols);

	//read first frame
	cap.read(frameA);
	imageA = frameA(roiRGB);
	cv::resize(imageA, imageA, size);
	cvtColor(imageA, imageA, CV_BGR2GRAY);

	ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapA);

	depthMatA = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);
	depthMatB = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);

	quantize(depthMapA, depthMatA, depthMapA.m_nrows * depthMapA.m_ncols);
	depthA = depthMatA(roiDepth);

	//clone to initialize motionRGB and motionDepth
	motionRGB = Mat(roiDepth.height, roiDepth.width, CV_8UC1);
	motionDepth = depthMatA.clone();
	motionRGBHistory = Mat(roiDepth.height, roiDepth.width, CV_8UC1, Scalar(0,0,0));
	uchar* ptr_history = (uchar*)motionRGBHistory.data;
	uchar* ptr_motion = (uchar*)motionRGB.data;
	sizeHistory = roiDepth.height * roiDepth.width;

	while(true)
	{
		if(odd_frame == true)
		{
			if(!cap.read(frameB))
				break;
			imageB = frameB(roiRGB);
			cv::resize(imageB, imageB, size);
			cvtColor(imageB, imageB, CV_BGR2GRAY);

			//the data will be stored in <depthMap>
			ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapB);
			quantize(depthMapB, depthMatB, depthMapB.m_nrows * depthMapB.m_ncols);
			depthB = depthMatB(roiDepth);

			tmp_meanDepth = 0;
			numberGesturePixel += getGestureRegion(imageA, imageB, motionRGB, depthB, tmp_meanDepth);
			meanDepthMotion += tmp_meanDepth;
		}
		else
		{
			if(!cap.read(frameA))
				break;
			imageA = frameA(roiRGB);
			cv::resize(imageA, imageA, size);
			cvtColor(imageA, imageA, CV_BGR2GRAY);

			//the data will be stored in <depthMap>
			ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapA);
			quantize(depthMapA, depthMatA, depthMapA.m_nrows * depthMapA.m_ncols);
			depthA = depthMatA(roiDepth);

			tmp_meanDepth = 0;
			numberGesturePixel += getGestureRegion(imageB, imageA, motionRGB, depthA, tmp_meanDepth);
			meanDepthMotion += tmp_meanDepth;
		}

		for(int i = 0; i < sizeHistory; i++)
		{
			ptr_history[i] = ptr_history[i] * 0.98 + ptr_motion[i];
		}

		/*imshow("motion", motionRGBHistory);
		waitKey(10);*/

		if(numberGesturePixel > _number_point_thresh * pow(esilon, - numberFrame * numberFrame / 700) ||
			numberFrame > 20)
		{
			result.push_back(compute(motionRGBHistory.clone()));
			
			//gan cac tham so = 0
			motionRGBHistory = Mat(roiDepth.height, roiDepth.width, CV_8UC1, Scalar(0,0,0));
			numberGesturePixel = 0;
			meanDepthMotion = 0;
			numberFrame = 0;

			ptr_history = (uchar*)motionRGBHistory.data;
			ptr_motion = (uchar*)motionRGB.data;
		}

		odd_frame = !odd_frame;
		numberFrame++;
	}
	return result;
}

//tim descriptor(fMHI + bMHI)
void Action::loadDepth(string rbg_fname, string depth_fname, Mat& fMHI, Mat& bMHI)
{
	int numberGesturePixel = 0, numberFrame = 1, meanDepthMotion = 0, tmp_meanDepth;
	int sizeHistory;

	VideoCapture cap(rbg_fname);
	FILE * fp = fopen(strdup(depth_fname.c_str()), "rb");	//khai bao bien doc file tt do sau

	ReadDepthMapSktBinFileHeader(fp, nofs, ncols, nrows);	//doc thong tin file depth

	Mat motionRGB, motionRGBHistory;
	Mat motionDepthIncrease, motionDepthDecrease, motionDepthIncreaseHistory, motionDepthDecreaseHistory;
	Mat depthMatA, depthMatB;
	Mat frameA, frameB;	//khai bao bien duyet frame grayscale
	Mat depthA, depthB, imageA, imageB, oldDescrip;
	Mat descrip, resultIncrease, resultDecrease;

	vector<KeyPoint> keyPoint;
	vector<KeyPoint> old_keyPoint;

	bool odd_frame = true;

	CDepthMapSkt depthMapA, depthMapB;	//khai bao bien duyet frame depth
	depthMapA.SetSize(nrows, ncols);	//it allocates space
	depthMapB.SetSize(nrows, ncols);

	//read first frame
	cap.read(frameA);
	imageA = frameA(roiRGB);
	cv::resize(imageA, imageA, size);
	cvtColor(imageA, imageA, CV_BGR2GRAY);
	//GaussianBlur(imageA, imageA, Size(3,3), 15);

	ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapA);

	depthMatA = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);
	depthMatB = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);

	quantize(depthMapA, depthMatA, depthMapA.m_nrows * depthMapA.m_ncols);
	depthA = depthMatA(roiDepth);

	//clone to initialize motionRGB and motionDepth
	motionDepthIncrease = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);
	motionDepthDecrease = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);

	motionDepthIncreaseHistory = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1, Scalar(0,0,0));
	motionDepthDecreaseHistory = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1, Scalar(0,0,0));

	uchar* ptr_Increase_history = (uchar*)motionDepthIncreaseHistory.data;
	uchar* ptr_Decrease_history = (uchar*)motionDepthDecreaseHistory.data;

	uchar* ptr_Increase_motion = (uchar*)motionDepthIncrease.data;
	uchar* ptr_Decrease_motion = (uchar*)motionDepthDecrease.data;

	motionRGB = Mat(roiDepth.height, roiDepth.width, CV_8UC1);
	motionRGBHistory = Mat(roiDepth.height, roiDepth.width, CV_8UC1, Scalar(0,0,0));
	
	uchar* ptr_history = (uchar*)motionRGBHistory.data;
	uchar* ptr_motion = (uchar*)motionRGB.data;

	sizeHistory = roiDepth.height * roiDepth.width;

	Mat element = getStructuringElement( 0,
                                       Size( 2*1 + 1, 2*1+1 ),
                                       Point( 1, 1 ) );

	int last_mean_motion_depth = 0;
	int number_of_frame_have_motion = 0;

	while(true)
	{
		if(odd_frame == true)
		{
			if(!cap.read(frameB))
				break;
			imageB = frameB(roiRGB);
			cv::resize(imageB, imageB, size);
			cvtColor(imageB, imageB, CV_BGR2GRAY);
			//GaussianBlur(imageB, imageB, Size(3,3), 15);

			//the data will be stored in <depthMap>
			ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapB);
			quantize(depthMapB, depthMatB, depthMapB.m_nrows * depthMapB.m_ncols);
			depthB = depthMatB(roiDepth);

			tmp_meanDepth = 0;
			getGestureRegion(imageA, imageB, motionRGB, depthB, tmp_meanDepth);
			
			if(tmp_meanDepth > 0)
				number_of_frame_have_motion++;
			meanDepthMotion += tmp_meanDepth;

			numberGesturePixel += getGesturDepthRegion(depthA, depthB, motionRGB,
													   motionDepthIncrease,
													   motionDepthDecrease, depthA, tmp_meanDepth);
		}
		else
		{
			if(!cap.read(frameA))
				break;
			imageA = frameA(roiRGB);
			cv::resize(imageA, imageA, size);
			cvtColor(imageA, imageA, CV_BGR2GRAY);
			//GaussianBlur(imageA, imageA, Size(3,3), 15);

			//the data will be stored in <depthMap>
			ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapA);
			quantize(depthMapA, depthMatA, depthMapA.m_nrows * depthMapA.m_ncols);
			depthA = depthMatA(roiDepth);

			tmp_meanDepth = 0;
			getGestureRegion(imageB, imageA, motionRGB, depthA, tmp_meanDepth);
			
			if(tmp_meanDepth > 0)
				number_of_frame_have_motion++;
			meanDepthMotion += tmp_meanDepth;

			numberGesturePixel += getGesturDepthRegion(depthB, depthA, motionRGB,
													   motionDepthIncrease,
													   motionDepthDecrease,
													   depthB, tmp_meanDepth);
		}

		/*imshow("fMHI", motionDepthIncreaseHistory);
		imshow("bMHI", motionDepthDecreaseHistory);
		waitKey(0);*/

		for(int i = 0; i < sizeHistory; i++)
		{
			ptr_Increase_history[i] = /*max(0,ptr_Increase_history[i] + ptr_Increase_motion[i])*/ptr_Increase_history[i] * 0.97 + ptr_Increase_motion[i];
			ptr_Decrease_history[i] = /*max(0,ptr_Decrease_history[i] + ptr_Decrease_motion[i])*/ptr_Decrease_history[i] * 0.97 + ptr_Decrease_motion[i];
		}

		if(numberGesturePixel > _number_point_depth_thresh * pow(esilon, - numberFrame * numberFrame / 700) ||
 			numberFrame > 20)
		{
			if(last_mean_motion_depth == 0 && numberFrame > 20 && numberGesturePixel < 100 && meanDepthMotion > 25)
			{
				meanDepthMotion /= number_of_frame_have_motion;
				getShape(meanDepthMotion, depthA, motionDepthIncreaseHistory);
			}
			else if(last_mean_motion_depth > 25 && numberFrame > 20 && numberGesturePixel < 100)
			{
				getShape(last_mean_motion_depth, depthA, motionDepthIncreaseHistory);
			}

			if(meanDepthMotion > 25)
				last_mean_motion_depth = meanDepthMotion;

			/*erode( motionDepthIncreaseHistory, motionDepthIncreaseHistory, element );
			erode( motionDepthDecreaseHistory, motionDepthDecreaseHistory, element );
			dilate( motionDepthIncreaseHistory, motionDepthIncreaseHistory, element );
			dilate( motionDepthDecreaseHistory, motionDepthDecreaseHistory, element );*/

			/*cout << numberFrame << " " << numberGesturePixel << endl;
			imshow("motion", motionDepthIncreaseHistory);
			waitKey(0);*/

			resultIncrease.push_back(compute2(motionDepthIncreaseHistory.clone()));
			resultDecrease.push_back(compute2(motionDepthDecreaseHistory.clone()));
			
			//gan cac tham so = 0
			motionDepthIncreaseHistory = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1, Scalar(0,0,0));
			motionDepthDecreaseHistory = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1, Scalar(0,0,0));
			numberGesturePixel = 0;
			meanDepthMotion = 0;
			numberFrame = 0;
			number_of_frame_have_motion = 0;

			ptr_Increase_history = (uchar*)motionDepthIncreaseHistory.data;
			ptr_Decrease_history = (uchar*)motionDepthDecreaseHistory.data;

			ptr_Increase_motion = (uchar*)motionDepthIncrease.data;
			ptr_Decrease_motion = (uchar*)motionDepthDecrease.data;
		}

		odd_frame = !odd_frame;
		numberFrame++;
	}
	fMHI = resultIncrease;
	bMHI = resultDecrease;
}

void Action::getShape(int mean_depth, Mat& depth, Mat& newmotion)
{
	uchar* ptr_depth = (uchar*)depth.data;
	uchar* ptr_motion = (uchar*)newmotion.data;

	int width, height, count, tmp, index, i, j;

	width = depth.cols; height = depth.rows;

	index = 0;

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			if(abs(ptr_depth[index] - mean_depth) <= 15)
			{
				ptr_motion[index] = 255;
			}
			else
			{
				ptr_motion[index] = 0;
			}
			index++;
		}
	}
}

//tim descriptor(HOG)
void Action::loadHOG(string rbg_fname, string depth_fname, Mat& HOG)
{
	int numberGesturePixel = 0, numberFrame = 1, meanDepthMotion = 0, tmp_meanDepth;
	int sizeHistory;

	VideoCapture cap(rbg_fname);
	FILE * fp = fopen(strdup(depth_fname.c_str()), "rb");	//khai bao bien doc file tt do sau

	ReadDepthMapSktBinFileHeader(fp, nofs, ncols, nrows);	//doc thong tin file depth

	Mat motionRGB, motionRGBHistory;
	Mat motionDepthIncrease, motionDepthDecrease, motionDepthIncreaseHistory, motionDepthDecreaseHistory;
	Mat depthMatA, depthMatB;
	Mat frameA, frameB;	//khai bao bien duyet frame grayscale
	Mat depthA, depthB, imageA, imageB, oldDescrip;
	Mat descrip, resultIncrease, resultDecrease;

	vector<KeyPoint> keyPoint;
	vector<KeyPoint> old_keyPoint;

	bool odd_frame = true;

	CDepthMapSkt depthMapA, depthMapB;	//khai bao bien duyet frame depth
	depthMapA.SetSize(nrows, ncols);	//it allocates space
	depthMapB.SetSize(nrows, ncols);

	//read first frame
	cap.read(frameA);
	imageA = frameA(roiRGB);
	cv::resize(imageA, imageA, size);
	cvtColor(imageA, imageA, CV_BGR2GRAY);

	ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapA);

	depthMatA = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);
	depthMatB = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);

	quantize(depthMapA, depthMatA, depthMapA.m_nrows * depthMapA.m_ncols);
	depthA = depthMatA(roiDepth);

	//clone to initialize motionRGB and motionDepth
	motionDepthIncrease = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);
	motionDepthDecrease = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);

	motionDepthIncreaseHistory = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1, Scalar(0,0,0));
	motionDepthDecreaseHistory = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1, Scalar(0,0,0));

	uchar* ptr_Increase_history = (uchar*)motionDepthIncreaseHistory.data;
	uchar* ptr_Decrease_history = (uchar*)motionDepthDecreaseHistory.data;

	uchar* ptr_Increase_motion = (uchar*)motionDepthIncrease.data;
	uchar* ptr_Decrease_motion = (uchar*)motionDepthDecrease.data;

	motionRGB = Mat(roiDepth.height, roiDepth.width, CV_8UC1);
	motionRGBHistory = Mat(roiDepth.height, roiDepth.width, CV_8UC1, Scalar(0,0,0));
	
	uchar* ptr_history = (uchar*)motionRGBHistory.data;
	uchar* ptr_motion = (uchar*)motionRGB.data;

	sizeHistory = roiDepth.height * roiDepth.width;

	HOGDescriptor hog;

	//hog.compute();

	while(true)
	{
		if(odd_frame == true)
		{
			if(!cap.read(frameB))
				break;
			imageB = frameB(roiRGB);
			cv::resize(imageB, imageB, size);
			cvtColor(imageB, imageB, CV_BGR2GRAY);

			//the data will be stored in <depthMap>
			ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapB);
			quantize(depthMapB, depthMatB, depthMapB.m_nrows * depthMapB.m_ncols);
			depthB = depthMatB(roiDepth);

			tmp_meanDepth = 0;
			getGestureRegion(imageA, imageB, motionRGB, depthB, tmp_meanDepth);
			numberGesturePixel += getGesturDepthRegion(depthA, depthB, motionRGB,
													   motionDepthIncrease,
													   motionDepthDecrease, depthA, tmp_meanDepth);
			meanDepthMotion += tmp_meanDepth;
		}
		else
		{
			if(!cap.read(frameA))
				break;
			imageA = frameA(roiRGB);
			cv::resize(imageA, imageA, size);
			cvtColor(imageA, imageA, CV_BGR2GRAY);

			//the data will be stored in <depthMap>
			ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapA);
			quantize(depthMapA, depthMatA, depthMapA.m_nrows * depthMapA.m_ncols);
			depthA = depthMatA(roiDepth);

			tmp_meanDepth = 0;
			getGestureRegion(imageB, imageA, motionRGB, depthA, tmp_meanDepth);
			numberGesturePixel += getGesturDepthRegion(depthB, depthA, motionRGB,
													   motionDepthIncrease,
													   motionDepthDecrease,
													   depthB, meanDepthMotion);
			meanDepthMotion += tmp_meanDepth;
		}

		for(int i = 0; i < sizeHistory; i++)
		{
			ptr_Increase_history[i] = ptr_Increase_history[i] * 0.99 + ptr_Increase_motion[i];
			ptr_Decrease_history[i] = ptr_Decrease_history[i] * 0.99 + ptr_Decrease_motion[i];
		}

		if(numberGesturePixel > _number_point_depth_thresh * pow(esilon, - numberFrame * numberFrame / 700) ||
 			numberFrame > 20)
		{
			resultIncrease.push_back(compute(motionDepthIncreaseHistory.clone()));
			resultDecrease.push_back(compute(motionDepthDecreaseHistory.clone()));
			
			//gan cac tham so = 0
			motionDepthIncreaseHistory = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1, Scalar(0,0,0));
			motionDepthDecreaseHistory = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1, Scalar(0,0,0));
			numberGesturePixel = 0;
			meanDepthMotion = 0;
			numberFrame = 0;

			ptr_Increase_history = (uchar*)motionDepthIncreaseHistory.data;
			ptr_Decrease_history = (uchar*)motionDepthDecreaseHistory.data;

			ptr_Increase_motion = (uchar*)motionDepthIncrease.data;
			ptr_Decrease_motion = (uchar*)motionDepthDecrease.data;
		}

		odd_frame = !odd_frame;
		numberFrame++;
	}
	HOG = resultIncrease;
}


////tim descriptor
//void Action::load(char* rbg_fname, char* depth_fname, char* ske_fname)
//{
//	int numberGesturePixel = 0, numberFrame = 1, meanDepthMotion = 0, tmp_meanDepth;
//
//	SurfFeatureDetector detector( _minHessian );
//	SurfDescriptorExtractor extractor;
//
//	VideoCapture cap(rbg_fname);
//	FILE * fp = fopen(depth_fname, "rb");	//khai bao bien doc file tt do sau
//
//	ReadDepthMapSktBinFileHeader(fp, nofs, ncols, nrows);	//doc thong tin file depth
//
//	Mat motionRGB, motionDepth;
//	Mat depthMatA, depthMatB;
//	Mat frameA, frameB;	//khai bao bien duyet frame grayscale
//	Mat depthA, depthB, imageA, imageB;
//	Mat descrip;
//
//	Mat element = getStructuringElement( 0,
//										Size( 3, 3 ));
//	Mat His;
//
//	vector<KeyPoint> keyPoint;
//
//	bool odd_frame = true;
//
//	CDepthMapSkt depthMapA, depthMapB;	//khai bao bien duyet frame depth
//	depthMapA.SetSize(nrows, ncols);	//it allocates space
//	depthMapB.SetSize(nrows, ncols);
//
//	//read first frame
//	cap.read(frameA);
//	imageA = frameA(roiRGB);
//	cv::resize(imageA, imageA, size);
//	cvtColor(imageA, imageA, CV_BGR2GRAY);
//	
//	ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapA);
//
//	depthMatA = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);
//	depthMatB = Mat(depthMapA.m_nrows, depthMapA.m_ncols, CV_8UC1);
//
//	quantize(depthMapA, depthMatA, depthMapA.m_nrows * depthMapA.m_ncols);
//
//	//clone to initialize motionRGB and motionDepth
//	motionRGB = Mat(roiDepth.height, roiDepth.width, CV_8UC1);
//	His = Mat(frameA.rows, frameA.cols, CV_8UC1);
//	motionDepth = depthMatA.clone();
//
//	//du lieu rut trich dac trung
//	uchar* data;
//
//	HOGDescriptor hog;
//
//	int thickness = -1;
//	int lineType = 8;
//
//	while(true)
//	{
//		if(odd_frame == true)
//		{
//			if(!cap.read(frameB))
//				break;
//			imageB = frameB(roiRGB);
//			cv::resize(imageB, imageB, size);
//			cvtColor(imageB, imageB, CV_BGR2GRAY);
//
//			//the data will be stored in <depthMap>
//			ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapB);
//			depthB = depthMatB(roiDepth);
//
//			quantize(depthMapB, depthMatB, depthMapB.m_nrows * depthMapB.m_ncols);
//
//			tmp_meanDepth = 0;
//			numberGesturePixel += getGestureRegion(imageA, imageB, motionRGB, depthB, tmp_meanDepth);
//			meanDepthMotion += tmp_meanDepth;
//
//			//imshow("vui", depthB);
//			//imshow("xx", imageB);
//		}
//		else
//		{
//			if(!cap.read(frameA))
//				break;
//			imageA = frameA(roiRGB);
//			cv::resize(imageA, imageA, size);
//			cvtColor(imageA, imageA, CV_BGR2GRAY);
//
//			//the data will be stored in <depthMap>
//			ReadDepthMapSktBinFileNextFrame(fp, ncols, nrows, depthMapA);
//			depthA = depthMatA(roiDepth);
//
//			quantize(depthMapA, depthMatA, depthMapA.m_nrows * depthMapA.m_ncols);
//
//			tmp_meanDepth = 0;
//			numberGesturePixel += getGestureRegion(imageB, imageA, motionRGB, depthA, tmp_meanDepth);
//			meanDepthMotion += tmp_meanDepth;
//
//			//imshow("vui", depthA);
//			//imshow("xx", imageA);
//		}
//
//		if(numberGesturePixel > _number_point_thresh * pow(esilon, - numberFrame * numberFrame / 700))
//		{
//			//chuan hoa do sau trung binh cua chuyen dong
//			meanDepthMotion /= numberFrame;
//
//			if(odd_frame == true)
//			{
//				detector.detect(imageB, keyPoint);
//				removeKeyPoint(depthB, keyPoint, meanDepthMotion);
//				extractor.compute(imageB, keyPoint, descrip);
//			}
//			else
//			{
//				detector.detect(imageA, keyPoint);
//				removeKeyPoint(depthA, keyPoint, meanDepthMotion);
//				extractor.compute(imageA, keyPoint, descrip);
//			}
//			
//			//gan cac tham so = 0
//			numberGesturePixel = 0;
//			meanDepthMotion = 0;
//			numberFrame = 0;
//
//			/*for(int i = 0; i < keyPoint.size(); i++)
//			{
//				circle( imageA,
//						keyPoint[i].pt,
//						1,
//						Scalar( 0, 0, 255 ),
//						thickness,
//						lineType );
//			}
//			imshow("xx", imageA);
//			*/
//		}
//
//		//getGestureRegion(depthMatA, depthMatB, motionDepth);
//
//		//dilate(motionRGB, motionRGB, element);
//		//imshow("motion", motionRGB);
//
//		/*uchar* ptr_tmp1, *ptr_tmp2;
//		ptr_tmp1 = (uchar*)motionRGB.data;
//		ptr_tmp2 = (uchar*)His.data;
//		int size = motionRGB.rows * motionRGB.cols;
//
//		for(int i = 0; i < size; i++)
//			ptr_tmp2[i] = ptr_tmp2[i] / 1.2 + ptr_tmp1[i];
//
//		imshow("motion2", His);*/
//		waitKey(10);
//
//		//Do something
//		/*
//		1. Read first frame
//			1.1. Compute surf key point /
//			1.2. Compute descriptor
//		2. Read seccond frame
//			2.1. Compute surf key point /
//			2.2. Compute surf descriptor
//		3. Compute different of two frame --> Motion Region /
//		4. Compute key point in seccond frame in motion region
//		5. Compute direction of motion
//		6. If motion is large enough, break it to base motion and compute new base motion
//		7. With base motion, compute histogram of direction of motion and compute
//		histogram of motion feature
//		8. When we have all base motion, cluster them with c-mean then compute
//		histogram of base motion and feature (descriptor of video)
//		9. Push to SVM and trainning it
//		10. Take a cup of coffee
//		11. We have a classifier
//		12. Write the report
//		13. Make a DVD
//		14. Rest :3
//		*/
//
//		odd_frame = !odd_frame;
//		//key frame
//		if(numberGesturePixel >= 50)
//		{
//			//odd_frame = !odd_frame;
//
//			//rut trich
//		}
//		numberFrame++;
//	}
//
//	cout << endl;
//}


//ham lay anh vung chuyen dong vat the
int Action::getGestureRegion(Mat &beforeScene, Mat &afterScene, Mat &result, Mat &depth, int &meanDepthMotion)
{
	int width, height, count, tmp, index, i, j;

	width = beforeScene.cols; height = beforeScene.rows;

	uchar* Ptr_befScene, *Ptr_aftScene, *Ptr_res, *Ptr_Depth;

	Ptr_befScene = (uchar*)beforeScene.data;
	Ptr_aftScene = (uchar*)afterScene.data;
	Ptr_res = (uchar*)result.data;
	Ptr_Depth = (uchar*)depth.data;

	index = 0; count = 0;

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			tmp = abs(Ptr_aftScene[index] - Ptr_befScene[index]);

			if(Ptr_Depth[index] != 0 && tmp > _gesture_thresh)
			{
				Ptr_res[index] = 255;
				meanDepthMotion += Ptr_Depth[index];
				count++;
			}
			else
			{
				Ptr_res[index] = 0;
			}
			index++;
		}
	}

	if(count != 0)
		meanDepthMotion /= count;
	return count;
}

//ham lay anh vung chuyen dong vat the(chua sua de thu duoc anh motion)
int Action::getGesturDepthRegion(Mat &beforeScene, Mat &afterScene, Mat& MotionRGB, Mat &resultIncrease, Mat &resultDecrease, Mat &depth, int &meanDepthMotion)
{
	int width, height, count, tmp, index, i, j;

	width = beforeScene.cols; height = beforeScene.rows;

	uchar* Ptr_befScene, *Ptr_aftScene, *Ptr_resIncrease, *Ptr_resDecrease, *Ptr_Depth;
	uchar* Ptr_mask = MotionRGB.data;

	Ptr_befScene = (uchar*)beforeScene.data;
	Ptr_aftScene = (uchar*)afterScene.data;
	Ptr_resIncrease = (uchar*)resultIncrease.data;
	Ptr_resDecrease = (uchar*)resultDecrease.data;
	Ptr_Depth = (uchar*)depth.data;

	index = 0; count = 0;

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			if(Ptr_mask[index] == 0)
			{
				Ptr_resIncrease[index] = 0;
				Ptr_resDecrease[index] = 0;
				index++;
				continue;
			}

			tmp = Ptr_aftScene[index] - Ptr_befScene[index];

			if(tmp >= 0)
			{
				Ptr_resIncrease[index] = 255;
				Ptr_resDecrease[index] = 0;
				meanDepthMotion += Ptr_Depth[index];
				count++;
			}
			else if(-tmp > 0)
			{
				Ptr_resDecrease[index] = 255;
				Ptr_resIncrease[index] = 0;
				meanDepthMotion += Ptr_Depth[index];
				count++;
			}

			index++;
		}
	}

	if(count != 0)
		meanDepthMotion /= count;
	return count;
}

//ham lay anh vung chuyen dong vat the(chua sua de thu duoc anh motion)
int Action::getGesturDepthRegion2(CDepthMapSkt &beforeScene, CDepthMapSkt &afterScene, Mat& MotionRGB, Mat &resultIncrease, Mat &resultDecrease)
{
	int width, height, count, tmp, index, i, j;

	width = beforeScene.m_ncols; height = beforeScene.m_nrows;

	uchar* Ptr_befScene, *Ptr_aftScene, *Ptr_resIncrease, *Ptr_resDecrease, *Ptr_Depth;
	uchar* Ptr_mask = MotionRGB.data;

	Ptr_resIncrease = (uchar*)resultIncrease.data;
	Ptr_resDecrease = (uchar*)resultDecrease.data;

	index = 0; count = 0;

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			tmp = beforeScene.m_depthVals[index] - afterScene.m_depthVals[index];

			if(tmp > 5)
			{
				Ptr_resIncrease[index] = 255;
				Ptr_resDecrease[index] = 0;
				count++;
			}
			else if(-tmp > 5)
			{
				Ptr_resDecrease[index] = 255;
				Ptr_resIncrease[index] = 0;
				count++;
			}
			else
			{
				Ptr_resIncrease[index] = 0;
				Ptr_resDecrease[index] = 0;
			}
			index++;
		}
	}

	return count;
}

//luong hoa anh do sau
void Action::quantize(CDepthMapSkt &depthMap, Mat &result, int size)
{
	uchar* ptr = (uchar*)result.data;
	for(int i = 0; i < size; i++)
	{
		ptr[i] = depthMap.m_depthVals[i] * 255 / 4000;
	}
}

//xoa cac diem keyPoint khong on dinh(ko co depth)
void Action::removeKeyPoint(Mat &depth, vector<KeyPoint> &keyPoint, int meanDepthMotion, bool control)
{
	uchar* ptr_depth = (uchar*)depth.data;
	int steps = depth.step;
	int index;
	for(int i = 0; i < keyPoint.size(); i++)
	{
		index = round(keyPoint[i].pt.y) * steps + round(keyPoint[i].pt.x);

		if(ptr_depth[index] == 0 || (control == true && abs(ptr_depth[index] - meanDepthMotion) > 30))
		{
			keyPoint.erase(keyPoint.begin() + i);
			i--;
		}
	}
}

//ham lam tron so
int Action::round(float src)
{
	return (int)(src + 0.5);
}

//Convolution cua 1 pixel
//m,n: kich thuoc cua kernel (mxn)
float Action::ConvolutionOnePixel(uchar* img, int &width, int &height,
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
void Action::Convolution(uchar* img, int width, int height,
					float** kernel, int m, int n, float** result)
{
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			result[i][j] = (float)ConvolutionOnePixel(img, width, height, kernel, m, n, i, j);
}

//tinh dao ham theo phuong doc
void Action::horizontalPrewitt(uchar* img, int width, int height, float** result)
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
void Action::verticalPrewitt(uchar* img, int width, int height, float** result)
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
//Gradient, Direction: bien do, huong canh
void Action::findEdgeDirection(uchar* img, int width, int height,
							float** Gradient, float** Direction)
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
				Direction[i][j] = PI/2;
			}
			else
			{
				if(Horizontal[i][j] > 0)
					Direction[i][j] = atan(Vertical[i][j]/Horizontal[i][j]) + PI / 2;
				else
					Direction[i][j] = atan(Vertical[i][j]/Horizontal[i][j]) + 3 * PI / 2;
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
void Action::correlogramDirection(int width, int height, int d, int n,
							float** Direction, float* correlogram, float* Histogram)
{
	int direction_index1, direction_index2;
	int di, dj, tmp, count = 0;
	int size = width * height;
	int d8 = 8 * d; //he so chuan hoa

	vector<Point> neigh;

	for(int i = 0; i < n; i++)
		Histogram[i] = 0;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			tmp = (int)(Direction[i][j]/Q);
			Histogram[tmp]++;
			if(tmp != 18)
				count++;
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//tang histogram mau Q(I(x,y))
			direction_index1 = (Direction[i][j]/Q);
			Histogram[direction_index1]++;

			//lay toa do cac diem lang gieng
			neigh.clear();
			getNeighbor(width, height, neigh, j, i, d, di, dj);

			//dem so diem trung mau
			for (int k = 0; k < neigh.size(); ++k)
			{
				direction_index2 = (Direction[neigh[k].y][neigh[k].x]/Q);

				if(direction_index1 == direction_index2)
					correlogram[direction_index2]++;
			}
		}
	}

	//normalize
	for (int i = 0; i < n; ++i)
	{
		if(Histogram[i] > 0)
			correlogram[i] /= (Histogram[i] * d8);
		Histogram[i] /= count;
	}
}

Mat Action::compute(Mat image)
{
	float** Gradient, **Direction;

	Gradient = new float* [image.rows];
	Direction = new float* [image.rows];
	for(int i = 0; i < image.rows; i++)
	{
		Gradient[i] = new float [image.cols];
		Direction[i] = new float [image.cols];
	}

	//khai bao mang luu ket qua vector lien ket mau
	float* correlogram = new float[72];
	for(int i = 0; i < 72; i++)
		correlogram[i] = 0;

	float* histogram = new float[72];
	for(int i = 0; i < 72; i++)
		histogram[i] = 0;

	uchar* img = (uchar*)image.data;

	findEdgeDirection(img, image.cols, image.rows,
						Gradient, Direction);

	//goi ham tinh vector lien ket mau
	correlogramDirection(image.cols, image.rows, 3, 72,
							Direction, correlogram, histogram);

	Mat result = Mat(1, 144, CV_8UC1, Scalar(0));
	uchar* ptr = (uchar*)result.data;

	for(int i = 0; i < 72; i++)
	{
		if(i != 18)
			ptr[i] = correlogram[i] * 255;
	}
	for(int i = 0; i < 72; i++)
	{
		if(i != 18)
			ptr[72 + i] = histogram[i] * 255;
	}

	//Huy du lieu da xin cap phat
	delete []correlogram;
	delete []histogram;

	for(int i = 0; i < image.rows; i++)
	{
		delete []Gradient[i];
		delete []Direction[i];
	}
	delete []Gradient;
	delete []Direction;

	return result;
}

Mat Action::compute2(Mat image)
{
	float** Gradient, **Direction;

	Gradient = new float* [image.rows];
	Direction = new float* [image.rows];
	for(int i = 0; i < image.rows; i++)
	{
		Gradient[i] = new float [image.cols];
		Direction[i] = new float [image.cols];
	}

	//khai bao mang luu ket qua vector lien ket mau
	float* correlogram = new float[72];
	for(int i = 0; i < 72; i++)
		correlogram[i] = 0;

	float* histogram = new float[72];
	for(int i = 0; i < 72; i++)
		histogram[i] = 0;

	uchar* img = (uchar*)image.data;

	findEdgeDirection(img, image.cols, image.rows,
						Gradient, Direction);

	//goi ham tinh vector lien ket mau
	correlogramDirection(image.cols, image.rows, 3, 72,
							Direction, correlogram, histogram);

	Mat result = Mat(1, 72, CV_8UC1, Scalar(0));
	uchar* ptr = (uchar*)result.data;

	for(int i = 0; i < 72; i++)
	{
		if(i != 18)
			ptr[i] = histogram[i] * 255;
	}

	//Huy du lieu da xin cap phat
	delete []correlogram;
	delete []histogram;

	for(int i = 0; i < image.rows; i++)
	{
		delete []Gradient[i];
		delete []Direction[i];
	}
	delete []Gradient;
	delete []Direction;

	return result;
}

void Action::getNeighbor(int width, int height, vector<Point> &neighbor, int &x, int &y, int &d, int &di, int &dj)
{
	di = -d;
	if(x + di >= 0)
	{
		for(int dj = -d; dj <= d; dj++)
			if(y + dj >= 0 && y + dj < height)
				neighbor.push_back(Point(x+di,y+dj));
	}
		
	di = d;
	if(x + di < width)
	{
		for(dj = -d; dj <= d; dj++)
			if(y + dj >= 0 && y + dj < height)
				neighbor.push_back(Point(x+di,y+dj));
	}

	dj = -d;
	if(y + dj >= 0)
	{
		for(di = -d+1; di < d; di++)
			if(x + di >= 0 && x + di < width)
				neighbor.push_back(Point(x+di,y+dj));
	}
		
	dj = d;
	if(y + dj < height)
	{
		for(di = -d+1; di < d; di++)
			if(x + di >= 0 && x + di < width)
				neighbor.push_back(Point(x+di,y+dj));
	}
}