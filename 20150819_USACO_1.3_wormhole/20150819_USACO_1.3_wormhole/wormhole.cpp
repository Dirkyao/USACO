/*
ID:dirkyao1
PROG:wormhole
LANG:C++
*/
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define MAX_HOLE 12

int N, hole_pos[MAX_HOLE + 1][MAX_HOLE + 1] = { 0 };
int partner[MAX_HOLE + 1] = { 0 };
int next_to_right[12] = { 0 };

bool check_circle()
{
	for (int i = 1; i <= N; i++)
	{
		int temp = i;
		for (int j = 0; j <= N; j++)
		{
			temp = next_to_right[partner[temp]];
		}
		if (temp != 0)
		{
			return true;
		}
	}
	return false;
}

int solve()
{
	int count = 0;
	int i;
	for (i = 1; i <= N; i++)
	{
		if (partner[i] == 0)
			break;
	}
	if (i > N)
	{
		if (check_circle())
		{
			return 1;
		}
		else
			return 0;
	}
	else
	{
		for (int j = i + 1; j <= N; j++)
		{
			if (partner[j] == 0)
			{
				partner[i] = j;
				partner[j] = i;
				count += solve();
				partner[i] = partner[j] = 0;
			}
		}
		return count;
	}
}

void find_next_left()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (hole_pos[i][1] == hole_pos[j][1]&&hole_pos[i][0]<hole_pos[j][0])
			{
				if (next_to_right[i] == 0 || hole_pos[next_to_right[i]][0]>hole_pos[j][0])
				{
					next_to_right[i] = j;
				}
			}
		}
	}
}

int main()
{
	ifstream fin("wormhole.in");
	ofstream fout("wormhole.out");

	fin >> N;
	for (int i = 1; i <= N; i++)
	{
		fin >> hole_pos[i][0] >> hole_pos[i][1];
	}
	find_next_left();

	fout << solve() << endl;
	return 0;
}