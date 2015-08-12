/*
ID:dirkyao1
PROG:milk
LANG:C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

struct merchant
{
	int price;
	int amount;
};

bool compare(merchant mer1, merchant mer2)
{
	return mer1.price < mer2.price;
}

int main()
{
	ifstream fin("milk.in");
	ofstream fout("milk.out");

	int demand, merchant_num;
	
	fin >> demand >> merchant_num;
	vector<merchant> merchants(merchant_num);
	for (int i = 0; i < merchant_num; i++)
	{
		fin >> merchants[i].price >> merchants[i].amount;
	}

	sort(merchants.begin(), merchants.end(), compare);

	int cargo_count = 0, cost_count = 0;
	for (int j = 0; cargo_count < demand; j++)
	{
		if (demand - cargo_count>merchants[j].amount)
		{
			cargo_count += merchants[j].amount;
			cost_count += merchants[j].amount * merchants[j].price;
		}
		else
		{
			cost_count += (demand - cargo_count) * merchants[j].price;
			cargo_count = demand;
		}
	}
	fout << cost_count << endl;
	return 0;
}