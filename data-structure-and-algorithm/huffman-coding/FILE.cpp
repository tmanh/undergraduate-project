/*
Truong Minh Anh - 1112010
truongminhanh93.it@gmail.com
*/

#include "file.h"


int MYFILE::getsize(){
	return size;
}

void MYFILE::set(wstring path){
	this->path = path;
}

string MYFILE::NameContainer(){
	return "file";
}

void MYFILE::input(){
	cout << "Nhap duong dan file: ";
	getline(wcin,path);
	updateSize();
}

void MYFILE::updateSize(){
	ifstream fin;
	fin.open(path,ios::binary);

	fin.seekg(0,ios::end);
	size = fin.tellg();

	fin.close();
}

void MYFILE::output(){
	cout << "File Name: ";
	wcout << path << endl;
}
