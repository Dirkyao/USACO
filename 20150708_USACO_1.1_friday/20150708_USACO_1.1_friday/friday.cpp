/*
ID:dirkyao1
PROG:friday
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void account_for_weekday(int days_sum,int* days_count)
{
	int weekday = days_sum % 7;
	days_count[weekday]++;
}

int main()
{
	ifstream fin("friday.in");
	ofstream fout("friday.out");

	int total_year,days_sum = 0;
	int days_count[7] = { 0 };
	fin >> total_year;

	for (int i = 1900; i < 1900 + total_year; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (j == 0)
			{
				if (i == 1900)
				{
					days_sum += 12;
				}
				else
					days_sum += 31;
				account_for_weekday(days_sum, days_count);
			}
			else if (j == 1 || j == 3 || j == 7 || j == 8 || j == 10 || j == 5)
			{
				days_sum += 31;
				account_for_weekday(days_sum, days_count);
			}
			else if (j == 2)
			{
				if (i % 4 == 0)
				{
					if (i % 100 == 0 && i % 400 != 0)
					{
						days_sum += 28;
					}
					else
						days_sum += 29;
				}
				else
				{
					days_sum += 28;
				}
				account_for_weekday(days_sum, days_count);
			}
			else
			{
				days_sum += 30;
				account_for_weekday(days_sum, days_count);
			}
		}
	}
	for (int k = 5; k < 11; k++)
	{
		fout << days_count[k % 7] << " ";
	}
	fout << days_count[4] << endl;

	return 0;
}