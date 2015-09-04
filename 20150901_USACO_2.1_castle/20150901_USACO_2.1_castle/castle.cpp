/*
ID:dirkyao1
PROG:castle
Lang:C++
*/
#include<iostream>
#include<fstream>
#include<bitset>
using namespace std;

typedef struct node{
	int component = 0;
	int wall_north = 0;
	int wall_south = 0;
	int wall_west = 0;
	int wall_east = 0;
}square;

typedef struct info{
	int comp_num = 0;
	int comp_size[2500];
	int wall_removed[3];
	int size_combine = 0;
};

info information;

void wall_inia(square (*room)[50], bitset<4> (*wall)[50], int row, int col)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (wall[i][j][0] == 1)
			{
				room[i][j].wall_south = 1;
			}
			if (wall[i][j][1] == 1)
			{
				room[i][j].wall_east = 1;
			}
			if (wall[i][j][2] == 1)
			{
				room[i][j].wall_north = 1;
			}
			if (wall[i][j][3] == 1)
			{
				room[i][j].wall_west = 1;
			}
		}
}

void paint(square(*room)[50], int row, int col, int r, int c,int comp)
{
	room[r][c].component = comp;
	information.comp_size[comp]++;
	if (r > 0 && room[r][c].wall_north != 1)
	{
		if (room[r - 1][c].component == 0)
		{
			paint(room, row, col, r - 1, c, comp);
		}
	}
	if (r < row - 1 && room[r][c].wall_south != 1)
	{
		if (room[r + 1][c].component == 0)
		{
			paint(room, row, col, r + 1, c, comp);
		}
	}
	if (c > 0 && room[r][c].wall_west != 1)
	{
		if (room[r][c - 1].component == 0)
		{
			paint(room, row, col, r, c - 1, comp);
		}
	}
	if (c < col - 1 && room[r][c].wall_east == 0)
	{
		if (room[r][c + 1].component == 0)
		{
			paint(room, row, col, r, c + 1, comp);
		}
	}
}

void component_count(square(*room)[50], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (room[i][j].component == 0)
			{
				information.comp_num++;
				paint(room, row, col, i, j, information.comp_num);
			}
		}
	}
}

bool check_size(info information, square(*room)[50], int row, int col, int r, int c,int direct)
{
	if (direct == 1)
	{
		if (r>0 && room[r][c].wall_north == 1)
		{
			if (room[r][c].component != room[r - 1][c].component)
			{
				if (information.size_combine < (information.comp_size[room[r][c].component] + information.comp_size[room[r - 1][c].component]))
					return true;
			}
		}
	}
	else
	{
		if (c < col - 1 && room[r][c].wall_east == 1)
		{
			if (room[r][c].component != room[r][c + 1].component)
			{
				if (information.size_combine < (information.comp_size[room[r][c].component] + information.comp_size[room[r][c + 1].component]))
					return true;
			}
		}
	}
	return false;
}

info check_wall(square(*room)[50], int row, int col,info information)
{
	for (int j = 0; j < col; j++)
	{
		for (int i = row - 1; i >= 0; i--)
		{
			bool update = check_size(information, room, row, col, i, j, 1);
			if (update == true)
			{
				information.size_combine = information.comp_size[room[i][j].component] + information.comp_size[room[i - 1][j].component];

				information.wall_removed[0] = i + 1;
				information.wall_removed[1] = j + 1;
				information.wall_removed[2] = 'N';
			}

			update = check_size(information, room, row, col, i, j, 2);
			if (update == true)
			{
				information.size_combine = information.comp_size[room[i][j].component] + information.comp_size[room[i][j+1].component];
				
				information.wall_removed[0] = i + 1;
				information.wall_removed[1] = j + 1;
				information.wall_removed[2] = 'E';
			}
		}
	}
	return information;
}

int main()
{
	ifstream fin("castle.in");
	ofstream fout("castle.out");

	int col = 0, row = 0;
	fin >> col >> row;
	
	square room[50][50];
	bitset<4> wall[50][50];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			fin >> wall[i][j];
	}
	
	wall_inia(room, wall, row, col);
	component_count(room, row, col);

	information = check_wall(room, row, col, information);
}