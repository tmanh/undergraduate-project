/*
Truong Minh Anh - 1112010
truongminhanh93.it@gmail.com
*/

#include "Huffman.h"

int main(int argc, char* argv[]){
	Huffman x;
	wchar_t tmp[256];
	string checkE;
	if(argc <= 2)
		return -1;
	if(argv[1][1] == 'e'){
		mbstowcs(tmp,argv[2],strlen(argv[2]));
		tmp[strlen(argv[2])] = '\0';
		x.setDataCompress(tmp);
		mbstowcs(tmp,argv[3],strlen(argv[3]));
		tmp[strlen(argv[3])] = '\0';
		x.setOutput(tmp);
		x.Compress();
	}
	else if(argv[1][1] == 'd'){
		for(int i=3; i<argc; ++i){
			checkE += argv[i];
			checkE += " ";
		}
		mbstowcs(tmp,argv[2],strlen(argv[2]));
		tmp[strlen(argv[2])] = '\0';
		x.setDataExtract(tmp,checkE);
		x.Extract();
		x.Display();
	}
	else{
		checkE = "-all";
		mbstowcs(tmp,argv[2],strlen(argv[2]));
		tmp[strlen(argv[2])] = '\0';
		x.setDataExtract(tmp,checkE);
		x.Display();
	}

    return 0;
}
