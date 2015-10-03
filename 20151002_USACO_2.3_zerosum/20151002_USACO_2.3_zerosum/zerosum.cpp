/*
ID:dirkyao1
PROG:zerosum
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

int raw_str[17];
int N;
string result[1000];
int result_index = 0;

void value2str()
{
	string temp = "";
	for (int i = 0; i < N; i++)
	{
		if (i % 2 == 0)
			temp.push_back(raw_str[i] + '0');
		else
		{
			if (raw_str[i] == 1)
				temp.push_back('+');
			else if (raw_str[i] == 0)
				temp.push_back(' ');
			else if (raw_str[i] == -1)
				temp.push_back('-');
		}
	}
	
	result[result_index++] = temp;
}

int digits2int(int *temp, int temp_index)
{
	int value = 0;
	for (int i = 0; i < temp_index; i++)
	{
		value = value * 10 + temp[temp_index] * 10;
	}
	return value;
}

int word_analysis()
{
	int digit[10];
	int my_operator[10];
	int index = 0;

	int temp[10];
	int temp_index;
	for (int i = 0; i < N * 2 - 1; i++)
	{
		if (i % 2 == 0)
			temp[temp_index++] = i / 2 + 1;
		else
		{
			if (raw_str[i] == 1 || raw_str[i] == -1)
			{
				int value = digits2int(temp, temp_index);
				digit[index] = value;
				my_operator[index++] = raw_str[i];

				temp_index = 0;
			}
			if (raw_str[i] == 0)
			{
				continue;
			}
		}
	}
	int value = digits2int(temp, temp_index);
	digit[index] = value;


	int count = digit[0];
	for (int i = 0; i < index; i++)
	{
		if (my_operator[i] == 1)
			count = count + digit[i + 1];
		else
			count = count - digit[i + 1];
	}

	return count;
}

void dfs(int current)
{
	if (current < N)
	{
		raw_str[current * 2 + 1] = 1;
		dfs(current + 1);

		raw_str[current * 2 + 1] = 0;
		dfs(current + 1);

		raw_str[current * 2 + 1] = -1;
		dfs(current + 1);
	}
	else
	{
		int value = word_analysis();
		if (value == 0)
		{
			value2str();
		}
	}
}


int main()
{
	ifstream fin("zerosum.in");
	ofstream fout("zerosum.out");

	fin >> N;
	for (int i = 0; i < N; i += 2)
	{
		raw_str[i] = i + 1;
	}

	sort(result, result + result_index);

	for (int i = 1; i < result_index; i++)
	{
		fout << result[i] << endl;
	}

	return 0;
}