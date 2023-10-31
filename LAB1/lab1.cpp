#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <secext.h>
 
int main()
{

    char buffer[256];
    char username[256];
    DWORD size = 256;
    // Получаем имя компьютера и выводим в консоль
    GetComputerNameA(buffer,&size);
    std::cout << "Computer name: " << buffer << std::endl;

    GetUserNameA(username, &size);
    std::cout << "User name: " << buffer << std::endl;
}
