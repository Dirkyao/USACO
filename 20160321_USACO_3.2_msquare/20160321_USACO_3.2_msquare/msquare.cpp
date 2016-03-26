/*
ID:dirkyao1
PROG:msquare
LANG:C++
*/
#include<iostream>
#include<fstream>
#include<map>
#include<string>
using namespace std;

string final;
typedef struct node{
	string value;
	string mother;
	char mother_action;
	node(string a, string b, char c) :value(a), mother(b), mother_action(c){};
public:
	node()
	{
		value = "NULL";
		mother = "NULL";
		mother_action = 'D';
	}
}state;
map<string, state> states;

void output(char action, state head, state last_node)
{
	char act_seq[10000];
	int index = 0;
	act_seq[index++] = action;

	state current = last_node;
	while (current.value != head.value)
	{
		act_seq[index++] = current.mother_action;
		current = states[current.mother];
	}

	ofstream fout("msquare.out");
	fout << index << endl;

	for (int i = 0; i < index; i++)
	{
		fout << act_seq[index - 1 - i];
		if (i % 60 == 59)
			fout << endl;
	}
	if (index % 60 != 0)
		fout << endl;
}

string action(string mother, char act)
{
	string result;
	if (act == 'A')
	{
		for (int i = 0; i < 8; i++)
			result += mother[7 - i];
	}
	if (act == 'B')
	{
		result += mother[3];
		result.append(mother, 0, 3);
		result.append(mother, 5, 3);
		result += mother[4];
	}
	if (act == 'C')
	{
		result += mother[0];
		result += mother[6];
		result += mother[1];
		result.append(mother, 3, 2);
		result += mother[2];
		result += mother[5];
		result += mother[7];
	}
	return result;
}

void bfs()
{
	state* head = new state("12345678", "NULL", 'D');
	char actions[3] = { 'A', 'B', 'C' };
	
	state* my_queue = new state[41000];
	int front = 0, rear = 0;
	states["12345678"] = *head;
	my_queue[rear++] = *head;
	if (head->value == final)
	{
		ofstream fout("msquare.out");
		fout << '0' << endl;
		fout << endl;
		return;
	}

	while (front != rear)
	{
		for (int i = 0; i < 3; i++)
		{
			string descendent = action(my_queue[front].value, actions[i]);
			if (states.count(descendent))
				continue;

			if (descendent == final)
			{
				//需要一系列动作；
				output(actions[i], *head, my_queue[front]);
				return;
			}
			state* current = new state(descendent, my_queue[front].value, actions[i]);
			states[descendent] = *current;
			my_queue[rear++] = *current;
		}
		front++;
	}
}

int main()
{
	ifstream fin("msquare.in");
	int temp;
	for (int i = 0; i < 8; i++)
	{
		fin >> temp;
		final += ('0' + temp);
	}
	bfs();
	return 0;
}