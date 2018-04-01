#pragma once

#include <fstream>
using namespace std;

#include "POINT.h"

//xac dinh huong
#define NONE	-1
#define	N		0
#define	E		2
#define	S		3
#define W		1

class BOARD
{
public:
	BOARD();

	bool read(char* fn);	//ham doc tu file

	bool operator==(const BOARD& src);	//ham so sanh bang
	
	char getDirect();		//ham lay gia tri huong

	int getN();				//ham lay n
	int getPrev();			//lay vi tri trang thai truoc
	int get_pX();			//lay vi zero
	int get_pY();

	bool Move(char dir, BOARD &result);	//ham tao 1 trang thai khac tu viec di chuyen o 0

	void createEND1();		//tao trang thai ket thuc
	void createEND2();		//tao trang thai ket thuc

	void setPrev(int p);	//tuy chinh vi tri trang thai truoc

private:
	static short i, j, tmp;	//cac bien dem
	char	data[5][5];		//bang du lieu
	char	direct;			//huong bien doi ve trang thai truoc

	static short n;			//kich thuoc bang du lieu

	int		prev;

	Point	Zero;			//vi tri so 0 trong bang du lieu
};

