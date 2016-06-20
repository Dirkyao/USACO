/*
ID:dirkyao1
PROG:shopping
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<map>
#include<memory.h>
using namespace std;

int schemes_num, products_num;
map<int, int> products_map;
int products_demond[5],products_price[5],schemes[105][6];

int current_state[5];
int states[6][6][6][6][6];

void schemes_dp(int index)
{
	if (index != products_num)
	{
		for (int i = 0; i <= products_demond[index]; i++)
		{
			current_state[index] = i;
			schemes_dp(index + 1);
		}
	}
	if (index == products_num)
	{
		for (int i = 0; i < schemes_num; i++)
		{
			if (current_state[0] < schemes[i][0] || current_state[1] < schemes[i][1] || current_state[2] < schemes[i][2] || current_state[3] < schemes[i][3] || current_state[4] < schemes[i][4])
				continue;
			else
			{
				int temp = states[current_state[0] - schemes[i][0]][current_state[1] - schemes[i][1]][current_state[2] - schemes[i][2]][current_state[3] - schemes[i][3]][current_state[4] - schemes[i][4]] + schemes[i][5];
				if (temp < states[current_state[0]][current_state[1]][current_state[2]][current_state[3]][current_state[4]])
					states[current_state[0]][current_state[1]][current_state[2]][current_state[3]][current_state[4]] = temp;
			}
		}
	}
}

void dfs_init(int index)
{
	if (index != products_num)
	{
		for (int i = 0; i <= products_demond[index]; i++)
		{
			current_state[index] = i;
			dfs_init(index + 1);
		}
	}
	if (index == products_num)
	{
		int temp_price = 0;
		for (int i = 0; i < products_num; i++)
		{
			temp_price += current_state[i] * products_price[i];
		}
		states[current_state[0]][current_state[1]][current_state[2]][current_state[3]][current_state[4]] = temp_price;
	}
}

int main()
{
	ifstream fin("shopping.in");
	ofstream fout("shopping.out");

	fin >> schemes_num;

	int count = 0;
	memset(schemes, 0, sizeof(schemes));
	memset(products_demond, 0, sizeof(products_demond));
	memset(products_price, 0, sizeof(products_price));
	for (int i = 0; i < schemes_num; i++)
	{
		int n;
		fin >> n;
		int index, amount;
		for (int j = 0; j < n; j++)
		{			
			fin >> index >> amount;
			if (products_map.find(index) == products_map.end())
			{
				products_map[index] = products_map.size();
				schemes[i][products_map[index]] = amount;
			}
			else
			{
				schemes[i][products_map[index]] = amount;
			}
		}
		fin >> schemes[i][5];
	}

	fin >> products_num;
	for (int i = 0; i < products_num; i++)
	{
		int c, k, p;
		fin >> c >> k >> p;
		products_demond[products_map[c]] = k;
		products_price[products_map[c]] = p;
	}

	memset(current_state, 0, sizeof(current_state));
	dfs_init(0);
	schemes_dp(0);
	
	fout << states[products_demond[0]][products_demond[1]][products_demond[2]][products_demond[3]][products_demond[4]] << endl;
	return 0;
}