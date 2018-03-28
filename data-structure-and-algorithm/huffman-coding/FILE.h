/*
Truong Minh Anh - 1112010
truongminhanh93.it@gmail.com
*/

#pragma once

#include "CONTAINER.h"

class MYFILE : public CONTAINER
{
protected:
	int size;
public:
	int getsize();			//lay kich thuoc cua file
	void set(wstring path);	//nhap duong dan file
	string NameContainer();	//ten cua doi tuong: tra ve file
	void input();			//nhap file
	void output();			//xuat file
	void updateSize();		//cap nhat kich thuoc file
};

