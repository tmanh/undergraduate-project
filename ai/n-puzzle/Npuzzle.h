#pragma once

#include "BOARD.h"
#include <iostream>
#include <vector>

#define MAX 30000

class Npuzzle
{
public:
	bool load(char* fn);	//ham load du lieu tu file
	bool save(char* fn, bool flag);	//ghi ket qua ra file

	bool search(short s);

	void createEND();		//tao trang thai ket thuc

private:
	BOARD start;	//trang thai bat dau
	BOARD end1;		//trang thai ket thuc 1
	BOARD end2;		//trang thai ket thuc 2

	vector<BOARD> open;
	vector<BOARD> close;

	void write(ofstream &fout, int i);

	bool DFS();
	bool BFS();

	int i,j,len;

	bool addSucc(bool &flag, BOARD& tmp, BOARD& tmp2);
};

