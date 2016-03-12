/*
ID:dirkyao1
PROG:fact4
LANG:C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int N;

int last_digits(long long seed)
{
	while (seed % 10 == 0)
	{
		seed = seed / 10;
	}
	return seed % 10000000;
}

int main()
{
	ifstream fin("fact4.in");
	ofstream fout("fact4.out");

	fin >> N;

	long long seed = 1;
	for (int i = 2; i <= N; i++)
	{
		seed = seed*i;
		seed = last_digits(seed);
	}
	fout << seed%10 << endl;
	return 0;
}