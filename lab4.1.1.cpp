

#include <windows.h>
#include <stdio.h>
#include <iostream>

int a;
int b;

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


// Функция для нахождения определителя матрицы
int calc_determinant(int a, int b) {
  int det;

  // det = (matrix[0][i] * (matrix[1][(i + 1)]  - matrix[0][(i + 1)] * matrix[1][(i)]));
  
  return det;
}

int main() {
  int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int det = calc_determinant(a, b);
  std::cout << "Определитель матрицы: " << det << std::endl;
  return 0;
}