/*
ID:dirkyao1
PROG:transform
LANG:C++
*/
#include<iostream>
#include<fstream>

using namespace std;

struct cord{
	int i;
	int j;
};

cord* index_converter(cord* position, int N,int mode,int submode = 0)
{
	cord* temp = new cord();
	if (mode == 1)
	{
		temp->i = position->j;
		temp->j = N - 1 - position->i;
	}
	if (mode == 2)
	{
		temp->i = N - 1 - position->i;
		temp->j = N - 1 - position->j;
	}
	if (mode == 3)
	{
		temp->i = N - 1 - position->j;
		temp->j = position->i;
	}
	if (mode == 4)
	{
		temp->i = position->i;
		temp->j = N - 1 - position->j;
	}
	if (mode == 5)
	{
		cord* temp2 = index_converter(position, N, 4);
		if (submode == 1)
		{
			temp = index_converter(temp2, N, 1);
		}
		else if (submode == 2)
		{
			temp = index_converter(temp2, N, 2);
		}
		else if (submode == 3)
		{
			temp = index_converter(temp2, N, 3);
		}
	}
	if (mode == 6)
	{
		temp = position;
	}
	return temp;
}

int main()
{
	ifstream fin("transform.in");
	ofstream fout("transform.out");

	int N;
	char tiles_one[10][10], tiles_two[10][10];

	fin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> tiles_one[i][j];
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> tiles_two[i][j];
		}
	}
	for (int mode = 1; mode < 7; mode++)
	{
		int flag = 1;
		cord* convertion = new cord();
		cord* present = new cord();
		if (mode != 5)
		{
			for (int i = 0; i < N; i++)
			{
				present->i = i;
				for (int j = 0; j < N; j++)
				{
					present->j = j;
					convertion = index_converter(present, N, mode);
					if (tiles_one[i][j] != tiles_two[convertion->i][convertion->j])
					{
						flag = 0;
						break;
					}
				}
				if (flag == 0)
					break;
			}
			if (flag == 1)
			{
				fout << mode << endl;
				return 0;
			}
		}
		else
		{
			for (int submode = 1; submode < 4; submode++)
			{
				flag = 1;
				for (int i = 0; i < N; i++)
				{
					present->i = i;
					for (int j = 0; j < N; j++)
					{
						present->j = j;
						convertion = index_converter(present, N, mode,submode);
						if (tiles_one[i][j] != tiles_two[convertion->i][convertion->j])
						{
							flag = 0;
							break;
						}
					}
					if (flag == 0)
						break;
				}
				if (flag == 1)
				{
					fout << mode << endl;
					return 0;
				}
			}
		}
	}
	fout << 7 << endl;
	return 0;
}
