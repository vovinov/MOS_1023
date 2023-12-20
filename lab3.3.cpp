#include <windows.h>
#include <stdio.h>

#define THREADCOUNT 4

HANDLE ghWriteEvent; 
HANDLE ghThreads[THREADCOUNT];

DWORD WINAPI ThreadProc(LPVOID);

// Функция  записи в буфер
void WriteToBuffer()
{    
    printf("Main thread writing to the shared buffer...\n");
    SetEvent(ghWriteEvent);
};

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    DWORD dwWaitResult;
    
    printf("Thread %d waiting for write event...\n", GetCurrentThreadId());
    
    dwWaitResult = WaitForSingleObject(ghWriteEvent, INFINITE);    

    if (dwWaitResult == WAIT_OBJECT_0)
    {
        printf("Thread %d reading from buffer\n", GetCurrentThreadId());
    };

    printf("Thread %d exiting\n", GetCurrentThreadId());
    return 1;
};

int main()
{

    int i; 
    DWORD dwThreadID; 
    DWORD dwWaitResult;

    // Создаём событие
    ghWriteEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("WriteEvent"));

    // Создаём потоки
    for(i = 0; i < THREADCOUNT; i++)
    {
        ghThreads[i] = CreateThread(NULL, 0, ThreadProc, NULL, 0, &dwThreadID); 
    };

    WriteToBuffer();
    printf("Main thread waiting for threads to exit...\n");

    dwWaitResult = WaitForMultipleObjects(
        THREADCOUNT,
        ghThreads,     
        TRUE,
        INFINITE);

    if (dwWaitResult == WAIT_OBJECT_0)
    {
        printf("All threads ended, cleaning up for application exit...\n");
    };
            
    // Закрываем процесс
    CloseHandle(ghWriteEvent);

    return 0;
}
