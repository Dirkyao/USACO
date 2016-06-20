/*
ID:dirkyao1
PROG:fence
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<memory.h>
#include<vector>
#include<algorithm>
using namespace std;

int F;
int fences[510][510];
vector<vector<int> > fences_link;
int stack[15000], stack_top = 0;

bool cmp(int A, int B)
{
	return A > B;
}

int find_source()
{
	int flag = 0;
	int small = 0;
	int small_flag = 0;
	for (int i = 1; i < 510; i++)
	{
		if (fences_link[i].size() > 0 && small_flag == 0)
		{
			small = i;
			small_flag = 1;
		}
		if (fences_link[i].size() % 2 == 1)
		{
			flag = i;
			break;
		}
	}
	if (flag > 0)
		return flag;
	else
		return small;
}

void euler_circuit(int source)
{
	if (fences_link[source].size() == 0)
	{
		stack[stack_top++] = source;
	}
	else
	{
		while (fences_link[source].size() != 0)
		{
			int next = *(fences_link[source].end() - 1);
			fences_link[source].pop_back();
			vector<int>::iterator it = find(fences_link[next].begin(), fences_link[next].end(), source);
			fences_link[next].erase(it);

			euler_circuit(next);
		}
		stack[stack_top++] = source;
	}
}

void solve()
{
	ofstream fout("fence.out");
	int source = find_source();
	euler_circuit(source);

	while (stack_top>0)
	{
		fout << stack[stack_top - 1] << endl;
		stack_top--;
	}
}

int main()
{
	ifstream fin("fence.in");
	fin >> F;
	memset(fences, 0, sizeof(fences));
	fences_link.resize(1500);

	for (int i = 0; i < F; i++)
	{
		int node1, node2;
		fin >> node1 >> node2;
		fences[node1][node2] = 1;
		fences[node2][node1] = 1;
		fences_link[node1].push_back(node2);
		fences_link[node2].push_back(node1);
	}
	for (int i = 0; i < 510; i++)
	{
		sort(fences_link[i].begin(), fences_link[i].end(), cmp);
	}
	solve();
}