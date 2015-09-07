/*
ID:dirkyao1
PROG:sort3
LANG:C++
*/
#include<iostream>
#include<fstream>
using namespace std;

void count_flow(int *integer, int *tri_index, int(*flow_mat)[3], int N)
{
	for (int i = 0;i < N;i++)
	{
		if (i < tri_index[0])
		{
			if (integer[i] == 2)
			{
				flow_mat[0][1]++;
			}
			else if (integer[i] == 3)
			{
				flow_mat[0][2]++;
			}
		}
		else if (i < tri_index[0] + tri_index[1])
		{
			if (integer[i] == 1)
			{
				flow_mat[1][0]++;
			}
			else if (integer[i] == 3)
			{
				flow_mat[1][2]++;
			}
		}
		else if (i < N)
		{
			if (integer[i] == 1)
			{
				flow_mat[2][0]++;
			}
			else if (integer[i] == 2)
			{
				flow_mat[2][1]++;
			}
		}
	}
}

void tri_count(int *integer, int *tri_index, int N)
{
	for (int i = 0;i < N;i++)
	{
		if (integer[i] == 1)
			tri_index[0]++;
		else if (integer[i] == 2)
			tri_index[1]++;
		else
			tri_index[2]++;
	}
}

int count_swap(int (*flow_mat)[3])
{
	int sum = 0;
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			sum += flow_mat[i][j]>flow_mat[j][i] ? flow_mat[j][i] : flow_mat[i][j];
			if (flow_mat[i][j]>flow_mat[j][i])
			{
				flow_mat[i][j] -= flow_mat[j][i];
				flow_mat[j][i] = 0;
			}
			else
			{
				flow_mat[j][i] -= flow_mat[i][j];
				flow_mat[i][j] = 0;
			}
		}
	}
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (flow_mat[i][j] != 0)
			{
				sum += flow_mat[i][j] * 2;
				return sum;
			}
		}
	}
	return sum;
}

int main()
{
	int N, swap_sum;
	int integer[1010];
	int tri_index[3] = { 0 };
	int flow_mat[3][3] = { 0 };
	ifstream fin("sort3.in");
	ofstream fout("sort3.out");

	fin >> N;
	for (int i = 0;i < N;i++)
	{
		fin >> integer[i];
	}
	tri_count(integer, tri_index, N);
	count_flow(integer, tri_index, flow_mat, N);
	swap_sum = count_swap(flow_mat);
	fout << swap_sum << endl;
	return 0;
}