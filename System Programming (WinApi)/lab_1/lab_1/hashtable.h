#ifndef _HASHTABLE_ // ����� ��������� (����� �� ���������� �� ��������)
#define _HASHTABLE_

#include "dns.h"

/* ���-������� */

typedef struct Hashtable Hashtable;

Hashtable* Create_HT(int size); // ������� ���-������� ������� size (�����������)

void Insert_In_HT(Hashtable* table, const char* key, IPADDRESS value); // ������� � ���-�������

IPADDRESS Find_In_HT(Hashtable* table, const char* key); // ����� � ���-�������

void Delete_HT(Hashtable* table); // �������� ���-������� (����������)

#endif