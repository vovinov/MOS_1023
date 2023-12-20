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