/*
ID:dirkyao1
PROG:cowtour
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<math.h>
#include<memory.h>
#include <iomanip>
using namespace std;

int N;
int nodes[151][2];
char map[151][151];
double graph[151][151];
int field_num = 0;

int field[151];
double origin_max[151];
double field_radius[151];

double find_min_radius()
{
	double min_radius = 9999998;
	for (int i = 0;i < N;i++)
	{
		for (int j = i + 1;j < N;j++)
		{
			if (field[i] != field[j])
			{
				double choice_1 = pow(pow(nodes[i][0] - nodes[j][0], 2) + pow(nodes[i][1] - nodes[j][1], 2), 0.5) + origin_max[i] + origin_max[j];
				double choice_2 = field_radius[field[i]] < field_radius[field[j]] ? field_radius[field[j]] : field_radius[field[i]];

				double temp_radius = choice_1 < choice_2 ? choice_2 : choice_1;
				if (temp_radius < min_radius)
				{
					min_radius = temp_radius;
				}
			}
		}
	}
	return min_radius;
}

void floyd(int current_field)
{
	for (int k = 0;k < N; k++)
	{
		if (field[k] == current_field)
		{
			for (int i = 0;i < N;i++)
			{
				if (field[i] == current_field)
				{
					for (int j = 0;j < N;j++)
					{
						if (field[j] == current_field)
						{
							if (graph[i][j]>graph[i][k] + graph[k][j])
							{
								graph[i][j] = graph[i][k] + graph[k][j];
							}
						}
					}
				}
			}
		}
	}

	double max_1 = 0;
	for (int i = 0;i < N;i++)
	{
		double max_2 = 0;
		if (field[i] == current_field)
		{
			for (int j = 0;j < N;j++)
			{
				if (graph[i][j] < 9999999)
				{
					if (graph[i][j] > max_2)
					{
						max_2 = graph[i][j];
					}
					if (graph[i][j]>max_1)
					{
						max_1 = graph[i][j];
					}
				}
			}
			origin_max[i] = max_2;
		}

	}
	field_radius[current_field] = max_1;
}

void dfs(int i)
{
	field[i] = field_num;
	for (int j = 0;j < N;j++)
	{
		if (graph[i][j] < 9999999)
		{
			if (field[j] == 0)
			{
				dfs(j);
			}
		}
	}
}

void find_fields()
{
	memset(field, 0, sizeof(field));
	for (int i = 0;i < N;i++)
	{
		if (field[i] == 0)
		{
			field_num++;
			dfs(i);
		}
	}

}

void init_map()
{
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			if (i == j)
			{
				graph[i][j] = 0;
			}
			else
			{
				if (map[i][j] == '0')
				{
					graph[i][j] = 9999999;
				}
				else if (map[i][j] == '1')
				{
					graph[i][j] = pow(pow(nodes[i][0] - nodes[j][0], 2) + pow(nodes[i][1] - nodes[j][1], 2), 0.5);
				}
			}
		}
	}
}

int main()
{
	ifstream fin("cowtour.in");
	ofstream fout("cowtour.out");

	fin >> N;
	for (int i = 0;i < N;i++)
	{
		fin >> nodes[i][0] >> nodes[i][1];
	}
	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			fin >> map[i][j];
		}
	}
	init_map();
	find_fields();

	memset(origin_max, 0, sizeof(origin_max));
	memset(field_radius, 0, sizeof(field_radius));
	for (int i = 1;i <= field_num;i++)
	{
		floyd(i);
	}
	fout << fixed << setprecision(6) << find_min_radius() << endl;

	return 0;
}