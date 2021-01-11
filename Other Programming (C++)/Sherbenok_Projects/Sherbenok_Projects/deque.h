#pragma once
#pragma warning(disable:4996)
#include <iostream>

using namespace std;

template <typename T>
class deque
{
private:
	struct QItem
	{
		T info;
		QItem* next;
		QItem* prev;
		QItem(T _info) : info(_info), prev(nullptr), next(nullptr) {}
	};

	QItem* first, *last;
	unsigned size;

	void Erase();
	void Clone(const deque& D);
	T GetAt(int);
	bool IsEmpty() const;

public:
	deque();
	deque(const deque&);
	~deque();

	const T GetFirst() const;
	const T GetLast() const;
	friend ostream& operator << (ostream&, const deque<T>&);
	ostream& PrintReverse(ostream&);

	deque& operator = (const deque&);
	unsigned GetSize();

	void PushBack(T);
	bool PopBack();
	void PushBegin(T);
	bool PopBegin();

	void sort_deque();
};