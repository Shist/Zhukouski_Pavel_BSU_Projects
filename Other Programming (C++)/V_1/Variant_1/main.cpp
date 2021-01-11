#include <iostream>
#include <fstream>
using namespace std;

bool IsPrime(int num)
{
	if (num == 1) return false;
	bool result = true;
	for (int i = 2; (i*i <= num) && result; i++)
	{
		result = (num % i != 0);
	}
	return result;
}

struct ListItem
{
	int data;
	ListItem *next;
};

ListItem *first = NULL;

ListItem *temp;

void InsertList(ListItem *pos, int data)
{
	if (pos == NULL)
	{
		cout << "Everything is bad" << endl;
		return;
	}
	else
	{
		temp = new ListItem;
		temp->data = data;
		temp->next = pos->next;
		pos->next = temp;
		delete temp;
	}
}

void InsertListBegin(int data)
{
	temp = new ListItem;
	temp->data = data;
	temp->next = first;
	first = temp->next;
	delete temp;
}

void DeleteList(ListItem *pos)
{
	if (pos->next == NULL)
	{
		cout << "everything is bad" << endl;
		return;
	}
	else
	{
		temp = pos->next;
		pos->next = temp->next;
		delete temp;
	}
}

void DeleteListBegin()
{
	if (first == NULL)
	{
		cerr << "everything is bad";
		return;
	}
	temp = first;
	first = temp->next;
	delete temp;
}

void  ClearList()
{
	ListItem *curr = first;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		delete temp;
	}
}

int main()
{
	ifstream fin("IN.TXT");
	if (fin.is_open())
	{
		if (fin.peek() == EOF) // EOF ��� ���� �����, ��� -1
		{
			cerr << "File IN.TXT is empty!";
			return 2;
		}
		ofstream fout("OUT.TXT"); // ��������� ����, � ������� ����� ������� �����
		int number;
		ListItem *curr;
		while (fin >> number) // ���� ���� �� ����������, ������ ���������...
		{
			curr = first; // first - ��� ��������� �� ������ ������� ������
			while (curr != NULL) // ���� �� �� ����� �� ���������� �������� ������, �� ��������� ����...
			{
				if (curr->data == number)
				{
					break; // ���� �� ��� ����� ����� �� ������� ������, ������� ��� ���, �� ������ ����
				}
				curr = curr->next;
			}
			if (curr != NULL) continue;
			InsertListBegin(number); // ������ ����� � ������ (���� �� ����� �� ���� ������)
			if (number == 1) // ���� ����� - �������, �� �������, ��� ��� �� �������, �� ���������
			{
				fout << "1: neither prime nor composite";
			}
			else
			{
				fout << number << " : " << (IsPrime(number) ? "prime" : "composite"); // ���� ��� �����, �� ������� prime, � �� ���� ��������� ������� ������� composite
			}
			fout << '\n';
		}
		ClearList(); // ������� ������
		fin.close(); // ��������� �������� ���� 
		fout.close(); // �������� ��������� ����
	}
	else
	{
		cerr << "File in IN.TXT did not open!";
		return 1;
	}
	return 0;
}