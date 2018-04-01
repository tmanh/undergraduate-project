#pragma once

#include <string>

using namespace std;

class BoundingBox
{
public:
	//data
	int begin_frame;
	int end_frame;

	int x;
	int y;
	int height;
	int width;

	float label;
	bool check;

	BoundingBox(void): label(-1), check(false), x(0), y(0), width(0), height(0){};
	~BoundingBox(void);
};

