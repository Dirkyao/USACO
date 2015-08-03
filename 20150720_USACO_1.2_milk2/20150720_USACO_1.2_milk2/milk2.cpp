/*
ID:Dirkyao1
PROG:milk2
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

#define MAXMUM 1000000

int maxInterval(int* distri, int val, int start, int sum)
{
	int max_interval = 0;
	for (int i = start; i < sum; i++)
	{
		int interval = 0;
		if (distri[i] == val)
		{
			while (distri[i] == val && i < sum)
			{
				interval++;
				i++;
			}
			max_interval = max_interval > interval ? max_interval : interval;
		}
	}
	return max_interval;
}

int main()
{
	//This comment is just for git test.
	ifstream fin("milk2.in");
	ofstream fout("milk2.out");

	int count, start, end;
	int max = 0,min = MAXMUM;
	int maxOne = 0, maxZero = 0;
	int* distribute = new int[MAXMUM];
	memset(distribute, 0, sizeof(int)*MAXMUM);

	fin >> count;
	for (int i = 0; i < count; i++)
	{
		fin >> start >> end;

		if (end > max)
		{
			max = end;
		}
		if (start < min)
		{
			min = start;
		}
		for (int i = start; i < end; i++)
		{
			distribute[i] = 1;
		}
	}
	maxOne = maxInterval(distribute, 1, min, max);
	maxZero = maxInterval(distribute, 0, min, max);

	fout << maxOne << " " << maxZero << endl;
	return 0;
}

