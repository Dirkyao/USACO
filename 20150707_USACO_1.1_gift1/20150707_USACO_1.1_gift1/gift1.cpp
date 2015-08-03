/*
ID:dirkyao1
PROG:gift1
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string>
#include<map>

using namespace std;

int main()
{
	ifstream fin("gift1.in");
	ofstream fout("gift1.out");

	int friends_count,friends_gifts[10];
	string friends_name,name_list[10];

	map<string, int> receive;

	fin >> friends_count;
	for (int i = 0; i < friends_count; i++)
	{
		fin >> friends_name;
		name_list[i] = friends_name;
		receive[friends_name] = 0;
	}
	for (int i = 0; i < friends_count; i++)
	{
		fin >> friends_name;

		int money, receiver;
		int left, give_sum;

		fin >> money;
		fin >> receiver;
		if (receiver != 0)
		{
			give_sum = money / receiver;
			left = money - receiver*(give_sum);

			receive[friends_name] = receive[friends_name] - money + left;
			for (int j = 0; j < receiver; j++)
			{
				fin >> friends_name;
				receive[friends_name] += give_sum;
			}
		}		
	}
	for (int i = 0; i < friends_count; i++)
	{
		fout << name_list[i] << " " << receive[name_list[i]] << endl;
	}
	return 0;
}