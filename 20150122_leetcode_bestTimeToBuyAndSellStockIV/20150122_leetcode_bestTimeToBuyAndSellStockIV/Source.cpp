#include<iostream>
#include<vector>
using namespace std;

int maxSequence(int k, int i, vector<int> profits, vector<vector<int> >states, vector<vector<int> > sums, vector<vector<int> >local)
{
	int max = 0;

	int profit_one = profits[i] > 0 ? states[k - 1][i - 1] + profits[i] : states[k - 1][i - 1];
	int profit_two = profits[i] > 0 ? states[k - 1][i - 1] + profits[i] : states[k - 1][i - 1];
	for (int j = 0; j < i; j++)
	{
		int profit_one = states[k - 1][j];
		int profit_two = sums[j + 1][i];
		if (profit_one + profit_two > max)
			max = profit_one + profit_two;
	}
	return max;
}

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

	vector<vector<int> >states(k + 1);
	for (int i = 0; i <= k; i++)
	{
		states[i].resize(prices.size());
	}
	states[1][0] = 0;

	vector<vector<int> > local(k + 1);
	for (int i = 0; i <= k; i++)
	{
		local[i].resize(prices.size());
	}
	local[1][0] = 0;

	vector<vector<int> >sums(prices.size());
	for (int i = 0; i < prices.size(); i++)
	{
		sums[i].resize(prices.size());
	}
	for (int i = 0; i < prices.size(); i++)
	{
		sums[i][i] = profits[i];
		for (int j = i+1; j < prices.size(); j++)
		{
			sums[i][j] = sums[i][j - 1] + profits[j];
		}
	}

	for (int i = 1; i <= k; i++)
	{
		for (int j = 1; j < prices.size();j++)
		{
			int profits_1 = states[i][j - 1];
			local[i][j] = maxSequence(i, j, profits, states,sums);

			states[i][j] = profits_1 > profits_2 ? profits_1 : profits_2;
		}
	}
	return states[k][prices.size() - 1];
}

int main()
{
	int test[9] = { 0, 1, 2, 3, 4, 0, 1, 2, 3 };
	vector<int> prices;
	for (int i = 0; i < 9; i++)
	{
		prices.push_back(test[i]);
	}
	int benefit = maxProfit(2, prices);
	return 0;
}