
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <string.h>
#include <cstring>


HANDLE hEvent = NULL;

int main() {

  char c[2];
  char yes[2]="Y";

  hEvent = CreateEventA(NULL, TRUE, FALSE, "check");

  std::cout << "Are you ready? Y/N" << std::endl;
  std::cin.getline(c, 2);

  if (strcmp(c, yes) == 0) {
    SetEvent(hEvent);
  std::cout << "Let's go!\n";  
  }
  else {
    std::cout << "Okey :(\n";
  }

  system("pause");
}
