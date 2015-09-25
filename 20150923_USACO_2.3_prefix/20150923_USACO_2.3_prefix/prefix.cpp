/*
ID:dirkyao
PROG:prefix
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string>
#include<memory.h>
#include<map>
using namespace std;

map<string, bool> list;

int find_max(int* candidate, int index)
{
	int max = 0;
	for (int i = 0; i < index; i++)
	{
		if (candidate[i]>max)
		{
			max = candidate[i];
		}
	}
	return max;
}

void dynamic_planning(int *dp,int count,string str)
{
	for (int i = count-1; i >= 0; i--)
	{
		int candidate[10];
		int index = 0;
  		for (int j = i + 10; j > i; j--)
		{
			if (j > count)
				continue;
			string temp = str.substr(i, j - i);
			if (list[temp])
			{
				candidate[index++] = temp.length() + dp[j];
			}
		}
		if (index > 0)
		{
			dp[i] = find_max(candidate, index);
		}
		else
			dp[i] = 0;
	}
}

void ini_map(string* primitive, int count)
{
	for (int i = 0; i < count; i++)
	{
		list[primitive[i]] = true;
	}
}

int main()
{
	ifstream fin("prefix.in");
	ofstream fout("prefix.out");

	string primitive[202];
	string str;
	int count;
	int str_count = 0;
	string temp;
	int dp[200500];
	
	for (int i = 0; i < 202; i++)
	{
		fin >> temp;
		if (temp != ".")
		{
			primitive[i] = temp;
		}
		else
		{
			count = i;
			break;
		}
	}
	while (!fin.eof())
	{
		fin >> temp;
		str.append(temp);
		str_count += temp.length();
	}

	ini_map(primitive,count);
	memset(dp, 0, sizeof(int) * 200500);

	dynamic_planning(dp, str_count, str);


	return 0;
}