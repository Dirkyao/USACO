/*
ID:dirkyao1
PROG:crypt1
LANG:C++
*/

#include<iostream>
#include<fstream>
using namespace std;

bool judge_subset(int* multi_up, int* subset, int sub_num, int digit)
{
	for (int i = 0; i < digit; i++)
	{
		int flag = 0;
		for (int j = 0; j < sub_num; j++)
		{
			if (multi_up[i] == subset[j])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			return false;
		}
	}
	return true;
}

int add(int* multi_large, int* multi_small,int* subset,int sub_num)
{
	int large = multi_large[0] * 1000 + multi_large[1] * 100 + multi_large[2] * 10;
	int small = multi_small[0] * 100 + multi_small[1] * 10 + multi_small[2];

	int add_rst = large + small;
	int ret_arr[4];
	int void_arr[4] = { 0, 0, 0, 0 };
	if (add_rst < 10000)
	{
		ret_arr[3] = add_rst % 10;
		add_rst = add_rst / 10;
		ret_arr[2] = add_rst % 10;
		add_rst = add_rst / 10;
		ret_arr[1] = add_rst % 10;
		add_rst = add_rst / 10;
		ret_arr[0] = add_rst % 10;

		bool flag = judge_subset(ret_arr, subset, sub_num, 4);
		if (flag == false)
			return 0;
		else
			return 1;
	}
	else
		return 0;
}



int* multiply(int* multi_up, int multi_down, int* subset, int sub_num)
{
	int up;
	up = multi_up[0] * 100 + multi_up[1] * 10 + multi_up[2];
	up = up*multi_down;
	int ret_arr[3];
	int void_arr[3] = { 0, 0, 0 };
	if (up < 1000)//need judge
	{
		ret_arr[2] = up % 10;
		up = up / 10;
		ret_arr[1] = up % 10;
		up = up / 10;
		ret_arr[0] = up % 10;

		bool flag = judge_subset(ret_arr, subset, sub_num, 3);
		if (flag)
			return ret_arr;
		else
		{
			return void_arr;
		}
	}
	else
	{
		return void_arr;
	}
}

bool judge_crypt(int* multi_up, int* multi_down,int* subset, int sub_num)
{
	int* temp_rst_1,*temp_rst_2;
	int temp_1[3], temp_2[3];
	//judge and count the first digit in multi_down;
	if (multi_up[0] * multi_down[0] > 9)
		return false;
	else
	{
		//multiply the numbers
		temp_rst_1 = multiply(multi_up, multi_down[0], subset, sub_num);

		int flag = 0;
		for (int i = 0; i < 3; i++)
		{
			if (temp_rst_1[i] == 0)
				flag++;
			else
				break;
		}
		if (flag == 3)
			return false;
	}
	for (int r = 0; r < 3; r++)
	{
		temp_1[r] = temp_rst_1[r];
	}
	if (multi_up[0] * multi_down[1] > 9)
		return false;
	else
	{
		temp_rst_2 = multiply(multi_up, multi_down[1], subset, sub_num);

		int flag = 0;
		for (int i = 0; i < 3; i++)
		{
			if (temp_rst_2[i] == 0)
			{
				flag++;
			}
		}
		if (flag == 3)
			return false;
	}
	
	for (int r = 0; r < 3; r++)
	{
		temp_2[r] = temp_rst_2[r];
	}
	int state = add(temp_1, temp_2, subset, sub_num);
	if (state == 1)
		return true;
	else
		return false;
}

int main()
{
	ifstream fin("crypt1.in");
	ofstream fout("crypt1.out");

	int sub_num;
	int subset[9];
	int multiply_up[3], multiply_down[2];
	fin >> sub_num;

	for (int i = 0; i < sub_num; i++)
	{
		fin >> subset[i];
	}
	int count = 0;
	for (int i = 0; i < sub_num; i++)
	{
		multiply_up[0] = subset[i];
		for (int j = 0; j < sub_num; j++)
		{
			multiply_up[1] = subset[j];
			for (int k = 0; k < sub_num; k++)
			{
				multiply_up[2] = subset[k];
				//the multiply_down round;
				for (int n = 0; n < sub_num; n++)
				{
					multiply_down[0] = subset[n];
					for (int m = 0; m < sub_num; m++)
					{
						multiply_down[1] = subset[m];
						bool rst = judge_crypt(multiply_up, multiply_down, subset, sub_num);
						if (rst == 1)
						{
							count++;
						}
					}
				}
			}
		}
	}
	fout << count << endl;
	return 0;
}

