
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <strsafe.h>

using namespace std;

int main() {

	setlocale(LC_ALL, "RUS");

	// Идентификатор канала Pipe
	HANDLE hNamedPipe;

	// Количество байт, переданных через канал
	DWORD cbWritten;

	// Количество байт, принятых через канал
	DWORD cbRead;

	// Буфер для передачи данных
	char szBuf[256];

	LPCTSTR szPipeName = TEXT("\\\\.\\pipe\\$MyPipe$");

	// Создаем канал с процессом PIPES
	hNamedPipe = CreateFile(
		szPipeName, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);


	// Выводим сообщение о создании канала
	fprintf(stdout, "\nСоединение успешно. Напишите 'exit' для выхода\n");

	// Цикл обмена данными с серверным процессом
	while (TRUE) {

		// Выводим приглашение для ввода команды
		printf("cmd>");

		// Вводим текстовую строку
		cin >> szBuf;

		// Передаем введенную строку серверному процессу  в качестве команды
		if (!WriteFile(hNamedPipe, szBuf, strlen(szBuf) + 1,
			&cbWritten, NULL))

			break;

		// Получаем эту же команду обратно от сервера
		if (ReadFile(hNamedPipe, szBuf, 512, &cbRead, NULL))
			printf("Отправленная команда: <%s>\n", szBuf);

		// Если произошла ошибка, выводим ее код и завершаем работу приложения
		else {
			fprintf(stdout, "Ошибка\n",
				GetLastError());

			_getch();
			break;
		}

		// В ответ на команду "exit" завершаем цикл
		// обмена данными с серверным процессом
		if (!strcmp(szBuf, "exit"))

			break;
	}

	// Закрываем идентификатор канала
	CloseHandle(hNamedPipe);

	return 0;
}