#define SECURITY_WIN32 
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TCHAR.h>
#include <winuser.h>

 
int main()
{

    DWORD size = 256;
    PVOID wheel_scroll_chars {};
    char buffer[256];
    char username[256];
    TCHAR windows_path_buffer[256];
    TCHAR system_path_buffer[256];
    TCHAR temp_path_buffer[256];
    TCHAR wallpaper_buffer[256];

    OSVERSIONINFO os;

    #define DIRECTORY_PATH 32767
    #define WALLPAPER_PATH 32767


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

    // Получаем и выводим в консоль версию операционной системы
    GetVersionEx(&os);
    std::cout << "OS Version: " << os.dwMajorVersion << std::endl;

    // Системные метрики

    // Получаем и выводим в консоль количество мониторов
    std::cout << "System metric. Monitors: " << GetSystemMetrics(SM_CMONITORS) << std::endl;

    // Получаем и выводим в консоль информацию установлена ли мышь
    if (GetSystemMetrics(SM_MOUSEPRESENT))
        std::cout << "System metric. Mouse installed" << std::endl;
    else
        std::cout << "System metric. No mouse installed" << std::endl;

    // Системные парамеры

    // Получаем и выводим в консоль полный путь к файлу рисунка рабочего стола
    SystemParametersInfoA(SPI_GETDESKWALLPAPER, WALLPAPER_PATH, wallpaper_buffer, 0);
    std::cout << "System parameters. Path to wallpaper: " << wallpaper_buffer << std::endl;
    
    // Получаем и выводим в консоль значение времени ожидания заставки экрана (в секундах)
    SystemParametersInfoA(SPI_GETWHEELSCROLLCHARS, 0, wheel_scroll_chars, 0);
    std::cout << "System parameters. Screensaver timeout: " << wheel_scroll_chars << std::endl;

    return 0;
}
