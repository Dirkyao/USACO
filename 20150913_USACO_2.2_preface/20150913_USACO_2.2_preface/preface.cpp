/*
ID:dirkyao1
PROG:preface
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<map>
using namespace std;

void digit2roman(char(*roman_list)[20], int num, int digit, int pos)
{
	char map[7] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
	if (digit < 4)
	{
		for (int i = 0; i < digit; i++)
		{
			roman_list[num][pos * 4 + i] = map[pos * 2];
		}
	}
	else if (digit == 4)
	{
		roman_list[num][pos * 4] = map[pos * 2];
		roman_list[num][pos * 4 + 1] = map[pos * 2 + 1];
	}
	else if (digit < 9)
	{
		roman_list[num][pos * 4] = map[pos * 2 + 1];
		for (int i = 5; i < digit; i++)
		{
			roman_list[num][pos * 4 + i - 5 + 1] = map[pos * 2];
		}
	}
	else if (digit == 9)
	{
		roman_list[num][pos * 4] = map[pos * 2];
		roman_list[num][pos * 4 + 1] = map[pos * 2 + 2];
	}
}

void digits2roman(char(*roman_list)[20], int* digits, int num)
{
	for (int i = 0; i < 4; i++)
	{
		digit2roman(roman_list, num, digits[i], i);
	}
}

void int2digit(int num, int *temp)
{
	int flag = 0;
	while (num > 0)
	{
		int digit = num % 10;
		temp[flag++] = digit;
		num /= 10;
	}
}

void create_element(int num, char(*roman_list)[20])
{
	int digits[4] = { 10 };
	int2digit(num, digits);
	int flag = 0;
	digits2roman(roman_list, digits, num);
}

int main()
{
	ifstream fin("preface.in");
	ofstream fout("preface.out");

	int N;
	fin >> N;

	char roman_list[3600][20];
	for (int i = 0; i < 3600; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			roman_list[i][j] = '0';
		}
	}
	for (int i = 1; i <= N; i++)
	{
		create_element(i, roman_list);
	}

	map<char, int> digit;
	char map[8] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M', '0' };
	for (int i = 0; i < 8; i++)
	{
		digit[map[i]] = i;
	}
	int count[8] = { 0 };
	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			count[digit[roman_list[i][j]]] ++;
		}
	}
	for (int i = 6; i >= 0; i--)
	{
		if (count[i] > 0)
		{
			for (int j = 0; j <= i; j++)
			{
				fout << map[j] << ' ' << count[j] << endl;
			}
			break;
		}
	}
	return 0;
}