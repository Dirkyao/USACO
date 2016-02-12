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
int mod_index_num[100010];
int digits[100010];
int my_index = 0;
int float_index;
int temp_value = 0;

int check_temp(int temp_value)
{
	if (temp_value == 0)
	{
		return 0;
	}
	else if (mod_index_num[temp_value] > 1)
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
		for (int i = 0;i < 1;i++)
		{
			fout << digits[i];
		}
		fout << '.';
		for (int i = 1;i < my_index;i++)
		{
			if ((i + float_index) % 76 == 0)
			{
				fout << endl;
			}
			fout << digits[i];
		}
		if (float_index == my_index)
		{
			fout << 0;
		}
	}
	if (mode == 1)
	{
		int cir_index = mod_index[temp_value];
		for (int i = 0;i < 1;i++)
		{
			fout << digits[i];
		}
		fout << '.';
		for (int i = 1;i <= cir_index;i++)
		{
			if ((i + float_index) % 76 == 0)
			{
				fout << endl;
			}
			fout << digits[i];
		}
		fout << '(';
		for (int i = cir_index + 1;i <= my_index;i++)
		{
			if ((i + float_index + 1) % 76 == 0)
			{
				fout << endl;
			}
			fout << digits[i];
		}
		fout << ')';
	}
	fout << endl;
}

int float_num()
{
	int num = 0;
	int result = a / b;

	while (result > 0)
	{
		num++;
		result /= 10;
	}
	return num == 0 ? 1 : num;
}

int main()
{
	ifstream fin("fracdec.in");

	fin >> a >> b;
	for (int i = 0;i <= a;i++)
	{
		mod_index[i] = -1;
	}
	memset(mod_index_num, 0, sizeof(int)*(a + 1));

	float_index = float_num();
	//float_index = 1;
	while (true)
	{
		temp_value = a%b;
		digits[my_index] = a / b;
		a = temp_value * 10;
		mod_index_num[temp_value]++;
		if (mod_index_num[temp_value] <= 1)
		{
			mod_index[temp_value] = my_index++;
		}

		int result = check_temp(temp_value);
		if (result < 2)
		{
			output_digits(result);
			return 0;
		}
	}
}