/*
Truong Minh Anh - 1112010
truongminhanh93.it@gmail.com
*/

#include "FOLDER.h"

FOLDER::~FOLDER(){
	if(n!=0){
		for(int i=0; i<n; ++i)
			delete data[i];
		data.clear();
		n = 0;
	}
}

int FOLDER::getsize(){
	int size = 0;
	int n = data.size();
	for(int i=0; i<n; ++i)
		size += data[i]->getsize();
	return size;
}
void FOLDER::set(wstring path){
	this->path = path;

	getListData();
	updateSize();
}

string FOLDER::NameContainer(){
	return "folder";
}

void FOLDER::getListData(){
	wstring searchPattern = L"\\*";
	wstring fullSearchPath = path + searchPattern;

	WIN32_FIND_DATA FindData;
	HANDLE hFind;

	hFind = FindFirstFile(fullSearchPath.c_str(), &FindData);

	if(hFind == INVALID_HANDLE_VALUE )
		cout << "File not fould!!!\n";

	do{
		wstring filePath = path + L"\\" + FindData.cFileName;
		if(filePath.find('.')!=(path.length()+1)){
			n++;
			data.resize(n);
			data[n-1] = new MYFILE;
			data[n-1]->set(filePath);
		}
	}
	while(FindNextFile(hFind, &FindData) > 0);
}

void FOLDER::updateSize(){
	for(int i=0; i<n; ++i)
		data[i]->updateSize();
}

void FOLDER::input(){
	cout << "Nhap duong dan folder: ";
	getline(wcin,path);

	getListData();
	updateSize();
}

void FOLDER::output(){
	cout << "Duong dan folder: ";
	wcout << path << endl;
	for(int i=0; i<n; ++i)
		data[i]->output();
}

wstring FOLDER::getpath(int index){
	if(index<0 || index>=n)
		return L"";
	return data[index]->getpath();
}

wstring FOLDER::getname(int index){
	if(index<0 || index>=n)
		return L"";
	int i = data[index]->getpath().rfind('\\');
	if(i==-1)
		return path;
	else
		return data[index]->getpath().substr(i+1,path.length()-i-1);
}

int FOLDER::getnFile(){
	return n;
}

int FOLDER::getsize(int index){
	return data[index]->getsize();
}
