//det(A) = 1 * det(A11) - 2 * det(A12) + 3 * det(A13),

//где A11, A12 и A13 - матрицы меньшего порядка, полученные из исходной матрицы A удалением первой строки и соответствующего столбца.

/*
матрицу A размером 3x3:

A = | 1  2  3 |
    | 4  5  6 |
    | 7  8  9 |

Мы можем вычислить определитель этой матрицы, используя разложение по первой строке:

det(A) = 1 * det(A11) - 2 * det(A12) + 3 * det(A13),

где A11, A12 и A13 - матрицы меньшего порядка, полученные из исходной матрицы A удалением первой строки и соответствующего столбца.

A11 = | 5  6 |
      | 8  9 |

A12 = | 4  6 |
      | 7  9 |

A13 = | 4  5 |
      | 7  8 |

Теперь мы можем вычислить определители A11, A12 и A13:

det(A11) = (5 * 9) - (6 * 8) = 45 - 48 = -3
det(A12) = (4 * 9) - (6 * 7) = 36 - 42 = -6
det(A13) = (4 * 8) - (5 * 7) = 32 - 35 = -3

Теперь мы можем подставить эти значения в формулу определителя:

det(A) = 1 * (-3) - 2 * (-6) + 3 * (-3)
       = -3 + 12 - 9
       = 0

Таким образом, определитель матрицы A равен 0.
*/

/*
#include <windows.h>
#include <stdio.h>

HANDLE hSlot;
LPCTSTR SlotName = TEXT("\\\\.\\mailslot\\sample_mailslot");

BOOL WINAPI MakeSlot(LPCTSTR lpszSlotName) { 
  hSlot = CreateMailslot(lpszSlotName, 
      0,                             
      MAILSLOT_WAIT_FOREVER,         
      (LPSECURITY_ATTRIBUTES) NULL); 

  if (hSlot == INVALID_HANDLE_VALUE) { 
    printf("CreateMailslot failed with %d\n", GetLastError());
    return FALSE; 
  } 
  else 
    printf("Mailslot created successfully.\n");
    
  return TRUE; 
};

int main() {

  MakeSlot(SlotName);

  return 0;
};
*/

#include <iostream>
#include <windows.h>
#include<cstdlib>
#include<ctime>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

using namespace std;

HANDLE hSlot;
LPCTSTR SlotName = TEXT("\\\\.\\mailslot\\sample_mailslot");

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

if (NULL == hEvent)
  return FALSE;

ov.Offset = 0;
ov.OffsetHigh = 0;
ov.hEvent = hEvent;

fResult = GetMailslotInfo(hSlot, // mailslot handle

(LPDWORD)NULL, // no maximum message size

&cbMessage, // size of next message
&cMessage, // number of messages

(LPDWORD)NULL); // no read time-out

if (!fResult) {
  printf("GetMailslotInfo failed with %d.\n", GetLastError());
  return FALSE;
};

if (cbMessage == MAILSLOT_NO_MESSAGE) {
  printf("Waiting for a message...\n");
  return TRUE;
};

cAllMessages = cMessage;

while (cMessage != 0) {

// Create a message-number string.

StringCchPrintf((LPTSTR)achID, 80, TEXT("\nMessage #%d of %d\n"),

cAllMessages - cMessage + 1,
cAllMessages);

// Allocate memory for the message.

lpszBuffer = (LPTSTR)GlobalAlloc(GPTR,
lstrlen((LPTSTR)achID) * sizeof(TCHAR) + cbMessage);

if (NULL == lpszBuffer) {
  return FALSE;

lpszBuffer[0] = '\0';

fResult = ReadFile(hSlot,

lpszBuffer,

cbMessage,

&cbRead,

&ov);

if (!fResult)

{

printf("ReadFile failed with %d.\n", GetLastError());

GlobalFree((HGLOBAL)lpszBuffer);

return FALSE;

}

// Concatenate the message and the message-number string.

StringCbCat(lpszBuffer,

lstrlen((LPTSTR)achID) * sizeof(TCHAR) + cbMessage,

(LPTSTR)achID);

// Display the message.

_tprintf(TEXT("Contents of the mailslot: %s\n"), lpszBuffer);

//Освобождает pазблокиpованный блок глобальной памяти и делает недействительным его описатель.

GlobalFree((HGLOBAL)lpszBuffer);

fResult = GetMailslotInfo(hSlot, // mailslot handle

(LPDWORD)NULL, // no maximum message size

&cbMessage, // size of next message

&cMessage, // number of messages

(LPDWORD)NULL); // no read time-out

if (!fResult) {
  printf("GetMailslotInfo failed (%d)\n", GetLastError());
  return FALSE;
}

}

CloseHandle(hEvent);

return TRUE;
}

BOOL WINAPI MakeSlot(LPCTSTR lpszSlotName) {

hSlot = CreateMailslot(lpszSlotName, 
                        0, // no maximum message size
                        MAILSLOT_WAIT_FOREVER, // no time-out for operations
                        (LPSECURITY_ATTRIBUTES)NULL); // default security

if (hSlot == INVALID_HANDLE_VALUE) {
  printf("CreateMailslot failed with %d\n", GetLastError());
  return FALSE;
};

  return TRUE;
}

int main() {

  MakeSlot(SlotName);

  while (TRUE) {
    ReadSlot();
    Sleep(3000);
  }

  return 0;
}