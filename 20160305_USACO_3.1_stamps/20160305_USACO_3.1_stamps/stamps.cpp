/*
ID:dirkyao1
PROG:stamps
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
#include<vector>
using namespace std;

typedef struct node{
	int num = 0;
	int total = 0;
}postage;

int* total = new int[2100001];

int K, N;
int stamps[51];
#define conse_num 2100001

void consecutive_dp()
{
	ofstream fout("stamps.out");
	int round_num = 0;

	memset(total, 0, sizeof(total));

	for (int i = 1; i < conse_num; i++)
	{

		int flag = 0;
		int min_stamps_num = 220;
		int stamp_choice = -1;

		//memset(postages[i].stamps, 0, sizeof(postages[0].stamps));

		for (int j = 0; j < N; j++)
		{
			int index = i - stamps[j];
			if (index >= 0 && total[index] + 1 < min_stamps_num && total[index] + 1 <= K)
			{
				flag = 1;
				stamp_choice = j;
				min_stamps_num = total[index] + 1;
			}
		}
		
		if (flag == 1)
		{
			int index = i - stamps[stamp_choice];
			total[i] = total[index] + 1;
		}
		else
		{
			fout << i-1 << endl;
			return;
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