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
#include <tlhelp32.h>
namespace fs = std::filesystem;

#define STRING_LENGTH 1024

int main()
{

  HMODULE hModule;  
  char fullName[STRING_LENGTH];

  // Получаем название файла user32.dll с помощью библиотеки filesystem
  std::string filename = "C:\\Users\\slava\\Desktop\\Project\\!C++\\MOS_LAB\\lab2.exe";
  std::cout << "Process name: " << fs::path(filename).filename() << std::endl;
  std::cout << "Full name of process: " << filename << std::endl;

  // Получаем имя модуля
  GetModuleHandleA(fullName);
  std::cout << "Descriptor name: " << hModule << std::endl;

  // Id процесса
  DWORD process_id = GetCurrentProcessId();
  std::cout << "Process id: " << process_id << std::endl;

  // Текущий процесс
  HANDLE process = GetCurrentProcess();
  std::cout << "Process: " << process << std::endl;

  // Дескриптор текущего процесса через псевдодескриптор
  HANDLE process_dublicate_id;

  DuplicateHandle(process, process, process, &process_dublicate_id, 0, 
                  FALSE, DUPLICATE_SAME_ACCESS);

  std::cout << "Descriptor by DublicateHandle: " << process_dublicate_id << std::endl;

  // Открываем процесс по id
  HANDLE open_current_process = OpenProcess(PROCESS_DUP_HANDLE, TRUE, process_id);
  std::cout << "Descriptor by OpenProcess: " << open_current_process << std::endl;
  
  // Закрываем дублированный процесс
  BOOL close_dublicate_process = CloseHandle(process_dublicate_id);
  if (close_dublicate_process)  
    std::cout << "Dublicated process is closed" << std::endl;
  else
    std::cout << "Dublicated process is -NOT- closed" << std::endl;

  // Закрываем текущий процесс
  BOOL close_current_process = CloseHandle(open_current_process);
  if (close_current_process)
    std::cout << "Opened process is closed" << std::endl;
  else
    std::cout << "Opened process is -NOT- closed" << std::endl;

  // Получение всех процессов с помощью библиотеки Toolhelp32

  // Снимок всех процессов
  HANDLE process_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 process_info;
  process_info.dwSize =  sizeof(PROCESSENTRY32);

  std::cout << "********* Start list of processes *********" << std::endl;
  Process32First(process_snapshot, &process_info);

  do {
    std::cout << "_______Process " << process_info.th32ProcessID << "_______" << std::endl;
    std::cout << "Number of threads: " << process_info.cntThreads << std::endl;
    std::cout << "Exe file: " << process_info.szExeFile << std::endl;
    
  }  while (Process32Next(process_snapshot, &process_info));

  CloseHandle(process_snapshot); // закрыли процесс снимка
  std::cout << "********* End list of processes *********" << std::endl;

  // Получение всех потоков с помощью библиотеки Toolhelp32

  // Снимок
  HANDLE threads_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
  THREADENTRY32 thread_info;
  thread_info.dwSize = sizeof(THREADENTRY32);

  std::cout << "********* Start list of threads *********" << std::endl;
  Thread32First(threads_snapshot, &thread_info);

  do {
    std::cout << "Thread " << thread_info.th32ThreadID << "_______" 
              << "Owner - " << thread_info.th32OwnerProcessID << std::endl;
    
  }  while (Thread32Next(threads_snapshot, &thread_info));

  CloseHandle(threads_snapshot); // закрыли процесс снимка
  std::cout << "********* End list of threads *********" << std::endl;

  // Получение всех модулей с помощью библиотеки Toolhelp32

  // Снимок
  HANDLE modules_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
  MODULEENTRY32 module_info;
  module_info.dwSize = sizeof(MODULEENTRY32);

  std::cout << "********* Start list of modules *********" << std::endl;
  Module32First(modules_snapshot, &module_info);

  do {
    std::cout << "_____ Module " << module_info.szModule << "_____" << std::endl;
    std::cout << "Path: " << module_info.szExePath << std::endl;
    std::cout << "Size: " << module_info.modBaseSize << std::endl;
    std::cout << "Usage: " << module_info.ProccntUsage << std::endl;

    
  }  while (Module32Next(modules_snapshot, &module_info));

  CloseHandle(modules_snapshot); // закрыли процесс снимка
  std::cout << "********* End list of modules *********" << std::endl;

  system("pause");

  return 0;
}
