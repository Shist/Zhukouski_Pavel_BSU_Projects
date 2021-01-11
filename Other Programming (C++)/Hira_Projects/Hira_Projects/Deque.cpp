#include "Deque.h"



template <>
Deque<const char*>::DequeItem::DequeItem(const char* const& newInfo)
	: next(nullptr), prev(nullptr)
{
	info = new char[strlen(newInfo) + 1];
	strcpy((char*)info, newInfo);
}

template <>
Deque<const char*>::DequeItem::~DequeItem()
{
	delete[] info;
}


template <typename InfoType>
Deque<InfoType>::Deque()
	: front(nullptr), back(nullptr), size(0) {}

template <typename InfoType>
Deque<InfoType>::Deque(const Deque<InfoType>& oldDeque)
	: front(nullptr), back(nullptr), size(0)
{
	clone(oldDeque);
}

template <typename InfoType>
Deque<InfoType>::~Deque()
{
	erase();
}

template <typename InfoType>
Deque<InfoType>& Deque<InfoType>::operator =
(const Deque<InfoType>& oldDeque)
{
	if (this != &oldDeque)
	{
		erase();
		clone(oldDeque);
	}
	return *this;
}

template <typename InfoType>
void Deque<InfoType>::clone(const Deque<InfoType>& oldDeque)
{
	for (DequeItem* curr = oldDeque.front; curr != nullptr; curr = curr->next)
		InsertBack(curr->info);
}

template <typename InfoType>
void Deque<InfoType>::erase() {
	while (EraseFront());
}

template <typename InfoType>
void Deque<InfoType>::InsertFront(const InfoType& a) {
	DequeItem* curr = new DequeItem(a);
	if (size == 0)
		back = curr;
	else
	{
		(front->prev) = curr;
		(curr->next) = front;
	}
	front = curr;
	size++;
}

template <typename InfoType>
void Deque<InfoType>::InsertBack(const InfoType& a) {
	DequeItem* curr = new DequeItem(a);
	if (size == 0)
		front = curr;
	else
	{
		(back->next) = curr;
		(curr->prev) = back;
	}
	back = curr;
	size++;
}

template <typename InfoType>
bool Deque<InfoType>::EraseFront() {
	if (size == 0)
		return 0;
	DequeItem* curr = front;
	front = front->next;
	delete curr;
	if (front != nullptr)
		front->prev = nullptr;
	size--;
	if (size == 0)
		front = back = nullptr;
	return 1;
}

template <typename InfoType>
bool Deque<InfoType>::EraseBack() {
	if (size == 0)
		return 0;
	DequeItem* curr = back;
	back = back->prev;
	delete curr;
	if (back != nullptr)
		back->next = nullptr;

	size--;
	if (size == 0)
		front = back = nullptr;
	return 1;
}

template <typename InfoType>
size_t Deque<InfoType>::Size() {
	return size;
}

template <typename InfoType>
ostream& Deque<InfoType>::Print(ostream& str) const {
	for (DequeItem *i = front; i != nullptr; i = i->next)
	{
		str << i->info << " ";
	}
	return str;
}

template <typename InfoType>
ostream& Deque<InfoType>::PrintBack(ostream& str) const {
	for (DequeItem* i = back; *i != nullptr; i = i->prev)
	{
		str << i->info << " ";
	}
	return str;
}

template <typename InfoType>
InfoType& Deque<InfoType>::operator[](const int index) {
	if (size - 1 < index)
		throw "this object doesn't exsist";
	DequeItem* curr = front;
	for (int i = 0; i < index; i++)
	{
		curr = curr->next;
	}
	return curr->info;
}

template <>
bool Deque<const char*>::sortinfo(const char* const& a, const char* const& b) {
	return strcmp(a, b) < 0;
}

template <typename InfoType>
bool Deque<InfoType>::sortinfo(const InfoType& a, const InfoType& b) {
	return a < b;
}



template <typename InfoType>
void Deque<InfoType>::Sort() {
	bool check = false;
	while (!check)
	{
		check = true;
		DequeItem* curr = front;
		while (curr->next != nullptr)
		{
			if (!sortinfo(curr->info, (curr->next)->info))
			{
				InfoType rem = curr->info;
				curr->info = (curr->next)->info;
				(curr->next)->info = rem;
				check = false;
			}
			curr = curr->next;
		}
	}
}