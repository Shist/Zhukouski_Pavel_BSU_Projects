#include "pch.h"
#include "Mum_Dad.h"

atomic<int> Mum_Dad::Whole_Count = 15; // �����������, � ��� ����� ����������� �������� 15 ���������� �����
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
	cout << "����� \"" << thrdName << "\" �����." << endl;
	x.unlock();
	while (thr_count < amount && Whole_Count > 0)
	{
		Sleep(time);
		if (Whole_Count <= 0) // ���� ����� ���������� �����������, �������
			break;
		Whole_Count--;
		x.lock();
		cout << thrdName << "(" << (thr_count + 1) << "/" << amount << ")" << endl;
		x.unlock();
		thr_count++;
	}
	x.lock();
	cout << "����� \"" << thrdName << "\" ��������." << endl;
	if (amount == thr_count)
		cout << "������� ����������: \"����������� ����������� ���������� �������.\"" << endl;
	if (Whole_Count <= 0)
		cout << "������� ����������: \"����������� ����� ���������� ���������� ��� ���� ��������.\"" << endl;
	x.unlock();
}

Mum_Dad::~Mum_Dad()
{
}