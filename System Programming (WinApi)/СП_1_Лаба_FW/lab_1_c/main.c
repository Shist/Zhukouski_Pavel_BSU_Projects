/*
* SPLPv1.c
* The file is part of practical task for System programming course.
* This file contains validation of SPLPv1 protocol.
*
* DON'T EDIT THIS FILE !!!
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "splpv1.h"



#define SPLP_INVALID_MSG_INDEX    0xffffffff
#define DEFAULT_CYCLE_COUNT       100
#define DEFAULT_TEST_FILENAME     "test.txt"




typedef enum _SPLP_STATUS
{
    SPLP_STATUS_OK,
    SPLP_STATUS_ERROR
} SPLP_STATUS;




/* SPLP_TEST_MESSAGE
* This is a utility data structure which holds a message to evaluate
* by validate_message() and the answer which is expected to be.
* if the result returned by validate_message() for msg member is NOT
* the same as  expectedTestStatus,  the function is implemented with
* mistakes.
*/
typedef struct _SPLP_TEST_MESSAGE
{
    enum test_status  expectedTestStatus;  /* Correct answer */
    struct Message    msg;                 /* Message */

}SPLP_TEST_MESSAGE, *PSPLP_TEST_MESSAGE;




/* SPLP_TEST_STATISTICS
* This structure holds the statistics about a test. If the test
* completed successfully, the 'falsePositive' and 'falseNegative'
* members of the structure are zero.
* If there are some errors in validate_message() implementation,
* firstWrongMsg member will contain the ind of the first message
* where expected result wasn't equal to one returned by
* validate_message().
*/
typedef struct _SPLP_TEST_STATISTICS
{
    unsigned int truePositive;
    unsigned int trueNegative;
    unsigned int falsePositive;
    unsigned int falseNegative;
    clock_t      duration;

    unsigned int firstWrongMsg;

}SPLP_TEST_STATISTICS, *PSPLP_TEST_STATISTICS;




/* SPLP_TEST_OPTIONS
* This structure contains configuration for a test
*/
typedef struct _SPLP_TEST_OPTIONS
{
    const char*  testFileName;  /* path to the file with test messages */
    unsigned int cycleCount;    /* how many times should the file be evaluated */

}SPLP_TEST_OPTIONS, *PSPLP_TEST_OPTIONS;




/* SPLP_TEST_DATA
* This structure contains data for a test
*/
typedef struct _SPLP_TEST_DATA
{
    PSPLP_TEST_MESSAGE   MessageArray; /* test messages to evaluate */
    unsigned int         size;         /* amount of messages in MessageArray */
    unsigned int         dataSize;     /* total size of test data, in bytes  */

}SPLP_TEST_DATA, *PSPLP_TEST_DATA;




SPLP_STATUS  SplpTestDataLoadFromFile(
    const char* fileName,
    PSPLP_TEST_DATA testData );




void SplpTestDataFree(
    PSPLP_TEST_DATA testData );




SPLP_STATUS  SplpTestOptionsInitializeFromCmdLine(
    PSPLP_TEST_OPTIONS pTestOptions,
    int argc,
    char* argv[ ] );




void SplpTestResultPrint(
    PSPLP_TEST_OPTIONS pOptions,
    PSPLP_TEST_STATISTICS pStat,
    PSPLP_TEST_DATA pData );




void SplpDoTest(
    PSPLP_TEST_OPTIONS pOptions,
    PSPLP_TEST_STATISTICS pStat,
    PSPLP_TEST_DATA pData );




void SplpPrintUsage( )
{
    printf( "usage:\n"
        "\ttest                 - run test program with default values.\n"
        "\ttest filename        - run with filename default cycles.\n"
        "\ttest filename count  - run filename count>0 iterations.\n" );
}




int main( int argc, char* argv[ ] )
{
    SPLP_TEST_DATA       TestData = { 0 };
    SPLP_TEST_OPTIONS    TestOptions = { 0 };
    SPLP_TEST_STATISTICS TestStatistics = { 0, 0, 0, 0, 0, SPLP_INVALID_MSG_INDEX };


    if ( SPLP_STATUS_OK != SplpTestOptionsInitializeFromCmdLine( &TestOptions, argc, argv ) ||
        SPLP_STATUS_OK != SplpTestDataLoadFromFile( TestOptions.testFileName, &TestData ) )
    {
        exit( 1 );
    }

    SplpDoTest( &TestOptions, &TestStatistics, &TestData );

    SplpTestResultPrint( &TestOptions, &TestStatistics, &TestData );

    SplpTestDataFree( &TestData );

    return 0;
}




void SplpTestResultPrint(
    PSPLP_TEST_OPTIONS pOptions,
    PSPLP_TEST_STATISTICS pStat,
    PSPLP_TEST_DATA pData )
{
    printf(
        "======================================================================\n"
        " TEST RESULTS:\n"
        "======================================================================\n"
        " Test Info:\n"
        "\tTest file:        \"%s\"\n"
        "\tMessages in file: \t%14u\n"
        "\tCycles:           \t%14u\n\n",
        pOptions->testFileName,
        pData->size,
        pOptions->cycleCount );


    printf(
        " Test correctness:\n"
        "\tTotal messages:   \t%14u\n"
        "\tCorrect:          \t%14u\n"
        "\tWrong:            \t%14u\n\n",
        pOptions->cycleCount * pData->size,
        pStat->trueNegative + pStat->truePositive,
        pStat->falseNegative + pStat->falsePositive );


    if ( pStat->falseNegative || pStat->falsePositive )
    {
        printf(
            " First wrong answer:\n"
            "\tMsg #:            \t%14u\n"
            "\tDirection:        \t%14s\n"
            "\tExpected:         \t%14s\n"
            "\tMessage:\n\t\t\"%s\"",
            pStat->firstWrongMsg,
            pData->MessageArray[ pStat->firstWrongMsg ].msg.direction == A_TO_B ?
            "A->B" : "B->A",
            pData->MessageArray[ pStat->firstWrongMsg ].expectedTestStatus == MESSAGE_VALID ?
            "MESSAGE_VALID" : "MESSAGE_INVALID",
            pData->MessageArray[ pStat->firstWrongMsg ].msg.text_message );
    }


    printf( "\n"
        " Performance Results:\n"
        "\tTest cycles:      \t%14u\n"
        "\tTotal clocks:     \t%14u\n"
        "\tTotal time (sec): \t%14.4f\n"
        "\t per cycle (usec):\t%14.4f (usec = 10^(-6) second)\n"
        "\tThroughput:	     \t%14.4f Mbps\n\n",
        pOptions->cycleCount,
        pStat->duration,
        (float) pStat->duration / (float) CLOCKS_PER_SEC,

        ( pOptions->cycleCount != 0 ) ?
        ( (float) pStat->duration * 1000000.0f / (float) CLOCKS_PER_SEC / (float) ( pOptions->cycleCount ) ) : 0,

        ( pStat->duration != 0 ) ?
        (float) pData->dataSize * (float) pOptions->cycleCount * 8.0f / ( (float) ( pStat->duration ) / (float) CLOCKS_PER_SEC ) / 1024.0 / 1024.0 : 0 );

    printf( "======================================================================\n" );
}




void SplpDoTest(
    PSPLP_TEST_OPTIONS pOptions,
    PSPLP_TEST_STATISTICS pStat,
    PSPLP_TEST_DATA pData )
{
    clock_t start = clock( );
    unsigned int cycleIdx = 0;
    unsigned int msgIdx = 0;

    for ( cycleIdx = 0; cycleIdx < pOptions->cycleCount; cycleIdx++ )
    {
        for ( msgIdx = 0; msgIdx < pData->size; msgIdx++ )
        {
            if ( validate_message( &pData->MessageArray[ msgIdx ].msg ) != pData->MessageArray[ msgIdx ].expectedTestStatus )
            {
                // WRONG answer
                if ( pStat->firstWrongMsg == SPLP_INVALID_MSG_INDEX )
                    pStat->firstWrongMsg = msgIdx;

                pData->MessageArray[ msgIdx ].expectedTestStatus == MESSAGE_VALID ?
                    pStat->falseNegative++ :
                    pStat->falsePositive++;
            }
            else
            {
                // CORRECT answer
                pData->MessageArray[ msgIdx ].expectedTestStatus == MESSAGE_VALID ?
                    pStat->truePositive++ :
                    pStat->trueNegative++;
            }
        }
    }

    pStat->duration = clock( ) - start;
}




void SplpTestDataFree(
    PSPLP_TEST_DATA testData )
{
    unsigned int i = 0;

    if ( testData->MessageArray )
    {
        for ( i = 0; i<testData->size; i++ )
        {
            free( testData->MessageArray[ i ].msg.text_message );
        }
        free( testData->MessageArray );
    }
}




unsigned int SplpGetMessageCount( FILE* fInput )
{
    unsigned int result = 0;
    fseek( fInput, 0, SEEK_SET );
    if ( 1 == fscanf_s( fInput, "%u", &result ) )
        return result;
    return 0;
}




SPLP_STATUS SplpReadMessage(
    FILE* fInput,
    PSPLP_TEST_MESSAGE pMsg )
{
    int direction = 0, correct = 0;

    if ( 2 == fscanf_s( fInput, "%d\t%d\t", &correct, &direction ) )
    {
        char buffer[ 8192 ];
        pMsg->expectedTestStatus = ( correct == 1 ) ? MESSAGE_VALID : MESSAGE_INVALID;
        pMsg->msg.direction = ( direction == 1 ) ? B_TO_A : A_TO_B;
        if ( fgets( buffer, sizeof( buffer ), fInput ) )
        {
            unsigned int size = strlen( buffer );

            char* pStrWalker;
            for ( pStrWalker = buffer + size - 1; pStrWalker != buffer; pStrWalker-- )
            {
                if ( *pStrWalker == '\n' || *pStrWalker == '\r' )
                {
                    *pStrWalker = 0;
                    size--;
                }
            }

            pMsg->msg.text_message = (char *) malloc( size + 1 );
            if ( pMsg->msg.text_message )
            {
                strncpy_s( pMsg->msg.text_message, size + 1, buffer, _TRUNCATE );
                return SPLP_STATUS_OK;
            }
        }
    }
    return SPLP_STATUS_ERROR;
}



unsigned int SplpGetTotalDataSize(
    PSPLP_TEST_MESSAGE pMessages,
    unsigned int msgCount )
{
    unsigned int i;
    unsigned int result = 0;
    for ( i = 0; i<msgCount; i++ )
    {
        result += strlen( pMessages[ i ].msg.text_message );
    }
    return result;
}




SPLP_STATUS  SplpTestDataLoadFromFile(
    const char* fileName,
    PSPLP_TEST_DATA testData )
{
    FILE*  fInput = 0;
    unsigned int fileSize = 0;
    SPLP_STATUS status = SPLP_STATUS_ERROR;


    if ( 0 == fopen_s( &fInput, fileName, "r" ) )
    {
        unsigned int msgCount = SplpGetMessageCount( fInput );
        PSPLP_TEST_MESSAGE testMessages;

        if ( msgCount &&
            NULL != ( testMessages = (PSPLP_TEST_MESSAGE) calloc( msgCount, sizeof( SPLP_TEST_MESSAGE ) ) ) )
        {
            unsigned int messagesRead;

            for ( messagesRead = 0; messagesRead < msgCount; messagesRead++ )
            {
                if ( SPLP_STATUS_OK != SplpReadMessage( fInput, &testMessages[ messagesRead ] ) )
                    break;
            }

            if ( messagesRead )
            {
                testData->size = messagesRead;
                testData->MessageArray = testMessages;
                testData->dataSize = SplpGetTotalDataSize( testMessages, messagesRead );
            }

            if ( messagesRead != msgCount )
            {
                printf( "***WARNING*** File \"%s\" wasn't loaded completely. Loaded %u out of %u\n",
                    fileName, messagesRead, msgCount );
            }

            if ( messagesRead != 0 )
                status = SPLP_STATUS_OK;
        }

        fclose( fInput );
    }
    else
    {
        printf( "***ERROR*** File \"%s\" can't be opened\n", fileName );
    }

    return status;
}




SPLP_STATUS  SplpTestOptionsInitializeFromCmdLine(
    PSPLP_TEST_OPTIONS pTestOptions,
    int argc,
    char* argv[ ] )
{
    SPLP_STATUS Status = SPLP_STATUS_OK;

    pTestOptions->cycleCount = DEFAULT_CYCLE_COUNT;
    pTestOptions->testFileName = DEFAULT_TEST_FILENAME;

    if ( argc > 1 )
    {
        pTestOptions->testFileName = argv[ 1 ];
    }

    if ( argc == 3 )
    {
        unsigned long cycleCount = strtoul( argv[ 2 ], NULL, 0 );
        if ( cycleCount > 0 && cycleCount < ULONG_MAX )
        {
            pTestOptions->cycleCount = cycleCount;
        }
        else
        {
            SplpPrintUsage( );
            Status = SPLP_STATUS_ERROR;
        }
    }

    return Status;
}