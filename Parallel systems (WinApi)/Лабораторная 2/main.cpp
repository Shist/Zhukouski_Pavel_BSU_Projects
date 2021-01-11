// OneThreadApp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <stdio.h>

int n = 1000;
const int pr_num = 2;
int **matrix;
int *vect;
int* answer;

void InitRand(int **B, int size1, int size2)
{
	for (int i = 0; i < size1; ++i)
		for (int j = 0; j < size2; ++j)
			B[i][j] = rand()%10;
}

void PrintArray(int **B, int size1, int size2)
{
	for (int i = 0; i < size1; ++i)
	{
		for (int j = 0; j < size2; ++j)
			printf(" %d", B[i][j]);

		printf("\n");
	}
}


void taskOnOneThread(int** matrix, int* vect, int size, int* answer)
{
	for (int i = 0; i < size; i++)
	{
		answer[i] = 0;
		for (int j = 0; j < size; j++)
		{
			answer[i] += vect[j] * matrix[i][j];
		}
	}
}

struct SThreadParam
{
	int start;
	int finish;
	int step;
	int answer;
};
DWORD WINAPI ThreadFunction(LPVOID pvParam)
{
	SThreadParam* param = (SThreadParam*)pvParam;

	for (int i = param->start; i < param->finish; i += param->step)
	{
		int sum = 0;
		for (int j = 0; j < n; j++)
		{
			sum += vect[j] * matrix[i][j];
		}
		answer[i] = sum;
	}

	return 0;
}

int task32()
{
	HANDLE hThreads[pr_num];
	SThreadParam params[pr_num];

	int step = n / pr_num;
	for (int k = 0; k < pr_num; ++k)
	{
		params[k].start = k*step;
		if (k != pr_num - 1)
			params[k].finish = (k + 1)*step;
		else
			params[k].finish = n;
		params[k].step = 1;

		hThreads[k] = CreateThread(NULL, 0, ThreadFunction, (LPVOID)&(params[k]), 0, NULL);
		if (hThreads[k] == NULL) 
		{
			printf("Create Thread %d Error=%d\n", k, GetLastError());
			return -1;
		}
	}
	WaitForMultipleObjects(pr_num, hThreads, TRUE, INFINITE);
	for (int k = 0; k < pr_num; ++k)
		CloseHandle(hThreads[k]);
	return 0;
}

int task33()
{
	HANDLE hThreads[pr_num];
	SThreadParam params[pr_num];

	int step = n / pr_num;
	for (int k = 0; k < pr_num; ++k)
	{
		params[k].start = k * step;
		params[k].finish = n;
		params[k].step = pr_num;

		hThreads[k] = CreateThread(NULL, 0, ThreadFunction, (LPVOID)&(params[k]), 0, NULL);
		if (hThreads[k] == NULL) 
		{
			printf("Create Thread %d Error=%d\n", k, GetLastError());
			return -1;
		}
	}
	WaitForMultipleObjects(pr_num, hThreads, TRUE, INFINITE);
	for (int k = 0; k < pr_num; ++k)
		CloseHandle(hThreads[k]);
	return 0;
}

int main()
{
	srand(time(0));

	matrix = new int*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];

	vect = new int[n];
	
	printf("Matrix: \n");
	InitRand(matrix, n, n);
	//PrintArray(matrix, n, n);

	printf("\nVector: \n");
	InitRand(&vect, 1, n);
	//PrintArray(&vect, 1, n);

	answer = new int[n];

	LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
	double dElapsedTime;
	QueryPerformanceFrequency(&liFrequency);
	QueryPerformanceCounter(&liStartTime);

	task33();

	QueryPerformanceCounter(&liFinishTime);
	dElapsedTime = 1000.0*(liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
	printf("\n%f", dElapsedTime);

	//printf("\nAnswer: \n");
	//PrintArray(&answer, 1, n);

	delete[] answer;

	delete[] vect;

	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
}