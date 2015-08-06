/*
ID:dirkyao1
PROG:namenum
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int check_char(char num, char dict_char)
{
	if (num == '2')
	{
		if (dict_char == 'A' || dict_char == 'B' || dict_char == 'C')
		{
			return 1;
		}
		else
			return 0;
	}
	else if (num == '3')
	{
		if (dict_char == 'D' || dict_char == 'E' || dict_char == 'F')
		{
			return 1;
		}
		else
			return 0;
	}
	else if (num == '4')
	{
		if (dict_char == 'G' || dict_char == 'H' || dict_char == 'I')
		{
			return 1;
		}
		else
			return 0;
	}
	else if (num == '5')
	{
		if (dict_char == 'J' || dict_char == 'K' || dict_char == 'L')
		{
			return 1;
		}
		else
			return 0;
	}
	else if (num == '6')
	{
		if (dict_char == 'M' || dict_char == 'N' || dict_char == 'O')
		{
			return 1;
		}
		else
			return 0;
	}
	else if (num == '7')
	{
		if (dict_char == 'P' || dict_char == 'R' || dict_char == 'S')
		{
			return 1;
		}
		else
			return 0;
	}
	else if (num == '8')
	{
		if (dict_char == 'T' || dict_char == 'U' || dict_char == 'V')
		{
			return 1;
		}
		else
			return 0;
	}
	else if (num == '9')
	{
		if (dict_char == 'W' || dict_char == 'X' || dict_char == 'Z')
		{
			return 1;
		}
		else
			return 0;
	}
}

int check_word(string num, string name)
{
	int flag = 1;
	for (int j = 0; j < num.length(); j++)
	{
		if (!check_char(num[j], name[j]))
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

int input_dict(string num, string *dict_arr, ifstream* dict_fin)
{
	
	int n = 0;
	string temp;

	while (*dict_fin >> temp)
	{
		if (check_char(num[0], temp[0]))
		{
			dict_arr[n] = temp;
			n++;
		}
	}
	return n;
}

int main()
{
	ifstream fin("namenum.in");
	ofstream fout("namenum.out");
	ifstream dict_fin("dict.txt");

	string num;
	string dict[5000];
	int str_num;
	int state = 0;
	int output_state = 0;

	fin >> num;
	str_num = input_dict(num, dict, &dict_fin);
	
	for (int i = 0; i < str_num; i++)
	{
		if (num.length() == dict[i].length())
		{
			state = check_word(num, dict[i]);
			if (state == 1)
			{
				fout << dict[i] << endl;
				output_state = 1;
			}
		}
	}
	if (output_state == 0)
	{
		fout << "NONE" << endl;
	}
	return 0;
}
