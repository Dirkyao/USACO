/*
ID:dirkyao1
PROG:camelot
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
using namespace std;

#define MAX(a,b)((a)>(b)?(a):(b))
#define ABS(a)((a)>0?(a):-(a))

int col, row;
int king_loc[2];
int knight_loc[2000][2];
int bfs_state[31][31];
//int shortest_path[2000][31][31];
int knight_num = 0;
typedef struct node{
	int distance_map[31][31];

	node()
	{
		for (int i = 0; i < 31; i++)
		{
			for (int j = 0; j < 31; j++)
			{
				distance_map[i][j] = 99999999;
			}
		}
	}
}shortest_path;

shortest_path shortest_paths[31][31];

void find_neighbor(int* neighbor, int ori_row, int ori_col, int num)
{
	int map[8][2] = {
		{ -2, 1 },
		{ -1, 2 },
		{ 1, 2 },
		{ 2, 1 },
		{ 2, -1 },
		{ 1, -2 },
		{ -1, -2 },
		{ -2, -1 }
	};
	int	new_row = ori_row + map[num][0];
	int new_col = ori_col + map[num][1];
	if (new_row >= row || new_row < 0 || new_col >= col || new_col < 0)
	{
		neighbor[0] = -1;
		return;
	}
	else
	{
		neighbor[0] = new_row;
		neighbor[1] = new_col;
		return;
	}
}

void my_bfs(int ori_row, int ori_col)
{
	int queue[1000][3];
	int visited[31][31];
	int front = 0, rear = 0;
	memset(visited, 0, sizeof(visited));

	queue[rear][0] = ori_row;
	queue[rear][1] = ori_col;
	queue[rear][2] = 0;
	visited[queue[rear][0]][queue[rear][1]] = 1;
	rear++;
	while (front < rear)
	{
		int neighbor[2];
		for (int i = 0; i < 8; i++)
		{
			find_neighbor(neighbor, queue[front][0], queue[front][1], i);
			if (neighbor[0] >= 0)
			{
				if (visited[neighbor[0]][neighbor[1]] == 0)
				{
					visited[neighbor[0]][neighbor[1]] = 1;
					queue[rear][0] = neighbor[0];
					queue[rear][1] = neighbor[1];
					queue[rear][2] = queue[front][2] + 1;
					rear++;
				}
			}
		}
		shortest_paths[ori_row][ori_col].distance_map[queue[front][0]][queue[front][1]] = queue[front][2];
		front++;
	}

}

int find_mini_cost()
{
	int mini_cost = 99999999;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int temp_cost = 0;
			int flag = 1;
			for (int k = 0; k < knight_num; k++)
			{
				temp_cost += shortest_paths[knight_loc[k][0]][knight_loc[k][1]].distance_map[i][j];
				if (temp_cost > mini_cost)
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				for (int m = MAX(0, king_loc[0] - 2); m < king_loc[0] + 3; m++)
				{
					for (int n = MAX(king_loc[1] - 2, 0); n < king_loc[1] + 3; n++)
					{
						for (int t = 0; t < knight_num; t++)
						{
							int final_cost = temp_cost;

							int test1 = ABS(king_loc[0] - m);
							int test2 = ABS(king_loc[1] - n);
							int test3 = MAX(ABS(king_loc[0] - m), ABS(king_loc[1] - n));

							final_cost = final_cost - shortest_paths[knight_loc[t][0]][knight_loc[t][1]].distance_map[i][j] + shortest_paths[knight_loc[t][0]][knight_loc[t][1]].distance_map[m][n] + shortest_paths[m][n].distance_map[i][j] + MAX(ABS(king_loc[0] - m), ABS(king_loc[1] - n));

							if (final_cost < mini_cost)
								mini_cost = final_cost;
						}
					}
				}
			}
		}
	}
	if (knight_num == 0)
		return 0;
	return mini_cost;
}

int main()
{
	ifstream fin("camelot.in");
	ofstream fout("camelot.out");
	fin >> row >> col;

	char temp_col;
	int temp_row;

	fin >> temp_col >> temp_row;
	king_loc[0] = temp_row - 1;
	king_loc[1] = temp_col - 'A';

	while (fin >> temp_col >> temp_row)
	{
		knight_loc[knight_num][0] = temp_row - 1;
		knight_loc[knight_num][1] = temp_col - 'A';
		knight_num++;
	}
	memset(bfs_state, 0, sizeof(bfs_state));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			my_bfs(i, j);
	}

	fout << find_mini_cost() << endl;
	return 0;
}