#include <windows.h>
#include <stdio.h>
#include "beacon.h"

WINUSERAPI int WINAPI USER32$MessageBoxA(HWND hWnd,LPCSTR lpText,LPCSTR lpCaption,UINT uType);
WINBASEAPI DWORD WINAPI KERNEL32$GetLastError(void);

int go(char * args, unsigned long len) {
   datap parser;
   BeaconDataParse(&parser, args, len);
   char *message;
   message = BeaconDataExtract(&parser, NULL);
   BeaconPrintf(CALLBACK_OUTPUT, "Executing MessageBoxA on the target machine\n");
   int result = USER32$MessageBoxA(NULL, message , "MessageBox BOF", MB_ICONINFORMATION | MB_OKCANCEL);
   
   if ( result ==0 ) {
      BeaconPrintf(CALLBACK_ERROR, "Could not execute MessageBoxA. Encountered error: %d",KERNEL32$GetLastError());
   }
   else {
      BeaconPrintf(CALLBACK_OUTPUT, "Successfully executed MessageBoxA on the target machine.\n");
   }
   
   return 0;
}
