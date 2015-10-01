/*
ID:dirkyao1
PROG:nocows
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
using namespace std;

#define MOD 9901;
int table[102][202], smalltable[102][202];

int solve(int N, int K)
{
	table[1][1] = 1;
	for (int i = 2; i <= K; i++)
	{
		for (int j = 1; j <= N; j+=2)
		{
			for (int k = 1; k <= j - 1 - k;k+=2)
			{
				int c = 0;
				if (k == j - 1 - k)
				{
					c = 1;
				}
				else
					c = 2;

				table[i][j] += (table[i - 1][k] * smalltable[i - 2][j - 1 - k] + table[i - 1][j - 1 - k] * smalltable[i - 2][k] + table[i - 1][k] * table[i - 1][j - 1 - k])*c;
				table[i][j] = table[i][j] % MOD;
			}
		}

		for (int k = 0; k <= N; k++)
		{
			smalltable[i - 1][k] = smalltable[i - 2][k] + table[i - 1][k];
			smalltable[i - 1][k] = smalltable[i - 1][k] % MOD; 
		}
	}
	return table[K][N];
}

int main()
{
	ifstream fin("nocows.in");
	ofstream fout("nocows.out");

	int N, K;
	fin >> N >> K;

	memset(table, 0, sizeof(int) * 102 * 202);
	memset(smalltable, 0, sizeof(int) * 102 * 202);

	fout << solve(N, K) << endl;
	return 0;
}