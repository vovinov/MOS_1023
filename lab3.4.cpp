#include <windows.h>
#include <stdio.h>
#include <iostream>

#define INITIAL_SEM_COUNT 1
#define MAX_SEM_COUNT 10
#define THREADCOUNT 5

HANDLE ghSemaphore;
WORD dwCounter;

DWORD WINAPI ThreadProc( LPVOID );

int main() {
  HANDLE aThread[THREADCOUNT];
  DWORD ThreadID;
  int i;

  // Создаём семафор
  ghSemaphore = CreateSemaphore(NULL, INITIAL_SEM_COUNT, MAX_SEM_COUNT, NULL);          // unnamed semaphore

  // Создаём потоки
  for(i = 0; i < THREADCOUNT; i++) {
      aThread[i] = CreateThread(NULL, 0, ThreadProc, NULL, 0, &ThreadID); 
  };
  WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

  // Закрываем потоки
  for(i = 0; i < THREADCOUNT; i++)
      CloseHandle(aThread[i]);

  // Закрываем семафор
  CloseHandle(ghSemaphore);

  return 0;
};

DWORD WINAPI ThreadProc(LPVOID lpParam) {

  DWORD dwWaitResult; 
  BOOL bContinue = TRUE;

  while(bContinue) {
    // 0L
    dwWaitResult = WaitForSingleObject(ghSemaphore, INFINITE);

    switch (dwWaitResult) {      
      case WAIT_OBJECT_0:             
        printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
        dwCounter++;
        std::cout << dwCounter << std::endl;
        bContinue = FALSE;

        Sleep(5);

        ReleaseSemaphore(ghSemaphore, 1, NULL);
        // if (!ReleaseSemaphore(ghSemaphore, 1, NULL)) {
        //   printf("ReleaseSemaphore error: %d\n", GetLastError());
        // };
        // break;

      case WAIT_TIMEOUT: 
        printf("Thread %d: wait timed out\n", GetCurrentThreadId());
        break; 
    };
  };

  return TRUE;
};