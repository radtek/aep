#ifndef __USER_DATA_FILE_H__
#define __USER_DATA_FILE_H__

#include "data_file.h"

class UserDataFile : public DataFile
{
public:
    UserDataFile(wstring fileName);
    virtual ~UserDataFile();

    RC InsertUser(const wstring &name, const wstring &password);
    RC QueryUser(const wstring &name, const wstring &password);

protected:
    virtual RC ParseLine(const wstring &line);

protected:
    typedef map<wstring, wstring> UserList;
    UserList m_UserList;
};

#endif // __USER_DATA_FILE_H__
