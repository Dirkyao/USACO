/*
ID:dirkyao1
PROG:pprime
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<math.h>
#include<algorithm>
using namespace std;

int a, b;
int pprime[100000];
int pp_count = 0;

bool check_prime(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n%i == 0)
			return false;
	}
	return true;
}

int digits2int(int dig, int* dig_arr)
{
	int sum = 0;
	for (int i = 0; i < dig; i++)
	{
		sum = (sum * 10 + dig_arr[i]);
	}
	return sum;
}

int count_digits(int a)
{
	int count=0;
	while (a != 0)
	{
		count++;
		a = a / 10;
	}
	return count;
}

void solve(int dig,int *dig_arr,int index)
{
	if (index <= dig / 2)
	{

		for (int i = 0; i < 10; i++)
		{
			if (index == 0 && i == 0)
				continue;

			dig_arr[index] = i;
			dig_arr[dig - index - 1] = i;
			solve(dig, dig_arr, index + 1);
		}
	}
	else
	{
		int sum = digits2int(dig, dig_arr);
		if (sum >= a && sum <= b)
		{
			bool flag = check_prime(sum);
			if (flag == true)
			{
				pprime[pp_count++] = sum;
			}
		}
	}
}

int main()
{
	ifstream fin("pprime.in");
	ofstream fout("pprime.out");

	fin >> a >> b;
	if (b == 100000000)
		b -= 1;

	int digits_low, digits_high;
	digits_low = count_digits(a);
	digits_high = count_digits(b);

	for (int i = digits_low; i <= digits_high; i++)
	{
		int dig_arr[8];
		solve(i, dig_arr, 0);
	}

	sort(pprime, pprime + pp_count);
	for (int j = 0; j < pp_count-1; j++)
	{
		if (pprime[j] != pprime[j+1])
			fout << pprime[j] << endl;
	}
	fout << pprime[pp_count-1] << endl;
	return 0;
}