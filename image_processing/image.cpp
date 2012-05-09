/**
* @file
* @brief 图像类cpp文件.
* @author ruoxi
*
* 实现了图像类.
*/

#include "stdafx.h"

#include "image.h"
#include "utility.h"
#include "matlab_helper.h"

Image::Image()
{
    m_Output = new IImageOutput;
}

Image::~Image()
{
    delete m_Output;
}

UINT32 Image::GetTypeId()
{
    return s_ComponentId;
}

void Image::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << CString(m_FilePath.c_str());
}

void Image::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> str;
    m_FilePath = str;
}

void Image::Destroy()
{
    delete this;
}

void *Image::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_IMAGE == iid)
    {
        iface = static_cast<IImage *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 Image::GetId()
{
    return m_Id;
}

void Image::SetId(UINT32 id)
{
    m_Id = id;
}

wstring Image::GetName()
{
    return m_Name;
}

void Image::SetName(wstring name)
{
    m_Name = name;
}

void Image::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_FILE_PATH;
    attribute.Name = TEXT("数据文件路径");
    attribute.Type = Attribute::TYPE_STRING;
    attributeList.push_back(attribute);
}

RC Image::GetAttribute(UINT32 aid, void *attr)
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

RC Image::SetAttribute(UINT32 aid, void *attr)
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

bool Image::Connect(IComponent *component)
{
    return false;
}

RC Image::Config()
{
    RC rc;

    return rc;
}

IComponent *Image::Clone()
{
    Image *image = new Image();
    image->m_FilePath = m_FilePath;
    image->m_Id = m_Id;
    image->m_Name = m_Name;
    return image;
}

RC Image::SetInput(IData *input)
{
    return RC::COMPONENT_SETINPUT_ERROR;
}

RC Image::GetOutput1(IData *&output)
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

RC Image::GetOutput2(IData *&output)
{
    return RC::COMPONENT_GETOUTPUT_ERROR;
}

Image *Image::Factory()
{
    Image *image = new Image;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    image->m_Name = name;
    ++s_Count;
    delete[] name;
    return image;
}

LPCWSTR Image::s_ComponentName = TEXT("图像");

UINT32 Image::s_Count = 0;
