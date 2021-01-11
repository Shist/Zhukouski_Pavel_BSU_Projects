#include <iostream>
#include <windows.h>
#include <profileapi.h>
#include <vector>
#include <process.h>

#include "SortMerge.cpp"
#include "RequestQueue.cpp"

#define ENTITY_LIMIT_IN_MEMORY 8192

bool allTasksGenerated = false;

int T;

void MergeSortOrder(FILE* file, long start, long finish)
{
    long len = finish - start;

    if (len)
        return;

    long med = start + len / 2;
    MergeSortOrder(file, start, med);
    MergeSortOrder(file, med, finish);
    MergeSortedParts(file, start, med, finish, ENTITY_LIMIT_IN_MEMORY / T);
}

unsigned int __stdcall MergeSortSorterThread(void* arg)
{
    auto* queue = (TaskQueue*)arg;
    Task task;
    FILE* main = fopen("main", "rb+");

    while (true)
    {
        if (!queue->Remove(&task, 3))
            if (allTasksGenerated)
                break;
            else
                continue;

        if (task.firstDepfinishency != INVALID_HANDLE_VALUE)
            WaitForSingleObject(task.firstDepfinishency, INFINITE);

        if (task.secondDepfinishency != INVALID_HANDLE_VALUE)
            WaitForSingleObject(task.secondDepfinishency, INFINITE);

        if (task.seq)
            MergeSortOrder(main, task.start, task.finish);
        else
            MergeSortedParts(main, task.start, task.med, task.finish, ENTITY_LIMIT_IN_MEMORY / T);

        SetEvent(task.ready);
        CloseHandle(task.firstDepfinishency);
        CloseHandle(task.secondDepfinishency);
    }

    fclose(main);
    return 0;
}

HANDLE MergeSortTaskGenerator(long start, long finish, TaskQueue* output, int parallelBarrier)
{
    int len = finish - start;

    if (len)
        return INVALID_HANDLE_VALUE;

    long med = start + len / 2;
    HANDLE readyEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (len > parallelBarrier)
    {
        HANDLE firstDep = MergeSortTaskGenerator(start, med, output, parallelBarrier);
        HANDLE secondDep = MergeSortTaskGenerator(med, finish, output, parallelBarrier);
        output->Insert({ 0, start, med, finish, firstDep, secondDep, readyEvent });
    }
    else
        output->Insert({ 1, start, med, finish, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, readyEvent });

    return readyEvent;
}

typedef struct
{
    long start;
    long finish;
    TaskQueue* output;
    int parallelBarrier;
} GeneratorArgs;

unsigned int __stdcall MergeSortTaskGeneratorThread(void* arg)
{
    auto* arguments = (GeneratorArgs*)arg;
    allTasksGenerated = false;
    HANDLE lastEvent = MergeSortTaskGenerator(
        arguments->start, arguments->finish, arguments->output, arguments->parallelBarrier);

    allTasksGenerated = true;
    WaitForSingleObject(lastEvent, INFINITE);
    CloseHandle(lastEvent);
    return 0;
}

/// @param parallelBarrier Parts that are lower that this barrier will be sorted sequentially.
void MergeSort(long start, long finish, int parallelBarrier)
{
    auto* threads = new HANDLE[T + 1];
    GeneratorArgs args;
    TaskQueue taskQueue(100);

    args.start = start;
    args.finish = finish;
    args.output = &taskQueue;
    args.parallelBarrier = parallelBarrier;

    threads[0] = (HANDLE)_beginthreadex(NULL, 0, MergeSortTaskGeneratorThread, &args, 0, NULL);
    for (int i = 1; i < T + 1; ++i)
    {
        threads[i] = (HANDLE)_beginthreadex(NULL, 0, MergeSortSorterThread, &taskQueue, 0, NULL);
    }

    WaitForMultipleObjects(T + 1, threads, TRUE, INFINITE);
    delete[] threads;
}

int main(int argc, char** argv)
{
    const int startN = 16384;
    const int maxN = startN * 8;
    FILE* defaultFile = fopen("default", "wb");

    for (int i = 0; i < maxN; ++i)
    {
        int value = rand();
        fwrite(&value, sizeof(int), 1, defaultFile);
    }

    fclose(defaultFile);
    for (T = 2; T <= 16; T *= 2)
    {
        printf("T: %d.\n", T);
        for (int N = startN; N <= maxN; N *= 2)
        {
            double total = 0.0;
            const int runs = argc == 2 ? atoi(argv[1]) : 10;

            for (int i = 0; i < runs; ++i)
            {
                system("del main > nul");
                system("copy default main > nul");

                LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
                QueryPerformanceFrequency(&liFrequency);
                QueryPerformanceCounter(&liStartTime);

                MergeSort(0, N, ENTITY_LIMIT_IN_MEMORY / T);
                QueryPerformanceCounter(&liFinishTime);
                total += 1000. * (liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
            }

            printf("    N: %d. Average: %lfms.\n", N, total / runs);
        }
    }

    return 0;
}
