#include <windows.h>
#include <stdio.h>
#include "beacon.h"

WINUSERAPI int WINAPI USER32$MessageBoxA(HWND hWnd,LPCSTR lpText,LPCSTR lpCaption,UINT uType);
WINBASEAPI DWORD WINAPI KERNEL32$GetLastError(void);
WINBASEAPI int __cdecl MSVCRT$strcmp(const char* _Str1, const char* _Str2);
WINBASEAPI WINBOOL WINAPI KERNEL32$ReadFile (HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
WINBASEAPI HANDLE WINAPI KERNEL32$CreateFileA(
    LPCSTR                lpFileName,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwCreationDisposition,
    DWORD                 dwFlagsAndAttributes,
    HANDLE                hTemplateFile
);
WINBASEAPI WINBOOL WINAPI KERNEL32$CloseHandle (HANDLE hObject);

int go(char * args, unsigned long len) {
   datap parser;
   BeaconDataParse(&parser, args, len);
   char *messageType;
   char *message;
   char *filePath;
   messageType = BeaconDataExtract(&parser, NULL);
   message = BeaconDataExtract(&parser, NULL);
   filePath = BeaconDataExtract(&parser, NULL);
   BeaconPrintf(CALLBACK_OUTPUT, "Executing MessageBoxA on the target machine\n");
   int result = -1;
   
   HANDLE hFile = KERNEL32$CreateFileA(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hFile == INVALID_HANDLE_VALUE) {
      BeaconPrintf(CALLBACK_ERROR, "Failed to open file: %s", filePath);
      return 1;
    }
      char buffer[1024];
      DWORD bytesRead;
      if (!KERNEL32$ReadFile(hFile, buffer, sizeof(buffer) -1, &bytesRead, NULL) || bytesRead == 0) {
        BeaconPrintf(CALLBACK_ERROR, "Failed to read file.");
        KERNEL32$CloseHandle(hFile);
        return 1;
    }
    
    KERNEL32$CloseHandle(hFile);
    result = USER32$MessageBoxA(NULL, buffer , "MessageBox BOF", MB_ICONINFORMATION | MB_OKCANCEL);
      
   
  
   
   if ( result ==0 ) {
      BeaconPrintf(CALLBACK_ERROR, "Could not execute MessageBoxA. Encountered error: %d",KERNEL32$GetLastError());
   }
   else {
      BeaconPrintf(CALLBACK_OUTPUT, "Successfully executed MessageBoxA on the target machine.\n");
   }
   
   return 0;
}
