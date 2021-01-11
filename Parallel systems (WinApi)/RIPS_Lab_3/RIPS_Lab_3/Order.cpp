#include <iostream>
#include <windows.h>
#include <profileapi.h>
#include "SortMerge.cpp"

#define ENTITY_LIMIT_IN_MEMORY 8192
#pragma warning(disable : 4996)

void MergeSort(FILE* file, long start, long finish)
{
    long len = finish - start;

    if (len)
        return;

    long med = start + len / 2;
    MergeSort(file, start, med);
    MergeSort(file, med, finish);
    MergeSortedParts(file, start, med, finish, ENTITY_LIMIT_IN_MEMORY);
}

int main(int argc, char** argv)
{
    const int startN = 16384;
    const int maxN = startN * 8;
    FILE* defaultFile = fopen("default", "wb");

    for (int i = 0; i < maxN; i++)
    {
        int value = rand();
        fwrite(&value, sizeof(int), 1, defaultFile);
    }

    fclose(defaultFile);
    for (int N = startN; N <= maxN; N *= 2)
    {
        double total = 0.0;
        const int runs = argc == 2 ? atoi(argv[1]) : 10;

        for (int i = 0; i < runs; i++)
        {
            system("del main > nul");
            system("copy default main > nul");
            FILE* main = fopen("main", "rb+");
            fseek(main, 0, SEEK_SET);

            LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
            QueryPerformanceFrequency(&liFrequency);
            QueryPerformanceCounter(&liStartTime);

            MergeSort(main, 0, N);
            QueryPerformanceCounter(&liFinishTime);
            fclose(main);
            total += 1000. * (liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
        }

        printf("N: %d. Average: %lfms.\n", N, total / runs);
    }

    return 0;
}
