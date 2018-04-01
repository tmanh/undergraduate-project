#include <iostream>
#include "BOARD.h"
#include "Npuzzle.h"
using namespace std;

int main(int argc, char* argv[])
{
	if(argc == 4)
	{
		Npuzzle x;
		bool flag;
		x.load(argv[2]);
		flag = x.search(atoi(argv[1]));
		x.save(argv[3], flag);
	}
}