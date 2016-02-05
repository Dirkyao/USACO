#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int map[10][10];
struct traceSet{
	int row;
	int col;
	char direction;
};

int curCow = 0, curFarmer = 0;

//cow = 0, 
traceSet (*Trace)[160000] = new traceSet[2][160000];

bool judge_equal(int k)
{

}

void str2map(string* str)
{
	for (int i = 0;i < 10;i++)
	{
		for (int j = 0;j < 10;j++)
		{
			if (str[i][j] == '.')
			{
				map[i][j] = 0;
			}
			else if (str[i][j] == '*')
			{
				map[i][j] == 1;
			}
			else if (str[i][j] == 'C')
			{
				map[i][j] == 0;
				Trace[0][0].row = i;
				Trace[0][0].col = j;
				Trace[0][0].direction = 'N';
				//curCow++;
			}
			else if (str[i][j] == 'F')
			{
				map[i][j] == 0;
				Trace[1][0].row = i;
				Trace[0].col = j;
				farmerTrace[0].direction = 'N';
				//curFarmer++;
			}
		}
	}
}

void simulate(int pace)
{
	for (int i = 0;i < pace;i++)
	{
		if (farmerTrace[curFarmer].direction == 'N')
		{
			if (map[farmerTrace[curFarmer].row - 1][farmerTrace[curFarmer].col] == 0)
			{
				farmerTrace[curFarmer + 1].row = farmerTrace[curFarmer].row - 1;
				farmerTrace[curFarmer + 1].col = farmerTrace[curFarmer].col;
				farmerTrace[curFarmer + 1].direction = 'N';
				curFarmer++;
			}
			else
			{
				farmerTrace[curFarmer + 1].row = farmerTrace[curFarmer].row;
				farmerTrace[curFarmer + 1].col = farmerTrace[curFarmer].col;
				farmerTrace[curFarmer + 1].direction = 'E';
				curFarmer++;
			}
		}
		if (farmerTrace[curFarmer].direction == 'E')
		{
			if (map[farmerTrace[curFarmer].row][farmerTrace[curFarmer].col+1] == 0)
			{
				farmerTrace[curFarmer + 1].row = farmerTrace[curFarmer].row;
				farmerTrace[curFarmer + 1].col = farmerTrace[curFarmer].col+1;
				farmerTrace[curFarmer + 1].direction = 'E';
				curFarmer++;
			}
			else
			{
				farmerTrace[curFarmer + 1].row = farmerTrace[curFarmer].row;
				farmerTrace[curFarmer + 1].col = farmerTrace[curFarmer].col;
				farmerTrace[curFarmer + 1].direction = 'S';
			}
		}
		if (farmerTrace[curFarmer].direction == 'S')
		{
			if (map[farmerTrace[curFarmer].row+1][farmerTrace[curFarmer].col] == 0)
			{
				farmerTrace[curFarmer + 1].row = farmerTrace[curFarmer].row + 1;
				farmerTrace[curFarmer + 1].col = farmerTrace[curFarmer].col;
				farmerTrace[curFarmer + 1].direction = 'S';
				curFarmer++;
			}
			else
			{
				farmerTrace[curFarmer + 1].row = farmerTrace[curFarmer].row;
				farmerTrace[curFarmer + 1].col = farmerTrace[curFarmer].col;
				farmerTrace[curFarmer + 1].direction = 'W';
			}
		}
		if (farmerTrace[curFarmer].direction == 'W')
		{
			if (map[farmerTrace[curFarmer].row][farmerTrace[curFarmer].col - 1] == 0)
			{
				farmerTrace[curFarmer + 1].row = farmerTrace[curFarmer].row;
				farmerTrace[curFarmer + 1].col = farmerTrace[curFarmer].col - 1;
				farmerTrace[curFarmer + 1].direction = 'W';
				curFarmer++;
			}
			else
			{
				farmerTrace[curFarmer + 1].row = farmerTrace[curFarmer].row;
				farmerTrace[curFarmer + 1].col = farmerTrace[curFarmer].col;
				farmerTrace[curFarmer + 1].direction = 'N';
			}
		}
	}
	if (cowTrace[curCow].direction == 'N')
	{
		if (map[cowTrace[curCow].row - 1][cowTrace[curCow].col] == 0)
		{
			cowTrace[curCow + 1].row = cowTrace[curCow].row - 1;
			cowTrace[curCow + 1].col = cowTrace[curCow].col;
			cowTrace[curCow + 1].direction = 'N';
			curCow++;
		}
		else
		{
			cowTrace[curCow + 1].row = cowTrace[curCow].row;
			cowTrace[curCow + 1].col = cowTrace[curCow].col;
			cowTrace[curCow + 1].direction = 'E';
			curCow++;
		}
	}
	if (cowTrace[curCow].direction == 'E')
	{
		if (map[cowTrace[curCow].row][cowTrace[curCow].col + 1] == 0)
		{
			cowTrace[curCow + 1].row = cowTrace[curCow].row;
			cowTrace[curCow + 1].col = cowTrace[curCow].col + 1;
			cowTrace[curCow + 1].direction = 'E';
			curCow++;
		}
		else
		{
			cowTrace[curCow + 1].row = cowTrace[curCow].row;
			cowTrace[curCow + 1].col = cowTrace[curCow].col;
			cowTrace[curCow + 1].direction = 'S';
		}
	}
	if (cowTrace[curCow].direction == 'S')
	{
		if (map[cowTrace[curCow].row + 1][cowTrace[curCow].col] == 0)
		{
			cowTrace[curCow + 1].row = cowTrace[curCow].row + 1;
			cowTrace[curCow + 1].col = cowTrace[curCow].col;
			cowTrace[curCow + 1].direction = 'S';
			curCow++;
		}
		else
		{
			cowTrace[curCow + 1].row = cowTrace[curCow].row;
			cowTrace[curCow + 1].col = cowTrace[curCow].col;
			cowTrace[curCow + 1].direction = 'W';
		}
	}
	if (cowTrace[curCow].direction == 'W')
	{
		if (map[cowTrace[curCow].row][cowTrace[curCow].col - 1] == 0)
		{
			cowTrace[curCow + 1].row = cowTrace[curCow].row;
			cowTrace[curCow + 1].col = cowTrace[curCow].col - 1;
			cowTrace[curCow + 1].direction = 'W';
			curCow++;
		}
		else
		{
			cowTrace[curCow + 1].row = cowTrace[curCow].row;
			cowTrace[curCow + 1].col = cowTrace[curCow].col;
			cowTrace[curCow + 1].direction = 'N';
		}
	}
}

void findCircle()
{
	for (int i = 1;i < 401;i++)
	{
		
	}
}

int main()
{
	ifstream fin("ttwo.in");
	ofstream fout("ttwo.out");

	string map_str[10];
	for (int i = 0;i < 10;i++)
	{
		fin >> map_str[i];
	}
	str2map(map_str);
	simulate(400);
	
}