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

	// Флаг успешного создания канала
	BOOL fConnected;

	// Идентификатор канала Pipe
	HANDLE hNamedPipe;

	// Имя создаваемого канала Pipe
	LPCTSTR lpszPipeName = TEXT("\\\\.\\pipe\\$MyPipe$");

	// Буфер для передачи данных через канал
	char szBuf[512];

	// Количество байт данных, принятых через канал
	DWORD cbRead;

	// Количество байт данных, переданных через канал
	DWORD cbWritten;

	// Создаем канал Pipe, имеющий имя lpszPipeName
	hNamedPipe = CreateNamedPipe(
		lpszPipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		512, 512, 5000, NULL);

	// Выводим сообщение о начале процесса создания канала
	fprintf(stdout, "Ожидание соединения...\n");

	// Ожидаем соединения со стороны клиента
	fConnected = ConnectNamedPipe(hNamedPipe, NULL);

	// Выводим сообщение об успешном создании канала
	fprintf(stdout, "\nСоединение успешно. Ожидаем команды...\n");

	// Цикл получения команд через канал
	while (TRUE) {

		// Получаем очередную команду через канал Pipe
		if (ReadFile(hNamedPipe, szBuf, 512, &cbRead, NULL)) {

			// Посылаем эту команду обратно клиентскому	приложению
			if (!WriteFile(hNamedPipe, szBuf, strlen(szBuf) + 1,
				&cbWritten, NULL))

				break;

			// Выводим принятую команду на консоль
			printf("Получено: <%s>\n", szBuf);

			// Если пришла команда "exit",завершаем работу приложения
			if (!strcmp(szBuf, "exit"))
				break;
		}

		else {
			fprintf(stdout, "ReadFile: Error %ld\n",
				GetLastError());

			_getch();
			break;
		}
	}

	CloseHandle(hNamedPipe);

	return 0;
}