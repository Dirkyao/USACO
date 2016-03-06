/*
ID:dirkyao1
PROG:contact
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<math.h>
#include<memory.h>
#include<algorithm>
using namespace std;

typedef struct node{
	int index = -1;
	int num = 0;
	string str;
}my_hash;

int A, B, N;
string signal;
my_hash str_hash[10000]; 

bool cmp(my_hash node_1, my_hash node_2)
{
	return node_1.num > node_2.num;
}

void re_sequence()
{
	ofstream fout("contact.out");

	int start = pow(2, A) - 2;
	int end = pow(2, B + 1) - 2;
	stable_sort(str_hash + start, str_hash + end, cmp);

	int num = 0;
	int str_num = pow(2, A) - 2;
	while (num < N)
	{
		int temp_num = str_hash[str_num].num;
		if (temp_num == 0)
			break;
		num++;
		fout << temp_num << endl;
		
		int six_count = 1;
		while (str_num < (pow(2, B + 1) - 2) & str_hash[str_num].num == temp_num)
		{
			if (six_count % 6 == 0 || str_hash[str_num + 1].num != temp_num)
				fout << str_hash[str_num].str.c_str() << endl;
			else
				fout << str_hash[str_num].str.c_str() << ' ';
			str_num++;
			six_count++;
		}
	}
}

void insert(int start, int end)
{
	int length = end - start;
	int index = 0;
	for (int i = 0; i < length; i++)
	{
		index = index + (signal[start + i]-'0') * pow(2, length - 1 - i);
	}
	int signal_index = pow(2, length) - 2 + index;

	if (str_hash[signal_index].num == 0)
	{
		for (int i = 0; i < length; i++)
		{
			str_hash[signal_index].str += signal[start + i];
		}
	}
	str_hash[signal_index].index = signal_index;
	str_hash[signal_index].num++;
}

void count()
{
	for (int i = 0; i < signal.length(); i++)
	{
		for (int j = A; j <= B; j++)
		{
			if (i + j <= signal.length())
			{
				insert(i, i + j);
			}
		}
	}
}

int main()
{
	ifstream fin("contact.in");

	fin >> A >> B >> N;

	char ch;
	while (fin.get(ch))
	{
		if (ch == '0' || ch == '1')
			signal += ch;
	}

	count();
	re_sequence();
	return 0;
}