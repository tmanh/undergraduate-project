#ifndef func_h
#define func_h

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void initNext(char* x,int* Next);
int stringSearchKMP(char *P,char *T, int* &NEXT);
int HASH(char* data, int m, int i);
int stringSearchRabinKarp(char* P, char* T, int &count);
bool get_input(char* &P, char* &T, const char* fname);
bool get_output(char* &P, char* &T, const char* fname);
void mysearch(const char* in_name, const char* out_name);

#endif /* func_h */
