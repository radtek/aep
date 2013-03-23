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
:
m_Width(0),
m_Height(0)
{
    m_Output = new IImageOutput;
}

Image::~Image()
{
    MatLabHelper::DestroyArray(m_Output->m_Array);
    delete m_Output;
}

UINT32 Image::GetInterfaceTypeId()
{
    return s_InterfaceId;
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
        << CString(m_FilePath.c_str())
        << m_Width
        << m_Height;
}

void Image::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> str;
    m_FilePath = str;

    ar >> m_Width >> m_Height;
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
    attribute.Name = TEXT("BMP图像文件路径");
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

RC Image::GetAttribute(UINT32 aid, void *attr)
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

RC Image::SetAttribute(UINT32 aid, void *attr)
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
    image->m_Width = m_Width;
    image->m_Height = m_Height;
    image->m_Id = m_Id;
    image->m_Name = m_Name;
    return image;
}

void Image::Reset()
{
    MatLabHelper::DestroyArray(m_Output->m_Array);
    m_Output->m_Array = 0;
}

RC Image::SetInput(IData *input)
{
    return RC::COMPONENT_SETINPUT_ERROR;
}

RC Image::Run(bool input)
{
    RC rc;

    CHECK_RC(g_PlatformService->DownloadFile(m_FilePath.c_str()));

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
    UINT32 width = m_Width * bitmap.bmBitsPixel / 8;
    UINT32 height = m_Height;
    if (width == 0 || height == 0)
    {
        width = bitmap.bmWidthBytes;
        height = bitmap.bmHeight;
    }
    m_Output->m_Array = MatLabHelper::CreateDoubleArray(width, height, (const unsigned char *)bitmap.bmBits, bitmap.bmWidthBytes, bitmap.bmHeight, 0, 0);
    DeleteObject(hBitmap);

    return rc;
}

RC Image::GetOutput(IData *&output)
{
    output = (IData *)(m_Output->GetInterface(CIID_IDATA));
    return OK;
}

Image *Image::Factory()
{
    Image *image = new Image;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    image->m_Name = name;
    ++s_Count;
    return image;
}

LPCWSTR Image::s_ComponentName = TEXT("BMP图像");

UINT32 Image::s_Count = 0;
