#ifndef __DATA_FILE_H__
#define __DATA_FILE_H__

#include "rc.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class DataFile
{
public:
    DataFile(wstring fileName, wstring comment = L"#");
    virtual ~DataFile();

    RC Parse();
    RC Save();

protected:
    virtual RC ParseLine(const wstring &line) = 0;

protected:
    wstring m_FileName;
    map<wstring, wstring> m_Lines;
    wstring m_Comment;

    // Write or read configuration
    friend wostream &operator<<(wostream &os, const DataFile &file);
    friend wistream &operator>>(wistream &is, DataFile &file);
};

#endif // __DATA_FILE_H__
