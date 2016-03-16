/*
ID:dirkyao1
PROG:kimbits
LANG:C++
*/
#include<iostream>
#include<memory.h>
#include<fstream>
using namespace std;

int K, L;
long long I;
long long states[33][33];
int bits[33];

void find()
{
	ofstream fout("kimbits.out");
	long long index = I;

	for (int i = 0; i < K; i++)
	{
		if (states[K - i - 1 ][L] < index && states[K - i][L] >= index)
		{
			if (i == K - 1)
			{
				bits[i] = index - 1;
				break;
			}
			bits[i] = 1;
			index = index - states[K - i - 1][L];
			L--;
		}
		else
			bits[i] = 0;
	}
	for (int i = 0; i < K; i++)
	{
		fout << bits[i];
	}
	fout << endl;
}

void dp()
{
	long long temp_states[33][33];
	for (int i = 1; i <= K; i++)
	{
		temp_states[i][0] = 1;
		for (int j = 1; j < i; j++)
		{
			temp_states[i][j] = temp_states[i - 1][j] + temp_states[i - 1][j - 1];
		}
		temp_states[i][i] = 1;
	}
	for (int i = 1; i <= K; i++)
	{
		long long sum = 0;
		for (int j = 0; j <= i; j++)
		{
			sum += temp_states[i][j];
			states[i][j] = sum;
		}
		for (int j = i + 1; j < 33; j++)
		{
			states[i][j] = sum;
		}
	}
}

int main()
{
	ifstream fin("kimbits.in");
	fin >> K >> L >> I;
	dp();
	find();
}