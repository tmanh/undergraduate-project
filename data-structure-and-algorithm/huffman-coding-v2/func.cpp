#include "func.h"

Huffman_Tree::~Huffman_Tree(){
	InputData.clear();
}

//doc file can nen
bool Huffman_Tree::readCompressFile(char* fn){
	ifstream fin(fn,ios::binary);
	if(fin==NULL)
		return 0;
	initTable();
	unsigned char ch;
	while(fin.read((char*)&ch,1)){
		InputData += ch;
		HTable[ch].n++;
	}
	fin.close();
	Fsize = InputData.size();
	return 1;
}
//doc file can giai nen
bool Huffman_Tree::readUncompressFile(char* fn){
	ifstream fin(fn, ios::binary);
	if(fin==NULL)
		return 0;
	initTable();
	fin.seekg(0,ios::end);
	int size = fin.tellg();
	fin.seekg(0,ios::beg);
	int i;
	char tmp;

	for(i=0; i<=255; ++i)
		fin.read((char*)&HTable[i].n,4);
	fin.read((char*)&Fsize,4);
	i = 1027;

	while(i<size){
		fin.read((char*)&tmp,1);
		InputData += tmp;
		i++;
	}

	fin.close();
	return 1;
}
//xuat file duoc nen
void Huffman_Tree::printCompressFile(char* fn){
	processCompress();
	ofstream fout(fn,ios::binary);
	int size = InputData.size();
	int j,len;
	len = HTree[0].key.size();

	for(j=0; j<=255; ++j)
			fout.write((char*)&HTable[j].n,4);
	fout.write((char*)&Fsize,4);

	bitout(fout);

	fout.close();
}

void Huffman_Tree::createbit(){
	int size = HTree[0].key.size();
	int j, len, k;
	bool flag;
	int index, s;
	for(int i=0; i<size; ++i){
		j=0;
		index = HTree[0].key[i];
		if(index<0)
			index += 256;
		do{
			flag = ktKey(HTree[j],HTable[index].key);
			if(flag == 0){
				HTable[index].bit.push_back('0');
				j = HTree[j].left;
			}
			else{
				HTable[index].bit.push_back('1');
				j = HTree[j].right;
			}
			s = HTree[j].key.size();
		}
		while(s!=1);
	}
}

bool Huffman_Tree::ktKey(const Node& src, unsigned char key){
	char tmp = key;
	int flag = HTree[src.left].key.find(tmp);
	if(flag>=0)
		return 0;
	return 1;
}

//xuat file giai nen
void Huffman_Tree::printUncompressFile(char* fn){
	processCompress();
	ofstream fout(fn,ios::binary);
	bitUout(fout);
	fout.close();
}

void Huffman_Tree::bitUout(ofstream &FileOut){
	char current_byte;
	char out;
	unsigned char nbit = 8;
	int i=0;

	while(i<Fsize){
		createUbyte(out,current_byte,nbit);
		FileOut.write((char*)&out,1);
		i++;
	}
}

//khoi tao gia tri cua bang
void Huffman_Tree::initTable(){
	count = 0;
	for(int i=0; i<256; ++i){
		HTable[i].key = i;
		HTable[i].n = 0;
		HTable[i].bit.clear();
	}
}

void Huffman_Tree::initTree(){
	for(int i=0; i<MAXNODE; ++i){
		HTree[i].n = 0;
		HTree[i].left = -1;
		HTree[i].right = -1;
		HTree[i].used = 0;
	}
}

//xu ly qua trinh nen
void Huffman_Tree::processCompress(){
	count = 0;
	for(int i=0; i<256; ++i)
		if(HTable[i].n!=0)
			++count;
	createTree();
	createbit();
}

void Huffman_Tree::createTree(){
	initTree();
	int i,start = 2048, end = 2304;

	int k = start;
	for(i=0; i<256; ++i){
		if(HTable[i].n != 0){
			HTree[k].key = HTable[i].key;
			HTree[k].n = HTable[i].n;
			k++;
		}
	}
	if(count == 1){
		HTree[0] = HTree[1778];
		return;
	}

	int x,y;
	for(i=2047; i>=0; --i){
		if(minNODE(x,y,start,end)){
			HTree[i].key = HTree[x].key + HTree[y].key;
			HTree[i].n = HTree[x].n + HTree[y].n;
			HTree[i].left = x;
			HTree[i].right = y;
			HTree[x].used = 1;
			HTree[y].used = 1;
		}
		else{
			HTree[0] = HTree[x];
			break;
		}
	}
}

bool Huffman_Tree::minNODE(int &i, int &j, int &start, int &end){
	i = -1; j =-1;
	for(int k=end-1; k>=start; --k){
		if(HTree[k].used == 0 && HTree[k].n>0){
			if(i==-1)
				i = k;
			else if(j==-1){
				if(ktNODElon(HTree[k],HTree[i]))
				j = k;
				else{
					j = i;
					i = k;
				}
			}
			else{
				if(ktNODElon(HTree[i],HTree[k]) && HTree[k].used == 0){
					j = i;
					i = k;
				}
				else{
					if(ktNODElon(HTree[j],HTree[k]) && HTree[k].used == 0)
							j = k;
				}
			}
		}
	}

	if(i!=-1 && j!=-1){
		if(ktNODElon(HTree[i],HTree[j])){
			int tmp = i;
			i = j;
			j = tmp;
		}
		start--;
		return 1;
	}
	return 0;
}

bool Huffman_Tree::ktNODElon(const Node& x, const Node& y){
	if(x.n > y.n || (x.n == y.n && x.key > y.key))
		return 1;
	return 0;
}

void Huffman_Tree::bitout(ofstream &FileOut){
	char current_byte;
	string nbit;
	int index;

	
	while(!InputData.empty()){
		index = InputData[0];
		if(index<0)
			index+=256;
		nbit += HTable[index].bit;		//doc du lieu bit cua ky tu dau
		InputData.erase(0,1);					//xoa ky tu dau
		if(nbit.length() >= 8){
			createbyte(current_byte,nbit);
			FileOut.write((char*)&current_byte,1);
		}
		if(InputData.empty()){
			while(!nbit.empty()){
				createbyte(current_byte,nbit);
				FileOut.write((char*)&current_byte,1);
			}
		}
	}
}

void Huffman_Tree::createbyte(char &x, string& nbit){
	x = 0;
	int i = 0;
	for(i=0; i<8; ++i){
		x <<= 1;
		if(i < nbit.length())
			if(nbit[i] == '1')
				x |= 1;
	}
	nbit.erase(0,8);
}

void Huffman_Tree::createUbyte(char &x, char &src, unsigned char &nbit){
	x = 0;
	char kq;
	int j = 0;
	while(1){
		if(nbit == 8){
			src = InputData[0];
			InputData.erase(0,1);
			nbit = 0;
		}
		if(HTree[j].key.length()==1){
			x = HTree[j].key[0];
			break;
		}
		kq = src&TBYTE;
		if(kq == 0)
			j = HTree[j].left;
		else
			j = HTree[j].right;
		src <<= 1;
		nbit++;
	}
}