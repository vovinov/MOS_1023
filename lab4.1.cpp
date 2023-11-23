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