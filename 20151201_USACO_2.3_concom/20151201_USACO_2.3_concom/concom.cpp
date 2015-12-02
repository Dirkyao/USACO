/*
ID:dirkyao1
PROG:concom
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
#include<vector>
#include<algorithm>
using namespace std;

int control_mat[120][120];
int vis[120];
int temp_price[120];
int max_n = 0;
vector< int > result[120];

bool compare(int a, int b)
{
	return a < b;
}

void dfs(int n,int cur)
{
	for (int i = 0; i < max_n; i++)
	{
		if (!vis[i])
		{
			if (control_mat[cur][i] > 0)
			{
				if (control_mat[cur][i] > 50)
				{
					result[n].push_back(i);
					vis[i] = 1;
					dfs(n, i);
				}
				else
				{
					temp_price[i] += control_mat[cur][i];
					if (temp_price[i] > 50)
					{
						result[n].push_back(i);
						vis[i] = 1;
						dfs(n, i);
					}
				}
			}
		}
		
	}
}

void find_n(int n)
{
	memset(temp_price, 0, sizeof(int) * 120);
	memset(vis, 0, sizeof(int) * 120);

	dfs(n, n);
}

int main()
{
	ifstream fin("concom.in");
	ofstream fout("concom.out");

	memset(control_mat, 0, sizeof(int) * 120 * 120);

	int n;
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		int s, t, p;
		fin >> s >> t >> p;
		control_mat[s - 1][t - 1] = p;
		if (s > max_n)
		{
			max_n = s;
		}
		if (t > max_n)
		{
			max_n = t;
		}
	}

	for (int i = 0; i < max_n; i++)
	{
		find_n(i);
	}
	for (int i = 0; i < max_n; i++)
	{
		sort(result[i].begin(),result[i].end(), compare);
	}
	for (int i = 0; i < max_n; i++)
	{
		for (vector<int>::iterator it = result[i].begin(); it != result[i].end(); it++)
			if(i!=*it)
				fout << i+1 << ' ' << (*it)+1 << endl;
	}
	return 0;
}