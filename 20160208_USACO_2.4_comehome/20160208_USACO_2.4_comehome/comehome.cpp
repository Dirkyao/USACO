/*
ID:dirkyao1
PROG:comehome
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
#include<queue>
using namespace std;

int graph[52][52];
int cow_position[25];
int visited[52];
int my_distance[52];
struct cmp {
	bool operator ()(int &a, int &b)
	{
		return my_distance[a] > my_distance[b];
	}
};

void dijkstra()
{
	memset(visited, 0, sizeof(visited));
	for (int i = 0;i < 52;i++)
	{
		my_distance[i] = 999999;
	}

	priority_queue<int, vector<int>, cmp> my_queue;
	my_distance[0] = 0;
	my_queue.push(52);
	visited[52] = 1;

	while (!my_queue.empty())
	{
		for (int i = 0;i < 52;i++)
		{
			if (graph[my_queue.top()][i] < 999999 && visited[i] == 0)
			{
				my_queue.push(i);
				visited[i] = 1;
				int temp_distance = my_distance[my_queue.top()] + graph[my_queue.top()][i];
				if (temp_distance < my_distance[i])
				{
					my_distance[i] = temp_distance;
				}
			}
		}
		my_queue.pop();
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
		if (src >= 'A'&&src <= 'Y')
		{
			cow_position[src - 'A'] = 1;
		}
		if (dst >= 'A' && dst <= 'Y')
		{
			cow_position[src - 'A'] = 1;
		}
		if (temp_length < graph[src - 'a'][dst - 'a'])
		{
			graph[src - 'a'][dst - 'a'] = temp_length;
			graph[dst - 'a'][src - 'a'] = temp_length;
		}
	}

	dijkstra();
	int min = 999999, min_index = -1;
	for (int i = 26;i < 51;i++)
	{
		if (my_distance[i] < min)
		{
			min = my_distance[i];
			min_index = i;
		}
	}
	fout << (char)('a' + min_index) << ' ' << min << endl;
	return 0;
}