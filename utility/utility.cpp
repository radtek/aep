/**
* @file
* @brief 定义辅助函数的cpp文件.
* @author ruoxi
*
* 定义辅助函数.
*/

#include "utility.h"
#include "massert.h"
#include <strsafe.h>
#include <locale.h>
#include <math.h>

/**
* @param fileName 文件路径.
*
* 调用Windows库函数打开文件.
*/
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

/**
* @param fileName 文件路径.
*
* 调用Windows库函数删除文件.
*/
RC Utility::DeleteFile(LPCWSTR fileName)
{
    RC rc;

    if (!::DeleteFile(fileName))
    {
        return RC::FILE_DELETE_ERROR;
    }

    return rc;
}

/**
* @param msg 提示信息.
*/
void Utility::PromptMessage(LPCWSTR msg)
{
    MessageBox(NULL, msg, TEXT("消息"), MB_OK); 
}

/**
* @param msg 提示信息.
*/
void Utility::PromptErrorMessage(LPCWSTR msg)
{
    MessageBox(NULL, msg, TEXT("错误"), MB_OK); 
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

/**
* @param attributeType 属性类型.
*
* 将属性类型转化成对应的字符串.
*/
LPCWSTR Utility::AttributeTypeToString(Attribute::AttributeType attributeType)
{
    switch (attributeType)
    {
    case Attribute::TYPE_INT:
        return TEXT("整型");
    case Attribute::TYPE_DOUBLE:
        return TEXT("浮点型");
    case Attribute::TYPE_STRING:
        return TEXT("字符型");
    default:
        return TEXT("未知类型");
    }
}

/**
* @param str 属性类型字符串.
*
* 将属性类型字符串转化成对应的属性类型.
*/
ute::AttributeType Utility::StringToAttributeType(wstring str)
{
    if (str == TEXT("整型"))
    {
        return Attribute::TYPE_INT;
    }
    else if (str == TEXT("浮点型"))
    {
        return Attribute::TYPE_DOUBLE;
    }
    else if (str == TEXT("字符型"))
    {
        return Attribute::TYPE_DOUBLE;
    }
    else
    {
        return Attribute::TYPE_UNKNOWN;
    }
}

/**
* @param p1 直线端点1.
* @param p2 直线端点2.
* @param p 点.
*
* 计算点p到由点p1点p2描述的直线的距离.
*/
double Utility::DistanceToEdge(CPoint p1, CPoint p2, CPoint p)
{
    return (fabs((double)((p2.y - p1.y) * p.x + (p1.x - p2.x) * p.y + ((p2.x * p1.y) - (p1.x * p2.y))))) / (sqrt(pow((double)(p2.y - p1.y), 2) + pow((double)(p1.x - p2.x), 2))); 
}

/**
* @param p1 点1.
* @param p2 点2.
*
* 计算点p1和点p2间的距离.
*/
double Utility::DistanceToPoint(CPoint p1, CPoint p2)
{
    return sqrt(pow((double)(p1.y - p2.y), 2) + pow((double)(p1.x - p2.x), 2));
}

bool Utility::DirectoryExists(LPCWSTR pathName)
{
    DWORD attr = GetFileAttributes(pathName);
    return (attr != (DWORD)(-1)) &&
        (attr & FILE_ATTRIBUTE_DIRECTORY);
}

/**
* @param pathName 文件路径.
*
* 从文件路径中提取文件名.
*/
wstring Utility::StripFilePath(LPCWSTR pathName)
{
    MASSERT(pathName);

    wstring fileName = pathName;
    wstring::size_type pos = fileName.find_last_of(TEXT("/\\"));
    if (pos != wstring::npos)
    {
        fileName = fileName.substr(pos + 1, fileName.length());
    }

    return fileName;
}
