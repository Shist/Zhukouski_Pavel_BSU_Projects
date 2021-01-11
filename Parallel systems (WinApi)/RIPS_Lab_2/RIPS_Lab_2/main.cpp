#include <iostream>
#include <windows.h>
#include <time.h>

int** mtrx;
int* vct;
int* result;

int N = 1000;
const int pr_num = 2;

struct ThreadInfo
{
	int begin;
	int end;
	int step;
	int result;
};

void GenerateRandMtrx(int** Mtrx, int length1, int length2)
{
	for (int i = 0; i < length1; ++i)
		for (int j = 0; j < length2; ++j)
			Mtrx[i][j] = rand() % 10;
}

void OutputMatrix(int** Mtrx, int length1, int length2)
{
	for (int i = 0; i < length1; ++i)
	{
		for (int j = 0; j < length2; ++j)
			printf(" %d", Mtrx[i][j]);

		printf("\n");
	}
}


void OneThreadRealization(int** mtrx, int* vct, int length, int* result)
{
	for (int i = 0; i < length; i++)
	{
		result[i] = 0;
		for (int j = 0; j < length; j++)
			result[i] += vct[j] * mtrx[i][j];
	}
}

DWORD WINAPI OneThreadCalculation(LPVOID thrParam)
{
	ThreadInfo* thr = (ThreadInfo*)thrParam;

	for (int i = thr->begin; i < thr->end; i += thr->step)
	{
		int sum = 0;
		for (int j = 0; j < N; j++)
			sum += vct[j] * mtrx[i][j];
		result[i] = sum;
	}

	return 0;
}

int ContinuousRowsetsRealization()
{
	ThreadInfo thrs[pr_num];
	HANDLE hThreads[pr_num];

	int step = N / pr_num;

	for (int k = 0; k < pr_num; ++k)
	{
		thrs[k].begin = k * step;
		if (k != pr_num - 1)
			thrs[k].end = (k + 1) * step;
		else
			thrs[k].end = N;
		thrs[k].step = 1;

		hThreads[k] = CreateThread(NULL,
			0,
			OneThreadCalculation,
			(LPVOID) & (thrs[k]),
			0,
			NULL);

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

int CircularRowsetsRealization()
{
	ThreadInfo thrs[pr_num];
	HANDLE hThreads[pr_num];

	int step = N / pr_num;

	for (int k = 0; k < pr_num; ++k)
	{
		thrs[k].begin = k * step;
		thrs[k].end = N;
		thrs[k].step = pr_num;

		hThreads[k] = CreateThread(NULL, 
			0, 
			OneThreadCalculation, 
			(LPVOID) & (thrs[k]), 
			0, 
			NULL);

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

	mtrx = new int* [N];
	for (int i = 0; i < N; i++)
		mtrx[i] = new int[N];

	vct = new int[N];

	printf("mtrx: \n");
	GenerateRandMtrx(mtrx, N, N);
	OutputMatrix(mtrx, N, N);

	printf("\nvctor: \n");
	GenerateRandMtrx(&vct, 1, N);
	OutputMatrix(&vct, 1, N);

	result = new int[N];

	LARGE_INTEGER liFrequency, libeginTime, liendTime;
	double dElapsedTime;
	QueryPerformanceFrequency(&liFrequency);
	QueryPerformanceCounter(&libeginTime);

	CircularRowsetsRealization();

	QueryPerformanceCounter(&liendTime);
	dElapsedTime = 1000.0 * (liendTime.QuadPart - libeginTime.QuadPart) / liFrequency.QuadPart;
	printf("\n%f", dElapsedTime);

	printf("\nresult: \n");
	OutputMatrix(&result, 1, N);

	delete[] result;

	delete[] vct;

	for (int i = 0; i < N; i++)
		delete[] mtrx[i];

	delete[] mtrx;

	return 0;
}