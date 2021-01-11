#include <iostream>
#include <cstring>
#include <conio.h>
#pragma warning(disable : 4996)

using namespace std;
//�������� �������� ������ book
class book //������� �����
{
public:
	book(const char*, const char*, int);
	void show_book(void);
private:
	char title[40]; //���������
	char author[40]; //�����
	int pages; //��������
};
//���������� ��������������� ������������ book ������� �����
book::book(const char* title, const char* author, int pages)
{
	strcpy(book::title, title);
	strcpy(book::author, author);
	book::pages = pages;
}

void book::show_book(void)
{
	cout << "���������:" << title << endl;
	cout << "�����:" << author << endl;
	cout << "���������� �������:" << pages << endl;
}

class library_card : public book
{
public:
	//����������� ������
	library_card(const char*, const char*, int, const char*, int);
	void show_card(void); //����� ������
private:
	char catalog[40];
	int checked_out;
};

//�����������
//����� ��������� ����������� ��� �������� ����������� ��������
library_card::library_card(const char* title, const char* author, int pages, const char* catalog, int checked_out) : book(title, author, pages)
{
	//���������� ���������� � ������� � ������������ ��������
	strcpy(library_card::catalog, catalog);
	library_card::checked_out = checked_out;
}

void library_card::show_card() {

	// �������� show_book ��������
	show_book();
	cout << "�������:" << catalog << endl;
	if (checked_out == 1)
		cout << "��������� �����: ���������" << endl;
	if (checked_out == 0)
		cout << "��������� �����: �� ���������" << endl;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	book kniga("�����", "�����", 420);
	library_card catalog("�����", "dasdas", 1000, "test", 1);
	kniga.show_book();
	catalog.show_card();
	_getch();
	return 0;
}