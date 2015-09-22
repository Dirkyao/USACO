/*
ID:dirkyao1
PROG:lamps
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<bitset>
#include<algorithm>
#include<memory.h>
using namespace std;

int N, C;
int lampstate[102];
bitset<102> start_state;
string final_state[20];
int operation[10010] = { 0 };
int bin_op[4];
int state_count = 0;

int check_final()
{
	for (int i = 0; i < N; i++)
	{
		if (lampstate[i] != -1)
		{
			if (lampstate[i] != start_state[i])
			{
				return 0;
			}
		}
	}
	return 1;
}

void gene_final()
{
	start_state.set();
	for (int i = 0; i < C; i++)
	{
		if (operation[i] == 1)
			start_state = start_state.flip();
		else if (operation[i] == 2)
			for (int i = 0; i < N; i = i + 2)
			{
				start_state[i] = start_state[i].flip();
			}
		else if (operation[i] == 3)
			for (int i = 1; i < N; i = i + 2)
			{
				start_state[i] = start_state[i].flip();
			}
		else
			for (int i = 0; i < N; i = i + 3)
			{
				start_state[i] = start_state[i].flip();
			}
	}
}

void iter_generate(int stage)
{
	if (stage < C)
	{
		for (int i = 1; i <= 4; i++)
		{
			operation[stage] = i;
			iter_generate(stage + 1);
		}
	}
	else
	{
		gene_final();
		int flag = check_final();
		if (flag == 1)
		{
			final_state[state_count++] = start_state.to_string();
		}
	}
}

void bin_geneFinal()
{
	start_state.set();
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			if (bin_op[i] == 1)
				start_state.flip();
		}
		else if (i == 1)
		{
			if (bin_op[i] == 1)
				for (int i = 0; i < N; i = i + 2)
				{
					start_state[i] = start_state[i].flip();
				}
		}
		else if (i == 2)
		{
			if (bin_op[i] == 1)
				for (int i = 1; i < N; i = i + 2)
				{
					start_state[i] = start_state[i].flip();
				}
		}
		else if (i == 3)
		{
			if (bin_op[i] == 1)
				for (int i = 0; i < N; i = i + 3)
				{
					start_state[i] = start_state[i].flip();
				}
		}
	}
}


void iter_binary_gene(int stage)
{
	if (stage < 3)
	{
		for (int i = 0; i < 2; i++)
		{
			bin_op[stage] = i;
			iter_binary_gene(stage + 1);
		}
	}
	else
	{
		int count = 0;
		for (int i = 0; i < 3; i++)
		{
			count += bin_op[i];
		}
		int rest = C - count;
		if (rest % 2 == 0)
		{
			bin_op[stage] = 0;
		}
		else
			bin_op[stage] = 1;

		bin_geneFinal();
		int flag = check_final();
		if (flag == 1)
		{
			final_state[state_count++] = start_state.to_string();
		}
	}
}

int main()
{
	ifstream fin("lamps.in");
	ofstream fout("lamps.out");
	memset(lampstate, -1, sizeof(int) * 102);
	memset(bin_op, -1, sizeof(int) * 4);

	fin >> N;
	fin >> C;
	int temp;
	fin >> temp;
	while (temp != -1)
	{
		lampstate[temp-1] = 1;
		fin >> temp;
	}
	fin >> temp;
	while (temp != -1)
	{
		lampstate[temp-1] = 0;
		fin >> temp;
	}

	if (C < 4)
	{
		iter_generate(0);
	}
	else
	{
		iter_binary_gene(0);
	}

	for (int i = 0; i < state_count; i++)
	{
		for (int j = 0; j <102-N; j++)
		{
			final_state[i][j] = '0';
		}
		reverse(final_state[i].begin()+102-N, final_state[i].end());
	}

	sort(final_state, final_state + state_count);
	
	if (state_count == 0)
	{
		fout << "IMPOSSIBLE" << endl;
		return 0;
	}
	for (int j = 102 - N; j < 102; j++)
	{
		fout << final_state[0][j];
	}
	fout << endl;
	for (int i = 1; i < state_count; i++)
	{
		if (final_state[i] != final_state[i - 1])
		{
			for (int j = 102 - N; j < 102; j++)
			{
				fout << final_state[i][j];
			}
			fout << endl;
		}
	}
	return 0;
}