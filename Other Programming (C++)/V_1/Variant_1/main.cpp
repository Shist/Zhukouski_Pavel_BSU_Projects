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
		if (fin.peek() == EOF) // EOF это тоже самое, что -1
		{
			cerr << "File IN.TXT is empty!";
			return 2;
		}
		ofstream fout("OUT.TXT"); // Открываем файл, в котором будем хранить вывод
		int number;
		ListItem *curr;
		while (fin >> number) // Пока файл не закончился, делаем следующее...
		{
			curr = first; // first - это указатель на первый элемент списка
			while (curr != NULL) // Пока мы не дошли до последнего элемента списка, то выполняем цикл...
			{
				if (curr->data == number)
				{
					break; // Если мы уже нашли такой же элемент списка, который уже был, то ломаем цикл
				}
				curr = curr->next;
			}
			if (curr != NULL) continue;
			InsertListBegin(number); // Пихаем число в список (если мы дошли до этой строки)
			if (number == 1) // Если число - единица, то говорим, что оно ни простое, ни составное
			{
				fout << "1: neither prime nor composite";
			}
			else
			{
				fout << number << " : " << (IsPrime(number) ? "prime" : "composite"); // Если это верно, то выводим prime, а во всех остальных случпях выводим composite
			}
			fout << '\n';
		}
		ClearList(); // Очищаем список
		fin.close(); // Закрываем входящий файл 
		fout.close(); // Закрывай выходящий файл
	}
	else
	{
		cerr << "File in IN.TXT did not open!";
		return 1;
	}
	return 0;
}