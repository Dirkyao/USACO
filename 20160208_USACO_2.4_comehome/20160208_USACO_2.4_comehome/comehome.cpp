/*
ID:dirkyao1
PROG:comehome
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
#include<queue>
#include<algorithm>
using namespace std;

int graph[52][52];
int cow_position[25];
int visited[52];
int my_distance[52];
int inqueue[52];

int cmp(int &a, int &b)
{
	return my_distance[a] > my_distance[b];
}

void dijkstra()
{
	memset(visited, 0, sizeof(visited));
	memset(inqueue, 0, sizeof(inqueue));
	for (int i = 0;i < 52;i++)
	{
		my_distance[i] = 999999;
	}

	int my_queue[52];
	int top = -1;
	my_distance[25] = 0;
	my_queue[++top] = 25;
	visited[25] = 1;
	inqueue[25] = 0;

	while (top!= -1)
	{
		for (int i = 0;i < 52;i++)
		{
			if (graph[my_queue[top]][i] < 999999 && visited[i] == 0)
			{
				if (inqueue[i] == 0)
				{
					my_queue[++top] = i;
					sort(my_queue, my_queue + top + 1, cmp);
					inqueue[i] = 1;
				}
				int temp_distance = my_distance[my_queue[top]] + graph[my_queue[top]][i];
				if (temp_distance < my_distance[i])
				{
					my_distance[i] = temp_distance;
				}
			}
		}
		visited[my_queue[top]] = 1;
		top--;
		sort(my_queue, my_queue + top + 1, cmp);
	}
}

int main()
{
	ifstream fin("comehome.in");
	ofstream fout("comehome.out");

	int path_number;
	for (int i = 0;i < 52;i++)
	{
		for (int j = 0;j < 52;j++)
		{
			graph[i][j] = 999999;
			if (i == j)
			{
				graph[i][j] = 0;
			}
		}
	}
	memset(cow_position, 0, sizeof(cow_position));

	fin >> path_number;
	for (int i = 0;i < path_number;i++)
	{
		char src, dst;
		int temp_length;
		fin >> src >> dst >> temp_length;

		int source, dest;
		if (src >= 'A'&&src <= 'Z')
		{
			cow_position[src - 'A'] = 1;
			source = src - 'A';
		}
		else
		{
			source = src - 'a' + 26;
		}
		if (dst >= 'A' && dst <= 'Z')
		{
			cow_position[src - 'A'] = 1;
			dest = dst - 'A';
		}
		else
		{
			dest = dst - 'a' + 26;
		}
 
		if (temp_length < graph[source][dest])
		{
			graph[source][dest] = temp_length;
			graph[dest][source] = temp_length;
		}
	}

	dijkstra();
	int min = 999999, min_index = -1;
	for (int i = 0;i < 25;i++)
	{
		if (my_distance[i] < min)
		{
			min = my_distance[i];
			min_index = i;
		}
	}
	fout << (char)('A' + min_index) << ' ' << min << endl;
	return 0;
}