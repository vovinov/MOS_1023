
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <Windows.h>
#include <cstring>

struct SharedData {
  int sch = 0;
  char mas[16];
};

HANDLE mutex;
HANDLE mapping;

int main() {

  DWORD dwBytesWritten = 0;

  HANDLE hFile = CreateFile(TEXT("test1.txt"), // name of the write

  GENERIC_WRITE | GENERIC_READ, // open for reading and writing

  FILE_SHARE_WRITE | FILE_SHARE_READ, // share for reading and writing

  NULL, // default security

  OPEN_ALWAYS, // create new file only

  FILE_ATTRIBUTE_NORMAL, // normal file

  NULL);

  mapping = CreateFileMappingA(hFile, nullptr, PAGE_READWRITE, 0, sizeof(SharedData), "first1");

  std::unique_ptr<SharedData, decltype(&UnmapViewOfFile)> data(

  (SharedData*)MapViewOfFile(mapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0),

  UnmapViewOfFile);

  mutex = OpenMutexA(MUTEX_ALL_ACCESS, TRUE, "first");
  if (mutex == NULL) {
    mutex = CreateMutexA(NULL, FALSE, "first");
  }

  std::cout << "hFile:" << hFile << std::endl;

  std::cout << "mapping:" << mapping << std::endl;

  std::cout << "mutex:" << mutex << std::endl;

  DWORD dwBytesToWrite = 13;

  //system("pause");

  std::thread user_input_thread([&] {

    WaitForSingleObject(mutex, INFINITE);

    for (int i = 0; i < 4; i++) {

      data->mas[data->sch] = '3';

      std::cout << "mas[" << data->sch << "]= " << data->mas[data->sch] << " ";

      WriteFile(

      hFile, // open file handle

      (LPCVOID)data->mas[data->sch], // start of data to write

      dwBytesToWrite, // number of bytes to write

      &dwBytesWritten, // number of bytes that were written

      NULL);

      Sleep(500);
      data->sch++;
    }
    ReleaseMutex(mutex);
  });

  user_input_thread.join();

  system("pause");

  CloseHandle(hFile);

}