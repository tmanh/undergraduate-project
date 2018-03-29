#include "func.h"

void initNext(char* x,int* Next)
{
    int m = int(strlen(x));

    Next[0] = -1;

    for (int k = 0; k < m; k++)
    {
        char c = x[k + 1];
        int v = Next[k];

        while (x[v+1] != c && v != -1) {
            v = Next[v];
        }

        if (x[v+1] == c) {
            Next[k+1] = v + 1;
        } else {
            Next[k + 1] = -1;
        }
    }
}

int stringSearchKMP(char *P,char *T, int* &NEXT)
{
    int i,j;

    int n = int(strlen(T));
    int m = int(strlen(P));

    NEXT = new int[m];
    initNext(P,NEXT);

    i=0;j=0;
    while(j+i<n)
    {
        if(P[i] == T[j+i])
        {
            i++;
            if(i==m-1)
                return j;
        }
        else
        {
            j = j+i-NEXT[i];
            if(NEXT[i]>-1)
                i = NEXT[i];
            else
                i = 0;
        }
    }

    return -1;
}

int HASH(char* data, int m, int i)
{
    int temp = 0;
    for(int j = 0; j<m; j++)
    {
        temp += ((int)data[i+j] << (m-j-1));
    }

    return temp;
}

int stringSearchRabinKarp(char* P, char* T, int &count)
{
    count = 0;
    int m = int(strlen(P)), n = int(strlen(T));
    int hashP = HASH(P,m,0);
    int hashTi = HASH(T,m,0);

    int i;
    for(i = 0; i<n; i++)
    {
        if(hashP == hashTi)
        {
            bool flag = true;
            count++;
            for(int j = 0; j<m; j++)
                if(P[j] != T[i+j]) {
                    flag = false;
                    break;
                }
            if(flag == true)
                return i;
        }

        int ti = ((int)T[i] << (m-1));
        hashTi = (hashTi - ti)*2 + T[i+m];
    }

    return -1;
}

void mysearch(const char* in_name, const char* out_name)
{
    char* x,*y;

    if(get_input(x, y, in_name)) {
        get_output(x, y, out_name);
    }
}

bool get_input(char* &P, char* &T, const char* fname)
{
    ifstream fin(fname);

    if(fin.is_open() && !fin.bad() && !fin.fail())
    {
        int m,n;
        fin >> m;
        fin >> n;

        char temp[100];

        fin.getline(temp,100,'\n');
        fin.getline(temp,100,'\r');
        P = new char [strlen(temp)];
        strcpy(P,temp);

        fin.getline(temp,100,'\n');
        fin.getline(temp,100,'\r');
        T = new char [strlen(temp)];
        strcpy(T,temp);

        return true;
    }
    return false;
}

bool get_output(char* &P, char* &T, const char* fname)
{
    ofstream fout;
    fout.open(fname);

    int* NEXT;

    //Rabin Karp
    int count;
    int kq = stringSearchRabinKarp(P,T,count);

    fout << "RABIN KARP" << endl;
    if(kq!=-1)
        fout << "+Ket qua: tim thay";
    else
        fout << "+Ket qua: khong tim thay";
    fout << endl;

    fout << "+Vi tri tim thay: ";
    if(kq!=-1)
        fout << kq;
    else
        fout << "_";
    fout << endl;

    fout << "So lan so sanh chi tiet: " << count << endl;

    //KMP
    kq = stringSearchKMP(P,T,NEXT);
    fout << "KMP" << endl;
    fout << "+NEXT: ";
    int m = (int)strlen(P);
    for(int i = 0; i<m; i++)
        fout << NEXT[i] << " ";
    fout << endl;

    if(kq!=-1)
        fout << "+Ket qua: tim thay";
    else
        fout << "+Ket qua: khong tim thay";
    fout << endl;

    fout << "+Vi tri tim thay: ";
    if(kq!=-1)
        fout << kq;
    else
        fout << "_";
    fout << endl;

    return true;
}
