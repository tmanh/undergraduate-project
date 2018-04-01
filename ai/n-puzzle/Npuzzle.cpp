#include "Npuzzle.h"

bool Npuzzle::load(char* fn)
{
	if(!start.read(fn))
		return 0;
	createEND();
	return 1;
}

bool Npuzzle::save(char* fn, bool flag)
{
	ofstream fout(fn);

	if(fout==NULL)
		return 0;

	if(flag == 1)
		write(fout,close.size()-1);
	else
		fout << "-1" << endl;

	fout.close();

	return 1;
}

void Npuzzle::createEND()
{
	end1.createEND1();
	end2.createEND2();
}

bool Npuzzle::search(short s)
{
	if(s == 1)
		return BFS();
	return DFS();
}

void Npuzzle::write(ofstream &fout, int i)
{
	if(i==0)
		return;

	write(fout,close[i].getPrev());

	fout << "(" << close[i].get_pY() << "," << close[i].get_pX() << ") ";
	if(close[i].getDirect() == N)
		fout << "N";
	else if(close[i].getDirect() == E)
		fout << "E";
	else if(close[i].getDirect() == S)
		fout << "S";
	else
		fout << "W";
	fout << endl;
}

bool Npuzzle::addSucc(bool &flag, BOARD& tmp, BOARD& tmp2)
{
	for(i=0; i<4; ++i)
		{
			tmp2 = tmp;
			if(!tmp.Move(i,tmp2))
				continue;
			tmp2.setPrev(close.size()-1);
			if(tmp2==end1 || tmp2==end2)
				return 1;

			flag = 1;

			len = open.size();
			for(j=0; j<len; ++j)
				if(tmp2 == open[j])
				{
					flag = 0;
					break;
				}
			if(flag == 1)
			{
				len = close.size();
				for(j=0; j<len; ++j)
					if(tmp2 == close[j])
					{
						flag = 0;
						break;
					}
			}
			if(flag == 1)
				open.push_back(tmp2);
		}
	return 0;
}

bool Npuzzle::BFS()
{
	BOARD tmp, tmp2;
	int count=0;
	bool flag;

	if(start == end1 || start == end2)
	{
		close.push_back(start);
		return 1;
	}
	open.push_back(start);

	while(!open.empty())
	{
		if(count == MAX)
			return 0;

		//dua trang thai dau open vap close
		tmp = open[0];
		open.erase(open.begin());
		close.push_back(tmp);

		if(addSucc(flag,tmp,tmp2))
		{
			close.push_back(tmp2);
			return 1;
		}

		count++;
	}

	return 0;
}

bool Npuzzle::DFS()
{
	BOARD tmp, tmp2;
	int count=0;
	bool flag;

	if(start == end1 || start == end2)
	{
		close.push_back(start);
		return 1;
	}
	open.push_back(start);

	while(!open.empty())
	{
		if(count == MAX)
			return 0;

		//dua trang thai dau open vap close
		tmp = open[0];
		open.erase(open.end()-1);
		close.push_back(tmp);

		if(addSucc(flag,tmp,tmp2))
		{
			close.push_back(tmp2);
			return 1;
		}

		count++;
	}

	return 0;
}