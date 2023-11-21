
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <string.h>
#include <cstring>

CRITICAL_SECTION cs;


int a=0;

HANDLE Event = NULL;

void vivod(int sch) {

  WaitForSingleObject(Event, INFINITE);

  EnterCriticalSection(&cs);

  for (int i = 0; i < 5; i++) {
    a += sch;
    std::cout << a << " ";
    Sleep(250);
  }
  std::cout << std::endl;
  LeaveCriticalSection(&cs);
}

int main() {

  InitializeCriticalSection(&cs);

  Event = OpenEventA(EVENT_ALL_ACCESS, FALSE, "check");

  std::thread thr1(vivod, -1);
  std::thread thr2(vivod, 1);
  std::thread thr3(vivod, -1);
  std::thread thr4(vivod, 1);

  thr1.join();
  thr2.join();
  thr3.join();
  thr4.join();

  ResetEvent(Event);
  CloseHandle(Event);

  std::cout << std::endl;
  system("pause");
}