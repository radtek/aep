/**
* @file
* @brief 外部数据类cpp文件.
* @author ruoxi
*
* 实现了外部数据类.
*/

#include "stdafx.h"

#include "external_data.h"
#include "utility.h"
#include "matlab_helper.h"

ExternalData::ExternalData()
:
m_Width(0),
m_Height(0)
{
    m_Output = new IExternalDataOutput;
}

ExternalData::~ExternalData()
{
    MatLabHelper::DestroyArray(m_Output->m_Array);
    delete m_Output;
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
        << CString(m_FilePath.c_str())
        << m_Width
        << m_Height;
}

void ExternalData::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> str;
    m_FilePath = str;

    ar >> m_Width >> m_Height;
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
    else if (CLIENT_CIID_EXTERNAL_DATA == iid)
    {
        iface = static_cast<IExternalData *>(this);
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

    attribute.Id = AAID_WIDTH;
    attribute.Name = TEXT("宽度");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);

    attribute.Id = AAID_HEIGHT;
    attribute.Name = TEXT("高度");
    attribute.Type = Attribute::TYPE_INT;
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
    case AAID_WIDTH:
        *((UINT32 *)attr) = m_Width;
        break;
    case AAID_HEIGHT:
        *((UINT32 *)attr) = m_Height;
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
    case AAID_WIDTH:
        m_Width = *((UINT32 *)attr);
        break;
    case AAID_HEIGHT:
        m_Height = *((UINT32 *)attr);
        break;
    }

    return rc;
}

bool ExternalData::Connect(IComponent *component)
{
    return false;
}

IComponent *ExternalData::Clone()
{
    ExternalData *externalData = new ExternalData();
    externalData->m_FilePath = m_FilePath;
    externalData->m_Width = m_Width;
    externalData->m_Height = m_Height;
    externalData->m_Id = m_Id;
    externalData->m_Name = m_Name;
    return externalData;
}

void ExternalData::Reset()
{
    MatLabHelper::DestroyArray(m_Output->m_Array);
    m_Output->m_Array = 0;
}

RC ExternalData::Config()
{
    RC rc;

    return rc;
}

RC ExternalData::SetInput(IData *input)
{
    return RC::COMPONENT_SETINPUT_ERROR;
}

RC ExternalData::Run()
{
    RC rc;

    if (!Utility::FileExists(m_FilePath.c_str()))
    {
        return RC::FILE_OPEN_ERROR;
    }

    HANDLE file = CreateFile(
        m_FilePath.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (file == INVALID_HANDLE_VALUE)
    {
        return RC::FILE_OPEN_ERROR;
    }
    UINT32 length = GetFileSize(file, NULL);
    char *buf = new char[length];
    DWORD read = 0;
    ReadFile(file, buf, length, &read, NULL);
    if (length != read)
    {
        return RC::FILE_OPEN_ERROR;
    }
    m_Output->m_Array = MatLabHelper::CreateDoubleArray(m_Width, m_Height, buf);
    CloseHandle(file);

    return rc;
}

RC ExternalData::GetOutput(IData *&output)
{
    RC rc;

    output = (IData *)(m_Output->GetInterface(CIID_IDATA));

    return rc;
}

ExternalData *ExternalData::Factory()
{
    ExternalData *externalData = new ExternalData;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    externalData->m_Name = name;
    ++s_Count;
    return externalData;
}

LPCWSTR ExternalData::s_ComponentName = TEXT("外部数据");

UINT32 ExternalData::s_Count = 0;
