/*
ID:dirkyao
PROG:skidesign
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

int solve(int *hills, int N)
{
	int cost = 1000000;
	if (hills[N - 1] - hills[0] < 18)
		return 0;
	else
	{
		for (int j = hills[0]; j <= hills[N-1]-17; j++)
		{
			int temp = 0;
			for (int i = 0; i < N; i++)
			{
				if (!(hills[i] >= j && hills[i] <= j + 17))
				{
					if (hills[i] < j)
					{
						temp += (j - hills[i])*(j - hills[i]);
					}
					else
					{
						temp += (hills[i] - j - 17)*(hills[i] - j - 17);
					}
				}
			}
			if (temp < cost)
				cost = temp;
		}
		return cost;
	}

}

int main()
{
	ifstream fin("skidesign.in");
	ofstream fout("skidesign.out");

	int N;
	int hills[1000];

	fin >> N;

	for (int i = 0; i < N; i++)
	{
		fin >> hills[i];
	}
	sort(hills, hills+N);

	fout << solve(hills, N) << endl;
	return 0;
}