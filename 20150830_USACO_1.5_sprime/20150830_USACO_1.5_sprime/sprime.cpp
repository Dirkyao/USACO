/*
ID:dirkyao
PROG:sprime
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

int arr2int(int* num, int index)
{
	int sum = 0;
	for (int i = 0; i <= index; i++)
	{
		sum = sum * 10 + num[i];
	}
	return sum;
}

bool check_prime(int* num, int index)
{
	int sum = arr2int(num, index);
	for (int i = 2; i <= sqrt(sum); i++)
	{
		if (sum%i == 0)
			return false;
	}
	
	return true;
}

void solve(int* num, int dig, int index, ofstream *fout)
{
	for (int i = 1; i < 10; i++)
	{
		if (index == 0 && i == 1)
		{
			continue;
		}

		num[index] = i;
		if (check_prime(num, index))
		{
			if (index < dig-1)
			{
				solve(num, dig, index + 1, fout);
			}
			else if (index == dig-1)
			{
				*fout << arr2int(num, index) << endl;
			}
		}
		else
			continue;
	}
}

int main()
{
	ifstream fin("sprime.in");
	ofstream fout("sprime.out");

	int N;
	fin >> N;
	int number[8] = { 0 };
	solve(number, N, 0, &fout);
	return 0;
}