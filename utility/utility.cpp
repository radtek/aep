/**
* @file
* @brief ���帨��������cpp�ļ�.
* @author ruoxi
*
* ���帨������.
*/

#include "utility.h"
#include <strsafe.h>

void Utility::PromptLastErrorMessage()
{
    LPVOID msg;
    LPVOID disp;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &msg,
        0, NULL );

    // Display the error message and exit the process

    disp = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)msg) + 100) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)disp, 
        LocalSize(disp) / sizeof(TCHAR),
        TEXT("Error code %d: %s"), 
        dw, msg); 
    MessageBox(NULL, (LPCTSTR)disp, TEXT("Error"), MB_OK); 

    LocalFree(msg);
    LocalFree(disp);
    // ExitProcess(dw); 
}
