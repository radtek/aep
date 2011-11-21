#include "user_data_file.h"
#include "utility.h"

UserDataFile::UserDataFile(wstring fileName)
:
DataFile(fileName)
{
}

UserDataFile::~UserDataFile()
{
}

RC UserDataFile::InsertUser(const wstring &name, const wstring &password)
{
    RC rc;

    static const wchar_t whitespace[] = L" \n\t\v\r\f";
    if (name.find_first_of(whitespace) != wstring::npos)
    {
        return RC::USER_BAD_NAME_ERROR;
    }
    if (password.find_first_of(whitespace) != wstring::npos)
    {
        return RC::USER_BAD_PASSWORD_ERROR;
    }
    if (m_Lines.find(name) != m_Lines.end())
    {
        return RC::USER_EXISTED_ERROR;
    }

    wostringstream ost;
    ost << name
        << TEXT(" ")
        << password
        << endl;
    m_Lines[name] = ost.str();

    CHECK_RC(Save());

    return rc;
}

RC UserDataFile::QueryUser(const wstring &name, const wstring &password)
{
    RC rc;

    if (Utility::ContainSpace(name.c_str()))
    {
        return RC::USER_BAD_NAME_ERROR;
    }
    if (Utility::ContainSpace(password.c_str()))
    {
        return RC::USER_BAD_PASSWORD_ERROR;
    }

    if (m_UserList.find(name) == m_UserList.end())
    {
        return RC::USER_UNEXISTS_USER_ERROR;
    }

    if (m_UserList[name] != password)
    {
        return RC::USER_WRONG_PASSWORD_ERROR;
    }

    return rc;
}

RC UserDataFile::ParseLine(const wstring &line)
{
    RC rc;

    wistringstream ist(line);

    wstring name, password;
    ist >> name >> password;

    m_UserList.insert(make_pair(name, password));

    return rc;
}