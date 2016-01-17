/*
ID:dirkyao1
PROG:ttwo
LANG:C++
*/
#include<iostream>
#include<fstream>
using namespace std;

struct position
{
	int i = -1;
	int j = -1 ;
	char direction = '0';
};

int operator==(position &pos_1, position &pos_2)
{
	if (pos_1.i == pos_2.i && pos_1.j == pos_2.j && pos_1.direction == pos_2.direction)
	{
		return 2;
	}
	else if (pos_1.i == pos_2.i && pos_1.j == pos_2.j)
	{
		return 1;
	}
	else return 0;
}

int cycleStart[2];
int cycle[2] = { -1, -1 };
int curTime = 0;
char map[10][10];
position(*route)[160000] = new position[2][160000];

void oneStep()
{
	for (int object = 0; object < 2; object++)
	{
		if (route[object][curTime].direction == 'N')
		{
			if (route[object][curTime].i > 0)
			{
				if (map[route[object][curTime].i - 1][route[object][curTime].j] == '*')
				{
					route[object][curTime + 1].i = route[object][curTime].i;
					route[object][curTime + 1].j = route[object][curTime].j;
					route[object][curTime + 1].direction = 'E';
				}
				else
				{
					route[object][curTime + 1].i = route[object][curTime].i-1;
					route[object][curTime + 1].j = route[object][curTime].j;
					route[object][curTime + 1].direction = 'N';
				}
			}
			else
			{
				route[object][curTime + 1].i = route[object][curTime].i;
				route[object][curTime + 1].j = route[object][curTime].j;
				route[object][curTime + 1].direction = 'E';
			}
		}
		else if (route[object][curTime].direction == 'E')
		{
			if (route[object][curTime].j < 9)
			{
				if (map[route[object][curTime].i][route[object][curTime].j+1] == '*')
				{
					route[object][curTime + 1].i = route[object][curTime].i;
					route[object][curTime + 1].j = route[object][curTime].j;
					route[object][curTime + 1].direction = 'S';
				}
				else
				{
					route[object][curTime + 1].i = route[object][curTime].i;
					route[object][curTime + 1].j = route[object][curTime].j + 1;
					route[object][curTime + 1].direction = 'E';
				}
			}
			else
			{
				route[object][curTime + 1].i = route[object][curTime].i;
				route[object][curTime + 1].j = route[object][curTime].j;
				route[object][curTime + 1].direction = 'S';
			}
		}
		else if (route[object][curTime].direction == 'S')
		{
			if (route[object][curTime].i < 9)
			{
				if (map[route[object][curTime].i+1][route[object][curTime].j] == '*')
				{
					route[object][curTime + 1].i = route[object][curTime].i;
					route[object][curTime + 1].j = route[object][curTime].j;
					route[object][curTime + 1].direction = 'W';
				}
				else
				{
					route[object][curTime + 1].i = route[object][curTime].i + 1;
					route[object][curTime + 1].j = route[object][curTime].j;
					route[object][curTime + 1].direction = 'S';
				}
			}
			else
			{
				route[object][curTime + 1].i = route[object][curTime].i;
				route[object][curTime + 1].j = route[object][curTime].j;
				route[object][curTime + 1].direction = 'W';
			}
		}
		else if (route[object][curTime].direction == 'W')
		{
			if (route[object][curTime].j>0)
			{
				if (map[route[object][curTime].i][route[object][curTime].j-1] == '*')
				{
					route[object][curTime + 1].i = route[object][curTime].i;
					route[object][curTime + 1].j = route[object][curTime].j;
					route[object][curTime + 1].direction = 'N';
				}
				else
				{
					route[object][curTime + 1].i = route[object][curTime].i;
					route[object][curTime + 1].j = route[object][curTime].j - 1;
					route[object][curTime + 1].direction = 'W';
				}
			}
			else
			{
				route[object][curTime + 1].i = route[object][curTime].i;
				route[object][curTime + 1].j = route[object][curTime].j;
				route[object][curTime + 1].direction = 'N';
			}
		}
	}
	curTime++;
}
void checkCycle()
{
	for (int index = 0; index < 2; index++)
	{
		for (int start = 0; start < 400; start++)
		{
			for (int moment = start + 1; moment < 400; moment++)
			{
				if ((route[index][start] == route[index][moment]) == 2)
				{
					cycle[index] = moment - start;
					cycleStart[index] = start;
					break;
				}
			}
			if (cycle[index] > 0)
				break;
		}

	}
}
int findMeet(int start)
{
	for (int i = 0; i < start + cycle[0] * cycle[1]; i++)
	{
		if ((route[0][i] == route[1][i])>0)
		{
			return i;
		}
	}
	return 0;
}

int main()
{
	ifstream fin("ttwo.in");
	ofstream fout("ttwo.out");

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fin >> map[i][j];
			if (map[i][j] != '*' && map[i][j]!='.')
			{
				if (map[i][j] == 'F')
				{
					map[i][j] = '.';
					route[0][0].i = i;
					route[0][0].j = j;
					route[0][0].direction = 'N';
				}
				else if (map[i][j] == 'C')
				{
					map[i][j] = '.';
					route[1][0].i = i;
					route[1][0].j = j;
					route[1][0].direction = 'N';
				}
			}
		}
	}
	for (int index = 0; index < 400; index++)
	{
		oneStep();
	}
	checkCycle();

	int start = cycleStart[0]>cycleStart[1] ? cycleStart[0] : cycleStart[1];
	for (int i = 399; i < start+cycle[0] * cycle[1]; i++)
	{
		oneStep();
	}

	fout << findMeet(start) << endl;
	return 0;
}