#include "MyActionReg.h"

Loader l;
MyActionReg reg;

void readall();

void main()
{
	bool isOpen = true;
	int flag = 0;
	char ch;
	
	while (isOpen)
	{
		//Nhap lua chon
		do
		{
			system("cls");

			cout << "1. Tranning" << endl;
			cout << "2. Test toan bo du lieu" << endl;
			cout << "3. Test 1 file (hien thi tren video)" << endl;
			cout << "4. Kiem tra toan bo du lieu (hien thi tren video)" << endl;
			cout << "5. Thoat" << endl;
			cout << "Nhap gia lua chon: ";
	
			cin >> flag;
		}
		while(!(flag > 0 && flag < 6));

		//Xu ly cac lua chon
		if(flag == 1)
		{
			cout << "Chuong trinh co the chay tu 20' - 30'. Xin vui long cho doi ..." << endl;
			reg.train("");
		}
		if(flag == 2)
		{
			cout << "Chuong trinh co the chay tu 10' - 15'. Xin vui long cho doi ..." << endl;
			reg.load();
			reg.predictall(" ");
		}
		if(flag == 3)
		{
			string fxml, fvideo;
			reg.load();

			cout << "Nhap duong dan file xml: ";
			cin >> fxml;

			cout << "Nhap duong dan file video: ";
			cin >> fvideo;

			reg.showresult(fxml, fvideo);
		}
		if(flag == 4)
			readall();
		if(flag == 5)
			return;

		//Xu ly tiep tuc chuong trinh
		do
		{
			cout << "Ban co muon tiep tuc chuong trinh (Y/N): ";
			cin >> ch;
		}while(!(ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N'));

		if(ch == 'y' || ch == 'Y')
			isOpen = true;
		else
			isOpen = false;
	}
}

void readall()
{
	vector<string> fname;
	vector<string> aname;

	reg.load();

	l.readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\basketball\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		reg.showresult(aname[i], fname[i]);
	}
	aname.clear();
	fname.clear();

	l.readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\biking\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		reg.showresult(aname[i], fname[i]);
	}
	aname.clear();
	fname.clear();

	l.readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\diving\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		reg.showresult(aname[i], fname[i]);
	}
	aname.clear();
	fname.clear();
	
	l.readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\golf_swing\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		reg.showresult(aname[i], fname[i]);
	}
	aname.clear();
	fname.clear();

	l.readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\horse_riding\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		reg.showresult(aname[i], fname[i]);
	}
	aname.clear();
	fname.clear();
	
	l.readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\soccer_juggling\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		reg.showresult(aname[i], fname[i]);
	}
	aname.clear();
	fname.clear();

	l.readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\tennis_swing\\test.txt", fname, aname);
	for(unsigned int i = 9; i < fname.size(); i++)
	{
		reg.showresult(aname[i], fname[i]);
	}
	aname.clear();
	fname.clear();

	l.readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\trampoline_jumping\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		reg.showresult(aname[i], fname[i]);
	}
	aname.clear();
	fname.clear();
	
	l.readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\volleyball_spiking\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		reg.showresult(aname[i], fname[i]);
	}
	aname.clear();
	fname.clear();

	l.readFilename("..\\..\\..\\DATA\\UCF11_updated_mpg\\walking\\test.txt", fname, aname);
	for(unsigned int i = 0; i < fname.size(); i++)
	{
		reg.showresult(aname[i], fname[i]);
	}
	aname.clear();
	fname.clear();
}