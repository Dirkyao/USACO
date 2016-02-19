/*
ID£ºdirkyao1
PROG:humble
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
#include<math.h>
using namespace std;

long long humble_set[100100];

int find_min(long long *temp,int K)
{
	long long min = 9999999999;
	int min_index = -1;
	for (int i = 0;i < K;i++)
	{
		if (temp[i] < min)
		{
			min = temp[i];
			min_index = i;
		}
			
	}
	return min_index;
}

int simulate(int N,int K, long long *prime_set, long long *prime_index)
{
	long long temp[110];
	int min_result;
	humble_set[0] = 1;

	for (int i = 1;i <= N;i++)
	{
		for (int j = 0;j < K;j++)
			temp[j] = humble_set[prime_index[j]] * prime_set[j];
		min_result = find_min(temp, K);

		for (int j = 0;j < K;j++)
		{
			if (temp[j] == temp[min_result])
			{
				prime_index[j]++;
			}
		}
		humble_set[i] = temp[min_result];
		//prime_index[min_result]++;
	}
	return humble_set[N];
}

int main()
{
	ifstream fin("humble.in");
	ofstream fout("humble.out");
	int K, N;
	
	long long prime_set[110],prime_index[110];

	fin >> K >> N;
	for (int i = 0;i < K;i++)
	{
		fin >> prime_set[i];
	}
	memset(prime_index, 0, sizeof(prime_index));

	fout << simulate(N, K, prime_set, prime_index) << endl;
	return 0;
}