/*
ID:dirkyao1
PROG:barn1
LANG:C++
*/

#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

bool compare(int a, int b)
{
	return a > b;
}

bool compare_up_order(int a, int b)
{
	return a < b;
}

int main()
{
	ifstream fin("barn1.in");
	ofstream fout("barn1.out");

	int boards_num, stalls_num, occupyed_num;
	int boards_occupyed_index[200], occupyed_interval[200];

	fin >> boards_num >> stalls_num >> occupyed_num;
	for (int i = 0; i < occupyed_num; i++)
	{
		fin >> boards_occupyed_index[i];
	}

	sort(&boards_occupyed_index[0], &boards_occupyed_index[occupyed_num], compare_up_order);

	for (int j = 1; j < occupyed_num; j++)
	{
		occupyed_interval[j - 1] = boards_occupyed_index[j] - boards_occupyed_index[j - 1];
	}
	sort(&occupyed_interval[0], &occupyed_interval[occupyed_num - 1], compare);

	int interval = 0;
	if (occupyed_num > boards_num)
	{
		for (int j = 0; j < boards_num - 1; j++)
		{
			interval += occupyed_interval[j] - 1;
		}
		fout << boards_occupyed_index[occupyed_num - 1] - boards_occupyed_index[0] + 1 - interval << endl;
	}
	else
		fout << occupyed_num << endl;
	return 0;
}