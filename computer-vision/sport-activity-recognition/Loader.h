#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "rapidxml.hpp"
#include "ObjectInfo.h"

#include "PixelOperators.h"
#include "Libraries\Headers\opencv2\core\core.hpp"
#include "Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "Libraries\Headers\opencv2\imgproc\imgproc.hpp"
#include "Libraries\Headers\opencv2\features2d\features2d.hpp"
#include "Libraries\Headers\opencv2\nonfree\features2d.hpp"
#include "Libraries\Headers\opencv2\ml\ml.hpp"

using namespace cv;

using namespace std;
using namespace rapidxml;

#define _minHessian	500
#define _number_of_word 100

class Loader
{
public:
	Loader(void): bowkmean( _number_of_word, cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6) , 1), matcher(NORM_L2){};
	~Loader(void);

	string fname;
	//Tai toan bo du lieu tranning
	void LoadAll(Mat& center, vector<ObjectInfo> &obj, Mat &his);
	//Tai toan bo du lieu test
	void LoadAllTest(vector<ObjectInfo> &obj, Mat &his, const Mat& srccenter);
	//Tai du lieu tu 2 file xml chua boundingbox va video
	void Load(string &xmlfile, string &videofile, vector<ObjectInfo> &object, Mat &mat);
	//Tai du lieu tu video
	void LoadFrame(string &file, vector<ObjectInfo> &object, Mat &mat);
	//Tai du lieu trong xml
	void LoadXml(string &file, vector<ObjectInfo> &object);
	//Tai du lieu 1 video
	void LoadOne(string &xmlfile, string &videofile, vector<ObjectInfo> &obj, Mat &his, const Mat& srccenter);
	//kiem tra ten file trung nhau
	void readFilename(string fn, vector<string> &fname, vector<string> &aname);
private:
	BOWKMeansTrainer bowkmean;	//doi tuong bag-of-word k-means
	BFMatcher matcher;			//doi tuong so khop

	//lay ten file trong duong dan
	string getFileName(string file);
	
	//Doc node viper
	void ReadNodeViper(xml_node<> *&node, vector<ObjectInfo> &object);
	//Doc node data
	void ReadNodeData(xml_node<> *&node, vector<ObjectInfo> &object);
	//Doc node source
	void ReadNodeSource(xml_node<> *&node, vector<ObjectInfo> &object);
	//Doc node object
	void ReadNodeObject(xml_node<> *&node, vector<ObjectInfo> &object);
	//Doc node attribute
	void ReadNodeAttr(xml_node<> *&node, vector<BoundingBox> &bbox);
	//Doc tat ca node bbox
	void ReadNodeBBox(xml_node<> *&node, vector<BoundingBox> &bbox);
	//Doc 1 node bbox
	void ReadBBox(xml_attribute<> *&attr, vector<BoundingBox> &bbox);
	//Doc node nhan cua bbox tu node attribute
	void ReadLBBAttr(int &begin, int& end, xml_attribute<> *&attr, vector<BoundingBox> &bbox, string label);
	//Doc node nhan cua bbox
	void ReadNodeLBBox(xml_node<> *&node, vector<BoundingBox> &bbox, string label);
	//Doc nhan cua bbox
	void ReadLBBox(xml_attribute<> *&attr, vector<BoundingBox> &bbox, string label);

	//kiem tra source da dung file hay chua
	bool checkSourceAttribute(xml_attribute<> *&attr);
	
	//ham push tat ca cac dong cua 1 vector sang 1 vector
	void pushall(vector<ObjectInfo>& a, vector<ObjectInfo>& b);

	//ham lay nhan tu ten
	float getLabel(string &name);

	//ham tinh BOW Descriptor (Histogram of word) cho anh
	void compute( Mat& imgDescriptor, const Mat& center, Mat descriptors, vector<ObjectInfo>& obj );
};