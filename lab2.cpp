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

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <locale>

#define cout wcout

#define cin wcin

using namespace std;

#define STRING_LENGTH 1024

int i = 0;

int GetFileName(wchar_t *outName, wchar_t *fullName, const int bufferLength) {

wchar_t *name = wcsrchr(fullName, L'\\');

rsize_t size = 256;

if (name == NULL)

{

wcsncpy_s(outName, size, fullName, bufferLength);

return 0;

} else

{

wcsncpy_s(outName, size, name + 1, bufferLength);

return 1;

}

}

void Vivod(HMODULE hModule, wchar_t* longName) {

wchar_t *shortName = new wchar_t[STRING_LENGTH];

GetFileName(shortName, longName, STRING_LENGTH);

cout << "\nHandle: " << hModule << endl << "Name: " << shortName << endl << "FName: " << longName << endl;

delete shortName;

}

void task2() {

setlocale(LC_ALL, "rus");

cout.imbue(locale("rus_rus.1251"));

DWORD dCurrentId = GetCurrentProcessId();

HANDLE hCurrentPseudo = GetCurrentProcess();

HANDLE hCurrentIdDup;

DuplicateHandle(hCurrentPseudo, hCurrentPseudo, hCurrentPseudo,

&hCurrentIdDup, 0, FALSE, DUPLICATE_SAME_ACCESS);

HANDLE hCurrentIdOpen = OpenProcess(PROCESS_DUP_HANDLE, TRUE, dCurrentId);

BOOL fClosedDup = CloseHandle(hCurrentIdDup);

BOOL fClosedOpen = CloseHandle(hCurrentIdOpen);

cout << "\nИдентификатор текущего процесса: " << dCurrentId

<< "\nПсевдодескриптор текущего процесса: " << hCurrentPseudo << " *** const = -1 (FF FFF FFF) "

<< "\nДескриптор, полученный функцией DuplicateHandle: " << hCurrentIdDup

<< "\nДескриптор, полученный функцией OpenProcess: " << hCurrentIdOpen

<< "\nЗакрываем дескриптор, полученный функцией OpenProcess: ";

if (fClosedOpen)

cout << "Закрыт";

else

cout << "Не закрыт";

cout << "\nЗакрываем дескриптор, полученный функцией DuplicateHandle: ";

if (fClosedDup)

cout << "Закрыт";

else

cout << "Не закрыт\n\n " << endl;

}

void ShowProcessEntry(PROCESSENTRY32 &entry) {

cout << "th32ProcessID = " << entry.th32ProcessID; // содержится идентификационный номер процесса.

cout << "\nth32DefaultHeapID = " << entry.th32DefaultHeapID; // предназначено для хранения идентификатора {ID} для кучи процесса, действующей по умолчанию.

cout << "\nth32ModuleID = " << entry.th32ModuleID; // идентифицирует модуль, связанный с процессом.

cout << "\nth32ParentProcessID = " << entry.th32ParentProcessID; // идентифицирует родительский процесс для данного процесса.

cout << "\ncntUsage = " << entry.cntUsage; /*В поле cntUsage хранится значение счетчика ссылок процесса.Когда это значение станет

равным нулю, операционная система выгрузит процесс. */

cout << "\ncntThreads = " << entry.cntThreads; // По значению поля cntThreads можно судить о том, сколько потоков начало выполняться в данном процессе.

cout << "\npcPriClassBase = " << entry.pcPriClassBase; // В поле pcPriClassBase хранится базовый приоритет процесса.

cout << "\ndwFlags = " << entry.dwFlags; // Поле dwFlags зарезервировано.

cout << "\nszExeFile = " << entry.szExeFile; /* В поле szExeFile содержится строка с ограничивающим нуль-символом, которая представляет

собой путь и имя файла ЕХЕ - программы или драйвера, связанного с данным процессом. */

}

void ShowThreadEntry(THREADENTRY32 &entry) {

cout << "\n\nth32ThreadID = " << entry.th32ThreadID; // Поле th32ThreadID представляет собой идентификационный номер потока

cout << "\nth32OwnerProcessID = " << entry.th32OwnerProcessID; // В поле th320wnerProcessID содержится идентификатор (ID) процесса, которому принадлежит данный поток.

cout << "\ncntUsage = " << entry.cntUsage; /* В поле cntUsage содержится счетчик ссылок данного потока. При обнулении этого счетчика

поток выгружается операционной системой. */

cout << "\ntpBasePri = " << entry.tpBasePri; /* Поле tpBasePri представляет собой базовый класс приоритета потока. Это значение одинаково

для всех потоков данного процесса.Возможные значения этого поля обычно лежат в диапазоне от 4 до

24. Описания этих значений приведены в следующей таблице.

Значение Описание

4 Ожидающий

8 Нормальный

13 Высокий

24 Реальное время

*/

cout << "\ntpDeltaPri = " << entry.tpDeltaPri; /* Поле tpDeltaPri представляет собой дельта-приоритет (разницу), определяющий величину

отличия реального приоритета от значения tpBasePri. Это число со знаком, которое в сочетании с

базовым классом приоритета отображает общий приоритет потока. Константы, определенные для всех

возможных значений дельта-приоритета, перечислены в следующей таблице.

Константа Значение

THREAD_PRIORITY_IDLE -15

THREAD_PRIOR ITY_LOWEST -2

THREAD PRIORITY BELOW NORMAL -1

THREAD_PRIOR IT Y_NORMAL 0

THREAD_PRIOR I TY_ABOVE_NORHAL 1

THREAD_PRIOR ITY_H IGHEST 2

THREAD_PRI OR ITY_TIME_CRIT ICAL 15

• */

cout << "\ndwFlags = " << entry.dwFlags;

}

void ShowModuleEntry(MODULEENTRY32 &entry) {

cout << "\n\nth32ModuleID \t= \t" << entry.th32ModuleID; // Поле th32ModuleID представляет собой идентификатор модуля

cout << "\nth32ProcessID \t= \t" << entry.th32ProcessID; // Поле th32processID содержит идентификатор (ID) опрашиваемого процесса.

cout << "\nGlblcntUsage \t= \t" << entry.GlblcntUsage; // Поле GlblcntUsage содержит глобальный счетчик ссылок данного модуля.

cout << "\nProccntUsage \t= \t" << entry.ProccntUsage; // Поле ProccntUsage содержит счетчик ссылок модуля в контексте процесса-владельца.

cout << "\nmodBaseAddr \t= \t" << entry.modBaseAddr; // Поле modBaseAddr представляет собой базовый адрес модуля в памяти.

cout << "\nmodBaseSize \t= \t" << entry.modBaseSize; // Поле modBaseSize определяет размер (в байтах) модуля в памяти.

cout << "\nhModule \t= \t" << entry.hModule; // В поле hHodule содержится дескриптор модуля.

cout << "\nszModule \t= \t" << entry.szModule; // имя модуля

cout << "\nszExePath \t= \t" << entry.szExePath; // Поле szExepath предназначено для хранения строки с ограничивающим нуль-символом, содержащей полный путь модуля.

}

void ShowThreads() {

HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); // Включает в снимок список потоков Win32

cout << "\nSnapshot ID = " << hSnapshot;

THREADENTRY32 entry;

entry.dwSize = sizeof(THREADENTRY32);

Thread32First(hSnapshot, &entry);

cout << endl << "\n ********* Потоки *********";

do

{

//if (entry.th32OwnerProcessID = ProcessID) {

ShowThreadEntry(entry);

//}

//i++;

} while (Thread32Next(hSnapshot, &entry) && i < 14);

//i = 0;

CloseHandle(hSnapshot);

cout << endl << "********* Конец данных о потоках *********" << endl;

}

void ShowModules() {

HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

MODULEENTRY32 meModuleEntry;

HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);

cout << "\nSnapshot ID = " << hSnapshot;

cout << "\n\n********* Модули *********" << endl;

if (INVALID_HANDLE_VALUE == hSnapshot) {

return;

}

meModuleEntry.dwSize = sizeof(MODULEENTRY32);

Module32First(hSnapshot, &meModuleEntry);

do {

ShowModuleEntry(meModuleEntry);

if (i == 10) {

system("pause");

i = 0;

}

else i++;

} while (Module32Next(hSnapshot, &meModuleEntry));

CloseHandle(hSnapshot);

cout << "\n\n********* Конец данных о модулях *********" << endl;

}

void ShowProcesses() {

PROCESSENTRY32 peProcessEntry;

HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

cout << "\nSnapshot ID = " << hSnapshot;

cout << endl << "********* Процессы *********" << endl;

if (INVALID_HANDLE_VALUE == hSnapshot) {

return;

}

peProcessEntry.dwSize = sizeof(PROCESSENTRY32);

Process32First(hSnapshot, &peProcessEntry);

do {

cout << endl << "********* Процесс *********\n" << endl;

ShowProcessEntry(peProcessEntry);

} while (Process32Next(hSnapshot, &peProcessEntry));

CloseHandle(hSnapshot);

cout << "********* Конец данных о процессах *********" << endl;

}

void task3() {

ShowProcesses();

system("pause");

ShowThreads();

system("pause");

ShowModules();

}

int main(int argv, char **argc)

{

setlocale(LC_ALL, "rus");

cout.imbue(locale("rus_rus.1251"));

bool flg = true;

while (flg)

{

char* param = new char[STRING_LENGTH];

size_t pReturnValue = strlen(param) + 1;

strcpy_s(param, STRING_LENGTH, argc[0]);

wchar_t* longName = new wchar_t[pReturnValue]; // полное имя модуля

wchar_t *shortName = new wchar_t[STRING_LENGTH]; // имя модуля

HMODULE hModule; //дескриптор модуля

system("cls");

cout << "\nЗдравствуйте, выберите нужный раздел, указав цифру:" << endl

<< "1: Вывести Name, FName, Handle" << endl

<< "2: Задать Name" << endl

<< "3: Задать FName" << endl

<< "4: Задать Handle" << endl

<< "5: Задание 2" << endl

<< "6: Задание 3" << endl

<< "0: Выход" << endl

<< "Выбор: ";

int n = 0;

cin >> n;

switch (n)

{

case 1:

{

size_t size;

mbstowcs_s(&size, longName, pReturnValue, param, 256);

hModule = GetModuleHandle(longName);

Vivod(hModule, longName);

break;

}

case 2:

{

cout << endl << "Введите Name: ";

cin >> shortName;

GetModuleFileName(GetModuleHandle(shortName), longName, STRING_LENGTH);

hModule = GetModuleHandle(longName);

Vivod(hModule, longName);

break;

}

case 3:

{

cout << endl << "Введите FName: ";

cin >> longName;

GetFileName(shortName, longName, STRING_LENGTH);

hModule = GetModuleHandle(longName); // получение дескриптора модуля по имени файла

Vivod(hModule, longName);

break;

}

case 4:

{

cout << endl << "Введите Handle: ";

wchar_t* temp = new wchar_t[10];

cin >> temp;

wchar_t *endptr;

long num = wcstoul(temp, &endptr, 16);

hModule = (HMODULE)num;

GetModuleFileName(hModule, longName, STRING_LENGTH);

Vivod(hModule, longName);

delete[] temp;

break;

}

case 5:

{

task2();

break;

}

case 6:

{

task3();

break;

}

case 0:

{

flg = false;

break;

}

}

delete[] param;

delete[] longName;

delete[] shortName;

system("pause");

}