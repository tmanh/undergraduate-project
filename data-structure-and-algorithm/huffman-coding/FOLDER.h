/*
Truong Minh Anh - 1112010
truongminhanh93.it@gmail.com
*/

#pragma once

#include <vector>
#include "CONTAINER.h"
#include "FILE.h"

class FOLDER : public CONTAINER
{
protected:
	vector<CONTAINER*> data;
	int n;
public:
	FOLDER(): n(0){};
	~FOLDER();
	int getsize();			//lay kich thuoc folder
	void set(wstring path);	//nhap duong dan folder
	void getListData();		//lay list file co trong thu muc
	string NameContainer();	//tra ve ten doi tuong: tra ve folder
	void input();			//nhap folder
	void output();			//xuat folder
	void updateSize();		//cap nhat kich thuoc folder
	wstring getpath(int index);	//lay duong dan
	wstring getname(int index);	//lay ten file
	int getsize(int index);		//lay kich thuoc
	int getnFile();				//lay so luong file co trong folder
};

