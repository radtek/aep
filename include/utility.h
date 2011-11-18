/**
* @file
* @brief ���帨��������ͷ�ļ�.
* @author ruoxi
*
* ������������.
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
