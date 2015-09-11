/*
ID:dirkyao1
PROG:holstein
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

int V, G;
int min_level = 200;
int vit_req[30], vit_provide[20][30];
int decision[20], result[30];
int vit_now[30] = { 0 };

int judge_satisfy(int stage)
{
	for (int i = 0;i < V;i++)
	{
		if (vit_now[i] < vit_req[i])
		{
			return 0;
		}
	}
	int stage_num = 0;
	for (int i = 0;i <= stage;i++)
	{
		if(decision[i])
			stage_num++;
	}
	return stage_num;
}

void count_sum(int stage)
{
	memset(vit_now,0,sizeof(int) * 30);
	for (int i = 0;i <= stage;i++)
	{
		if (decision[i] == 1)
		{
			for (int j = 0;j < V;j++)
			{
				vit_now[j] += vit_provide[i][j];
			}
		}
	}
	int state = judge_satisfy(stage);
	if (state > 0 && state < min_level)
	{
		memset(result, 0, sizeof(int) * 30);
		min_level = state;
		for (int i = 0;i <= stage;i++)
		{
			result[i] = decision[i];
		}
	}
}

void solve(int stage)
{
	if (stage < G)
	{
		decision[stage] = 1;
		count_sum(stage);
		solve(stage + 1);

		decision[stage] = 0;
		count_sum(stage);
		solve(stage + 1);
	}
	else
		return;
}

int main()
{
	ifstream fin("holstein.in");
	ofstream fout("holstein.out");

	fin >> V;
	for (int i = 0;i < V;i++)
	{
		fin >> vit_req[i];
	}
	fin >> G;
	for (int i = 0;i < G;i++)
	{
		for (int j = 0;j < V;j++)
		{
			fin >> vit_provide[i][j];
		}
	}

	solve(0);

	fout << min_level;
	for (int i = 0;i < G;i++)
	{
		if (result[i] == 1)
			fout << ' ' << i + 1;
	}
	fout << endl;
	return 0;
}