#include "deque.h"
#include "Dexception.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

template <typename T>
deque <T> ::deque() : first(nullptr), last(nullptr), size(0) {}

/*
template <typename T>
bool deque <T> ::IsEmpty() const
{
	if (first == nullptr) {
		return true;
	}
	return false;
}

template <typename T>
const T deque <T> ::GetFirst() const
{
	if (IsEmpty())
	{
		throw Dexception("Deque is empty!");
	}

	return first->info;
}

template <typename T>
const T deque <T> ::GetLast() const
{
	if (IsEmpty())
	{
		throw Dexception("Deque is empty!");
	}

	return last->info;
}

template<>
deque <const char*> ::QItem::QItem(const char* _info) : prev(nullptr), next(nullptr)
{
	char * info = new char[strlen(_info) + 1];
	strcpy(info, _info);
}

template <typename T>
void deque <T> ::Erase()
{
	while (PopBack());
	size = 0;
}

template <typename T>
void deque <T> ::Clone(const deque<T>& d)
{
	QItem* tmp = d.last;
	for (unsigned i = 0; i < d.size; i++)
	{
		PushBack(tmp->info);
		tmp = tmp->next;
	}
}

template <typename T>
T deque <T> ::GetAt(int num)
{
	if (!IsEmpty()) {
		QItem* tmp = last;
		for (int i = 0; i < num; i++)
		{
			tmp = tmp->next;
		}

		return tmp->info;
	}
	else return NULL;
}

template <typename T>
deque <T> ::deque() : first(nullptr), last(nullptr), size(0) {}

template <typename T>
deque<T> ::deque(const deque<T>& d)
{
	size = 0;
	Clone(d);
}

template <typename T>
deque <T> :: ~deque()
{
	Erase();
}



template <typename T>
ostream& operator << (ostream& s, const deque<T>& d)
{
	for (int i = 0; i < d.size; i++)
	{
		s << d.getElement(i) << " ";
	}
	s << endl;
	for (int i = d.size - 1; i >= 0; i--)
	{
		s << d.getElement(i) << " ";
	}
	s << endl;

	return s;
}

template <typename T>
ostream& deque <T> ::PrintReverse(ostream& os)
{
	for (int i = size - 1; i >= 0; i--)
	{
		os << GetAt(i) << " ";
	}
	os << endl;
	return os;
}

template <typename T>
deque<T>& deque <T>::operator = (const deque<T>& d)
{
	if (this != &d)
	{
		Erase();
		Clone(d);
	}
	return *this;

}

template <typename T>
unsigned deque <T>::GetSize()
{
	return size;
}

template <typename T>
void deque <T>::PushBack(T _info)
{
	QItem* tmp = new QItem(_info);
	if (size > 0)
	{
		tmp->prev = first;
		first->next = tmp;
	}
	else
	{
		last = tmp;
	}
	first = tmp;
	size++;
}

template <typename T>
void deque <T>::PushBegin(T _info)
{
	QItem* tmp = new QItem(_info);
	if (size > 0)
	{
		tmp->next = last;
		last->prev = tmp;
	}
	else
	{
		first = tmp;
	}
	last = tmp;
	size++;
}

template <typename T>
bool deque <T>::PopBack()
{
	if (size == 0) {
		return false;
	}
	QItem* tmp = first;
	if (size > 1) {
		first = first->prev;
	}
	delete tmp;
	size--;
	first->next = nullptr;
	if (size == 0)
	{
		first = nullptr;
		last = nullptr;
	}
	return true;
}

template <typename T>
bool deque <T>::PopBegin()
{
	if (size == 0) {
		return false;
	}
	QItem* tmp = last;
	last = last->next;
	delete tmp;
	size--;
	if (last) {
		last->prev = nullptr;
	}
	if (size == 0)
	{
		first = nullptr;
		last = nullptr;
	}
	return true;
}

bool isBigger(const char* s1, const char* s2)
{
	int a = strcmp(s1, s2);
	if (a <= 0) {
		return true;
	}
	else {
		return false;
	}
}

template<>
void deque <const char*>::sort_deque()
{
	vector <const char*> arr;
	int _size = (*this).GetSize();
	for (int i = 0; i < _size; i++)
	{
		arr.push_back(last->info);
		PopBegin();
	}
	sort(arr.rbegin(), arr.rend(), isBigger);
	for (int i = 0; i < _size; i++)
	{
		PushBegin(arr[i]);
	}
}

template <typename T>
void deque <T>::sort_deque()
{
	vector <T> arr;
	int _size = (*this).GetSize();
	for (int i = 0; i < _size; i++)
	{
		arr.push_back(last->info);
		PopBegin();
	}
	sort(arr.rbegin(), arr.rend());
	for (int i = 0; i < _size; i++)
	{
		T tmp = arr[i];
		PushBegin(tmp);
	}
}
*/