/*
ID:dirkyao
PROG:inflate
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
using namespace std;

typedef struct node{
	int score;
	int minute;
}category;

int dp(int M, int N, category *cates)
{
	int scores[10010];
	memset(scores, 0, sizeof(scores));

	for (int i = 0;i <= M; i++)
	{
		for (int j = 0;j < N;j++)
		{
			if (i - cates[j].minute>=0 && scores[i] < scores[i - cates[j].minute] + cates[j].score)
			{
				scores[i] = scores[i - cates[j].minute] + cates[j].score;
			}
		}
	}
	int max = 0;
	for (int i = 0;i <= M;i++)
	{
		if (scores[i] > max)
			max = scores[i];
	}
	return max;
}

int main()
{
	int M, N;
	category cates[10010];
	ifstream fin("inflate.in");
	ofstream fout("inflate.out");

	fin >> M >> N;
	for (int i = 0;i < N;i++)
	{
		fin >> cates[i].score >> cates[i].minute;
	}
	fout << dp(M, N, cates) << endl;
	return 0;
}