#include <iostream>
#include <cstring>
#include <conio.h>
#pragma warning(disable : 4996)

using namespace std;
//описание базового класса book
class book //базовый класс
{
public:
	book(const char*, const char*, int);
	void show_book(void);
private:
	char title[40]; //заголовок
	char author[40]; //автор
	int pages; //страницы
};
//реализация праметрического конструктора book базовоо класа
book::book(const char* title, const char* author, int pages)
{
	strcpy(book::title, title);
	strcpy(book::author, author);
	book::pages = pages;
}

void book::show_book(void)
{
	cout << "Заголовок:" << title << endl;
	cout << "Автор:" << author << endl;
	cout << "Количество страниц:" << pages << endl;
}

class library_card : public book
{
public:
	//конструктор класса
	library_card(const char*, const char*, int, const char*, int);
	void show_card(void); //метод класса
private:
	char catalog[40];
	int checked_out;
};

//конструктор
//после двоиточия указывается как вызывать конструктор родителя
library_card::library_card(const char* title, const char* author, int pages, const char* catalog, int checked_out) : book(title, author, pages)
{
	//наращиваем функционал в довесок к конструктору родителя
	strcpy(library_card::catalog, catalog);
	library_card::checked_out = checked_out;
}

void library_card::show_card() {

	// вызываем show_book родителя
	show_book();
	cout << "Каталог:" << catalog << endl;
	if (checked_out == 1)
		cout << "состояние крини: проверена" << endl;
	if (checked_out == 0)
		cout << "состояние крини: не проверена" << endl;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	book kniga("Книга", "Оруэл", 420);
	library_card catalog("Книги", "dasdas", 1000, "test", 1);
	kniga.show_book();
	catalog.show_card();
	_getch();
	return 0;
}