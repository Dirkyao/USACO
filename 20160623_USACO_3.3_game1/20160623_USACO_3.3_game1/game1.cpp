/*
ID:dirkyao1
PROG:game1
LANG:C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int N;
int nums[120];

#define MAX(a,b)((a)>(b)?(a):(b))

int my_sum(int i, int j)
{
	int count = 0;
	for (int k = i; k <= j; k++)
	{
		count += nums[k];
	}
	return count;
}

void init_dp(int(*dp)[120])
{
	for (int i = 0; i + 1 < N; i++)
	{
		dp[i][i + 1] = MAX(nums[i], nums[i + 1]);
	}
}

void dp_simulate(int(*dp)[120])
{
	for (int i = 2; i < N; i++)
	{
		for (int j = 0; j + i < N; j++)
		{
			dp[j][i+j] = MAX(nums[j + i] + my_sum(j, i + j - 1) - dp[j][i + j - 1], nums[j] + my_sum(j + 1,i + j) - dp[j + 1][i + j]);
		}
	}
}

int main()
{
	ifstream fin("game1.in");
	ofstream fout("game1.out");

	fin >> N;
	for (int i = 0; i < N; i++)
	{
		fin >> nums[i];
	}
	int dp[120][120];
	init_dp(dp);
	dp_simulate(dp);
	fout << dp[0][N - 1]<<' '<< my_sum(0,N-1)-dp[0][N-1] << endl;
	return 0;
}