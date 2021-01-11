#pragma once
#pragma warning (disable: 4996)
#include <iostream>
#include <exception>
#include <cstring>
#include <list>

using namespace std;

template <typename InfoType>

class Deque
{
private:
	struct DequeItem // ������� ������� ����
	{
		InfoType info;
		DequeItem *next, *prev; // ������� ��������� �� ��������� � ���������� ��������
		DequeItem(const InfoType& new_info) : info(new_info), next(nullptr), prev(nullptr) {}; // �����������
		~DequeItem() {}; // ����������
	};
	DequeItem *front, *rear;
	size_t size;
	void erase();
	void clone(const Deque <InfoType>&);
	typedef bool(*compare)(const InfoType&, const InfoType&);
	static bool defaultCompare(const InfoType& a, const InfoType& b)
	{
		return a < b;
	}
	void MergeLists(DequeItem*, DequeItem*, DequeItem*&, compare);
public:
	Deque(); // ����������� �� ��������� (������� ������ ���)
	Deque(const Deque <InfoType>&);
	virtual ~Deque();
	Deque <InfoType>& operator = (const Deque <InfoType>&); // ����������
	void PushFront(const InfoType&); // ��� ���������� ������ �������� � ������
	bool PopFront(); // ��� �������� ������� ��������
	const InfoType& Front() const; // ��� ��������� ������� ��������
	void PushBack(const InfoType&);  // ��� ���������� ������ �������� � �����
	bool PopBack(); // ��� �������� ���������� ��������
	const InfoType& Back() const; // ��� ��������� ���������� ��������
	size_t Size() const; // ������������ ����� ��������� � ����
	void PrintDeque(ostream&, const char* = " ") const; // �����
	void PrintDequeInverse(ostream&, const char* = " ") const; // ����� � �������� �������
	void Sort(compare = defaultCompare); // ���������� (��������)
};