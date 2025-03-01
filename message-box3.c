#include <windows.h>
#include <stdio.h>
#include "beacon.h"

WINUSERAPI int WINAPI USER32$MessageBoxA(HWND hWnd,LPCSTR lpText,LPCSTR lpCaption,UINT uType);
WINBASEAPI DWORD WINAPI KERNEL32$GetLastError(void);
WINBASEAPI int __cdecl MSVCRT$strcmp(const char* _Str1, const char* _Str2);

int go(char * args, unsigned long len) {
   datap parser;
   BeaconDataParse(&parser, args, len);
   char *messageType;
   char *message;
   messageType = BeaconDataExtract(&parser, NULL);
   message = BeaconDataExtract(&parser, NULL);
   BeaconPrintf(CALLBACK_OUTPUT, "Executing MessageBoxA on the target machine\n");
   int result = -1;
   
   if (MSVCRT$strcmp(messageType, "custom") == 0) { 
   
      result = USER32$MessageBoxA(NULL, message , "MessageBox BOF", MB_ICONINFORMATION | MB_OKCANCEL);
      }
   else {
      result = USER32$MessageBoxA(NULL, "Thank you for joining 100 Days of Red Team." , "MessageBox BOF", MB_ICONINFORMATION | MB_OKCANCEL);
   }
   
   if ( result ==0 ) {
      BeaconPrintf(CALLBACK_ERROR, "Could not execute MessageBoxA. Encountered error: %d",KERNEL32$GetLastError());
   }
   else {
      BeaconPrintf(CALLBACK_OUTPUT, "Successfully executed MessageBoxA on the target machine.\n");
   }
   
   return 0;
}
