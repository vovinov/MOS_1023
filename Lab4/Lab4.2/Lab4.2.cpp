#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <windows.h>
#include <stdio.h>

LPCTSTR SlotName = TEXT("\\\\.\\mailslot\\lab4.1");

BOOL WriteSlot(HANDLE hSlot, LPTSTR lpszMessage) {

	BOOL fResult;
	DWORD cbWritten;
	fResult = WriteFile(hSlot,

		lpszMessage,
		(DWORD)(lstrlen(lpszMessage) + 1) * sizeof(TCHAR),
		&cbWritten,
		(LPOVERLAPPED)NULL);

	printf("Текст сообщения.\n");
	return TRUE;
}

int main() {

	setlocale(LC_ALL, "RUS");

	HANDLE hFile;

	hFile = CreateFile(SlotName,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		(LPSECURITY_ATTRIBUTES)NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);

	LPCTSTR text1 = TEXT("Текст сообщения 1.");
	LPCTSTR text2 = TEXT("Текст сообщения 2.");
	LPCTSTR text3 = TEXT("Текст сообщения 3.");

	WriteSlot(hFile, LPTSTR(text1));

	Sleep(3000);

	WriteSlot(hFile, LPTSTR(text2));

	Sleep(3000);

	WriteSlot(hFile, LPTSTR(text3));

	printf("Завершение");

	CloseHandle(hFile);

	return TRUE;
}