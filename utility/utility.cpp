/**
* @file
* @brief ���帨��������cpp�ļ�.
* @author ruoxi
*
* ���帨������.
*/

#include "utility.h"
#include <strsafe.h>
#include <locale.h>

bool Utility::FileExists(LPCWSTR fileName)
{
    HANDLE handle =
        CreateFile(fileName,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (INVALID_HANDLE_VALUE != handle)
    {
        CloseHandle(handle);
        return true;
    }
    return false;
}

RC Utility::DeleteFile(LPCWSTR fileName)
{
    RC rc;

    if (!::DeleteFile(fileName))
    {
        return RC::FILE_DELETE_ERROR;
    }

    return rc;
}

void Utility::PromptMessage(LPCWSTR msg)
{
    MessageBox(NULL, msg, TEXT("��Ϣ"), MB_OK); 
}

void Utility::PromptErrorMessage(LPCWSTR msg)
{
    MessageBox(NULL, msg, TEXT("����"), MB_OK); 
}

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

string Utility::Wstring2String(const wstring &ws)
{
    string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
    setlocale(LC_ALL, "chs");
    const wchar_t *_Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest, 0, _Dsize);
    wcstombs(_Dest, _Source, _Dsize);
    string result = _Dest;
    delete[] _Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

wstring Utility::String2Wstring(const string &s)
{
    setlocale(LC_ALL, "chs");
    const char *_Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest, _Source, _Dsize);
    wstring result = _Dest;
    delete[] _Dest;
    setlocale(LC_ALL, "C");
    return result;
}

bool Utility::ContainSpace(LPCSTR str)
{
    static const char whitespace[] = " \n\t\v\r\f";
    return string(str).find_first_of(whitespace) != string.npos;
}

bool Utility::ContainSpace(LPCWSTR str)
{
    static const wchar_t whitespace[] = L" \n\t\v\r\f";
    return wstring(str).find_first_of(whitespace) != wstring.npos;
}

LPCWSTR Utility::AttributeTypeToString(Attribute::AttributeType attributeType)
{
    switch (attributeType)
    {
    case Attribute::TYPE_INT:
        return TEXT("����");
    case Attribute::TYPE_DOUBLE:
        return TEXT("������");
    case Attribute::TYPE_STRING:
        return TEXT("�ַ���");
    default:
        return TEXT("δ֪����");
    }
}

Attribute::AttributeType Utility::StringToAttributeType(wstring str)
{
    if (str == TEXT("����"))
    {
        return Attribute::TYPE_INT;
    }
    else if (str == TEXT("������"))
    {
        return Attribute::TYPE_DOUBLE;
    }
    else if (str == TEXT("�ַ���"))
    {
        return Attribute::TYPE_DOUBLE;
    }
    else
    {
        return Attribute::TYPE_UNKNOWN;
    }
}