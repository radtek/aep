/**
* @file
* @brief 定义辅助函数的头文件.
* @author ruoxi
*
* 声明辅助函数.
*/

#include "rc.h"

#include <string>

using namespace std;

namespace Utility
{
    bool FileExists(LPCWSTR fileName);
    RC DeleteFile(LPCWSTR fileName);

    void PromptErrorMessage(LPCWSTR msg);
    void PromptLastErrorMessage();

    string Wstring2String(const wstring &ws);
    wstring String2Wstring(const string &s);
};
