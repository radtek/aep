/**
* @file
* @brief 组件相关函数cpp文件.
* @author ruoxi
*
* 实现了组件相关函数.
*/

#include "component.h"
#include <strsafe.h>

LPCSTR Component::registerClientComponentFuncName = "RegisterClientComponent";

static void ErrorExit(LPTSTR lpszFunction);

RC Component::LoadClientComponentDll(LPCWSTR fileName, void **dllHandle)
{
    *dllHandle = LoadLibrary(fileName);

    if (!*dllHandle)
    {
        return RC::COMPONENT_LOADDLL_ERROR;
    }

    return OK;
}

RC Component::RegisterClientComponent(void *dllHandle, ComponentInfoList &componentInfoList)
{
    RC rc;

    typedef void (*RegisterClientComponentFunc)(ComponentInfoList &componentInfoList);
    RegisterClientComponentFunc func = (RegisterClientComponentFunc)GetProcAddress((HMODULE)dllHandle, registerClientComponentFuncName);

    if (!func)
    {
        return RC::COMPONENT_REGISTERCLIENTCOMPONENT_ERROR;
    }

    func(componentInfoList);

    return rc;
}

RC Component::UnloadClientComponentDll(void *dllHandle)
{
    FreeLibrary((HMODULE)dllHandle);
    return OK;
}

void ErrorExit(LPTSTR lpszFunction)
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw); 
}
