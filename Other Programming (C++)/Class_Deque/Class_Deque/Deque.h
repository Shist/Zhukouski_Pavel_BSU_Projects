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
	struct DequeItem // Создаем элемент дека
	{
		InfoType info;
		DequeItem *next, *prev; // Создаем указатели на следующий и предыдущий элементы
		DequeItem(const InfoType& new_info) : info(new_info), next(nullptr), prev(nullptr) {}; // Конструктор
		~DequeItem() {}; // Деструктор
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
	Deque(); // Конструктор по умолчанию (создает пустой дек)
	Deque(const Deque <InfoType>&);
	virtual ~Deque();
	Deque <InfoType>& operator = (const Deque <InfoType>&); // Присвоение
	void PushFront(const InfoType&); // Для добавления нового элемента в начало
	bool PopFront(); // Для удаления первого элемента
	const InfoType& Front() const; // Для просмотра первого элемента
	void PushBack(const InfoType&);  // Для добавления нового элемента в конец
	bool PopBack(); // Для удаления последнего элемента
	const InfoType& Back() const; // Для просмотра последнего элемента
	size_t Size() const; // Подсчитывает число элементов в деке
	void PrintDeque(ostream&, const char* = " ") const; // Вывод
	void PrintDequeInverse(ostream&, const char* = " ") const; // Вывод в обратном порядке
	void Sort(compare = defaultCompare); // Сортировка (слиянием)
};