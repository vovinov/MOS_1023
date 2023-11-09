/*
2. Программа, которая принимая дескриптор, имя или полное имя модуля, возвращает
другие два элемента в своих выходных параметрах (выполнить задание для своей
программы и для любой известной библиотеки). 
Например:
• Получить дескриптор, имя и полное имя ЕХЕ.
Handle: &HFFFFFFFF
Name: VB6.EXE
FName: G:\Visual Studio\VB98\VB6.EXE
• Получить имя и полное имя модуля.
Задаем: Handle: &H77E70000
Получаем:
Name: User32.dll
FName: G:\WINNT\system32\USER32.DLL
• Получить дескриптор и полное имя.
Задаем: Name: User32.dll
Получаем:
Handle: &H77E70000
FName: G:\WINNT\system32\USER32.DLL
• Получить дескриптор и имя.
Задаем: FName: G:\WINNT\system32\USER32.DLL
Получаем:
Handle: &H77E70000
Name: User32.dll
А также будет выполнять последовательно по шагам следующее:
• используя функцию GetCurrentProcessId определит идентификатор текущего
процесса;
• используя функцию GetCurrentProcess определит псевдодескриптор текущего
процесса;
• используя функцию DuplicateHandl и значение псевдодескриптора определит
дескриптор текущего процесса;
• используя функцию OpenProcess определит копию дескриптора текущего процесса.
• закроет дескриптор, полученный функцией DuplicateHandl.
• закроет дескриптор, полученный функцией OpenProcess.
• выдает список перечисления всех процессов, потоков, модулей и их свойства в
системе, а также список загруженных драйверов устройств)
*/


#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
namespace fs = std::filesystem;

#define STRING_LENGTH 1024


int main()
{
 
  HMODULE hModule;  
  char fullName[STRING_LENGTH];

  std::string filename = "C:\\Windows\\System32\\user32.dll";
  std::cout << fs::path(filename).filename() << std::endl;


  // Получаем имя модуля
  HMODULE hModule = GetModuleHandleA(fullName);


  return 0;
}
