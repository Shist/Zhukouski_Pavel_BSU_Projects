#include "Deque.cpp"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	int i;
	int front;
	double d;
	srand(time(nullptr));
	Deque<int> intDeque;
	Deque<double> doubleDeque;
	Deque<const char *> stringDeque;
	for (i = 0; i < 10; i++)
	{
		cout << "Sending integer " << i << " to the front of intDeque...\n";
		intDeque.PushFront(i);
	}
	cout << "The resulting deque: ";
	intDeque.PrintDeque(cout);
	cout << endl;
	for (d = 0.0; d < 15.0; d += 0.5)
	{
		front = rand() & 1;
		cout << "Sending a double " << d << " to the "
			<< (front ? "front" : "back")
			<< " of doubleDeque...\n";
		if (front)
			doubleDeque.PushFront(d);
		else
			doubleDeque.PushBack(d);
	}
	cout << "The resulting deque: ";
	doubleDeque.PrintDeque(cout);
	cout << endl;
	const char * names[] =
	{
		"Sasha Malyavko",
		"Pavel Zhukovski",
		"Dmitry Soloduha",
		"Daniil Lebedev",
		"Anya Grydushko",
		"Nastya Katsuba",
		"Gleb Levotski",
		"Andrey Grishkin",
		"Liza Moiseychik"
	};
	for (auto name : names)
	{
		cout << "Sending a string \"" << name
			<< "\" to the back of stringDeque...\n";
		stringDeque.PushBack(name);
	}
	cout << "The resulting deque, inversed:\n";
	stringDeque.PrintDequeInverse(cout, "\n");
	cout << endl;
	cout << "Popping first integer: ";
	intDeque.PopFront();
	cout << "The resulting deque: ";
	intDeque.PrintDeque(cout);
	cout << endl;
	cout << "Popping doubles from the end and clearing the deque:" << endl;
	do
	{
		doubleDeque.PrintDeque(cout);
		cout << endl;
	} while (doubleDeque.PopBack());
	try
	{
		cout << "Trying to get the first element: ";
		cout << doubleDeque.Front();
	}
	catch (exception &ex)
	{
		cerr << "Error! Have a look: " << ex.what() << endl;
	}
	cout << "Obtaining the size of stringDeque: " << stringDeque.Size() << endl;
	cout << "Sorting stringDeque...\n";
	stringDeque.Sort();
	cout << "The resulting deque:" << endl;
	stringDeque.PrintDeque(cout, "\n");
	cout << endl;
	return 0;
}