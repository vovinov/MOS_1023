#include <iostream>
#include <windows.h>
#include<cstdlib>
#include<ctime>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

using namespace std;

HANDLE hSlot;

LPCTSTR SlotName = TEXT("\\\\.\\mailslot\\lab4.1");

BOOL ReadSlot() {

	DWORD cbMessage, cMessage, cbRead;
	BOOL fResult;
	LPTSTR lpszBuffer;
	TCHAR achID[80];
	DWORD cAllMessages;
	HANDLE hEvent;
	OVERLAPPED ov;

	cbMessage = cMessage = cbRead = 0;

	hEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("ExampleSlot"));

	if (NULL == hEvent) {
		return FALSE;
	}

	ov.Offset = 0;
	ov.OffsetHigh = 0;

	ov.hEvent = hEvent;

	fResult = GetMailslotInfo(hSlot,
		(LPDWORD)NULL,
		&cbMessage,
		&cMessage,
		(LPDWORD)NULL);


	if (cbMessage == MAILSLOT_NO_MESSAGE) {

		printf("Ожидание сообщения...\n");

		return TRUE;
	}

	cAllMessages = cMessage;

	while (cMessage != 0) {

		StringCchPrintf((LPTSTR)achID,
			80,
			TEXT("\nСообщение #%d of %d\n"),
			cAllMessages - cMessage + 1,
			cAllMessages);

		lpszBuffer = (LPTSTR)GlobalAlloc(GPTR,

			lstrlen((LPTSTR)achID) * sizeof(TCHAR) + cbMessage);

		if (NULL == lpszBuffer) {
			return FALSE;
		}

		lpszBuffer[0] = '\0';

		fResult = ReadFile(hSlot,
			lpszBuffer,
			cbMessage,
			&cbRead,
			&ov);


		StringCbCat(lpszBuffer,

			lstrlen((LPTSTR)achID) * sizeof(TCHAR) + cbMessage,

			(LPTSTR)achID);

		_tprintf(TEXT("Сообщение: %s\n"), lpszBuffer);

		GlobalFree((HGLOBAL)lpszBuffer);

		fResult = GetMailslotInfo(hSlot,

			(LPDWORD)NULL,
			&cbMessage,
			&cMessage,
			(LPDWORD)NULL);
	}

	CloseHandle(hEvent);

	return TRUE;
}

BOOL WINAPI MakeSlot(LPCTSTR lpszSlotName) {

	hSlot = CreateMailslot(lpszSlotName,

		0,
		MAILSLOT_WAIT_FOREVER,
		(LPSECURITY_ATTRIBUTES)NULL);

	return TRUE;
}

int main() {

	setlocale(LC_ALL, "RUS");

	MakeSlot(SlotName);

	while (TRUE) {

		ReadSlot();
		Sleep(3000);
	}

	return 0;
}