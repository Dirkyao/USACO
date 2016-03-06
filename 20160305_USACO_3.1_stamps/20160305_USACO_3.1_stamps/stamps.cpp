/*
ID:dirkyao1
PROG:stamps
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
using namespace std;

typedef struct node{
	int stamps[51];
	int total = 0;
}postage;

int K, N;
int stamps[51];
#define conse_num 50000

int consecutive_dp()
{
	ofstream fout("stamps.out");
	postage postages[conse_num];
	memset(postages[0].stamps, 0, sizeof(postages[0].stamps));

	for (int i = 1; i < conse_num; i++)
	{
		int flag = 0;
		int min_stamps_num = 220;
		int stamp_choice = -1;
		memset(postages[i].stamps, 0, sizeof(postages[0].stamps));

		for (int j = 0; j < N; j++)
		{
			int index = i - stamps[j];
			if (index >= 0 & postages[index].total + 1 <= min_stamps_num & postages[index].total + 1 < K)
			{
				flag = 1;
				stamp_choice = j;
				min_stamps_num = postages[index].total + 1;
			}
		}
		
		if (flag == 1)
		{
			int index = i - stamps[stamp_choice];
			postages[i].total = postages[index].total + 1;
			for (int j = 0; j < N; j++)
			{
				postages[i].stamps[j] = postages[index].stamps[j];
			}
			postages[i].stamps[stamp_choice]++;
		}
		else
		{
			fout << i - 1 << endl;
		}
	}
}

int main()
{
	ifstream fin("stamps.in");

	fin >> K >> N;
	for (int i = 0; i < N; i++)
	{
		fin >> stamps[i];
	}

	consecutive_dp();
	return 0;
}