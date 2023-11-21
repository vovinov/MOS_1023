/*
2. Исследование на конкретном примере следующих методов синхронизации потоков:
1) критическая секция
2) мьтекс
3) событие
4) * семафор, ждущий таймер или барьер
Задачи для демонстрации применения средств синхронизации придумайте
самостоятельно.
3. Примеры разработанных приложений (описание задачи, код приложений, результаты
выполнения).
*/

#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
#include <thread>

// Пример использования синхронизации с помощью метода критической секции

CRITICAL_SECTION critical_section;

void print_thread(int k) {
  EnterCriticalSection(&critical_section);

  for (int i = 0; i < 10; i++) {
  std::cout << k;

  Sleep(50);

  LeaveCriticalSection(&critical_section);
};

int main() {
  
  InitializeCriticalSection(&critical_section);
  
  HANDLE hTread;
  DWORD IDThread;

  thread thread1(print_thread ,1);

  DeleteCriticalSection(&critical_section);

  pause(0)

  return 0;
}