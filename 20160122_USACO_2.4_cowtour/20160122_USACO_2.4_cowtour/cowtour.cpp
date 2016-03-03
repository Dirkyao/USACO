/*
ID:dirkyao
PROG:cowtour
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
#include<math.h>
using namespace std;

int N;
double coord[160][2];
double my_distance[160][160];
int edges[160][160];
int fields[160];
int longest_path_c1[160];
int longest_path_c2[160];
int field_num = 1;

void build_graph()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			my_distance[i][j] = 9999999;
			if (edges[i][j] == 1)
			{
				my_distance[i][j] = pow((coord[i][0] - coord[j][0])*(coord[i][0] - coord[j][0]) + (coord[i][1] - coord[j][1])*(coord[i][1] - coord[j][1]), 0.5);
			}
		}
	}
}

void dfs(int i)
{
	for (int j = 0; j < N; j++)
	{
		if (edges[i][j] ==1 && fields[j] == 0)
		{
			fields[j] = field_num;
			dfs(j);
		}
	}
}

void find_fields()
{
	memset(fields, 0, sizeof(fields));
	
	for (int i = 0; i < N; i++)
	{
		if (fields[i] == 0)
		{
			fields[i] = field_num++;
			dfs(i);
		}
	}
}

void floyd()
{
	for (int i = 1; i < field_num; i++)
	{
		for (int k = 0; k < N; k++)
		{
			if (fields[k] == i)
			{
				for (int i = 0; i < N; i++)
				{
					if (fields[i] == i)
					{
						for (int j = 0; j < N; j++)
						{
							if (fields[j] == i)
							{
								if (my_distance[i][j] < my_distance[i][k] + my_distance[k][j])
								{
									my_distance[i][j] = my_distance[i][k] + my_distance[k][j];
								}
							}
						}
					}
				}
			}
		}
	}
}

void find_longest_path()
{
	
}

int main()
{
	ifstream fin("cowtour.in");
	ofstream fout("cowtour.out");

	fin >> N;
	for (int i = 0; i < N; i++)
	{
		fin >> coord[i][0] >> coord[i][1];
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> edges[i][j];
		}
	}


	find_fields();

	floyd();
}