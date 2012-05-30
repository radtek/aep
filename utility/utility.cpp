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
#include "Shlwapi.h"

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
Attribute::AttributeType Utility::StringToAttributeType(wstring str)
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
        return Attribute::TYPE_STRING;
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

RC Utility::SaveBmpFile(CString fileName, UINT32 x, UINT32 y,
                        const char *content,
                        UINT32 width, UINT32 height,
                        UINT32 startX, UINT32 startY,
                        UINT32 depth, RGBQUAD *colorTable)
{
    RC rc;

    if (x == 0 || y == 0)
    {
        return RC::UTILITY_SAVE_IMAGE_ERROR;
    }

    if (width == 0)
    {
        width = x;
    }
    if (height == 0)
    {
        height = y;
    }
    if (startX >= width || startY >= height)
    {
        return RC::UTILITY_SAVE_IMAGE_ERROR;
    }

    UINT32 colorTableSize = 0;
    if (depth == 8)
    {
        colorTableSize = 1024;
    }

    UINT32 xByte = (x * (depth / 8) + 3) / 4 * 4;
    UINT32 widthByte = (width * (depth / 8) + 3) / 4 * 4;
    UINT32 startXByte = (startX * (depth / 8) + 3) / 4 * 4;

    char *buf = new char[xByte * y];
    memset(buf, 0, xByte * y * sizeof(char));
    for (UINT32 yy = 0; yy < min(y, height - startY); ++yy)
    {
        for (UINT32 xx = 0; xx < min(xByte, widthByte - startXByte); ++xx)
        {
            buf[yy * xByte + xx] = content[(startY + yy) * widthByte + startXByte + xx];
        }
    }

    BITMAPFILEHEADER bfh;
    bfh.bfType = 0x4D42;

    bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
        + colorTableSize + xByte * y;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;

    bfh.bfOffBits = 54 + colorTableSize;

    BITMAPINFOHEADER bih;

    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = x;
    bih.biHeight = y;
    bih.biPlanes = 1;
    bih.biBitCount = depth;
    bih.biCompression = BI_RGB;
    bih.biSizeImage = xByte * y;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrImportant = 0;
    bih.biClrUsed = 0;

    if (!FileExists(fileName))
    {
        if (!CreateFileNested(fileName))
        {
            delete[] buf;
            return RC::UTILITY_SAVE_IMAGE_ERROR;
        }
    }
    HANDLE file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    UINT32 written = 0;
    if (FALSE == WriteFile(file, (LPCVOID)&bfh, sizeof(BITMAPFILEHEADER), (LPDWORD)&written, NULL))
    {
        delete[] buf;
        return RC::UTILITY_SAVE_IMAGE_ERROR;
    }
    if (FALSE == WriteFile(file, (LPCVOID)&bih, sizeof(BITMAPINFOHEADER), (LPDWORD)&written, NULL))
    {
        delete[] buf;
        return RC::UTILITY_SAVE_IMAGE_ERROR;
    }
    if (depth == 8)
    {
        if (FALSE == WriteFile(file, (LPCVOID)colorTable, colorTableSize, (LPDWORD)&written, NULL))
        {
            delete[] buf;
            return RC::UTILITY_SAVE_IMAGE_ERROR;
        }
    }
    if (FALSE == WriteFile(file, (LPCVOID)buf, xByte * y, (LPDWORD)&written, NULL))
    {
        delete[] buf;
        return RC::UTILITY_SAVE_IMAGE_ERROR;
    }
    delete[] buf;
    CloseHandle(file);

    return rc;
}

/*
bool Utility::SaveBmpFile(HBITMAP hBitmap, CString fileName)       
{       
    HDC     hDC;       
    //当前分辨率下每象素所占字节数       
    int     iBits;       
    //位图中每象素所占字节数       
    WORD     wBitCount;       
    //定义调色板大小，     位图中像素字节大小     ，位图文件大小     ，     写入文件字节数           
    DWORD     dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;           
    //位图属性结构           
    BITMAP     Bitmap;               
    //位图文件头结构       
    BITMAPFILEHEADER     bmfHdr;               
    //位图信息头结构           
    BITMAPINFOHEADER     bi;               
    //指向位图信息头结构               
    LPBITMAPINFOHEADER     lpbi;               
    //定义文件，分配内存句柄，调色板句柄           
    HANDLE     fh,   hDib,   hPal,hOldPal=NULL;           

    //计算位图文件每个像素所占字节数           
    hDC  = CreateDC(TEXT("DISPLAY"),   NULL,   NULL,   NULL);       
    iBits  = GetDeviceCaps(hDC,   BITSPIXEL)     *     GetDeviceCaps(hDC,   PLANES);           
    DeleteDC(hDC);           
    if(iBits <=  1)                                                 
        wBitCount = 1;           
    else  if(iBits <=  4)                             
        wBitCount  = 4;           
    else if(iBits <=  8)                             
        wBitCount  = 8;           
    else                                                                                                                             
        wBitCount  = 24;           

    GetObject(hBitmap,   sizeof(Bitmap),   (LPSTR)&Bitmap);       
    bi.biSize= sizeof(BITMAPINFOHEADER);       
    bi.biWidth = Bitmap.bmWidth;       
    bi.biHeight =  Bitmap.bmHeight;       
    bi.biPlanes =  1;       
    bi.biBitCount = wBitCount;       
    bi.biCompression= BI_RGB;       
    bi.biSizeImage=0;       
    bi.biXPelsPerMeter = 0;       
    bi.biYPelsPerMeter = 0;       
    bi.biClrImportant = 0;       
    bi.biClrUsed =  0;       

    dwBmBitsSize  = ((Bitmap.bmWidth *wBitCount+31) / 32)*4* Bitmap.bmHeight;       

    //为位图内容分配内存           
    hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));           
    lpbi  = (LPBITMAPINFOHEADER)GlobalLock(hDib);           
    *lpbi  = bi;           

    //     处理调色板               
    hPal  = GetStockObject(DEFAULT_PALETTE);           
    if (hPal)           
    {           
        hDC  = ::GetDC(NULL);           
        hOldPal = ::SelectPalette(hDC,(HPALETTE)hPal, FALSE);           
        RealizePalette(hDC);           
    }       

    //     获取该调色板下新的像素值           
    GetDIBits(hDC,hBitmap, 0,(UINT)Bitmap.bmHeight,
        (LPSTR)lpbi+ sizeof(BITMAPINFOHEADER)+dwPaletteSize, 
        (BITMAPINFO *)lpbi, DIB_RGB_COLORS);           

    //恢复调色板               
    if (hOldPal)           
    {           
        ::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);           
        RealizePalette(hDC);           
        ::ReleaseDC(NULL,   hDC);           
    }           

    //创建位图文件               
    fh  = CreateFile(fileName,   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,         
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,   NULL);           

    if (fh     ==  INVALID_HANDLE_VALUE)         return     false;           

    //     设置位图文件头           
    bmfHdr.bfType  = 0x4D42;     //     "BM"           
    dwDIBSize  = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;               
    bmfHdr.bfSize  = dwDIBSize;           
    bmfHdr.bfReserved1  = 0;           
    bmfHdr.bfReserved2  = 0;           
    bmfHdr.bfOffBits  = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;           
    //     写入位图文件头           
    WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);           
    //     写入位图文件其余内容           
    WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);           
    //清除               
    GlobalUnlock(hDib);           
    GlobalFree(hDib);           
    CloseHandle(fh);           

    return     true;       
}
*/

wstring Utility::ModifyPathSpec(const wstring &path, bool addSpec)
{
    if (path.empty())
    {
        return TEXT("");
    }

    wstring modified = path;
    wchar_t ch = path[path.length() - 1];
    if ((ch == TEXT('\\')) || (ch == _T('/')))
    {
        if (!addSpec)
        {
            modified.erase(path.length() - 1);
        }
    }
    else
    {
        if (addSpec)
        {
            modified + TEXT('\\');
        }
    }
    return modified;
}

bool Utility::CreateDirectoryNested(LPCWSTR dirPath)
{
    if (::PathIsDirectory(dirPath))
    {
        return true;
    }

    wstring modifiedDirPath = ModifyPathSpec(dirPath, false);

    //获取上级目录
    wchar_t *parentDirPath = new wchar_t[modifiedDirPath.length() + 1];
    memcpy(parentDirPath, modifiedDirPath.c_str(), modifiedDirPath.length() * sizeof(wchar_t));
    parentDirPath[modifiedDirPath.length()] = 0;
    BOOL getPreDir = ::PathRemoveFileSpec(parentDirPath);
    if (!getPreDir)
    {
        delete[] parentDirPath;
        return false;
    }

    //如果上级目录不存在,则递归创建上级目录
    if (!::PathIsDirectory(parentDirPath))
    {
        CreateDirectoryNested(parentDirPath);
    }

    delete[] parentDirPath;

    return ::CreateDirectory(modifiedDirPath.c_str(), NULL);
}

bool Utility::CreateFileNested(LPCWSTR filePath)
{
    if (::PathFileExists(filePath))
    {
        return true;
    }

    //获取文件目录
    wstring wsFilePath(filePath);
    if (::PathIsRelative(filePath))
    {
        wsFilePath = TEXT(".\\") + wsFilePath;
    }
    wchar_t *parentDirPath = new wchar_t[wsFilePath.length() + 1];
    memcpy(parentDirPath, wsFilePath.c_str(), wsFilePath.length() * sizeof(wchar_t));
    parentDirPath[wsFilePath.length()] = 0;
    BOOL getDir = ::PathRemoveFileSpec(parentDirPath);
    if (!getDir)
    {
        delete[] parentDirPath;
        return false;
    }

    //创建文件目录
    if (!CreateDirectoryNested(parentDirPath))
    {
        delete[] parentDirPath;
        return false;
    }

    HANDLE file = ::CreateFile(filePath, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
        CREATE_ALWAYS, FILE_FLAG_BACKUP_SEMANTICS, NULL);

    if (file == INVALID_HANDLE_VALUE)
    {
        delete[] parentDirPath;
        return false;
    }

    delete[] parentDirPath;
    ::CloseHandle(file);

    return true;
}