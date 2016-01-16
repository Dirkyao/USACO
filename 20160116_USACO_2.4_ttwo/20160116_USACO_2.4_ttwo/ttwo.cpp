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

int map[10][10];
position(*route)[160000] = new position[2][160000];

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
					map[i][j] == '.';
					route[1][0].i = i;
					route[1][0].j = j;
					route[1][0].direction = 'N';
				}
			}
		}
	}
}