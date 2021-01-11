#include <cstdio>
#include <windows.h>

typedef struct
{
    int seq;
    long start;
    long med;
    long finish;
    HANDLE firstDepfinishency;
    HANDLE secondDepfinishency;
    HANDLE ready;
} Task;

class TaskQueue
{
public:
    TaskQueue(int len);
    virtual ~TaskQueue();

    void Insert(Task element);
    bool Remove(Task* output, DWORD emptyWaitMs);

private:
    HANDLE insertSemaphore_;
    HANDLE removeSemaphore_;
    CRITICAL_SECTION editingGuard_;

    int outputIndex_;
    int startIndex_;
    int len_;
    Task* array_;
};


TaskQueue::TaskQueue(int len)
{
    insertSemaphore_ = CreateSemaphore(NULL, len, len, NULL);
    removeSemaphore_ = CreateSemaphore(NULL, 0, len, NULL);
    InitializeCriticalSection(&editingGuard_);

    outputIndex_ = 0;
    startIndex_ = 0;
    len_ = len;
    array_ = new Task[len_];
}

TaskQueue::~TaskQueue()
{
    CloseHandle(insertSemaphore_);
    CloseHandle(removeSemaphore_);
    DeleteCriticalSection(&editingGuard_);
    delete[] array_;
}

void TaskQueue::Insert(Task element)
{
    WaitForSingleObject(insertSemaphore_, INFINITE);
    EnterCriticalSection(&editingGuard_);
    ReleaseSemaphore(removeSemaphore_, 1, NULL);

    array_[outputIndex_] = element;
    ++outputIndex_;
    if (outputIndex_ >= len_)
    {
        outputIndex_ -= len_;
    }

    LeaveCriticalSection(&editingGuard_);
}

bool TaskQueue::Remove(Task* output, DWORD emptyWaitMs)
{
    DWORD removeWaitResult = WaitForSingleObject(removeSemaphore_, emptyWaitMs);
    if (removeWaitResult != WAIT_OBJECT_0)
    {
        return false;
    }

    EnterCriticalSection(&editingGuard_);
    ReleaseSemaphore(insertSemaphore_, 1, NULL);

    *output = array_[startIndex_];
    ++startIndex_;

    if (startIndex_ >= len_)
    {
        startIndex_ -= len_;
    }

    LeaveCriticalSection(&editingGuard_);
    return true;
}
