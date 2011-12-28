/**
* @file
* @brief 定义辅助函数的头文件.
* @author ruoxi
*
* 声明辅助函数.
*/

#include "rc.h"
#include "interfaces.h"

#include <string>

using namespace std;

namespace Utility
{
    bool FileExists(LPCWSTR fileName);
    RC DeleteFile(LPCWSTR fileName);

    void PromptMessage(LPCWSTR msg);
    void PromptErrorMessage(LPCWSTR msg);
    void PromptLastErrorMessage();

    string Wstring2String(const wstring &ws);
    wstring String2Wstring(const string &s);

    bool ContainSpace(LPCSTR str);
    bool ContainSpace(LPCWSTR str);

    LPCWSTR AttributeTypeToString(Attribute::AttributeType attributeType);
    Attribute::AttributeType StringToAttributeType(wstring str);

    double DistanceToEdge(CPoint p1, CPoint p2, CPoint p);
    double DistanceToPoint(CPoint p1, CPoint p2);

    bool DirectoryExists(LPCWSTR pathName);
    wstring StripFilePath(LPCWSTR pathName);
};
