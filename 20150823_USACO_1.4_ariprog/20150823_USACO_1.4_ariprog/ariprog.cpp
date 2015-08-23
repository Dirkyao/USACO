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
inline bool in_arr(int *bisquare, int count, int index, int interval,int *hash)
{
	int goal = bisquare[index] + interval;
	if (hash[goal] == 1)
		return true;

	return false;
}

inline int check_ariprog(int* bisquare, int count, int start_index, int N, int interval,int* hash)
{
	if ((bisquare[start_index] + (N - 1)*interval) > bisquare[count - 1])
		return 0;
	int flag = 1;
	for (int i = 1; i < N; i++)
	{
		if (in_arr(bisquare, count, start_index, i*interval,hash))
		{
			flag++;
		}
		else
			break;
	}
	return flag;
}

inline void solve(int* bisquare, int count, int N,int* hash)
{
	int flag = 0;
	ofstream fout("ariprog.out");
	for (int i = 1; i <= bisquare[count - 1] / (N - 1); i++)
	{
		for (int j = 0; j <= count - N; j++)
		{
			int num = check_ariprog(bisquare, count, j, N, i,hash);
			if (num == N)
			{
				fout << bisquare[j] << ' ' << i << endl;
				flag = 1;
			}
		}
	}
	if (flag == 0)
	{
		fout << "NONE" << endl;
	}
}

int generate_bisquare(int M, int* bisquare)
{
	int *temp = new int[(M + 1)*(M + 1)];
	for (int i = 0; i <= M; i++)
	{
		for (int j = 0; j <= M; j++)
		{
			temp[i*(M + 1) + j] = i*i + j*j;
		}
	}
	sort(temp, temp + (M + 1)*(M + 1), compare);

	int count = 0;
	bisquare[count] = temp[count];
	for (int i = 1; i < (M + 1)*(M + 1); i++)
	{
		if (temp[i] != temp[i - 1])
		{
			bisquare[++count] = temp[i];
		}
	}
	cout << "done" << endl;
	return count + 1;
}

int main()
{
	ifstream fin("ariprog.in");
	int N, M;
	fin >> N >> M;

	int* bisquare = new int[(M + 1)*(M + 1)];
	int* hash = new int[M*M * 2];

	int num;
	num = generate_bisquare(M, bisquare);

	for (int i = 0; i < num; i++)
	{
		hash[bisquare[i]] = 1;
	}
	solve(bisquare, num, N,hash);

	return 0;
}