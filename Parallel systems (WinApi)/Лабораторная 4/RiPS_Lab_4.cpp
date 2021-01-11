#define HAVE_STRUCT_TIMESPEC
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <queue>
#include <stdio.h>
#include <time.h>
#include "pthread.h"
#include <time.h>
#include <stdlib.h>

#define SMALL_SPLITED_FILE_NAME ".tmp"
#define INPUT_FILE "input.txt"
#define SMALL_FILE_SIZE 1000
#define NUM_OF_THREADS 3

using namespace std;

char* OUTPUT_FILE;

// Буфер для разделенных файлов
std::queue<int> buffer;

pthread_mutex_t mutex;
pthread_cond_t cond_merge;

// Проверка того, закончился ли распределённый поток
bool finishSplited = false;

void bubble_sort(int* arr, int n) 
{
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				std::swap(arr[j], arr[j + 1]);
}

void merge_two_files_in_one(char* name1, char* name2, char* outname)
{
	// Поток для чтения file1
	std::fstream in1(name1);

	// Поток для чтения file2
	std::fstream in2(name2);

	// Поток для записи выходного файла
	std::ofstream out(outname);

	// Размер входных файлов
	int small_file_size1, small_file_size2;

	// Переменная для чтения чисел
	int number1, number2;

	in1 >> small_file_size1;
	in2 >> small_file_size2;
	in1 >> number1;
	in2 >> number2;

	// Общее количество обоих файлов
	int count = small_file_size1 + small_file_size2;

	out << count << "\n";

	int peek1 = small_file_size1 - 1;
	int peek2 = small_file_size2 - 1;

	for (int i = 0; i < count; ++i)
	{
		if (!peek1)
		{
			out << number2 << " ";
			in2 >> number2;
			continue;
		}
		if (!peek2)
		{
			out << number1 << " ";
			in1 >> number1;
			continue;
		}

		// Сравнение двух чисел
		if (number1 > number2)
		{
			out << number2 << " ";
			in2 >> number2;
			peek2--;
		}
		else
		{
			out << number1 << " ";
			in1 >> number1;
			peek1--;
		}
	}

	in1.close();
	in2.close();
	out.close();
}

void *split(void *data) 
{
	char * input = (char*)data;
	std::ifstream fin(input);

	char* name = new char[20];
	int number;
	int big_file_size = 0;
	fin >> big_file_size;

	int small_file_count = big_file_size / SMALL_FILE_SIZE;
	int residue = big_file_size - small_file_count * SMALL_FILE_SIZE;
	if (residue)
		small_file_count += 1;

	for (int i = 0; i < small_file_count; ++i) 
	{
		sprintf(name, "%d%s", i, SMALL_SPLITED_FILE_NAME);
		int size = ((i == small_file_count - 1 && residue != 0) ? residue : SMALL_FILE_SIZE);
		int* arr = new int[size];
		for (int i = 0; i < size; ++i) 
		{
			fin >> number;
			arr[i] = number;
		}
		std::ofstream out(name);
		out << size << "\n";
		bubble_sort(arr, size);
		for (int j = 0; j < size; j++)
			out << arr[j] << " ";

		out.close();
	
		pthread_mutex_lock(&mutex);
		buffer.push(i);
		pthread_mutex_unlock(&mutex);

		pthread_cond_signal(&cond_merge);
		
	}

	do 
	{
		pthread_cond_signal(&cond_merge);
	}
	while(!buffer.empty());

	pthread_cond_signal(&cond_merge);

	finishSplited = true;

	delete name;
	pthread_exit(NULL);
}

void* merge(void *data) 
{
	int n = *((int*)data);
	char* name1 = new char[20];
	char* buf_name = new char[20];
	char* rez_name = new char[20];

	char* output = new char[20];
	
	sprintf(output, "output%d.txt", n);

	sprintf(rez_name, "rez%d.tmp", n);
	sprintf(buf_name, "buf%d.tmp", n);

	std::ofstream out(buf_name);
	out << 0;
	out.close();

	int file1;
	bool isFinished = false;

	while(!isFinished) 
	{
		pthread_mutex_lock(&mutex);
		
		if(!finishSplited)
			pthread_cond_wait(&cond_merge, &mutex);

		if(!buffer.empty()) 
		{
			file1 = buffer.front();
			buffer.pop();
			pthread_mutex_unlock(&mutex);

			sprintf(name1, "%d%s", file1, SMALL_SPLITED_FILE_NAME);
			merge_two_files_in_one(name1, buf_name, rez_name);
			remove(name1);
			remove(buf_name);
			rename(rez_name, buf_name);
	
		} 
		else 
		{
			isFinished = true;			
			pthread_mutex_unlock(&mutex);
		}
	}

	remove(output);
	rename(buf_name, output);

	delete name1;
	delete buf_name;
	delete rez_name;

	pthread_exit(NULL);
}

int main() {
	OUTPUT_FILE = new char[20];
	sprintf(OUTPUT_FILE, "output.txt");

	pthread_attr_t attr;
	pthread_t sortThread;
	pthread_t* threadsArr = new pthread_t[NUM_OF_THREADS];
	int sortThreadCreateResult, mergeThreadCreateResult;

  	pthread_attr_init(&attr);
  	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_merge, NULL);

	struct timespec startTime, finishTime;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTime);

	unsigned int start_time = clock();

	sortThreadCreateResult = pthread_create(&sortThread, &attr, split, (void*)INPUT_FILE);

	int* nums = new int[NUM_OF_THREADS];
	for(int i = 1; i <= NUM_OF_THREADS; i++)
	{	
		nums[i-1] = i;
		mergeThreadCreateResult = pthread_create(&(threadsArr[i-1]), &attr, merge, (void*)&(nums[i-1]));
	}

	pthread_join(sortThread, NULL);

	for(int i = 1; i <= NUM_OF_THREADS; i++)
	{
		pthread_join(threadsArr[i-1], NULL);
	}

	char* output1 = new char[20];
	char* output2 = new char[20];

	sprintf(output1, "output%d.txt", 1);		
	sprintf(output2, "output%d.txt", 2);

	merge_two_files_in_one(output1, output2, OUTPUT_FILE);
	remove(output1);
	remove(output2);

	for(int i = 3; i <= NUM_OF_THREADS; i++)
	{		
		sprintf(output2, "output%d.txt", i);

		merge_two_files_in_one(OUTPUT_FILE, output2, OUTPUT_FILE);

		remove(output2);
	}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &finishTime);

	double resultTime = (finishTime.tv_sec + 1e-9*finishTime.tv_nsec)
                     - (startTime.tv_sec + 1e-9*startTime.tv_nsec);

	printf("Elapsed time: %.5f s.\n", resultTime);

	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_merge);

	return 0;
}


