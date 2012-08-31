/**
* @file
* @brief 图像类cpp文件.
* @author ruoxi
*
* 实现了图像类.
*/

#include "stdafx.h"

#include "dat_image.h"
#include "utility.h"
#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

DatImage::DatImage()
:
m_Width(0),
m_Height(0)
{
    m_Output = new IImageOutput;
}

DatImage::~DatImage()
{
    MatLabHelper::DestroyArray(m_Output->m_Array);
    delete m_Output;
}

UINT32 DatImage::GetTypeId()
{
    return s_ComponentId;
}

void DatImage::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << CString(m_FilePath.c_str())
        << m_Width
        << m_Height;
}

void DatImage::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> str;
    m_FilePath = str;

    ar >> m_Width >> m_Height;
}

void DatImage::Destroy()
{
    delete this;
}

void *DatImage::GetInterface(UINT32 iid)
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

UINT32 DatImage::GetId()
{
    return m_Id;
}

void DatImage::SetId(UINT32 id)
{
    m_Id = id;
}

wstring DatImage::GetName()
{
    return m_Name;
}

void DatImage::SetName(wstring name)
{
    m_Name = name;
}

void DatImage::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_FILE_PATH;
    attribute.Name = TEXT("DAT数据文件路径");
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

RC DatImage::GetAttribute(UINT32 aid, void *attr)
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

RC DatImage::SetAttribute(UINT32 aid, void *attr)
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

bool DatImage::Connect(IComponent *component)
{
    return false;
}

RC DatImage::Config()
{
    RC rc;

    return rc;
}

IComponent *DatImage::Clone()
{
    DatImage *datImage = new DatImage();
    datImage->m_FilePath = m_FilePath;
    datImage->m_Width = m_Width;
    datImage->m_Height = m_Height;
    datImage->m_Id = m_Id;
    datImage->m_Name = m_Name;
    return datImage;
}

void DatImage::Reset()
{
    MatLabHelper::DestroyArray(m_Output->m_Array);
    m_Output->m_Array = 0;
}

RC DatImage::SetInput(IData *input)
{
    return RC::COMPONENT_SETINPUT_ERROR;
}

RC DatImage::Run()
{
    RC rc;

    wifstream ifs(m_FilePath.c_str());
    if (!ifs)
    {
        return RC::FILE_OPEN_ERROR;
    }
    UINT32 width, height, size;
    ifs >> width >> height;
    size = width * height;
    double *buf = new double[size];
    memset(buf, 0, size * sizeof(double));

    for (UINT32 i = 0; i < size; ++i)
    {
        if (ifs.eof())
        {
            delete[] buf;
            return RC::FILE_OPEN_ERROR;
        }
        double data;
        ifs >> data;
        buf[i] = data;
    }

    m_Output->m_Array = MatLabHelper::CreateDoubleArray(m_Width, m_Height, buf, size, 0);

    delete[] buf;
    ifs.close();

    return rc;
}

RC DatImage::GetOutput(IData *&output)
{
    output = (IData *)(m_Output->GetInterface(CIID_IDATA));
    return OK;
}

DatImage *DatImage::Factory()
{
    DatImage *image = new DatImage;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    image->m_Name = name;
    ++s_Count;
    return image;
}

LPCWSTR DatImage::s_ComponentName = TEXT("DAT图像");

UINT32 DatImage::s_Count = 0;
