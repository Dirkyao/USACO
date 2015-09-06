/*
ID:dirkyao1
PROG:frac1
LANG:C++
*/
#include<iostream>
#include<fstream>
using namespace std;



bool judge_prime(int a, int b)
{
	if (a == 0)
	{
		if (b > 1)
			return false;
		return true;
	}
	else if (a == 1)
	{
		return true;
	}
	else
	{

		for (int j = 2; j <= a; j++)
		{
			if (b%j == 0 && a%j == 0)
				return false;
		}
		return true;
	}
}

struct fraction{
	int a;
	int b;
	float value;
};

void my_swap(fraction *frac, int i, int j)
{
	fraction temp;
	temp = frac[i];
	frac[i] = frac[j];
	frac[j] = temp;
}

void my_qsort(fraction *frac, int left, int right)
{
	int i, j;
	fraction temp, pivot;

	if (left > right)
		return;

	pivot = frac[right];
	i = left;
	j = right;
	while (i < j)
	{
		while (frac[i].value < pivot.value)
		{
			i++;
		}
		while (frac[j].value >= pivot.value)
		{
			j--;
		}
		if (i < j)
		{
			temp = frac[i];
			frac[i] = frac[j];
			frac[j] = temp;
		}
	}

	temp = frac[right];
	frac[right] = frac[i];
	frac[i] = temp;

	my_qsort(frac, left, i - 1);
	my_qsort(frac, i + 1, right);
}

int main()
{
	ifstream fin("frac1.in");
	ofstream fout("frac1.out");

	int N, frac_count = -1;
	fraction frac[40000];

	fin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			bool flag = judge_prime(j, i);
			if (flag)
			{
				frac[++frac_count].a = j;
				frac[frac_count].b = i;
				frac[frac_count].value = (float)j / i;
			}
		}
	}

	my_swap(frac, frac_count / 2, frac_count);
	my_qsort(frac, 0, frac_count);
	for(int i = 0; i <= frac_count; i++)
	{
		fout << frac[i].a << '/' << frac[i].b << endl;
	}
	return 0;
}