#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Table{
	unsigned char key;
	string bit;
	int n;
};
struct Node{
	string key;
	int n;
	int left;
	int right;
	bool used;
};

#define	MAXNODE	2304
#define MAXTAB	256
#define BLOCK	100
#define NUM_BIT 8
#define TBYTE	0x80

class Huffman_Tree{
private:
	int count;
	Table HTable[MAXTAB];
	Node HTree[MAXNODE];
	string InputData;
	int Fsize;

	void createbyte(char &x, string& nbit);
	void createUbyte(char &x, char &src, unsigned char &nbit);
	void bitUout(ofstream &FileOut);
	void bitout(ofstream &FileOut);
	void initTable();					//khoi tao gia tri cua bang
	void initTree();					//khoi tao gia tri cua cay
	void createTree();					//tao cay Huffman
	void createbit();					//tao bang ma bit
	bool ktKey(const Node& src, unsigned char key);			//tim mot key nam ben phai hay trai node
	bool ktNODElon(const Node& x, const Node& y);		//ktra NODE nao lon hon
	bool minNODE(int &i, int &j, int &start, int &end);	//tim 2 vi tri co so lan xuat hien nho nhat
public:
	~Huffman_Tree();
	bool readCompressFile(char* fn);	//doc file can nen
	bool readUncompressFile(char* fn);	//doc file can giai nen
	void printCompressFile(char* fn);	//xuat file duoc nen 
	void printUncompressFile(char* fn);	//xuat file giai nen
	void processCompress();				//xu ly qua trinh nen/giai nen
};