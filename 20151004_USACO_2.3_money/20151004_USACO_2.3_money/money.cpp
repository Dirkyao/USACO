/*
ID:dirkyao
PROG:money
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string.h>
using namespace std;

int main()
{
	ifstream fin("money.in");
	ofstream fout("money.out");

	int V, N;
	int coins[30];

	long long(*approach)[30] = new long long[10010][30];

	fin >> V >> N;
	for (int i = 0; i < V; i++)
	{
		fin >> coins[i];
	}
	sort(coins, coins + V);
	memset(approach, 0, sizeof(long long) * 10010 * 30);

	for (int i = 0; i < 30; i++)
	{
		approach[0][i] = 1;
	}

	for (int i = coins[0]; i <= N; i++)
	{
		for (int j = 0; j < V; j++)
		{
			if (j == 0)
			{
				approach[i][j] = approach[i - coins[j]][j];
			}
			else
			{
				if (i - coins[j] > -1)
					approach[i][j] = approach[i][j - 1] + approach[i - coins[j]][j];
				else
					approach[i][j] = approach[i][j - 1];
			}
		}
	}
	fout << approach[N][V - 1] << endl;
	return 0;
}