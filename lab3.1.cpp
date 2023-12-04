#include <iostream>
#include <windows.h>
#include <thread>

// Пример использования синхронизации с помощью метода критической секции

CRITICAL_SECTION critical_section;

// Функция последовательно выводит число 
void print_thread(int k) {
  
  EnterCriticalSection(&critical_section);
  std::cout << "******" << std::endl;
  std::cout << "Enter critical section" << std::endl;
  for (int i = 0; i < 10; i++) {
  std::cout << k;

  Sleep(300);
  };
  std::cout << std::endl;
  std::cout << "Leave critical section" << std::endl;
  LeaveCriticalSection(&critical_section);
  
};

int main() {
  
  InitializeCriticalSection(&critical_section);

  std::thread thread1(print_thread, 1);
  std::thread thread2(print_thread, 2);
  std::thread thread3(print_thread, 3);

  // Завершение потока
  thread1.join();
  thread2.join();
  thread3.join();

  DeleteCriticalSection(&critical_section);

  system("pause");

  return 0;
};
