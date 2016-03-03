#include<iostream>
#include<vector>
using namespace std;

int maxProfit(int k, vector<int>& prices)
{
	if (prices.size() == 0 || k == 0)
		return  0;

	vector<int> profits;
	profits.push_back(0);
	for (vector<int>::iterator it = prices.begin() + 1; it != prices.end(); it++)
	{
		profits.push_back(*it - *(it - 1));
	}

	if (k > prices.size() / 2)
	{
		int sum = 0;
		for (vector<int>::iterator it = profits.begin(); it != profits.end(); it++)
		{
			if (*it > 0)
			{
				sum += *it;
			}
		}
		return sum;
	}
	vector<vector<int> > globals(k + 1);
	for (int i = 0; i <= k; i++)
	{
		globals[i].resize(prices.size());
	}
	globals[1][0] = 0;

	vector<vector<int> > locals(k + 1);
	for (int i = 0; i <= k; i++)
	{
		locals[i].resize(prices.size());
	}
	locals[1][0] = 0;

	
	for (int i = 1; i <= k; i++)
	{
		for (int j = 1; j < prices.size();j++)
		{
			int last_profit = profits[j]>0 ? profits[j] : 0;
			locals[i][j] = globals[i - 1][j - 1] + last_profit > locals[i][j - 1] + profits[j] ? globals[i - 1][j - 1] + last_profit : locals[i][j - 1] + profits[j];
			globals[i][j] = globals[i][j - 1] > locals[i][j] ? globals[i][j-1] : locals[i][j];
		}
	}
	return globals[k][prices.size() - 1];
}

int main()
{
	int test[9] = { 0, 1, 2, 3, 4, 0, 1, 2, 3 };
	vector<int> prices;
	for (int i = 0; i < 9; i++)
	{
		prices.push_back(test[i]);
	}
	int benefit = maxProfit(9, prices);
	return 0;
}