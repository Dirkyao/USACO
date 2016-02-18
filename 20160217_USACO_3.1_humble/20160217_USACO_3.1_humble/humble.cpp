/*
ID£ºdirkyao1
PROG:humble
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
using namespace std;

int find_min(int* temp,int K)
{
	int min = INFINITY;
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

int simulate(int N,int K, int* humble_set, int* prime_set, int* prime_index)
{
	int temp[110];
	int min_result;
	prime_index[0] = humble_set[0];

	for (int i = 1;i < N;i++)
	{
		for (int j = 0;j < K;j++)
			temp[j] = humble_set[prime_index[j]] + prime_set[j];
		min_result = find_min(temp, K);

		humble_set[i] = temp[min_result];
		prime_index[min_result]++;
	}
	return humble_set[N - 1];
}

int main()
{
	ifstream fin("humble.in");
	ofstream fout("humble.out");
	int K, N;
	int humble_set[100100];
	int prime_set[110],prime_index[110];

	fin >> K >> N;
	for (int i = 0;i < K;i++)
	{
		fin >> prime_set[i];
	}
	memset(prime_index, 0, sizeof(prime_index));

	fout << simulate(N, K, humble_set, prime_set, prime_index) << endl;
	return 0;
}