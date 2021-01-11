#include <stdio.h>
#include <stdlib.h>

struct WORKER2
{
	int Worker_code;				 // Код работника
	char Worker_last_name[256];		 // Фамилися работника
	char Post[256];					 // Должность
	char Gender[256];				 // Пол
	int Contract_signing_day;		 // Дата подписания контракта (день )
	int Contract_signing_month;		 // Дата подписания контракта (месяц)
	int Contract_signing_year;		 // Дата подписания контракта (год)
	int Contract_duration;			 // Срок действия контракта (в днях)
	int Salary;						 // Оклад
};

struct WORKER2* Creating_workers_array(int N)
{ // Создание массива указателей на структуры "Работник"
	struct WORKER2* Workers_arr = (struct WORKER2*)malloc(N * sizeof(struct WORKER2)); // Выделение памяти
	printf("The function of creating workers array:\n");
	for (int i = 0; i < N; i++)
	{ // Ввод элементов массива
		printf("Enter information about the %d structure:\n", (i+1));
		printf("Enter information about the worker's code: ");
		scanf_s("%d", &Workers_arr[i].Worker_code);
		printf("Enter information about the worker's last name: ");
		scanf_s("%s", &Workers_arr[i].Worker_last_name, 256);
		printf("Enter information about the worker's post: ");
		scanf_s("%s", &Workers_arr[i].Post, 256);
		printf("Enter information about the worker's gender: ");
		scanf_s("%s", &Workers_arr[i].Gender, 256);
		printf("Enter information about the worker's day of signing contract: ");
		scanf_s("%d", &Workers_arr[i].Contract_signing_day);
		printf("Enter information about the worker's month of signing contract: ");
		scanf_s("%d", &Workers_arr[i].Contract_signing_month);
		printf("Enter information about the worker's year of signing contract: ");
		scanf_s("%d", &Workers_arr[i].Contract_signing_year);
		printf("Enter information about the worker's contract duration: ");
		scanf_s("%d", &Workers_arr[i].Contract_duration);
		printf("Enter information about the worker's salary: ");
		scanf_s("%d", &Workers_arr[i].Salary);
		printf("\n\n");
	}
	return Workers_arr;
}

void Deleting_workers_array(struct WORKER2* Workers_arr)
{ // Удаление массива работников
	free(Workers_arr);
}

void Worker_Output(struct WORKER2 w)
{ // Вывод сведений о конкретном сотруднике
	printf("\n");
	printf("Information about the worker's code: %d\n", w.Worker_code);
	printf("Information about the worker's last name: %s\n", w.Worker_last_name);
	printf("Information about the worker's post: %s\n", w.Post);
	printf("Information about the worker's gender: %s\n", w.Gender);
	printf("Information about the worker's day of signing contract: %d\n", w.Contract_signing_day);
	printf("Information about the worker's month of signing contract: %d\n", w.Contract_signing_month);
	printf("Information about the worker's year of signing contract: %d\n", w.Contract_signing_year);
	printf("Information about the worker's contract duration: %d\n", w.Contract_duration);
	printf("Information about the worker's salary: %d\n", w.Salary);
	printf("\n");
}

void Employees_signed_contract_less_than_year_ago(struct WORKER2* Workers_arr, int N)
{ // Функция, дающая сведения о работниках, подписавших контракт менее года назад
	printf("The function of output the employees that signed contract less than year ago:\n");
	char check = 0;
	for (int i = 0; i < N; i++)
		if (Workers_arr[i].Contract_signing_year == 2020 ||
			(Workers_arr[i].Contract_signing_year == 2019 && Workers_arr[i].Contract_signing_month > 3) ||
			(Workers_arr[i].Contract_signing_year == 2019 && Workers_arr[i].Contract_signing_month == 3 && Workers_arr[i].Contract_signing_day > 7))
		{
			check = 1;
			Worker_Output(Workers_arr[i]);
		}
	if (!check)
		printf("No employess that signed contract less than year ago\n");
	printf("\n\n");
}

void Employees_with_double_times_contract(struct WORKER2* Workers_arr, int N)
{ // Функция, дающая сведения о работниках, которые заключали контракт хотя бы дважды
	printf("The function of output the employees that made contract at least double times:\n");
	int k = 0;
	char check = 0;
	int* ind = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (i == j)
				continue;
			char flag = 0;
			for (int t = 0; t < k; t++)
				if (ind[t] == i || ind[t] == j)
				{
					flag = 1;
					break;
				}
			if (flag)
				continue;
			if (strcmp(Workers_arr[i].Worker_last_name, Workers_arr[j].Worker_last_name) == 0)
			{
				ind[k] = i;
				k++;
				ind[k] = j;
				k++;
				check = 1;
			}
		}
	for (int i = 0; i < k; i += 2)
		Worker_Output(Workers_arr[i]);
	free(ind);
	if (!check)
		printf("No employess that made contract at least double times\n");
	printf("\n\n");
}

void Average_contract_duration_for_given_post(char post[256], struct WORKER2* Workers_arr, int N)
{ // Функция, выводящая средний срок контракта для заданной должности post
	printf("The function of output the average value of contract duration for current post:\n");
	int sum = 0;
	char check = 0;
	int k = 0;
	for (int i = 0; i < N; i++)
		if (strcmp(Workers_arr[i].Post, post) == 0)
		{
			check = 1;
			sum += Workers_arr[i].Contract_duration;
			k++;
		}
	float result = (float)sum / k;
	if (!check)
		printf("No employess with current post\n\n");
	else
		printf("The average value of contract durtion for the post %s is: %f\n\n", post, result);
}

void Amount_of_workers_men_and_women_gender(struct WORKER2* Workers_arr, int N)
{
	printf("The function of output the amount of men workers and amount of women workers:\n");
	int m = 0;
	int w = 0;
	for (int i = 0; i < N; i++)
		if (strcmp(Workers_arr[i].Gender, "man") == 0)
			m++;
		else
			w++;
	printf("The amount of men workers is: %d\n", m);
	printf("The amount of women workers is: %d\n\n", w);
}

int main(int argc, char* argv[])
{ // Дата 07.03.2020
	int g = 2020;
	int m = 3;
	int n = 7;
	printf("Current date: %d.%d.%d\n", n, m, g);
	int N = 3;
	struct WORKER2* Workers_arr = Creating_workers_array(N);
	Employees_signed_contract_less_than_year_ago(Workers_arr, N);
	Employees_with_double_times_contract(Workers_arr, N);
	Average_contract_duration_for_given_post("post", Workers_arr, N);
	Amount_of_workers_men_and_women_gender(Workers_arr, N);
	Deleting_workers_array(Workers_arr);
	return 0;
}