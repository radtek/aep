/**
* @file
* @brief 外部数据类cpp文件.
* @author ruoxi
*
* 实现了外部数据类.
*/

#include "external_data.h"

ExternalData::ExternalData()
:
m_Array(NULL)
{
}

ExternalData::~ExternalData()
{
}

UINT32 ExternalData::GetTypeId()
{
    return s_ComponentId;
}

void ExternalData::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << CString(m_FilePath.c_str());
}

void ExternalData::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> str;
    m_FilePath = str;
}

void ExternalData::Destroy()
{
    delete this;
}

void *ExternalData::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_DATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 ExternalData::GetId()
{
    return m_Id;
}

void ExternalData::SetId(UINT32 id)
{
    m_Id = id;
}

wstring ExternalData::GetName()
{
    return m_Name;
}

void ExternalData::SetName(wstring name)
{
    m_Name = name;
}

void ExternalData::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_FILE_PATH;
    attribute.Name = TEXT("数据文件路径");
    attribute.Type = Attribute::TYPE_STRING;
    attributeList.push_back(attribute);
}

RC ExternalData::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_FILE_PATH:
        *((wstring *)attr) = m_FilePath;
        break;
    }

    return rc;
}

RC ExternalData::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_FILE_PATH:
        m_FilePath = *((wstring *)attr);
        break;
    }

    return rc;
}

bool ExternalData::Connect(IComponent *component)
{
    return false;
}

RC ExternalData::LoadFile()
{
    RC rc;

    // FIXME

    return rc;
}

Array *ExternalData::GetArray()
{
    // FIXME
    return NULL;
}

UINT32 ExternalData::GetSize()
{
    // FIXME
    return 0;
}

ExternalData *ExternalData::Factory()
{
    ExternalData *externalData = new ExternalData;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    externalData->m_Name = name;
    ++s_Count;
    delete[] name;
    return externalData;
}

LPCWSTR ExternalData::s_ComponentName = TEXT("外部数据");

UINT32 ExternalData::s_Count = 0;
