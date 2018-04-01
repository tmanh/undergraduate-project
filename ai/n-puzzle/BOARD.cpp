#include "BOARD.h"

short BOARD::i = 0;
short BOARD::j = 0;
short BOARD::tmp = 0;
short BOARD::n = 0;

BOARD::BOARD()
{
	Zero.x = 0;
	Zero.y = 0;
	direct = -1;
}

bool BOARD::operator==(const BOARD& src){
	for(i=0; i<n; ++i)
		for(j=0; j<n; ++j)
			if(data[i][j] != src.data[i][j])
				return 0;
	return 1;
}

bool BOARD::read(char* fn){
	ifstream fin(fn);
	
	if(fin == NULL)
		return 0;

	fin >> n;

	for(i=0; i<n; ++i)
		for(j=0; j<n; ++j)
		{
			fin >> tmp;
			
			if(tmp == 0)
			{
				Zero.x = j;
				Zero.y = i;
			}

			data[i][j] = tmp;
		}

	fin.close();
	return 1;
}

char BOARD::getDirect()
{
	return direct;
}

bool BOARD::Move(char dir, BOARD& result){
	Point tmp;
	bool flag = 0;

	tmp.x = Zero.x;
	tmp.y = Zero.y;

	if(dir == 0 && Zero.y >= 1)
	{
		flag = 1;
		tmp.y--;
	}
	else if(dir == 3 && Zero.y < n-1)
	{
		flag = 1;
		tmp.y++;
	}
	else if(dir == 2 && Zero.x < n-1)
	{
		flag = 1;
		tmp.x++;
	}
	else if(dir == 1 && Zero.x >= 1)
	{
		flag = 1;
		tmp.x--;
	}

	result.data[Zero.y][Zero.x] =  result.data[tmp.y][tmp.x];
	result.data[tmp.y][tmp.x] = 0;
	result.direct = 3-dir;
	result.Zero = tmp;

	return flag;
}

void BOARD::createEND1()
{
	short k = 0;
	for(i=0; i<n; ++i)
		for(j=0; j<n; ++j)
			data[i][j] = k++;
}
void BOARD::createEND2()
{
	short k = 1;
	for(i=0; i<n; ++i)
		for(j=0; j<n; ++j)
			data[i][j] = k++;
	data[n-1][n-1] = 0;
}

int BOARD::getN()
{
	return n;
}

int BOARD::getPrev()
{
	return prev;
}

int BOARD::get_pX()
{
	return Zero.x;
}

int BOARD::get_pY()
{
	return Zero.y;
}

void BOARD::setPrev(int p)
{
	prev = p;
}