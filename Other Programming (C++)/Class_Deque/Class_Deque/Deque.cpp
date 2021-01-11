#include "Deque.h"

template <>
Deque <const char * > :: DequeItem :: DequeItem(const char * const& new_info) : next(nullptr), prev(nullptr)
{
	info = new char[strlen(new_info) + 1];
	strcpy((char*)info, new_info);
}

template <>
Deque <const char * > ::DequeItem :: ~DequeItem()
{
	delete[] info;
}

template <typename InfoType>
void Deque <InfoType> :: erase()
{
	while (PopFront()); // в while пустой оператор
	front = rear = nullptr;
}

template <typename InfoType>
void Deque <InfoType> :: clone(const Deque <InfoType>& oldDeque)
{
	size = 0;
	for (DequeItem *curr = oldDeque.front; curr != nullptr; curr = curr->next)
		PushBack(curr->info);
}

template <typename InfoType>
Deque<InfoType> :: Deque() : front(nullptr), rear(nullptr), size(0) {}

template <typename InfoType>
Deque <InfoType> ::Deque(const Deque<InfoType>& oldDeque) : front(nullptr), rear(nullptr), size(0)
{
	clone(oldDeque);
}

template <typename InfoType>
Deque <InfoType> :: ~Deque()
{
	erase();
}

template <typename InfoType>
Deque<InfoType>& Deque<InfoType> :: operator = (const Deque <InfoType>& oldDeque)
{
	if (this != &oldDeque)
	{
		erase();
		clone(oldDeque);
	}
	return *this;
}

template <typename InfoType>
const InfoType& Deque <InfoType> ::Front() const
{
	if (size == 0)
		throw exception("Impossible to see the first element of the deque!");
	return front->info;
}

template <typename InfoType>
const InfoType& Deque <InfoType> ::Back() const
{
	if (size == 0)
		throw exception("Impossible to see the last element of the deque!");
	return rear->info;
}

template <typename InfoType>
void Deque <InfoType> :: PushFront(const InfoType& info)
{
	DequeItem *temp = new DequeItem(info);
	if (size == 0)
	{
		rear = temp;
	}
	else
	{
		temp->next = front;
		front->prev = temp;
	}
	front = temp;
	size++;
}

template <typename InfoType>
void Deque <InfoType> :: PushBack(const InfoType& info)
{
	DequeItem *temp = new DequeItem(info);
	if (size == 0)
	{
		front = temp;
	}
	else
	{
		rear->next = temp;
		temp->prev = rear;
	}
	rear = temp;
	size++;
}

template <typename InfoType>
bool Deque <InfoType> ::PopFront()
{
	if (size == 0)
		return false;
	DequeItem *temp;
	temp = front;
	front = front->next;
	if (front != nullptr)
		front->prev = nullptr;
	delete temp;
	size--;
	if (size == 0)
		front = rear = nullptr;
	return true;
}

template <typename InfoType>
bool Deque <InfoType> ::PopBack()
{
	if (size == 0)
		return false;
	DequeItem *temp;
	temp = rear;
	rear = rear->prev;
	if (rear != nullptr)
		rear->next = nullptr;
	delete temp;
	size--;
	if (size == 0)
		rear = front = nullptr;
	return true;
}

template <typename InfoType>
size_t Deque <InfoType> :: Size() const
{
	return size;
}

template <typename InfoType>
void Deque <InfoType> :: PrintDeque (ostream& str, const char* delimiter) const
{
	for (DequeItem *curr = front; curr != nullptr; curr = curr->next)
		str << curr->info << (curr == rear ? " ": delimiter);
}

template <typename InfoType>
void Deque <InfoType> ::PrintDequeInverse(ostream& str, const char* delimiter) const
{
	for (DequeItem *curr = rear; curr != nullptr; curr = curr->prev)
		str << curr->info << (curr == front ? " " : delimiter);
}

template <>
static bool Deque <const char*> :: defaultCompare(const char* const& a, const char* const& b)
{
	return strcmp(a, b) < 0;
}

template <typename InfoType>
void Deque <InfoType> ::MergeLists(DequeItem * listA, DequeItem * listB, DequeItem *&result, compare comp)
{
	if (listA == nullptr || listB == nullptr)
	{
		result = (listB == nullptr ? listA : listB);
		return;
	}
	DequeItem * endMerged;
	if (comp(listA->info, listB->info))
	{
		endMerged = listA;
		listA = listA->next;
	}
	else
	{
		endMerged = listB;
		listB = listB->next;
	}
	result = endMerged;
	while (listA != nullptr && listB != nullptr)
	{
		if (comp(listA->info, listB->info))
		{
			endMerged->next = listA;
			listA = listA->next;
		}
		else
		{
			endMerged->next = listB;
			listB = listB->next;
		}
		endMerged = endMerged->next;
	}
	while (listA != nullptr)
	{
		endMerged->next = listA;
		listA = listA->next;
		endMerged = endMerged->next;
	}
	while (listB != nullptr)
	{
		endMerged->next = listB;
		listB = listB->next;
		endMerged = endMerged->next;
	}
	DequeItem * prevItem = nullptr;
	for (DequeItem * curr = result; curr != nullptr; curr = curr->next)
	{
		curr->prev = prevItem;
		prevItem = curr;
	}
}

template <typename InfoType>
void Deque <InfoType> :: Sort(compare comp)
{
	DequeItem * temp;
	list <DequeItem *> itemList, tempList;
	for (DequeItem * curr = front; curr != nullptr; )
	{
		temp = curr;
		curr = curr->next;
		temp->next = temp->prev = nullptr;
		itemList.push_back(temp);
	}
	while (itemList.size() > 1)
	{
		while (itemList.size() > 1)
		{
			DequeItem *first, *second, *result;
			first = itemList.front();
			itemList.pop_front();
			second = itemList.front();
			itemList.pop_front();
			MergeLists(first, second, result, comp);
			tempList.push_back(result);
		}
		if (itemList.size() == 1)
		{
			tempList.push_back(itemList.front());
			itemList.pop_front();
		}
		itemList.splice(itemList.begin(), tempList);
	}
	if (itemList.size() == 1)
	{
		front = itemList.front();
		for (DequeItem * curr = front; curr != nullptr; curr = curr->next)
		{
			rear = curr;
		}
	}
}