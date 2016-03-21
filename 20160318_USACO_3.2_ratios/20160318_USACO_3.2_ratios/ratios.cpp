/*
ID:dirkyao1
PROG:ratios
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
using namespace std;

double data[3][4];
double para[4];

void solve()
{
	ofstream fout("ratios.out");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j)
				continue;

			double param = data[j][i] / data[i][i];
			double temp[4];
			for (int k = 0; k < 4; k++)
			{
				temp[k] = data[j][k] - param*data[i][k];
			}
			for (int k = 0; k < 4; k++)
			{
				data[j][k] = temp[k];
			}
		}
		double param = data[i][i];
		for (int j = 0; j < 4; j++)
		{
			data[i][j] = data[i][j] / param;
		}
	}
	//检查解是否符合条件
	for (int i = 0; i < 3; i++)
	{
		para[i] = data[i][3];
	}
	para[3] = 1;
	if (para[0] == 0 && para[1] == 0 && para[2] == 0)
	{
		fout << "NONE" << endl;
		return;
	}
	if (para[0] < 0 || para[1] < 0 || 0 && para[2] < 0 || 0)
	{
		fout << "NONE" << endl;
		return;
	}
	//查找整数解
	for (int n = 1; n < 100; n++)
	{
		double temp[4];
		for (int i = 0; i < 4; i++)
		{
			temp[i] = para[i] * n;
			if (temp[i]>100)
			{
				fout << "NONE" << endl;
				return;
			}
		}

		int flag = 1;
		for (int i = 0; i < 4; i++)
		{
			if ((temp[i] - (int)(temp[i] + 0.5)) > 0.000001 || (temp[i] - (int)(temp[i] + 0.5)) < -0.000001)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			fout << (int)(temp[0] + 0.5) << ' ' << (int)(temp[1] + 0.5) << ' ' << (int)(temp[2] + 0.5) << ' ' << (int)(temp[3] + 0.5) << endl;
			return;
		}
	}
}

int main()
{
	ifstream fin("ratios.in");
	fin >> data[0][3] >> data[1][3] >> data[2][3];
	for (int i = 0; i < 3; i++)
	{
		fin >> data[0][i] >> data[1][i] >> data[2][i];
	}

	solve();
	return 0;
}
