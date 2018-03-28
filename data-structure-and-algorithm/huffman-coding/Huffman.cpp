/*
Truong Minh Anh - 1112010
truongminhanh93.it@gmail.com
*/

#include "Huffman.h"

Huffman::Huffman(){
	initTable();
}

void Huffman::seekByte(){
	int len;
	int seek = 1028;
	seek += MyHeader.n*8;
	for(unsigned int i=0; i<MyHeader.n; ++i){
		len = MyHeader.FName[i].length();
		seek += (1 + 2*(len+1));
	}
	fout.write((char*)&seek,seek);
}

void Huffman::writeHeader(){
	fout.seekp(0,ios::beg);
	unsigned char len;
	for(int i=0; i<MAXTAB; ++i)						//ghi bang tan so
		fout.write((char*)&MyHeader.FreqInfo[i].n,4);
	fout.write((char*)&MyHeader.n,4);				//ghi so file
	for(unsigned int i=0; i<MyHeader.n; ++i){
		len = MyHeader.FName[i].length();
		fout.write((char*)&len,1);
		fout.write((char*)MyHeader.FName[i].c_str(),2*(len+1));
		fout.write((char*)&MyHeader.FSize[i],4);
		fout.write((char*)&MyHeader.FSeekByte[i],4);
	}
}

void Huffman::readFileHeader(){
	unsigned char len;
	wchar_t tmp[256];
	fin.open(FName,ios::binary);
	readTable();
	fin.read((char*)&MyHeader.n,4);
	MyHeader.FName.resize(MyHeader.n);
	MyHeader.FSize.resize(MyHeader.n);
	MyHeader.FSeekByte.resize(MyHeader.n);
	check.resize(MyHeader.n);
	for(unsigned int i=0; i<MyHeader.n; ++i){
		check[i] = 0;
		fin.read((char*)&len,1);
		MyHeader.FName[i].resize(len);
		fin.read((char*)&tmp,2*(len+1));
		MyHeader.FName[i] = tmp;
		fin.read((char*)&MyHeader.FSize[i],4);
		fin.read((char*)&MyHeader.FSeekByte[i],4);
	}
}

void Huffman::getFileHeader(){
	int n = data.getnFile();
	MyHeader.n = n;
	MyHeader.FPath.resize(n);
	MyHeader.FName.resize(n);
	MyHeader.FSeekByte.resize(n);
	MyHeader.FSize.resize(n);
	for(int i=0; i<n; ++i){
		MyHeader.FName[i] = data.getname(i);
		MyHeader.FPath[i] = data.getpath(i);
		MyHeader.FSize[i] = data.getsize(i);
		MyHeader.FSeekByte[i] = 0;
	}
}

void Huffman::setOutput(wstring name){
	FName = name;
}
void Huffman::setDataCompress(wstring name){
	data.set(name);
	getFileHeader();
}
void Huffman::setDataExtract(wstring name, string checkE){
	FName = name;
	readExtract();
	if(checkE == "-all "){
		for(unsigned int i=0; i<MyHeader.n; ++i)
			check[i] = 1;
		return;
	}

	checkE.erase(0,1);
	istringstream ss(checkE); // 255 0 0
	int tmp;
	while(!checkE.empty()){
		ss >> tmp;
		check[tmp] = 1;
		int index = checkE.find(' ');
		if(index>=0)
			checkE.erase(0,checkE.find(' ')+1);
		else
			checkE.clear();
	}
}

void Huffman::initTable(){
	nchar = 0;
	for(int i=0; i<256; ++i){
		MyHeader.FreqInfo[i].key = i;
		MyHeader.FreqInfo[i].n = 0;
		MyHeader.FreqInfo[i].bit.clear();
	}
}
void Huffman::initTree(){
	int i,k=256;
	for(i=0; i<512; ++i){
		HTree[i].Freq = 0;
		HTree[i].left = HTree[i].right = -1;
		HTree[i].used = 0;
	}
	for(i=0; i<256; ++i)
		if(MyHeader.FreqInfo[i].n != 0){
			HTree[k].key = MyHeader.FreqInfo[i].key;
			HTree[k].Freq = MyHeader.FreqInfo[i].n;
			k++;
		}
}

void Huffman::readTable(){
	initTable();
	for(int i=0; i<MAXTAB; ++i)
		fin.read((char*)&MyHeader.FreqInfo[i].n,4);
}

void Huffman::readCompress(){
	char ch;
	initTable();
	for(unsigned int i=0; i<MyHeader.n; ++i){
		fin.open(data.getpath(i),ios::binary);

		if(fin==NULL)
			return;
		while(fin.read((char*)&ch,1))
			if(ch>=0)
				MyHeader.FreqInfo[ch].n++;
			else
				MyHeader.FreqInfo[MAXTAB+ch].n++;

		fin.close();
	}
}
void Huffman::readExtract(){
	readFileHeader();
}

void Huffman::Compress(){
	processCompress();
}

void Huffman::Extract(){
	processExtract();
}

void Huffman::processCompress(){
	readCompress();
	createTree();
	createbit();
	printFileCompress();
}

void Huffman::processExtract(){
	createTree();
	printFileExtract();
}

void Huffman::createTree(){
	initTree();
	int x,y, start = 256, end = 512;
	if(nchar == 1){
		HTree[0] = HTree[256];
		return;
	}

	for(int i=255; i>=0; --i)
		if(minNODE(x,y,start,end)){
			HTree[i].key = HTree[x].key + HTree[y].key;
			HTree[i].Freq = HTree[x].Freq + HTree[y].Freq;
			HTree[i].left = x;
			HTree[i].right = y;
			HTree[x].used = HTree[y].used = 1;
		}
		else{
			HTree[0] = HTree[x];
			break;
		}
}
void Huffman::createbit(){
	int size = HTree[0].key.size();
	int j;
	bool flag;
	int index, s;
	for(int i=0; i<size; ++i){
		j=0;
		index = HTree[0].key[i];
		if(index<0)
			index += MAXTAB;
		do{
			flag = ktKey(HTree[j],MyHeader.FreqInfo[index].key);
			if(flag == 0){
				MyHeader.FreqInfo[index].bit.push_back('0');
				j = HTree[j].left;
			}
			else{
				MyHeader.FreqInfo[index].bit.push_back('1');
				j = HTree[j].right;
			}
			s = HTree[j].key.size();
		}
		while(s!=1);
	}
}

void Huffman::printFileCompress(){
	fout.open(FName,ios::binary);
	seekByte();
	for(unsigned int i=0; i<MyHeader.n; ++i){
		fin.open(MyHeader.FPath[i],ios::binary);
		bitout(MyHeader.FSize[i],MyHeader.FSeekByte[i]);
		fin.close();
	}
	writeHeader();
	fout.close();
}

void Huffman::printFileExtract(){
	for(unsigned int i=0; i<MyHeader.n ;i++){
		if(check[i] == 1){
			fout.open(MyHeader.FName[i],ios::binary);
			bitUout(i);
			int size = fout.tellp();
			if(size != MyHeader.FSize[i])
				SizeFileError(i);
			fout.close();
		}
		else
			fin.seekg(MyHeader.FSeekByte[i],ios::cur);
	}
}

void Huffman::bitUout(int index){
	char out;
	char InputData;
	unsigned char nbit = 8;
	unsigned int i=0;
	while(i<MyHeader.FSize[index]){
		createUbyte(out,InputData,nbit);
		fout.write((char*)&out,1);
		i++;
	}
}

void Huffman::bitout(unsigned int Fsize, unsigned int& seek){
	char current_byte, InputData;
	string nbit;
	unsigned char index;

	for(unsigned int i=0; i<Fsize; ++i){
		fin.read((char*)&InputData,1);
		index = InputData;
		nbit += MyHeader.FreqInfo[index].bit;	//doc du lieu bit cua ky tu dau
		
		if(nbit.length() >= 8){
			seek++;
			createbyte(current_byte,nbit);
			fout.write((char*)&current_byte,1);
		}
	}
	while(!nbit.empty()){
		seek++;
		createbyte(current_byte,nbit);
		fout.write((char*)&current_byte,1);
	}
}

bool Huffman::minNODE(int &i, int &j, int &start, int &end){
	i = -1; j =-1;
	for(int k=end-1; k>=start; --k){
		if(HTree[k].used == 0 && HTree[k].Freq>0){
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
			else
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
bool Huffman::ktKey(const Node& src, char key){
	char tmp = key;
	int flag = HTree[src.left].key.find(tmp);
	if(flag>=0)
		return 0;
	return 1;
}
bool Huffman::ktNODElon(const Node& x, const Node& y){
	if(x.Freq > y.Freq || (x.Freq == y.Freq && x.key > y.key))
		return 1;
	return 0;
}

void Huffman::createbyte(char &x, string& nbit){
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

void Huffman::createUbyte(char &x, char& InputData , unsigned char &nbit){
	x = 0;
	char kq;
	int j = 0;
	while(1){
		if(nbit == 8){
			fin.read((char*)&InputData,1);
			nbit = 0;
		}
		if(HTree[j].key.length()==1){
			x = HTree[j].key[0];
			break;
		}
		kq = InputData&HBIT;
		if(kq == 0)
			j = HTree[j].left;
		else
			j = HTree[j].right;
		InputData <<= 1;
		nbit++;
	}
}

void Huffman::Display(){
	for(unsigned int i=0; i<MyHeader.n; ++i){
		cout << i << ".\t";
		wcout << MyHeader.FName[i] << "\t";
		cout << MyHeader.FSize[i] << "\t";
		cout << MyHeader.FSeekByte[i] << endl;
	}
}

void Huffman::SizeFileError(int index){
	cout << "Loi: File " << index << " sai kich thuoc" << endl;
}