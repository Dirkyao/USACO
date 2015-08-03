/*
ID:dirkyao1
PROG:beads
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

int count_succession(int count, char* necklace)
{
	int count_left = 0, count_right = 0;

	int i = 0;
	while (necklace[i] == 'w' && i < count)
	{
		count_left++;
		i++;
	}
	if (i < count && necklace[i] == 'r')
	{
		while (i < count && (necklace[i] == 'r' || necklace[i] == 'w'))
		{
			count_left++;
			i++;
		}
	}
	else if ((i < count && necklace[i] == 'b'))
	{
		while (i < count && (necklace[i] == 'b' || necklace[i] == 'w'))
		{
			count_left++;
			i++;
		}
	}

	int j = count-1;
	while (necklace[j] == 'w' && j >= i)
	{
		count_right++;
		j--;
	}
	if (j >=i && necklace[j] == 'r')
	{
		while (j >= i && (necklace[j] == 'r' || necklace[j] == 'w'))
		{
			count_right++;
			j--;
		}
	}
	else if (j >= i &&necklace[j] == 'b')
	{
		while (j >= i && (necklace[j] == 'b' || necklace[j] == 'w'))
		{
			count_right++;
			j--;
		}
	}
	return count_left + count_right;
}

void rotate(int count, char* necklace)
{
	char temp = necklace[0];
	for (int i = 0; i < count - 1; i++)
	{
		necklace[i] = necklace[i + 1];
	}
	necklace[count-1] = temp;

}

int main()
{
	ifstream fin("beads.in");
	ofstream fout("beads.out");

	int beads_count,max = 0;
	char necklace[400];

	fin >> beads_count;
	fin >> necklace;

	for (int i = 0; i < beads_count; i++)
	{
		int temp;
		temp = count_succession(beads_count, necklace);
		max = max > temp ? max : temp;
		
		rotate(beads_count, necklace);
	}

	fout << max << endl;
	return 0;
}