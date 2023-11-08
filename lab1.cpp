#define SECURITY_WIN32 
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// #include <TCHAR.h>
// #include <winuser.h>

 
int main()
{

    DWORD size = 256;
    PVOID wheel_scroll_chars;
    char buffer[MAX_PATH];
    char username[MAX_PATH];
    TCHAR windows_path_buffer[MAX_PATH];
    TCHAR system_path_buffer[MAX_PATH];
    TCHAR temp_path_buffer[MAX_PATH];
    TCHAR wallpaper_buffer[MAX_PATH];
    DWORD context_menu_buffer[MAX_PATH];
    UINT mouse_buffer[MAX_PATH];
    DWORD system_color_highlight;

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
    printf("Windows Directory: %s\n", windows_path_buffer);

    // Получаем и выводим в консоль путь к папке SYSTEM 
    GetSystemDirectory(system_path_buffer, DIRECTORY_PATH);
    printf("System Directory:: %s\n", system_path_buffer);

    // Получаем и выводим в консоль путь к папке TEMP
    GetTempPath(MAX_PATH, temp_path_buffer);
    // if (temp_path_buffer > DIRECTORY_PATH || (temp_path_buffer == 0))
    // {
    //     PrintError(TEXT("GetTempPath failed"));
    // }
    printf("Temp Directory: %s\n", temp_path_buffer);

    // Получаем и выводим в консоль версию операционной системы
    GetVersionEx(&os);
    printf("OS Version: %d\n", os.dwMajorVersion);

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
    
    // Получаем и выводим в консоль значение времени ожидания контекстного меню (в милисекундах)
    SystemParametersInfoA(SPI_GETMENUSHOWDELAY, 0, context_menu_buffer, 0);
    std::cout << "System parameters. Mouseover context menu activate after " <<  *context_menu_buffer << " ms" << std::endl;

    // Получаем и выводим в консоль текущее значение скорость мыши (значения от 1 до 20, по умолчанию - 10)
    SystemParametersInfoA(SPI_GETMOUSESPEED, 0, mouse_buffer, 0);
    std::cout << "System parameters. Mouse buffer: " <<  *mouse_buffer << std::endl;

    //  Системные цвета
    
    int aElements[1] = {COLOR_HIGHLIGHT};
    DWORD aOldColors[1];
    DWORD aNewColors[1];

    // Получение цвета для рамки выделения файлов
 
    aOldColors[0] = GetSysColor(aElements[0]); 

    printf("Current highlight color: {0x%x, 0x%x, 0x%x}\n", 
        GetRValue(aOldColors[0]), 
        GetGValue(aOldColors[0]), 
        GetBValue(aOldColors[0]));

    // Установка нового цвета
    // aNewColors[0] = RGB(0xFF, 0x7F, 0x50);  // оранженый

    // printf("\nNew highlight color: {0x%x, 0x%x, 0x%x}\n", 
    //     GetRValue(aNewColors[0]), 
    //     GetGValue(aNewColors[0]), 
    //     GetBValue(aNewColors[0]));

    // SetSysColors(1, aElements, aNewColors); 

    // printf("\nHighlight color have been changed.\n");
    // printf("Reverting to previous colors in 30 seconds...\n");

    // Sleep(30000);    

    // Возврат к первоначальным настройкам цвета

    // SetSysColors(1, aElements, aOldColors); 

    // Функции для работы со временем
    SYSTEMTIME tm, lt;

    GetSystemTime(&tm);
    GetLocalTime(&lt);  

    printf("The system time is: %02d:%02d\n", tm.wHour, tm.wMinute);
    printf("The local time is: %02d:%02d\n", lt.wHour, lt.wMinute);

    // API
    // Позиция курсора (координаты x, y)
    POINT cursor_coordinates;
    GetCursorPos(&cursor_coordinates);
    printf("The cursor coodinates is: %02d:%02d\n", cursor_coordinates.x, cursor_coordinates.y);
    
    // Выводит в консоль состояние системы питания
    SYSTEM_POWER_STATUS power_status;
    GetSystemPowerStatus(&power_status);
    printf("Battery life: %d percent\n", power_status.BatteryLifePercent);

    // Меняет местами назначение клавиш компьютерной мыши, по умолчанию - false
    BOOL swap_mouse {false};
    SwapMouseButton(swap_mouse);
  
    // Воспроизводит звуковой сигнал
    MessageBeep(0xFFFFFFFF);

    return 0;
}
