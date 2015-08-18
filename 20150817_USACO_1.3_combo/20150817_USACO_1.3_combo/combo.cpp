/*
ID:dirkyao1
PROG:combo
LANG:C++
*/
#include<iostream>
#include<fstream>
using namespace std;

int count_overlap(int a, int b,int N)
{
	int lock_num[100] = { 0 };
	int count = 0;

	for (int i = -2; i < 3; i++)
	{
		lock_num[(N + a + i) % N]++;
	}
	for (int i = -2; i < 3; i++)
	{
		lock_num[(N + b + i) % N]++;
	}
	for (int j = 0; j < N; j++)
	{
		if (lock_num[j] == 2)
		{
			count++;
		}
	}
	return count;
}

int main()
{
	ifstream fin("combo.in");
	ofstream fout("combo.out");

	int N;
	int farmer_lock[3], maker_lock[3];

	fin >> N;
	fin >> farmer_lock[0] >> farmer_lock[1] >> farmer_lock[2];
	fin >> maker_lock[0] >> maker_lock[1] >> maker_lock[2];
	
	if (N <= 5)
	{
		fout << N*N*N << endl;
	}
	else
	{
		int overlap[3];
		for (int i = 0; i < 3; i++)
		{
			overlap[i] = count_overlap(farmer_lock[i], maker_lock[i], N);
		}
		fout << 250 - overlap[0] * overlap[1] * overlap[2] << endl;
	}

	return 0;
}
