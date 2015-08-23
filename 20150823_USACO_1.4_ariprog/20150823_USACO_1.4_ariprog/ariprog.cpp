/*
ID:dirkyao1
PROG:ariprog
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

bool compare(int a, int b)
{
	return a < b;
}
bool in_arr(int *bisquare,int count, int index, int interval)
{
	int goal = bisquare[index] + interval;
	for (int j = index; j < count; j++)
	{
		if (bisquare[j] == goal)
			return true;
	}
	return false;
}

int check_ariprog(int* bisquare,int count,int start_index, int N,int interval)
{
	int flag = 1;
	for (int i = 1; i < N; i++)
	{
		if (in_arr(bisquare, count, start_index, i*interval))
		{
			flag++;
		}
	}
	return flag;
}

void solve(int* bisquare, int count, int N,ofstream * fout)
{
	for (int i = 1; i < bisquare[count-1]/N; i++)
	{
		for (int j = 0; j <= count - N; j++)
		{
			int num = check_ariprog(bisquare, count, j, N, i);
			if (num == N)
			{
				*fout << bisquare[j] << i<<endl;
			}
			j = j + num-1;
		}
	}
}

int generate_bisquare(int M, int* bisquare)
{
	int *temp = new int((M+1)*(M+1));
	for (int i = 0; i <= M; i++)
	{
		for (int j = 0; j <= M; j++)
		{
			temp[i*(M+1) + j] = i*i + j*j;
		}
	}
	sort(temp, temp+(M + 1)*(M + 1), compare);

	int count = 0;
	bisquare[count] = temp[count];
	for (int i = 1; i < (M + 1)*(M + 1); i++)
	{
		if (temp[i] != temp[i - 1])
		{
			bisquare[++count] = temp[i];
		}
	}
	return count + 1;
}

int main()
{
	ifstream fin("ariprog.in");
	ofstream fout("ariprog.out");

	int N, M;
	fin >> N >> M;

	int* bisquare = new int((M + 1)*(M + 1));

	int num;
	num = generate_bisquare(M, bisquare);


}