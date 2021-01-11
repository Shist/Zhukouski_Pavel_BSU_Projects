#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include "dns.h"

typedef struct _DNS_ENTRY
{
    char* domainName;
    IPADDRESS    ip;
} DNS_ENTRY, * PDNS_ENTRY;


typedef struct _DNS_TEST_RESULT
{
    unsigned int    total;
    unsigned int    correct;
    unsigned int    wrong;
    unsigned int    firstWrong;
}DNS_TEST_RESULT, * PDNS_TEST_RESULT;



typedef unsigned int BOOL;
#define FALSE 0
#define TRUE  1

/************************************************************************/
/* TEST                                                                 */
/************************************************************************/

DNS_TEST_RESULT TestDNS_Random(DNSHandle DNEngine, DNS_ENTRY* testArray, unsigned int arraySize)
{
    DNS_TEST_RESULT result = { 0, 0, 0, -1 };
    unsigned int i;

    unsigned int* pIndexes = (unsigned int*)calloc(arraySize, sizeof(unsigned int));
    if (!pIndexes)
        return result;



    // shuffle indexes
    for (i = 0; i < arraySize; i++)
    {
        pIndexes[i] = (arraySize / 2) + ((i + 1) / 2) * ((i % 2) ? -1 : 1);
    }


    for (i = 0; i < arraySize; i++)
    {
        IPADDRESS ipResponse;

        if (testArray[pIndexes[i]].domainName == NULL)
            continue;

        result.total++;

        ipResponse = DnsLookUp(DNEngine, testArray[pIndexes[i]].domainName);
        if (ipResponse == testArray[pIndexes[i]].ip)
        {
            result.correct++;
        }
        else
        {
            result.wrong++;
            if (result.firstWrong == -1)
                result.firstWrong = i;
        }
    }

    free(pIndexes);

    return result;
}

DNS_TEST_RESULT TestDNS_Reverse(DNSHandle DNEngine, DNS_ENTRY* testArray, unsigned int arraySize)
{
    DNS_TEST_RESULT result = { 0, 0, 0, -1 };

    unsigned int i = 0;
    for (i = arraySize - 1; i != -1; i--)
    {
        IPADDRESS ipResponse;

        if (testArray[i].domainName == NULL)
            continue;

        result.total++;

        ipResponse = DnsLookUp(DNEngine, testArray[i].domainName);
        if (ipResponse == testArray[i].ip)
        {
            result.correct++;
        }
        else
        {
            result.wrong++;
            if (result.firstWrong == -1)
                result.firstWrong = i;
        }
    }

    return result;
}

DNS_TEST_RESULT TestDNS(DNSHandle DNEngine, DNS_ENTRY* testArray, unsigned int arraySize)
{
    DNS_TEST_RESULT result = { 0, 0, 0, -1 };

    unsigned int i = 0;
    for (i = 0; i < arraySize; i++)
    {
        IPADDRESS ipResponse;

        if (testArray[i].domainName == NULL)
            continue;

        result.total++;

        ipResponse = DnsLookUp(DNEngine, testArray[i].domainName);

        if (ipResponse == testArray[i].ip)
        {
            result.correct++;
        }
        else
        {
            result.wrong++;
            if (result.firstWrong == -1)
                result.firstWrong = i;
        }
    }

    return result;
}


/************************************************************************/
/* UTILITY                                                              */
/************************************************************************/

unsigned int getNumOfLines(FILE* fInput)
{
#define BUFFER_SIZE 200
    unsigned int lineCounter = 0;
    char buffer[BUFFER_SIZE];

    if (!fInput)
        return 0;

    fseek(fInput, 0, SEEK_SET);
    while (!feof(fInput))
    {
        fgets(buffer, BUFFER_SIZE, fInput);
        lineCounter++;
    }
    return lineCounter;
}

BOOL loadFromFile(const char* filename, PDNS_ENTRY* pDnsArray, unsigned int* size)
{
    FILE* fInput = NULL;
    unsigned int dnCount = 0;
    unsigned int i = 0;

    if (*pDnsArray)
        return FALSE;

    fInput = fopen(filename, "r");
    if (NULL == fInput)
        return FALSE;

    dnCount = getNumOfLines(fInput);

    if ((0 == dnCount) || !(*pDnsArray = (PDNS_ENTRY)calloc(dnCount, sizeof(DNS_ENTRY))))
    {
        fclose(fInput);
        return FALSE;
    }

    *size = dnCount;
    fseek(fInput, 0, SEEK_SET);

    for (i = 0; i < dnCount && !feof(fInput); i++)
    {
        char buffer[201] = { 0 };
        char* pStringWalker = &buffer[0];
        unsigned int uHostNameLength = 0;
        unsigned int ip1 = 0, ip2 = 0, ip3 = 0, ip4 = 0;

        fgets(buffer, 200, fInput);

        if (5 != fscanf_s(fInput, "%d.%d.%d.%d %s", &ip1, &ip2, &ip3, &ip4, buffer, 200))
            continue;

        (*pDnsArray)[i].ip = (ip1 & 0xFF) << 24 |
            (ip2 & 0xFF) << 16 |
            (ip3 & 0xFF) << 8 |
            (ip4 & 0xFF);


        uHostNameLength = strlen(buffer);
        if (uHostNameLength)
        {
            (*pDnsArray)[i].domainName = (char*)malloc(uHostNameLength + 1);
            strcpy((*pDnsArray)[i].domainName, pStringWalker);
        }
    }

    fclose(fInput);
    return TRUE;
}

void freeDnsEntries(PDNS_ENTRY* pDnsArray, unsigned int size)
{
    unsigned int i = 0;
    for (i = 0; i < size; i++)
    {
        if ((*pDnsArray)[i].domainName)
            free((*pDnsArray)[i].domainName);
    }

    free(*pDnsArray);
    *pDnsArray = 0;
}


/************************************************************************/
/* MAIN()                                                               */
/************************************************************************/

#define DEFAULT_HOSTS_FILENAME "hosts"

int main(int argc, char* argv[])
{
    PDNS_ENTRY pDnsArray = NULL;
    unsigned int size = 0;
    DNSHandle hDnsEngine = INVALID_DNS_HANDLE;
    unsigned int i = 0;


    clock_t start, init, total_regular, total_reverse, total_random, total_load;
    total_regular = total_reverse = total_random = total_load = 0;



    if (TRUE == loadFromFile(DEFAULT_HOSTS_FILENAME, &pDnsArray, &size))
    {
        printf("Test file loaded!\n\n");

        if (pDnsArray)
        {
            start = clock();
            hDnsEngine = InitDNS();
            init = clock() - start;

            if (hDnsEngine != INVALID_DNS_HANDLE)
            {
                DNS_TEST_RESULT regularResult, reverseResult, randomResult;


                start = clock();
                LoadHostsFile(hDnsEngine, DEFAULT_HOSTS_FILENAME);
                total_load = clock() - start;


                start = clock();
                regularResult = TestDNS(hDnsEngine, pDnsArray, size);
                total_regular = clock() - start;


                start = clock();
                reverseResult = TestDNS_Reverse(hDnsEngine, pDnsArray, size);
                total_reverse = clock() - start;


                start = clock();
                randomResult = TestDNS_Random(hDnsEngine, pDnsArray, size);
                total_random = clock() - start;


                // Print statistics
                printf("DNS engine initialized in %d ms\n", init);
                printf("DNS engine load \"%s\" in %d ms\n\n", DEFAULT_HOSTS_FILENAME, total_load);

                printf("Statistics for regular test:\n"
                    "\tTotal........: %d\n"
                    "\tCorrect......: %d\n"
                    "\tWrong........: %d\n"
                    "\tTime.........: %d\n\n",
                    regularResult.total, regularResult.correct, regularResult.wrong, (unsigned int)total_regular);

                printf("Statistics for reverse test:\n"
                    "\tTotal........: %d\n"
                    "\tCorrect......: %d\n"
                    "\tWrong........: %d\n"
                    "\tTime.........: %d\n\n",
                    reverseResult.total, reverseResult.correct, reverseResult.wrong, (unsigned int)total_reverse);

                printf("Statistics for random test:\n"
                    "\tTotal........: %d\n"
                    "\tCorrect......: %d\n"
                    "\tWrong........: %d\n"
                    "\tTime.........: %d\n\n",
                    randomResult.total, randomResult.correct, randomResult.wrong, (unsigned int)total_random);

            }
            else
            {
                printf("DNS engine failed to start!\n");
            }

            ShutdownDNS(hDnsEngine);
            freeDnsEntries(&pDnsArray, size);
        }
    }

    return 0;
}