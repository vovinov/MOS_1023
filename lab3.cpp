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


int main() {
  // Пример использования синхронизации с помощью метода критической секции
  CRITICAL_SECTION critical_section;
  InitializeCriticalSection(&critical_section);
  
  return 0;
}