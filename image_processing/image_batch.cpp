/**
* @file
* @brief 外部数据类cpp文件.
* @author ruoxi
*
* 实现了外部数据类.
*/

#include "stdafx.h"

#include "image_batch.h"
#include "utility.h"
#include "matlab_helper.h"

ImageBatch::ImageBatch()
:
m_StartId(0),
m_EndId(0),
m_CurrentId(0),
Image()
{
}

ImageBatch::~ImageBatch()
{
}

UINT32 ImageBatch::GetTypeId()
{
    return s_ComponentId;
}

void ImageBatch::Save(CArchive &ar)
{
    ar << s_ComponentId;

    Image::Save(ar);

    ar << m_StartId
       << m_EndId;
}

void ImageBatch::Load(CArchive &ar)
{
    UINT32 dummy;
    ar >> dummy;

    Image::Load(ar);

    ar >> m_StartId
       >> m_EndId;

    m_CurrentId = m_StartId;
}

void ImageBatch::GetAttributeList(AttributeList &attributeList)
{
    Image::GetAttributeList(attributeList);

    Attribute attribute;

    attribute.Id = AAID_START_ID;
    attribute.Name = TEXT("起始文件序号");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);

    attribute.Id = AAID_END_ID;
    attribute.Name = TEXT("结束文件序号");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);
}

RC ImageBatch::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_START_ID:
        *((UINT32 *)attr) = m_StartId;
        break;
    case AAID_END_ID:
        *((UINT32 *)attr) = m_EndId;
        break;
    default:
        rc = Image::GetAttribute(aid, attr);
        break;
    }

    return rc;
}

RC ImageBatch::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_START_ID:
        m_StartId = *((UINT32 *)attr);
        m_CurrentId = m_StartId;
        break;
    case AAID_END_ID:
        m_EndId = *((UINT32 *)attr);
        break;
    default:
        rc = Image::SetAttribute(aid, attr);
        break;
    }

    return rc;
}

IComponent *ImageBatch::Clone()
{
    ImageBatch *imageBatch = new ImageBatch();
    imageBatch->m_FilePath = m_FilePath;
    imageBatch->m_Width = m_Width;
    imageBatch->m_Height = m_Height;
    imageBatch->m_Id = m_Id;
    imageBatch->m_Name = m_Name;
    imageBatch->m_StartId = m_StartId;
    imageBatch->m_EndId = m_EndId;
    imageBatch->m_CurrentId = m_CurrentId;
    return imageBatch;
}

RC ImageBatch::Config()
{
    RC rc;

    return rc;
}

RC ImageBatch::Run(bool input)
{
    RC rc;

    wstring filePath = m_FilePath;

    m_FilePath = Utility::InsertNumToFileName(m_FilePath, m_CurrentId);

    rc = Image::Run();

    m_FilePath = filePath;

    if (m_CurrentId < m_EndId)
    {
        ++m_CurrentId;
    }

    return rc;
}

ImageBatch *ImageBatch::Factory()
{
    ImageBatch *imageBatch = new ImageBatch;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    imageBatch->m_Name = name;
    ++s_Count;
    return imageBatch;
}

LPCWSTR ImageBatch::s_ComponentName = TEXT("批量BMP图像");

UINT32 ImageBatch::s_Count = 0;
