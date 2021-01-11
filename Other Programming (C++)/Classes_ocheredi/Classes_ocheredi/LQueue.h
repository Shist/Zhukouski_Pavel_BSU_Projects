#pragma once

#include <iostream>
using namespace std;

typedef int InfoType;
template <typename InfoType = int>
class LQueue
{
private:
	struct QItem
	{
		InfoType info;
		QItem* next;
		QItem(InfoType Ainfo) : info(Ainfo), next(NULL) {}
	};
	QItem *front, *rear;
	unsigned size;

	void Erase();
	void Clone(const LQueue &);

public:
	LQueue() : front(NULL), rear(NULL), size(0) {};
	LQueue(const LQueue&);
	~LQueue();
	LQueue& operator = (const LQueue&);
	void Push(InfoType AInfo);
	bool Pop();
	InfoType GetFirst() const;
	bool IsEmpty()const;
	unsigned GetSize() const;
	InfoType operator [] (unsigned) const;
	const InfoType& GetByIndex(unsigned k) const;
	InfoType& operator [] (unsigned k);
	void Browse(void ItemWork(InfoType)) const;
	void Browse(void ItemWork(InfoType&));
};