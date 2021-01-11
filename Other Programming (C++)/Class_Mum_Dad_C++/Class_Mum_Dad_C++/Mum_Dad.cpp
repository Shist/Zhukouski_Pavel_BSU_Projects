#include "pch.h"
#include "Mum_Dad.h"

atomic<int> Mum_Dad::Whole_Count = 15; // Предположим, у нас может выполниться максимум 15 повторений всего
mutex Mum_Dad::x;

Mum_Dad::Mum_Dad(string name, int am, int t)
{
	thr_count = 0;
	thrdName = name;
	amount = am;
	time = t;
}

void Mum_Dad::Run()
{
	x.lock();
	cout << "Поток \"" << thrdName << "\" начат." << endl;
	x.unlock();
	while (thr_count < amount && Whole_Count > 0)
	{
		Sleep(time);
		if (Whole_Count <= 0) // Если общие повторения закончились, выходим
			break;
		Whole_Count--;
		x.lock();
		cout << thrdName << "(" << (thr_count + 1) << "/" << amount << ")" << endl;
		x.unlock();
		thr_count++;
	}
	x.lock();
	cout << "Поток \"" << thrdName << "\" завершен." << endl;
	if (amount == thr_count)
		cout << "Причина завершения: \"Закончились собственные повторения объекта.\"" << endl;
	if (Whole_Count <= 0)
		cout << "Причина завершения: \"Закончилось общее количество повторений для всех объектов.\"" << endl;
	x.unlock();
}

Mum_Dad::~Mum_Dad()
{
}