#define _CRT_SECURE_NO_WARNINGS // Подключаем, потому что мы использовали небезопасные функции (fgets и т.д.)
#define HASH_BASE 47UL // UL - Unsigned Long

#include "dns.h"
#include <string.h>
#include "hashtable.h"
#include <stdlib.h>

// Мы выбрали 47, т.к. оно простое и относительно далекое от степеней двойки (32 и 64)

/* РЕАЛИЗАЦИЯ ХЕШ-ТАБЛИЦЫ */

typedef struct List
{
	const char* key; // Доменное имя
	IPADDRESS value; // IP-адрес
	struct List* next; // Указатель на следующий список с данными следующего элемента
} List; // В противном случае он скажет, что структуры не существует

typedef struct Hashtable
{
	int size; // Размер хеш-таблицы
	List** arr; // Массив списков
} Hashtable;

List* Create_List_Node(const char* akey, IPADDRESS aValue) // Создать элемент списка
{
	List* result = (List*)malloc(sizeof(List));
	(*result).key = (const char*)malloc((strlen(akey) + 1) * sizeof(char));
	strcpy((char*)(*result).key, akey);
	// Функция ctrcpy копирует Си-строку akey, включая завершающий нулевой символ в строку назначения, на которую ссылается указатель (char*)(*result).key
	(*result).value = aValue; // Предполагается, что строка, на которую ссылаемся, достаточно длинная, чтобы скопировать в нее другую
	(*result).next = NULL;
	return result;
}

void Delete_List_Node(List* node) // Убрать один элемент списка
{
	free((*node).key);
	free(node); // free - почистить память в стиле языка C
}

void Delete_List(List* start) // Почистить список
{
	List* curr = start, * temp;
	while (curr != NULL)
	{
		temp = curr;
		curr = (*curr).next;
		Delete_List_Node(temp);
	}
}

unsigned long Hash_Function(const char* str) // Хеш-функция, преобразующая строку
{ // Вставляем строку - получаем число
	unsigned long result = 47;
	int i = 0;
	while (str[i] != '\0')
	{
		result = result * HASH_BASE + str[i]; // HASH_BASE = 47UL (Unsigned Long)
		i++;
	}
	return result;
}

Hashtable* Create_HT(int size) // Создать хеш-таблицу размера size (Конструктор)
{
	Hashtable* result = (Hashtable*)malloc(sizeof(Hashtable)); // malloc - выделить память в стиле языка C
	(*result).arr = (List**)calloc(size, sizeof(List*)); // calloc - выделяет память для массива
	(*result).size = size;
	return result;
}

void Insert_In_HT(Hashtable* table, const char* key, IPADDRESS value) // Вставка в хеш-таблицу
{
	List* node = Create_List_Node(key, value);
	int position = Hash_Function(key) % table->size;
	List* curr = table->arr[position];
	List* prev = NULL;
	while (curr != NULL)
	{
		prev = curr;
		curr = (*curr).next;
	}
	if (prev == NULL)
	{
		(*table).arr[position] = node;
	}
	else
	{
		(*prev).next = node;
	}
}

IPADDRESS Find_In_HT(Hashtable* table, const char* key) // Поиск в хеш-таблице
{
	int position = Hash_Function(key) % (*table).size;
	List* curr = (*table).arr[position];
	while (curr != NULL)
	{
		/* Функция strcmp сравнивает символы двух строк, key и (*curr).key
		Начиная с первых символов функция strcmp сравнивает поочередно каждую пару символов,
		и продолжается это до тех пор, пока не будут найдены различные символы или
		не будет достигнут конец строки.*/
		if (strcmp(key, (*curr).key) == 0) // Если строки совпадают, то...
		{
			return (*curr).value;
		}
		curr = (*curr).next;
	}
	return INVALID_IP_ADDRESS;
}

void Delete_HT(Hashtable* table) // Удаление из хеш-таблицы (Деструктор)
{
	for (int i = 0; i < (*table).size; i++) // Пробежимся по массивчику и поудаляем списочки
	{
		Delete_List((*table).arr[i]);
	}
	free((*table).arr);
	free(table);
}