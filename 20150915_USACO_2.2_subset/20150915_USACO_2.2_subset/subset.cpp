/*
ID:dirkyao1
PROG:subset
LANG:C++
*/
#include<fstream>
#include<iostream>
#include<string.h>
using namespace std;

long long approachs[40][800] = { 0 };

int main()
{
	ifstream fin("subset.in");
	ofstream fout("subset.out");

	int N;
	fin >> N;

	approachs[1][0] = 1;
	approachs[1][1] = 1;
	for (int i = 2; i <= N;i++)
	{
		int sum = (1 + i)*i / 2;
		for (int j = 0;j <= sum;j++)
		{
			if (j < i)
			{
				approachs[i][j] = approachs[i - 1][j];
			}
			else
			{
				approachs[i][j] = approachs[i - 1][j] + approachs[i - 1][j - i];
			}
		}
	}
	int target = (1 + N)*N / 2;
	if (target % 2 == 1)
		fout << 0<<endl;
	else
		fout << approachs[N][target / 2]/2 << endl;
	return 0;
}