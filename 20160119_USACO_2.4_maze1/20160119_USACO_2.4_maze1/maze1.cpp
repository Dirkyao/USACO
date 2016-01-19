/*
ID:dirkyao1
PROG:maze1
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
#include<string>
using namespace std;

int w, h;
char map[220][80];
int exits[2][2];
int dist[2][220][80];
int visited[200][80];
int nearst[220][80];

struct graph
{
	int left = 1;
	int right = 1;
	int top = 1;
	int bottom = 1;
};
graph my_graph[220][80];

void inia_map()
{
	for (int i = 1; i < 2 * h + 1; i += 2)
	{
		for (int j = 1; j < 2 * w + 1; j += 2)
		{
			if (map[i - 1][j] == ' ')
			{
				my_graph[i / 2][j / 2].top = 0;
			}
			if (map[i+1][j] == ' ')
			{
				my_graph[i / 2][j / 2].bottom = 0;
			}
			if (map[i][j - 1] == ' ')
			{
				my_graph[i / 2][j / 2].left = 0;
			}
			if (map[i ][j+ 1] == ' ')
			{
				my_graph[i / 2][j / 2].right = 0;
			}
		}
	}
}

void bfs(int i, int j,int k)
{
	int queue[5000][2];
	memset(queue, 0, sizeof(queue));
	memset(visited, 0, sizeof(visited));

	queue[0][0] = i;
	queue[0][1] = j;
	visited[i][j] = 1;
	int front = 0; int rear = 1;
	while (front < rear)
	{
		if (my_graph[queue[front][0]][queue[front][1]].top == 0 && visited[queue[front][0] - 1][queue[front][1]] == 0 && queue[front][0]>0)
		{

			queue[rear][0] = queue[front][0] - 1;
			queue[rear][1] = queue[front][1];
			dist[k][queue[rear][0]][queue[rear][1]] = dist[k][queue[front][0]][queue[front][1]] + 1;
			visited[queue[rear][0]][queue[rear][1]] = 1;
			rear++;
			
		}
		if (my_graph[queue[front][0]][queue[front][1]].bottom == 0 && visited[queue[front][0] + 1][queue[front][1]] == 0)
		{
			queue[rear][0] = queue[front][0] + 1;
			queue[rear][1] = queue[front][1];
			dist[k][queue[rear][0]][queue[rear][1]] = dist[k][queue[front][0]][queue[front][1]] + 1;
			visited[queue[rear][0]][queue[rear][1]] = 1;
			rear++;
		}
		if (my_graph[queue[front][0]][queue[front][1]].left == 0 && visited[queue[front][0]][queue[front][1] - 1] == 0 && queue[front][1] >0)
		{
			queue[rear][0] = queue[front][0];
			queue[rear][1] = queue[front][1]-1;
			dist[k][queue[rear][0]][queue[rear][1]] = dist[k][queue[front][0]][queue[front][1]] + 1;
			visited[queue[rear][0]][queue[rear][1]] = 1;
			rear++;
		}
		if (my_graph[queue[front][0]][queue[front][1]].right == 0 && visited[queue[front][0]][queue[front][1] + 1] == 0)
		{
				queue[rear][0] = queue[front][0];
				queue[rear][1] = queue[front][1] + 1;
				dist[k][queue[rear][0]][queue[rear][1]] = dist[k][queue[front][0]][queue[front][1]] + 1;
				visited[queue[rear][0]][queue[rear][1]] = 1;
				rear++;
		}
		front++;
	}
}

int find_max()
{
	int max = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (dist[0][i][j] > max)
			{
				max = dist[0][i][j];
			}
		}
	}
	return max;
}

int main()
{
	ifstream fin("maze1.in");
	ofstream fout("maze1.out");

	fin >> w >> h;
	char temp[220];
	fin.getline(temp, w+1);
	int index = 0;
	for (int i = 0; i < 2 * h + 1; i++)
	{
		fin.getline(temp, w*2+2);
		for (int j = 0; j < 2 * w + 1; j++)
		{
			map[i][j] = temp[j];
			if (i == 0 || i == 2 * h || j == 0 || j == 2 * w)
			{
				if (map[i][j] == ' ')
				{
					if (i == 0)
					{
						exits[index][0] = (i+1)/2;
						exits[index++][1] = j/2;
					}
					if (i == 2*h)
					{
						exits[index][0] = (i - 1)/2;
						exits[index++][1] = j/2;
					}
					if (j == 0)
					{
						exits[index][0] = i/2;
						exits[index++][1] = (j+1)/2;
					}
					if (j == 2 * w)
					{
						exits[index][0] = i/2;
						exits[index++][1] = (j-1)/2;
					}
				}
			}
		}
	}

	inia_map();
	memset(dist, 0, sizeof(dist));
	for (int i = 0; i < 2; i++)
	{
		bfs(exits[i][0], exits[i][1],i);
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (dist[0][i][j] > dist[1][i][j])
			{
				dist[0][i][j] = dist[1][i][j];
			}
		}
	}
	fout<<find_max()+1<<endl;
}