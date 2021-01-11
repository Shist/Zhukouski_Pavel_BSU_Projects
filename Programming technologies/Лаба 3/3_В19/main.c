//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*«Международная компания»: (Вариант 19)
название; интернет сайт; адрес главного офиса (почтовый индекс, страна,
область, район, город, улица, дом, квартира) продолжительность пребывания на
мировом рынке; количество сотрудников; количество филиалов в Европе.

Вывести международные компании, количество сотрудников у которых больше
10000.*/

typedef struct International_Company
{
	char name[256];
	char internet_site[256];
	int mail_index;
	char country[256];
	char region[256];
	char district[256];
	char town[256];
	char street[256];
	int house;
	int flat;
	int foundation_year;
	int length_of_stay_in_the_global_market;
	int employees_num;
	int europe_branches_num;
}International_Company;

typedef
struct ListNode
{
	International_Company *info;
	struct ListNode *next;
}
ListNode;

void fgetsWithoutNewline(char *str, int size, FILE *file)
{
	str[1] = '\0';
	fgets(str, size, file);
	int len = strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
}

void PrintIntComp(International_Company *comp)
{
	printf("Company's name: %s\n", comp->name);
	printf("Company's internet site: %s\n", comp->internet_site);
	printf("Company's mail_index: %d\n", comp->mail_index);
	printf("Company's country: %s\n", comp->country);
	printf("Company's region: %s\n", comp->region);
	printf("Company's district: %s\n", comp->district);
	printf("Company's town: %s\n", comp->town);
	printf("Company's street: %s\n", comp->street);
	printf("Company's house: %d\n", comp->house);
	printf("Company's flat: %d\n", comp->flat);
	printf("Company's foundation year: %d\n", comp->foundation_year);
	printf("Company's length of stay in the global market: %d\n", comp->length_of_stay_in_the_global_market);
	printf("Company's number of employees: %d\n", comp->employees_num);
	printf("Company's number of Europe branches: %d\n", comp->europe_branches_num);
}

int ReadIntComp(International_Company *comp)
{
	int status;
	fgetsWithoutNewline(comp->name, 256, stdin);
	if (feof(stdin))
		return EOF;
	fgetsWithoutNewline(comp->internet_site, 256, stdin);
	if (feof(stdin))
		return EOF;
	status = scanf("%d\n", &(comp->mail_index));
	if (status == EOF)
		return EOF;
	fgetsWithoutNewline(comp->country, 256, stdin);
	if (feof(stdin))
		return EOF;
	fgetsWithoutNewline(comp->region, 256, stdin);
	if (status == EOF)
		return EOF;
	fgetsWithoutNewline(comp->district, 256, stdin);
	if (status == EOF)
		return EOF;
	fgetsWithoutNewline(comp->town, 256, stdin);
	if (status == EOF)
		return EOF;
	fgetsWithoutNewline(comp->street, 256, stdin);
	if (status == EOF)
		return EOF;
	status = scanf("%d\n", &(comp->house));
	if (status == EOF)
		return EOF;
	status = scanf("%d\n", &(comp->flat));
	if (status == EOF)
		return EOF;
	status = scanf("%d\n", &(comp->foundation_year));
	if (status == EOF)
		return EOF;
	status = scanf("%d\n", &(comp->length_of_stay_in_the_global_market));
	if (status == EOF)
		return EOF;
	status = scanf("%d\n", &(comp->employees_num));
	if (status == EOF)
		return EOF;
	status = scanf("%d\n", &(comp->europe_branches_num));
	if (status == EOF)
		return EOF;
	return 0;
}

ListNode * CreateListFromInput()
{
	International_Company *comp = malloc(sizeof(International_Company));
	ListNode *head = NULL;
	while (ReadIntComp(comp) != EOF)
	{
		ListNode *curr = malloc(sizeof(ListNode));

		curr->info = comp;
		curr->next = head;
		head = curr;

		comp = malloc(sizeof(International_Company));
	}
	free(comp);
	return head;
}

void TraverseList(ListNode *head)
{
	while (head != NULL)
	{
		PrintIntComp(head->info);
		head = head->next;
	}
}

void IntComp_with_many_employees(ListNode *head)
{
	char check = 0;
	while (head != NULL)
	{
		if (head->info->employees_num > 10000)
		{
			check = 1;
			PrintIntComp(head->info);
		}
		head = head->next;
	}
	if (!check)
		printf("There are no any companies with more than 10000 employees in the list!\n");
}

void DestroyList(ListNode *head)
{
	ListNode *temp = NULL;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

int main(int argc, char **argv)
{
	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);
	ListNode *listHead = CreateListFromInput();
	puts("The list of companies:");
	TraverseList(listHead);
	puts("The companies that have more than 10000 employes:");
	IntComp_with_many_employees(listHead);
	puts("Deleting the list...");
	DestroyList(listHead);
	return 0;
}