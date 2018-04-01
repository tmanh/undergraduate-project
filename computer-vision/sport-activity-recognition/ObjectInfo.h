#pragma once

#include <vector>
#include "BoundingBox.h"

class ObjectInfo
{
public:
	vector<BoundingBox> bbox;
	int size;

	ObjectInfo(void): size(0), bbox(){};
	~ObjectInfo(void);
};