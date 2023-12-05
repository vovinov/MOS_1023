#include <windows.h>
#include <stdio.h>
#include <iostream>

#define INITIAL_SEM_COUNT 1
#define MAX_SEM_COUNT 10
#define THREADCOUNT 5

HANDLE ghSemaphore;
WORD dwCounter;

DWORD WINAPI ThreadProc( LPVOID );

DWORD WINAPI ThreadProc(LPVOID lpParam) {

  DWORD dwWaitResult; 
  BOOL bContinue = TRUE;

  while(bContinue) {
    
    dwWaitResult = WaitForSingleObject(ghSemaphore, INFINITE);
    printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
    if (dwWaitResult == WAIT_OBJECT_0) {                
      
      dwCounter++;
      std::cout << dwCounter << std::endl;
      bContinue = FALSE;

      Sleep(2000);

      ReleaseSemaphore(ghSemaphore, 1, NULL);
    };
  };

  return 1;
};

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
  for(i = 0; i < THREADCOUNT; i++) {
    CloseHandle(aThread[i]);
  };

  std::cout << "Close threads" << std::endl;

  // Закрываем семафор
  CloseHandle(ghSemaphore);

  return 0;
};
