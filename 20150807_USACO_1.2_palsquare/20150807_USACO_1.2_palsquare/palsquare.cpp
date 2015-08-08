/*
ID:dirkyao1
PROG:palsquare
LANG:C++
*/
#include<iostream>
#include<string>
#include<fstream>
#include<math.h>
using namespace std;

string reverse_string(string str)
{
	string result = "";
	for (int i = 0; i < str.length(); i++)
	{
		result += str[str.length() - 1 - i];
	}
	return result;
}

string convert_base(int i, int base)
{
	string result_string = "";
	char char_temp;
	while (i != 0)
	{
		int left = i%base;
		if (0 <= left &&left < 10)
		{
			char_temp = left + '0';
		}
		else
		{
			char_temp = 'A' + left - 10;
		}
		result_string = result_string+char_temp;
		i = i / base;
	}
	return result_string;
}

int judge_reversible(string target)
{
	if (target == reverse_string(target))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	ifstream fin("palsquare.in");
	ofstream fout("palsquare.out");

	int base;
	fin >> base;
	for (int i = 1; i <= 300; i++)
	{
		string origin = convert_base(i, base);
		string target = convert_base(i*i, base);
		if (judge_reversible(target))
		{
			fout << reverse_string(origin) << " " << reverse_string(target) <<endl;
		}
	}
	return 0;
}
