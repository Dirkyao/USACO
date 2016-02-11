/*
ID:dirkyao1
PROG:fracdec
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<math.h>
#include<memory.h>
using namespace std;

int a, b;
int mod_index[100010];
int digits[100010];
int index = 0;
int float_index;
int temp_value = 0;

int check_temp(int temp_value)
{
	if (temp_value == 0)
	{
		return 0;
	}
	else if (mod_index[temp_value] >= 0)
	{
		return 1;
	}
	return 2;
}

void output_digits(int mode)
{
	ofstream fout("fracdec.out");
	if (mode == 0)
	{
		for (int i = 0;i < float_index;i++)
		{
			fout << digits[i];
		}
		fout << '.';
		for (int i = float_index;i < index;i++)
		{
			fout << digits[i];
		}
		if (float_index == index)
		{
			fout << 0;
		}
	}
	if (mode == 1)
	{
		int cir_index = mod_index[temp_value];
		for (int i = 0;i < float_index;i++)
		{
			fout << digits[i];
		}
		fout << '.';
		for (int i = float_index;i < cir_index;i++)
		{
			fout << digits[i];
		}
		fout << '(';
		for (int i = cir_index;i < index;i++)
		{
			fout << digits[i];
		}
		fout << ')';
	}
}

int main()
{
	ifstream fin("fracdec.in");

	fin >> a >> b;
	for (int i = 0;i < a;i++)
	{
		mod_index[i] = -1;
	}

	while (true)
	{
		if (a < b)
		{
			float_index = index + 1;
		}
		temp_value = a%b;
		digits[index] = a / b;
		a = temp_value;
		mod_index[temp_value] = index++;

		int result = check_temp(temp_value);
		if (result < 2)
		{
			output_digits(result);
			return 0;
		}
	}
}