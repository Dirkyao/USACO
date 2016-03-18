/*
ID:dirkyao1
PROG:spin
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
#include<algorithm>
using namespace std;

int speed[5];
typedef struct node{
	int ini_angle;
	int extent;
}wedge;
int wedge_num[5];
wedge wedges[5][6];

int states[5][360];

bool check_state()
{
	bool flag = false;
	for (int i = 0; i < 360; i++)
	{
		if (states[0][i] && states[1][i] && states[2][i] && states[3][i] && states[4][i])
		{
			flag = true;
			break;
		}
	}
	return  flag;
}

void proceed()
{
	int temp[360];
	for (int i = 0; i < 5; i++)
	{
		memset(temp, 0, sizeof(temp));
		for (int j = 0; j < 360; j++)
		{
			temp[(j + speed[i]) % 360] = states[i][j];
		}
		for (int j = 0; j < 360; j++)
		{
			states[i][j] = temp[j];
		}
	}
}

void simulate()
{
	ofstream fout("spin.out");
	for (int i = 0; i <= 360; i++)
	{
		int temp_result = check_state();
		if (temp_result)
		{
			fout << i << endl;
			return;
		}
		proceed();
	}
	fout << "none" << endl;
	return;
}

void ini_states()
{
	memset(states, 0, sizeof(states));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < wedge_num[i]; j++)
		{
			int start = wedges[i][j].ini_angle;
			int end = wedges[i][j].ini_angle + wedges[i][j].extent;
			for (int k = start; k <= end; k++)
			{
				states[i][k%360] = 1;
			}
		}
	}
}

int main()
{
	ifstream fin("spin.in");
	for (int i = 0; i < 5; i++)
	{
		fin >> speed[i];
		fin >> wedge_num[i];
		for (int j = 0; j < wedge_num[i]; j++)
		{
			fin >> wedges[i][j].ini_angle >> wedges[i][j].extent;
		}
	}
	ini_states();
	simulate();
	return 0;
}