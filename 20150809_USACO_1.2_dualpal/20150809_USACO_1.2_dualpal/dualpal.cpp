/*
ID:dirkyao1
PROG:dualpal
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int check_string(string result)
{
	int flag = 1;
	for(int i = 0; i < result.length()/2; i++)
	{
		if (result[i] != result[result.length() - 1 - i])
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

int judge_pal(int num, int base)
{
	string result;
	while (num != 0)
	{
		int mod_num = num%base;
		char temp = '0' + mod_num;
		result += temp;
		num = num / base;
	}
	//deside a string whether be a palstring
	return check_string(result);
}

int judge_dualpal(int num)
{
	int flag = 0;
	for (int j = 2; j <= 10; j++)
	{
		//to decide a number could or not to be a palnum
		flag += judge_pal(num, j);
		if (flag == 2)
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	ifstream fin("dualpal.in");
	ofstream fout("dualpal.out");

	int N, S;
	int count = 0;
	int state;
	fin >> N >> S;

	for (int i = S + 1; count < N; i++)
	{
		//the function to judge whether	a integer is a dualpal
		state = judge_dualpal(i);
		if (state == 1)
		{
			fout << i << endl;
			count++;
		}
	}
	return 0;
}