/*
ID:dirkyao1
PROG:range
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
using namespace std;

#define MIN(a,b,c)((a)<(b)?((a)<(c)?(a):(c)):((b)<(c)?(b):(c)))

int N;
int fields[251][251];
int counts[251];

void account(int sub_rects[][250])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 2; k <= sub_rects[i][j]; k++)
			{
				counts[k]++;
			}
		}
	}
}

int calculate_neighbor(int sub_rects[][250],int row,int col)
{
	if (row < N - 1 && col < N - 1 && sub_rects[row][col] == 1)
	{
		return MIN(sub_rects[row + 1][col], sub_rects[row][col + 1], sub_rects[row + 1][col + 1]) + 1;
	}
	else
		return sub_rects[row][col];
}

void two_dim_dp(int(*sub_rects)[250])
{
	for (int i = N - 1; i >= 0; i--)
		for (int j = N - 1; j >= 0; j--)
		{
			sub_rects[i][j] = calculate_neighbor(sub_rects, i, j);
		}
}

int main()
{
	ifstream fin("range.in");
	ofstream fout("range.out");

	fin >> N;
	int sub_rects[250][250];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			char state;
			fin >> state;
			fields[i][j] = state - '0';
			sub_rects[i][j] = fields[i][j];
		}
	}
	two_dim_dp(sub_rects);
	memset(counts, 0, sizeof(counts));
	account(sub_rects);
	for (int i = 2; i <= N; i++)
	{
		if (counts[i] > 0)
		{
			fout << i << ' ' << counts[i] << endl;
		}
	}

	return 0;
}