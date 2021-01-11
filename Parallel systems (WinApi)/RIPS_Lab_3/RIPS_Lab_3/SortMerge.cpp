#include <cstring>
#include <cstdio>
#include <string>

#pragma warning(disable : 4996)

void MergeSortedPartsInCash(FILE* file, long start, long med, long finish)
{
    int* buffer = new int[finish - start];
    fseek(file, start * sizeof(int), SEEK_SET);
    fread(buffer, sizeof(int), finish - start, file);
    fseek(file, start * sizeof(int), SEEK_SET);

    int* firstPart = buffer;
    int* secondPart = buffer + (med - start);
    int* firstEnd = secondPart;
    int* secondEnd = buffer + (finish - start);

    while (start < finish)
    {
        if (firstPart >= firstEnd)
        {
            fwrite(secondPart, sizeof(int), 1, file);
            ++secondPart;
        }
        else if (secondPart >= secondEnd)
        {
            fwrite(firstPart, sizeof(int), 1, file);
            ++firstPart;
        }
        else
        {
            if (*firstPart < *secondPart)
            {
                fwrite(firstPart, sizeof(int), 1, file);
                ++firstPart;
            }
            else
            {
                fwrite(secondPart, sizeof(int), 1, file);
                ++secondPart;
            }
        }

        start++;
    }

    delete[] buffer;
}

void MergeSortedPartsInFiles(FILE* file, long start, long med, long finish)
{
    FILE* first = fopen((std::to_string(start) + "_" + std::to_string(med)).c_str(), "wb+");
    FILE* second = fopen((std::to_string(med) + "_" + std::to_string(finish)).c_str(), "wb+");

    int firstValue;
    int secondValue;

    fseek(file, start * sizeof(int), SEEK_SET);
    for (int i = start; i < finish; ++i)
    {
        fread(&firstValue, sizeof(int), 1, file);
        fwrite(&firstValue, sizeof(int), 1, i < med ? first : second);
    }

    fseek(file, start * sizeof(int), SEEK_SET);
    fseek(first, 0, SEEK_SET);
    fseek(second, 0, SEEK_SET);

    long firstLeft = med - start;
    long secondLeft = finish - med;

    while (start < finish)
    {
        if (firstLeft == 0)
        {
            fread(&secondValue, sizeof(int), 1, second);
            fwrite(&secondValue, sizeof(int), 1, file);
        }
        else if (secondLeft == 0)
        {
            fread(&firstValue, sizeof(int), 1, first);
            fwrite(&firstValue, sizeof(int), 1, file);
        }
        else
        {
            fread(&firstValue, sizeof(int), 1, first);
            fread(&secondValue, sizeof(int), 1, second);

            if (firstValue < secondValue)
            {
                fwrite(&firstValue, sizeof(int), 1, file);
                fseek(second, sizeof(int), SEEK_CUR);
                --firstLeft;
            }
            else
            {
                fwrite(&secondValue, sizeof(int), 1, file);
                fseek(first, sizeof(int), SEEK_CUR);
                --secondLeft;
            }
        }

        start++;
    }

    fclose(first);
    fclose(second);
}

void MergeSortedParts(FILE* file, long start, long med, long finish, long memoryLimit)
{
    if (finish - start < memoryLimit)
        MergeSortedPartsInCash(file, start, med, finish);
    else
        MergeSortedPartsInFiles(file, start, med, finish);
}
