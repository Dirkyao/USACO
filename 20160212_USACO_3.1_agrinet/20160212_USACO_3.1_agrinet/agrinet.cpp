/*
ID:dirkyao1
PROG:agrinet
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
using namespace std;

int N;
int cost[110][110];
int vis[110];
const int INF = 99999999;

int prim()
{
	memset(vis, 0, sizeof(vis));
	int minPath = 0;
	int lowc[110];
	int cur;

	vis[0] = 1;
	for (int i = 0;i < N;i++)
		lowc[i] = cost[0][i];
	for (int i = 0;i < N - 1;i++)
	{
		int minc = INF;
		cur = -1;

		for (int j = 0;j < N;j++)
		{
			if (lowc[j] < minc && vis[j] == 0)
			{
				minc = lowc[j];
				cur = j;
			}
		}
		if (cur == -1)
			return -1;

		vis[cur] = 1;
		minPath += minc;
		for (int k = 0;k < N;k++)
		{
			if (cost[cur][k] < lowc[k] && vis[k] == 0)
			{
				lowc[k] = cost[cur][k];
			}
		}
	}
	return minPath;
}

int main()
{
	ifstream fin("agrinet.in");
	ofstream fout("agrinet.out");

	fin >> N;
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			fin >> cost[i][j];
		}
	}

	int lowcost = prim();
	fout << lowcost << endl;
	return 0;
}