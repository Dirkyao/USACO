/*
ID:dirkyao1
PROG:runround
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

int num[9] = { 0 };
int flag[9] = { 0 };
int track[9] = { 0 };

void reverse(int N)
{
	for (int i = 0; i < N / 2; i++)
	{
		int temp = num[i];
		num[i] = num[N - 1 - i];
		num[N - i - 1] = temp;
	}
}

int judge(int N)
{
	int next = 0;

	reverse(N);

	for (int i = 0; i < N; i++)
	{
		next = (next + num[next]) % (N);
		track[num[next] - 1]++;
	}
	for (int j = 0; j < N; j++)
	{
		if (track[num[j] - 1] != 1)
		{
			memset(track, 0, sizeof(int) * 9);
			return 0;
		}
	}
	return 1;
}

int transfor(int N)
{
	int temp = 0;
	for (int i = 0; i < N; i++)
	{
		temp = temp * 10 + num[i];
	}
	return temp;
}

bool judge_unique(int count)
{
	for (int i = 0; i < count; i++)
	{
		flag[num[i] - 1]++;
		if (num[i] == 0 || flag[num[i] - 1] != 1)
		{
			memset(flag, 0, sizeof(int) * 9);
			return false;
		}
	}
	memset(flag, 0, sizeof(int) * 9);
	return true;
}

int int2digits(unsigned int origin)
{
	int count = 0;

	while (origin > 0)
	{
		num[count] = origin % 10;
		count++;
		origin /= 10;
	}
	return count;
}


int main()
{
	ifstream fin("runround.in");
	ofstream fout("runround.out");

	int origin;
	fin >> origin;

	int ans = -3 % 8;

	for (unsigned int i = origin + 1; i < 999999999; i++)
	{
		int N = int2digits(i);
		if (judge_unique(N))
		{
			int result = judge(N);
			if (result == 1)
			{
				fout << i << endl;
				return 0;
			}

		}
	}
}