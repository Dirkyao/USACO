/*
ID:dirkyao1
PROG:heritage
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

char out_stack[27];
int top = 0;

int find_root(string in_order, string pre_order)
{
	int position;
	int index = -1, min = 27;
	for (int i = 0; i < in_order.length(); i++)
	{
		position = pre_order.find(in_order[i]);
		if (position < min)
		{
			min = position;
			index = i;
		}
	}
	return index;
}

void order_transfer(string in_order, string pre_order)
{
	int root = find_root(in_order, pre_order);
	out_stack[top++] = in_order[root];
	if (root <in_order.length()-1)
		order_transfer(in_order.substr(root + 1, in_order.length()-root-1),pre_order);
	if (root > 0)
		order_transfer(in_order.substr(0, root), pre_order);
}

int main()
{
	string in_order, pre_order;

	ifstream fin("heritage.in");
	ofstream fout("heritage.out");
	
	fin >> in_order >> pre_order;

	order_transfer(in_order, pre_order);
	
	for (int i = top; i > 0; i--)
	{
		fout << out_stack[i - 1];
	}
	fout << endl;
	return 0;
}