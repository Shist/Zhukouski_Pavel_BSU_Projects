#include "LQueue.h"


template <typename InfoType>
void LQueue <InfoType> : Erase()
{
	while (Pop());
	size = 0;
}


template <typename InfoType>
void LQueue <InfoType> ::Clone(const LQueue& Q)
{
	QItem *tmp = Q.front;
	for (unsigned i = 0; i < Q.size; i++)
	{
		Push(tmp->info);
		tmp = tmp->next;
	}
}


LQueue::LQueue()
{
}


LQueue::~LQueue()
{
}


void LQueue::Erase()
{
	while (Pop());
	size = 0;
}
void LQueue::Clone(const LQueue& Q)
{
	//for (unsigned i=0; i<Q.size; i++)
	// Push(Q[i]);
	QItem *tmp = Q.front;
	for (unsigned i = 0; i < Q.size; i++)
	{
		Push(tmp->info);
		tmp = tmp->next;
	}
}


LQueue::LQueue(const LQueue& Q)
{
	size = 0; Clone(Q);
}
LQueue::~LQueue()
{
	Erase();
}
LQueue& LQueue::operator = (const LQueue& Q)
{
	if (this != &Q)
	{
		Erase();
		Clone(Q);
	}
	return *this;
}


void LQueue::Push(InfoType Ainfo)
{
	QItem* tmp = new QItem(Ainfo);
	if (size > 0)
		rear->next = tmp;
	else
		front = tmp;
	rear = tmp;
	size++;
}


bool LQueue::Pop()
{
	if (size == 0)
		return false;
	QItem *tmp = front;
	front = front->next;
	delete tmp;
	size--;
	if (size == 0)
		rear = NULL;
	return true;
}


InfoType LQueue::GetFirst() const
{
	if (size == 0)
		throw exception("Impossible to execute GetFirst: queue is empty");
			return front->info;
}
bool LQueue::IsEmpty() const
{
	return (size == 0);
}


unsigned LQueue::GetSize() const
{
	return size;
}
InfoType LQueue::operator [] (unsigned k) const
{
	if ((k < 0) || (k >= size))
		throw exception("Impossible to execute operator[]: invalid index");
			QItem *tmp = front;
	for (unsigned i = 0; i < k; i++)
		tmp = tmp->next;
	return tmp->info;
}


const InfoType& LQueue::GetByIndex(unsigned k) const
{
	if ((k < 0) || (k >= size))
		throw exception("Impossible to execute operator[]: invalid index");
			QItem *tmp = front;
	for (unsigned i = 0; i < k; i++)
		tmp = tmp->next;
	return tmp->info;
}
InfoType& LQueue::operator [] (unsigned k)
{
	return (InfoType&)GetByIndex(k);
}


void LQueue::Browse(void ItemWork(InfoType)) const
{
	QItem *tmp = front;
	for (unsigned i = 0; i < size; i++)
	{

		ItemWork(tmp->info);
		tmp = tmp->next;

	}
}
void LQueue::Browse(void ItemWork(InfoType&))
{
	QItem *tmp = front;
	for (unsigned i = 0; i < size; i++)
	{

		ItemWork(tmp->info);
		tmp = tmp->next;

	}
}