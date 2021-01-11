#define _CRT_SECURE_NO_WARNINGS // ����������, ������ ��� �� ������������ ������������ ������� (fgets � �.�.)
#define HASH_BASE 47UL // UL - Unsigned Long

#include "dns.h"
#include <string.h>
#include "hashtable.h"
#include <stdlib.h>

// �� ������� 47, �.�. ��� ������� � ������������ ������� �� �������� ������ (32 � 64)

/* ���������� ���-������� */

typedef struct List
{
	const char* key; // �������� ���
	IPADDRESS value; // IP-�����
	struct List* next; // ��������� �� ��������� ������ � ������� ���������� ��������
} List; // � ��������� ������ �� ������, ��� ��������� �� ����������

typedef struct Hashtable
{
	int size; // ������ ���-�������
	List** arr; // ������ �������
} Hashtable;

List* Create_List_Node(const char* akey, IPADDRESS aValue) // ������� ������� ������
{
	List* result = (List*)malloc(sizeof(List));
	(*result).key = (const char*)malloc((strlen(akey) + 1) * sizeof(char));
	strcpy((char*)(*result).key, akey);
	// ������� ctrcpy �������� ��-������ akey, ������� ����������� ������� ������ � ������ ����������, �� ������� ��������� ��������� (char*)(*result).key
	(*result).value = aValue; // ��������������, ��� ������, �� ������� ���������, ���������� �������, ����� ����������� � ��� ������
	(*result).next = NULL;
	return result;
}

void Delete_List_Node(List* node) // ������ ���� ������� ������
{
	free((*node).key);
	free(node); // free - ��������� ������ � ����� ����� C
}

void Delete_List(List* start) // ��������� ������
{
	List* curr = start, * temp;
	while (curr != NULL)
	{
		temp = curr;
		curr = (*curr).next;
		Delete_List_Node(temp);
	}
}

unsigned long Hash_Function(const char* str) // ���-�������, ������������� ������
{ // ��������� ������ - �������� �����
	unsigned long result = 47;
	int i = 0;
	while (str[i] != '\0')
	{
		result = result * HASH_BASE + str[i]; // HASH_BASE = 47UL (Unsigned Long)
		i++;
	}
	return result;
}

Hashtable* Create_HT(int size) // ������� ���-������� ������� size (�����������)
{
	Hashtable* result = (Hashtable*)malloc(sizeof(Hashtable)); // malloc - �������� ������ � ����� ����� C
	(*result).arr = (List**)calloc(size, sizeof(List*)); // calloc - �������� ������ ��� �������
	(*result).size = size;
	return result;
}

void Insert_In_HT(Hashtable* table, const char* key, IPADDRESS value) // ������� � ���-�������
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

IPADDRESS Find_In_HT(Hashtable* table, const char* key) // ����� � ���-�������
{
	int position = Hash_Function(key) % (*table).size;
	List* curr = (*table).arr[position];
	while (curr != NULL)
	{
		/* ������� strcmp ���������� ������� ���� �����, key � (*curr).key
		������� � ������ �������� ������� strcmp ���������� ���������� ������ ���� ��������,
		� ������������ ��� �� ��� ���, ���� �� ����� ������� ��������� ������� ���
		�� ����� ��������� ����� ������.*/
		if (strcmp(key, (*curr).key) == 0) // ���� ������ ���������, ��...
		{
			return (*curr).value;
		}
		curr = (*curr).next;
	}
	return INVALID_IP_ADDRESS;
}

void Delete_HT(Hashtable* table) // �������� �� ���-������� (����������)
{
	for (int i = 0; i < (*table).size; i++) // ���������� �� ���������� � ��������� ��������
	{
		Delete_List((*table).arr[i]);
	}
	free((*table).arr);
	free(table);
}