#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <strsafe.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

int main() {

	setlocale(LC_ALL, "RUS");

	// ���� ��������� �������� ������
	BOOL fConnected;

	// ������������� ������ Pipe
	HANDLE hNamedPipe;

	// ��� ������������ ������ Pipe
	LPCTSTR lpszPipeName = TEXT("\\\\.\\pipe\\$MyPipe$");

	// ����� ��� �������� ������ ����� �����
	char szBuf[512];

	// ���������� ���� ������, �������� ����� �����
	DWORD cbRead;

	// ���������� ���� ������, ���������� ����� �����
	DWORD cbWritten;

	// ������� ����� Pipe, ������� ��� lpszPipeName
	hNamedPipe = CreateNamedPipe(
		lpszPipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		512, 512, 5000, NULL);

	// ������� ��������� � ������ �������� �������� ������
	fprintf(stdout, "�������� ����������...\n");

	// ������� ���������� �� ������� �������
	fConnected = ConnectNamedPipe(hNamedPipe, NULL);

	// ��� ������������� ������ ������� �� ���
	if (!fConnected)	{

		switch (GetLastError()) {

		case ERROR_NO_DATA:

			fprintf(stdout, "ConnectNamedPipe: ERROR_NO_DATA");
			_getch();
			CloseHandle(hNamedPipe);
			return 0;
			break;

		case ERROR_PIPE_CONNECTED:
			fprintf(stdout,
				"ConnectNamedPipe: ERROR_PIPE_CONNECTED");
			_getch();
			CloseHandle(hNamedPipe);
			return 0;

			break;

		case ERROR_PIPE_LISTENING:
			fprintf(stdout,
				"ConnectNamedPipe: ERROR_PIPE_LISTENING");
			_getch();
			CloseHandle(hNamedPipe);
			return 0;

			break;

		case ERROR_CALL_NOT_IMPLEMENTED:
			fprintf(stdout,
				"ConnectNamedPipe: ERROR_CALL_NOT_IMPLEMENTED");
			_getch();
			CloseHandle(hNamedPipe);
			return 0;

			break;

		default:

			fprintf(stdout, "ConnectNamedPipe: Error %ld\n",
				GetLastError());
			_getch();
			CloseHandle(hNamedPipe);
			return 0;

			break;
		}

		CloseHandle(hNamedPipe);

		_getch();
		return 0;
	}

	// ������� ��������� �� �������� �������� ������
	fprintf(stdout, "\n���������� �������. ������� �������...\n");

	// ���� ��������� ������ ����� �����
	while (TRUE) {

		// �������� ��������� ������� ����� ����� Pipe
		if (ReadFile(hNamedPipe, szBuf, 512, &cbRead, NULL)) {

			// �������� ��� ������� ������� �����������	����������
			if (!WriteFile(hNamedPipe, szBuf, strlen(szBuf) + 1,
				&cbWritten, NULL))

				break;

			// ������� �������� ������� �� �������
			printf("��������: <%s>\n", szBuf);

			// ���� ������ ������� "exit",��������� ������ ����������
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