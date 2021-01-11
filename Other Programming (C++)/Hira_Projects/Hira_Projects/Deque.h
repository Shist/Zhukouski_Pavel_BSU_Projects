#pragma once

#include <iostream>
#include <cstring>
#include <exception>
#include <list>

using namespace std;
#pragma warning (disable: 4996)


template <typename InfoType>
class Deque
{
private:
	struct DequeItem {
		InfoType info;
		DequeItem* next, *prev;
		DequeItem(const InfoType& newInfo)
			: info(newInfo), next(nullptr), prev(nullptr) {}
		~DequeItem() {}
	};
	DequeItem* front, *back;
	size_t size;

	void clone(const Deque<InfoType>&);
	void erase();
	bool inline sortinfo(const InfoType&, const InfoType&);
public:
	Deque();
	Deque(const Deque<InfoType>&);
	virtual ~Deque();

	Deque<InfoType>& operator= (const Deque<InfoType>&);

	void InsertFront(const InfoType&);
	void InsertBack(const InfoType&);
	bool EraseFront();
	bool EraseBack();

	size_t Size();

	ostream& Print(ostream&) const;
	ostream& PrintBack(ostream&) const;

	InfoType& operator[](const int);

	void Sort();
};
