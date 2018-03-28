/*
Truong Minh Anh - 1112010
truongminhanh93.it@gmail.com
*/

#pragma once

#include "FOLDER.h"
#include <sstream>

#define	MAXNODE	512
#define MAXTAB	256
#define BLOCK	100
#define NUM_BIT 8
#define HBIT	0x80

struct Table{
	char key;
	string bit;
	unsigned int n;
};

struct Node{
	string key;
	unsigned int Freq;
	int left;
	int right;
	bool used;
};

struct header{
	Table FreqInfo[256];
	unsigned int n;
	vector<wstring> FPath;
	vector<wstring> FName;
	vector<unsigned int> FSize;
	vector<unsigned int> FSeekByte;
};

class Huffman
{
private:
	FOLDER data;
	header MyHeader;
	Node HTree[MAXNODE];
	int nchar;
	vector<bool> check;
	wstring FName;

	ifstream fin;
	ofstream fout;

	void initTable();	//khoi tao gia tri cua bang thong ke
	void initTree();	//khoi tao gia tri cua cay huffman

	void readTable();		//doc bang thong ke
	void readCompress();	//doc cho qua trinh nen
	void readExtract();		//doc cho qua trinh giai nen

	bool ktKey(const Node& src, char key);				//tim mot key nam ben phai hay trai node
	bool ktNODElon(const Node& x, const Node& y);		//ktra NODE nao lon hon
	bool minNODE(int &i, int &j, int &start, int &end);	//tim 2 vi tri co so lan xuat hien nho nhat

	void createbyte(char &x, string& nbit);				//tao 1 byte khi nen
	void createUbyte(char &x, char& InputData, unsigned char &nbit);	//tao 1 byte khi giai nen
	
	void seekByte();
	void printFileCompress();	//ghi file thu index
	void printFileExtract();	//ghi file thu index
	
	void bitUout(int index);		//ghi 1 byte ra file giai nen
	void bitout(unsigned int Fsize, unsigned int& seek);		//ghi 1 byte ra file nen

	void createTree();		//tao cay Huffman
	void createbit();		//tao bang ma bit

	void processCompress();	//xu ly qua trinh nen
	void processExtract();	//xu ly qua trinh giai nen

	void readFileHeader();	//doc thong tin header tu file
	void getFileHeader();	//ham lay thong tin ve cho header
	void writeHeader();		//ham ghi header file

	void SizeFileError(int index);
public:
	Huffman();
	void setOutput(wstring name);		//lay ten file output khi nen
	void setDataCompress(wstring name);	//lay data cho viec nen
	void setDataExtract(wstring name, string checkE);	//lay data cho viec giai nen
	void Compress();			//nen
	void Extract();				//giai nen
	void Display();				//hien thong tin file
};

