
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

	// ������������� ������ Pipe
	HANDLE hNamedPipe;

	// ���������� ����, ���������� ����� �����
	DWORD cbWritten;

	// ���������� ����, �������� ����� �����
	DWORD cbRead;

	// ����� ��� �������� ������
	char szBuf[256];

	LPCTSTR szPipeName = TEXT("\\\\.\\pipe\\$MyPipe$");

	// ������� ����� � ��������� PIPES
	hNamedPipe = CreateFile(
		szPipeName, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);


	// ������� ��������� � �������� ������
	fprintf(stdout, "\n���������� �������. �������� 'exit' ��� ������\n");

	// ���� ������ ������� � ��������� ���������
	while (TRUE) {

		// ������� ����������� ��� ����� �������
		printf("cmd>");

		// ������ ��������� ������
		cin >> szBuf;

		// �������� ��������� ������ ���������� ��������  � �������� �������
		if (!WriteFile(hNamedPipe, szBuf, strlen(szBuf) + 1,
			&cbWritten, NULL))

			break;

		// �������� ��� �� ������� ������� �� �������
		if (ReadFile(hNamedPipe, szBuf, 512, &cbRead, NULL))
			printf("������������ �������: <%s>\n", szBuf);

		// ���� ��������� ������, ������� �� ��� � ��������� ������ ����������
		else {
			fprintf(stdout, "������\n",
				GetLastError());

			_getch();
			break;
		}

		// � ����� �� ������� "exit" ��������� ����
		// ������ ������� � ��������� ���������
		if (!strcmp(szBuf, "exit"))

			break;
	}

	// ��������� ������������� ������
	CloseHandle(hNamedPipe);

	return 0;
}