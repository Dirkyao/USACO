/*
ID:dirkyao1
PROG:milk3
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int my_hash[21] = { 0 };
int state[21][21][21] = { 0 };
int A, B, C;

void solve(int a, int b, int c)
{
	if (state[a][b][c] != 0)
		return;
	else
	{
		int count = 0;
		if (a == 0)
		{
			state[a][b][c] = 1;
			my_hash[c] = 1;
		}			
		else
			state[a][b][c] = -1;
		
		count = a - 0 > C - c ? C - c : a - 0;
		solve(a - count, b, c + count);
		count = a - 0 > B - b ? B - b : a - 0;
		solve(a - count, b + count, c);

		count = b - 0 > C - c ? C - c : b - 0;
		solve(a, b - count, c + count);
		count = b - 0 > A - a ? A - a : b - 0;
		solve(a + count, b - count, c);
		
		count = c - 0 > A - a ? A - a : c - 0;
		solve(a + count, b, c - count);
		count = c - 0 > B - b ? B - b : c - 0;
		solve(a, b + count, c - count);

		return;
	}
}

int main()
{
	ifstream fin("milk3.in");
	ofstream fout("milk3.out");

	fin >> A >> B >> C;
	solve(0, 0, C);

	int sum = 0;
	for (int i = 0; i <= C; i++)
	{
		if (my_hash[i] == 1)
			sum = i;
	}
	for (int i = 0; i <= C; i++)
	{
		if (my_hash[i] == 1 && i != sum)
		{
			fout << i << ' ';
		}
		else if (i == sum)
			fout << sum << endl;
	}
	return 0;
}