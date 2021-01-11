#ifndef _HASHTABLE_ // Страж включения (чтобы не подключить ее повторно)
#define _HASHTABLE_

#include "dns.h"

/* ХЕШ-ТАБЛИЦА */

typedef struct Hashtable Hashtable;

Hashtable* Create_HT(int size); // Создать хеш-таблицу размера size (Конструктор)

void Insert_In_HT(Hashtable* table, const char* key, IPADDRESS value); // Вставка в хеш-таблицу

IPADDRESS Find_In_HT(Hashtable* table, const char* key); // Поиск в хеш-таблице

void Delete_HT(Hashtable* table); // Удаление хеш-таблицы (Деструктор)

#endif