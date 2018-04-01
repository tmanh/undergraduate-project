/*
Truong Minh Anh - 1112010
truongminhanh93.it@gmail.com
*/

#pragma once

#include <iostream>
#include <fstream>
// #include <windows.h> // this is for Windows
#include <string>
#include <cstdlib>
using namespace std;

class CONTAINER
{
protected:
	wstring path;
public:
	virtual void updateSize() = 0;
	virtual int getsize() = 0;
	virtual void set(wstring path) = 0;
	virtual string NameContainer() = 0;
	virtual void input() = 0;
	virtual void output() = 0;
	wstring getpath();
};
