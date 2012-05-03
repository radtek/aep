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
{
    m_Output = new IExternalDataOutput;
}

ExternalData::~ExternalData()
{
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

RC ExternalData::Config()
{
    RC rc;

    return rc;
}

RC ExternalData::SetInput(IData *input)
{
    return RC::COMPONENT_SETINPUT_ERROR;
}

RC ExternalData::GetOutput1(IData *&output)
{
    /*
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
    */
    HBITMAP hBitmap = (HBITMAP)::LoadImage(
        NULL,
        m_FilePath.c_str(),
        IMAGE_BITMAP,
        0,
        0,
        LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (!hBitmap)
    {
        Utility::PromptLastErrorMessage();
        return RC::FILE_OPEN_ERROR;
    }
    BITMAP bitmap;
    ::GetObject(hBitmap, sizeof(bitmap), &bitmap); 

    m_Output->m_Array = MatLabHelper::CreateDoubleArray(bitmap.bmWidthBytes, bitmap.bmHeight, (const char *)bitmap.bmBits);

    ::DeleteObject(hBitmap);

    output = (IData *)(m_Output->GetInterface(CIID_IDATA));
    return OK;
}

RC ExternalData::GetOutput2(IData *&output)
{
    return RC::COMPONENT_GETOUTPUT_ERROR;
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
