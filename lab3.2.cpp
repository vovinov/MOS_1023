
#include <windows.h>
#include <iostream>

#define THREADS_NUMBER 10
#define ITERATIONS_NUMBER 5
#define PAUSE 1000 /* ms */

DWORD dwCounter = 0;

DWORD WINAPI ThreadProc(CONST LPVOID lpParam) {
  CONST HANDLE hMutex = (CONST HANDLE)lpParam;
  DWORD i;
  for(i = 0; i < ITERATIONS_NUMBER; i++) {
    WaitForSingleObject(hMutex, INFINITE);    
    dwCounter++;
    std::cout << dwCounter << std::endl;
    ReleaseMutex(hMutex);
    
    Sleep(PAUSE);
  }
  ExitThread(0);
}


int main() {
  TCHAR szMessage[256];
  DWORD dwTemp, i;
  HANDLE hThreads[THREADS_NUMBER];
  // CONST HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

  for(i = 0; i < THREADS_NUMBER; i++) {
    hThreads[i] = CreateThread(NULL, 0, &ThreadProc, hMutex, 0, NULL);
    // std::cout << "Thread " << i << " starts" << std::endl;
  }

  WaitForMultipleObjects(THREADS_NUMBER, hThreads, TRUE, INFINITE);
  printf("Counter = %d\r\n", dwCounter);
  

  for(i = 0; i < THREADS_NUMBER; i++) {
    CloseHandle(hThreads[i]);
  }
  CloseHandle(hMutex);
  ExitProcess(0);

  return 0;
}