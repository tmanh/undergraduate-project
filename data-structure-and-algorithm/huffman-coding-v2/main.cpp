/*
Truong Minh Anh
1112010
truongminhanh93.it@gmail.com
*/

#include "func.h"

void main(){
	Huffman_Tree x;
	x.readCompressFile("1.txt");
	x.printCompressFile("test.mrar");
	x.readUncompressFile("test.mrar");
	x.printUncompressFile("2.txt");
}