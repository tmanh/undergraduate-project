#include "Loader.h"


Loader::~Loader(void)
{
}

//ham push tat ca cac dong cua 1 vector sang 1 vector
void Loader::pushall(vector<ObjectInfo>& a, vector<ObjectInfo>& b)
{
	for(unsigned int i = 0; i < b.size(); i++)
		a.push_back(b[i]);
	b.clear();
}

//lay ten file trong duong dan
string Loader::getFileName(string file)
{
	string tmp = file;
	int begin = tmp.find_last_of('//') + 1;
	int begin2 = tmp.find_last_of('\\') + 1;
	int end = tmp.find('.');

	if(begin > begin2)
		tmp = tmp.substr(begin, end - begin);
	else
		tmp = tmp.substr(begin2, end - begin2);

	return tmp;
}

//kiem tra ten file trung nhau
void Loader::readFilename(string fn, vector<string> &fname, vector<string> &aname)
{
	ifstream fin(fn);

	while(fin == NULL)
	{
		fn = fn.substr(3,fn.length() - 3);

		fin.open(fn);
	}

	string tmp, link;

	link = fn;
	link = link.substr(0, link.find_last_of('\\') + 1);

	

	while(!fin.eof())
	{
		fin >> tmp;

		fname.push_back(link + "Video\\" + tmp + ".mpg");
		aname.push_back(link + "Annotation\\" + tmp + ".xgtf");
	}

	fin.close();
}

//ham tinh BOWDescriptor
void Loader::compute( Mat& imgDescriptor, const Mat& center, Mat descriptors, vector<ObjectInfo>& obj )
{
    // Match keypoint descriptors to cluster center (to vocabulary)
    vector<DMatch> matches;
    matcher.match( descriptors, center, matches );

	int k = 0;
	size_t i = 0;
	size_t tmp = 0;
	float *iptr = (float*)imgDescriptor.data;
	for(unsigned int index = 0; index < obj.size(); index++)
	{
		tmp += obj[index].size;

		// Compute image descriptor
		Mat _imgDescriptor = Mat( 1, _number_of_word, CV_32FC1, Scalar::all(0.0) );
		float *dptr = (float*)_imgDescriptor.data;

		for( i; i < tmp; i++ )
		{
			int trainIdx = matches[i].trainIdx; // cluster index
			dptr[trainIdx] = dptr[trainIdx] + 1.f;
		}

		_imgDescriptor /= obj[index].size;		//Chuan hoa

		for(int j = 0; j < _number_of_word; j++)
		{
			if(dptr[j] >= 0.005)
				iptr[k++] = dptr[j];
			else
				iptr[k++] = 0;
		}
	}
}

//Tai du lieu 1 video
void Loader::LoadOne(string &xmlfile, string &videofile, vector<ObjectInfo> &obj, Mat &his, const Mat& srccenter)
{
	Mat hist;

	his.release();
	Load(xmlfile, videofile, obj, hist);
	his.create(obj.size(),_number_of_word,CV_32FC1);
	compute(his, srccenter, hist, obj);
}

//Tai toan bo du lieu test
void Loader::LoadAllTest(vector<ObjectInfo> &obj, Mat &his, const Mat& srccenter)
{
	vector<ObjectInfo> object;
	vector<string> fname;
	vector<string> aname;
	Mat hist;

	his.release();
	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\basketball\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\biking\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\diving\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();
	
	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\golf_swing\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\horse_riding\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();
	
	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\soccer_juggling\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\tennis_swing\\test.txt", fname, aname);
	for(unsigned int i = 2; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\trampoline_jumping\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\walking\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	cout << "Hoan tat qua trinh tai du lieu ..." << endl;

	his.create(obj.size(),_number_of_word,CV_32FC1);
	compute(his, srccenter, hist, obj);
	cout << "Hoan tat qua trinh tinh BOW Descriptor ..." << endl;
	
}

//Tai toan bo du lieu tranning
void Loader::LoadAll(Mat& center, vector<ObjectInfo> &obj, Mat &his)
{
	vector<ObjectInfo> object;
	vector<string> fname;
	vector<string> aname;
	Mat hist;

	his.release();
	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\basketball\\trainning.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\biking\\trainning.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\diving\\trainning.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\golf_swing\\trainning.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\horse_riding\\trainning.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\soccer_juggling\\trainning.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\tennis_swing\\trainning.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\trampoline_jumping\\trainning.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\walking\\trainning.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		Load(aname[i], fname[i], object, hist);
		pushall(obj, object);
	}
	aname.clear();
	fname.clear();

	cout << "Hoan tat qua trinh tai du lieu ..." << endl;

	bowkmean.add(hist);				//su dung bag-of-word-kmean de gom cum
	center = bowkmean.cluster();	//tao thanh k tam tuong ung voi k-word

	cout << "Hoan tat qua trinh gom cum ..." << endl;

	his.create(obj.size(),_number_of_word,CV_32FC1);
	compute(his, center, hist, obj);	//tinh BOWDescriptor
	cout << "Hoan tat qua trinh tinh BOW Descriptor ..." << endl;
}

//Tai du lieu tu 2 file xml chua boundingbox va video
void Loader::Load(string &xmlfile, string &videofile, vector<ObjectInfo> &object, Mat &mat)
{
	LoadXml(xmlfile, object);
	LoadFrame(videofile, object, mat);
}

//Tai du lieu tu video
void Loader::LoadFrame(string &file, vector<ObjectInfo> &object, Mat &mat)
{
	VideoCapture cap(file); // open the video from file

    if(!cap.isOpened())  // check if we succeeded
        return;
	
	//Khai bao ma tran frame de luu tung frame cua video
	//Khai bao doi tuong tinh dac trung SURF va tinh Descriptor cua SURF
	Mat frame;
	SurfFeatureDetector detector(_minHessian);
	SurfDescriptorExtractor extractor;

	vector<Mat> tmp_his_obj;
	tmp_his_obj.resize( object.size() );
	
	unsigned int j, k;

	float range[] = { 0, 255 } ;
	const float* histRange = { range };
	int nPts;
	int d1, d2;
	int thresh1, thresh2;

    for(int i = 0; ; i += 5)
    {
		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
			break;

		Rect rct;

		//Tim descriptor tat ca cac frame trong video cua doi tuong
		for(j = 0; j < object.size(); j++)
		{
			for(k = 0; k < object[j].bbox.size(); k++)
			{
				if(i >= object[j].bbox[k].begin_frame && i <= object[j].bbox[k].end_frame)
				{
					//xac dinh vi tri doi tuong
					Mat hist, descriptors;
					vector<KeyPoint> keypoints;

					rct.height = object[j].bbox[k].height;
					rct.width = object[j].bbox[k].width;
					rct.x = object[j].bbox[k].x;
					rct.y = object[j].bbox[k].y;
					
					if(rct.height + rct.y >= frame.rows)
						rct.height = frame.rows - rct.y;
					if(rct.width + rct.x >= frame.cols)
						rct.width = frame.cols - rct.x;

					if(rct.height <= 0 || rct.width <= 0)
						break;

					//trich vung anh chua doi tuong
					Mat roi(frame, rct);

					//Detect keypoint
					detector.detect( roi, keypoints );

					if(keypoints.size() <= 1)
						break;

					if(keypoints.size() > 10)
					{
						thresh1 = (rct.width / 6.5);
						thresh2 = (rct.height / 6.5);

						for(int count = 0; count < keypoints.size(); count++)
						{
							nPts = 0;
							for(int count2 = 0; count2 < keypoints.size(); count2++)
							{
								d1 = abs((keypoints[count].pt.x - keypoints[count2].pt.x));
								d2 = abs((keypoints[count].pt.y - keypoints[count2].pt.y));
								if(d1 < thresh1 && d2 < thresh2)
									nPts++;
							}
							if(nPts < 2)
							{
								keypoints.erase(keypoints.begin()+count);
								count--;
							}
						}
					}

					for(int count = 0; count < keypoints.size(); count++)
					{
						if(keypoints[count].angle > 275 && keypoints[count].size > 25)
						{
							keypoints.erase(keypoints.begin()+count);
							count--;
						}
					}

					//tinh SURF descriptor cua anh
					extractor.compute( roi, keypoints, descriptors );

					tmp_his_obj[j].push_back(descriptors);
					break;
				}
			}
		}
    }

	//xoa cac doi tuong khong tinh duoc descriptor
	for(unsigned int i = 0; i < object.size(); i++)
	{
		if(tmp_his_obj[i].rows > 0)
		{
			mat.push_back( tmp_his_obj[i] );
			object[i].size = tmp_his_obj[i].rows;
		}
	}

	for(unsigned int i = 0; i < object.size(); i++)
	{
		if(object[i].size == 0)
		{
			object.erase(object.begin()+i);
			i--;
		}
	}
}

//Tai du lieu trong xml
void Loader::LoadXml(string &file, vector<ObjectInfo> &object)
{
	fname = getFileName(file);
	string input_xml;
	string line;
	ifstream in(file);

	if (!in)
		return;

	// read file into input_xml
	while(getline(in,line))
		input_xml += line;

	in.close();
	
	vector<char> xml_copy(input_xml.begin(), input_xml.end());
	xml_copy.push_back('\0');

	xml_document<> doc = xml_document<>();

	doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);

	xml_node<> *node = doc.first_node();

	ReadNodeViper(node, object);
}

//Doc node viper
void Loader::ReadNodeViper(xml_node<> *&node, vector<ObjectInfo> &object)
{
	do
	{
		if (string(node->name()) == "viper")
		{
			xml_node<> *new_node = node->first_node();

			ReadNodeData(new_node, object);
		}

		node = node->next_sibling();
	}
	while(node);
}

//Doc node data
void Loader::ReadNodeData(xml_node<> *&node, vector<ObjectInfo> &object)
{
	do
	{
		if (string(node->name()) == "data")
		{
			xml_node<> *new_node = node->first_node();

			ReadNodeSource(new_node, object);
		}

		node = node->next_sibling();
	}
	while(node);
}

//Doc node source
void Loader::ReadNodeSource(xml_node<> *&node, vector<ObjectInfo> &object)
{
	do
	{
		if (string(node->name()) == "sourcefile")
		{
			xml_attribute<> *attr = node->first_attribute();

			if(checkSourceAttribute(attr))
			{
				xml_node<> *new_node = node->first_node();
				ReadNodeObject(new_node, object);
			}
		}

		node = node->next_sibling();
	}
	while(node);
}

//kiem tra source da dung file hay chua
bool Loader::checkSourceAttribute(xml_attribute<> *&attr)
{
	do
	{
		if (string(attr->name()) == "filename")
		{
			if(getFileName(attr->value()) == getFileName(fname))
				return true;
		}

		attr = attr->next_attribute();
	}
	while(attr);

	return false;
}

//Doc node object
void Loader::ReadNodeObject(xml_node<> *&node, vector<ObjectInfo> &object)
{
	do
	{
		if (string(node->name()) == "object")
		{
			xml_node<> *new_node = node->first_node();

			ObjectInfo obj;
			ReadNodeAttr(new_node, obj.bbox);
			if(obj.bbox.size() > 0 && obj.bbox[0].label >= 0)
				object.push_back(obj);
		}

		node = node->next_sibling();
	}
	while(node);
}

//Doc node attribute
void Loader::ReadNodeAttr(xml_node<> *&node, vector<BoundingBox> &bbox)
{
	xml_attribute<> *attr = node->first_attribute();
	xml_node<> *new_node = node->first_node();

	if(string(attr->value()) == "Location")
		ReadNodeBBox(new_node, bbox);

	node = node->next_sibling();

	do
	{
		new_node = node->first_node();
		ReadNodeLBBox(new_node, bbox, node->first_attribute()->value());
		node = node->next_sibling();
	}
	while(node);

	for(unsigned int i = 0; i < bbox.size(); i++)
	{
		if(!bbox[i].check)
		{
			bbox.erase(bbox.begin() + i);
			i--;
		}
	}
}

//Doc node bbox
void Loader::ReadNodeBBox(xml_node<> *&node, vector<BoundingBox> &bbox)
{
	do
	{
		xml_attribute<> *attr = node->first_attribute();
		ReadBBox(attr, bbox);
		node = node->next_sibling();
	}
	while(node);
}

//doc bbox
void Loader::ReadBBox(xml_attribute<> *&attr, vector<BoundingBox> &bbox)
{	
	BoundingBox result;

	do
	{
		if(string(attr->name())== "framespan")
		{
			string tmp = attr->value();
			tmp[tmp.find(':')] = ' ';
			
			istringstream ss(tmp);
			ss >> result.begin_frame >> result.end_frame;
		}

		if(string(attr->name())== "height")
		{
			result.height = atoi(attr->value());
		}

		if(string(attr->name())== "width")
		{
			result.width = atoi(attr->value());
		}

		if(string(attr->name())== "x")
		{
			result.x = atoi(attr->value());
			if(result.x < 0)
				result.x = 0;
			if(result.x > 320)
				return;
		}

		if(string(attr->name())== "y")
		{
			result.y = atoi(attr->value());
			if(result.y < 0)
				result.y = 0;
			if(result.y > 240)
				return;
		}

		attr = attr->next_attribute();
	}
	while(attr);

	bbox.push_back(result);
}

//Doc node nhan bbox
void Loader::ReadNodeLBBox(xml_node<> *&node, vector<BoundingBox> &bbox, string label)
{
	do
	{
		xml_attribute<> *attr = node->first_attribute();
		ReadLBBox(attr, bbox, label);
		node = node->next_sibling();
	}
	while(node);
}

//Doc nhan bbox
void Loader::ReadLBBox(xml_attribute<> *&attr, vector<BoundingBox> &bbox, string label)
{
	int begin = 0, end = 0;

	do
	{
		if(string(attr->name())== "framespan")
		{
			string tmp = attr->value();
			tmp[tmp.find(':')] = ' ';
			
			istringstream ss(tmp);
			ss >> begin >> end;
		}

		if(string(attr->name())== "value")
		{
			if(string(attr->value()) == "true")
			{
				for(unsigned int i = 0; i < bbox.size(); i++)
				{
					if(bbox[i].begin_frame > end)
					{
						bbox[i].check = false;
					}
					else if(bbox[i].end_frame < begin)
					{
						bbox[i].check = false;
					}
					else
					{
						if(bbox[i].begin_frame < begin)
							bbox[i].begin_frame = begin;
						if(bbox[i].end_frame > end)
							bbox[i].end_frame = end;
						bbox[i].label = getLabel(label);
						bbox[i].check = true;
					}
				}
			}
		}

		attr = attr->next_attribute();
	}
	while(attr);
}

//lay nhan tu ten lop
float Loader::getLabel(string &name)
{
	string tmp(name);
	if(tmp == "basketball_shooting")
		return 0;
	if(tmp == "biking")
		return 1.0;
	if(tmp == "diving")
		return 2.0;
	if(tmp == "golf_swing")
		return 3.0;
	if(tmp == "horse_riding")
		return 4.0;
	if(tmp == "soccer_juggling")
		return 5.0;
	if(tmp == "tennis_swing")
		return 6.0;
	if(tmp == "trampoline_jumping")
		return 7.0;
	return 8.0;
}