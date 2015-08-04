/*
ID:dirkyao1
PROG:transform
LANG:C++
*/
#include<iostream>
#include<fstream>

using namespace std;

struct cord{
	int i;
	int j;
};

cord* index_converter(cord* position, int mode)
{

}

int main()
{
	ifstream fin("transform.in");
	ofstream fout("transform.out");

	int N;
	char tiles_one[10][10], tiles_two[10][10];

	fin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> tiles_one[i][j];
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> tiles_two[i][j];
		}
	}
}
