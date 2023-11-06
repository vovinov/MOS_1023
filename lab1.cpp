#define SECURITY_WIN32 
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TCHAR.h>

 
int main()
{

    char buffer[256];
    char username[256];
    TCHAR windows_path_buffer[256];
    TCHAR system_path_buffer[256];
    TCHAR temp_path_buffer[256];
    DWORD size = 256;

    OSVERSIONINFO os;

    #define DIRECTORY_PATH 32767


    // void PrintError(LPCTSTR errDesc);

    // Получаем и выводим в консоль имя компьютера
    GetComputerNameA(buffer,&size);
    std::cout << "Computer name: " << buffer << std::endl;

    // Получаем и выводим в консоль имя пользователя
    GetUserNameA(username, &size);
    std::cout << "User name: " << username << std::endl;

    // Получаем и выводим в консоль путь к папке WINDOWS
    GetWindowsDirectory(windows_path_buffer, DIRECTORY_PATH);
    std::cout << "Windows Directory: " << windows_path_buffer << std::endl;

    // Получаем и выводим в консоль путь к папке SYSTEM 
    GetSystemDirectory( system_path_buffer, DIRECTORY_PATH);
    std::cout << "System Directory: " << system_path_buffer << std::endl;

    // Получаем и выводим в консоль путь к папке TEMP
    /*
    GetTempPath( DIRECTORY_PATH, temp_path_buffer);
    if (temp_path_buffer > DIRECTORY_PATH || (temp_path_buffer == 0))
    {
        PrintError(TEXT("GetTempPath failed"));
    }
    std::cout << "Temp directory: " << temp_path_buffer << std::endl;
    */

    GetVersionEx(&os);
    std::cout << "OS Version: " << os.dwMajorVersion << std::endl;
}
