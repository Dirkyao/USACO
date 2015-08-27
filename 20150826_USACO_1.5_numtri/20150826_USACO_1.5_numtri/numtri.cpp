/*
ID:dirkyao1
PROG:numtri
LANG:C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	int R;
	int(*numtri)[1000] = new int[1000][1000];
	int(*long_path)[1000] = new int[1000][1000];

	ifstream fin("numtri.in");
	ofstream fout("numtri.out");

	fin >> R;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			fin >> numtri[i][j];
		}
	}

	for (int k = 0; k < R; k++)
	{
		long_path[R - 1][k] = numtri[R - 1][k];
	}
	for (int i = R - 2; i >= 0; i--)
	{
		for (int j = 0; j <= i; j++)
		{
			long_path[i][j] = long_path[i + 1][j] < long_path[i + 1][j + 1] ? long_path[i + 1][j + 1] : long_path[i + 1][j];
			long_path[i][j] += numtri[i][j];
		}
	}
	fout << long_path[0][0] << endl;
	return 0;
}