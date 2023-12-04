

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

  // Получаем название короткое и полное файла lab2 с помощью библиотеки filesystem
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

  // Делаем снимок всех процессов
  HANDLE process_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 process_info;
  process_info.dwSize =  sizeof(PROCESSENTRY32);

  std::cout << "********* Start list of processes *********" << std::endl;
  Process32First(process_snapshot, &process_info);

  // Цикл для вывода списка процессов
  do {
    std::cout << "_______Process " << process_info.th32ProcessID << "_______" << std::endl;
    std::cout << "Number of threads: " << process_info.cntThreads << std::endl;
    std::cout << "Exe file: " << process_info.szExeFile << std::endl;
    
  }  while (Process32Next(process_snapshot, &process_info));

  CloseHandle(process_snapshot); // закрываем процесс снимка
  std::cout << "********* End list of processes *********" << std::endl;

  // Получение всех потоков с помощью библиотеки Toolhelp32

  // Делаем снимок потоков
  HANDLE threads_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
  THREADENTRY32 thread_info;
  thread_info.dwSize = sizeof(THREADENTRY32);

  std::cout << "********* Start list of threads *********" << std::endl;
  Thread32First(threads_snapshot, &thread_info);

  // Цикл для вывода списка процессов
  do {
    std::cout << "Thread " << thread_info.th32ThreadID << "_______" 
              << "Owner - " << thread_info.th32OwnerProcessID << std::endl;
    
  }  while (Thread32Next(threads_snapshot, &thread_info));

  CloseHandle(threads_snapshot); // закрыли процесс снимка
  std::cout << "********* End list of threads *********" << std::endl;

  // Получение всех модулей с помощью библиотеки Toolhelp32

  // Делаем снимок модулей
  HANDLE modules_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
  MODULEENTRY32 module_info;
  module_info.dwSize = sizeof(MODULEENTRY32);

  std::cout << "********* Start list of modules *********" << std::endl;
  Module32First(modules_snapshot, &module_info);

  // Цикл для вывода списка модулей
  do {
    std::cout << "_____ Module " << module_info.szModule << "_____" << std::endl;
    std::cout << "Path: " << module_info.szExePath << std::endl;
    std::cout << "Size: " << module_info.modBaseSize << std::endl;
    std::cout << "Usage: " << module_info.ProccntUsage << std::endl;

    
  }  while (Module32Next(modules_snapshot, &module_info));

  // Закрываем процесс снимка
  CloseHandle(modules_snapshot); 
  std::cout << "********* End list of modules *********" << std::endl;

  // Пауза
  system("pause");

  return 0;
}
