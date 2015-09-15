/*
ID:dirkyao
PROG:hamming
LANG:C++
*/
#include<fstream>
#include<iostream>
#include<bitset>
#include<math.h>
using namespace std;

bitset<8> bin_list[260];
int dis_map[260][260] = { 0 };

void find_index(int *index, int N, int B,int D)
{
	int cur_index = 0;
	index[0] = 0;
	for (int i = 1; i < N; i++)
	{
		for (int j = cur_index; j < pow(2, B); j++)
		{
			int flag = 1;
			for (int k = 0; k < i; k++)
			{
				if (dis_map[index[k]][j] < D)
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				index[i] = j;
				cur_index = j;
				break;
			}
		}
	}
}

void generate_map(int B)
{
	for (int i = 0; i < pow(2, B); i++)
	{
		for (int j = 0; j < pow(2, B); j++)
		{
			bitset<8> count = bin_list[i] ^ bin_list[j];
			for (int k = 0; k < B; k++)
			{
				if (count[k] == 1)
					dis_map[i][j] ++;
			}
		}
	}
}

void generate_list(int B)
{
	for (int i = 0; i < pow(2, B); i++)
	{
		bin_list[i] = (unsigned int)i;
	}
}

int main()
{
	ifstream fin("hamming.in");
	ofstream fout("hamming.out");

	int N, B, D;
	fin >> N >> B >> D; 

	generate_list(B);
	generate_map(B);
	
	int *index = new int[N];
	find_index(index, N, B, D);

	int i = 0;
	for (i = 0; i < N / 10; i++)
	{
		for (int j = 0; j < 9; j++)
			fout << bin_list[index[i * 10 + j]].to_ulong()<<' ';
		fout << bin_list[index[i * 10 + 9]].to_ulong() << endl;
	}
	for (int j = i * 10; j < N-1; j++)
	{
		fout << bin_list[index[j]].to_ulong() << ' ';
	}
	if (N % 10 != 0)
		fout << bin_list[index[N - 1]].to_ulong() << endl;

	return 0;
}