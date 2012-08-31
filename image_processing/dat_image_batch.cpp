/**
* @file
* @brief 外部数据类cpp文件.
* @author ruoxi
*
* 实现了外部数据类.
*/

#include "stdafx.h"

#include "dat_image_batch.h"
#include "utility.h"
#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

DatImageBatch::DatImageBatch()
:
m_StartId(0),
m_EndId(0),
m_CurrentId(0),
DatImage()
{
}

DatImageBatch::~DatImageBatch()
{
}

UINT32 DatImageBatch::GetTypeId()
{
    return s_ComponentId;
}

void DatImageBatch::Save(CArchive &ar)
{
    ar << s_ComponentId;

    DatImage::Save(ar);

    ar << m_StartId
       << m_EndId;
}

void DatImageBatch::Load(CArchive &ar)
{
    UINT32 dummy;
    ar >> dummy;

    DatImage::Load(ar);

    ar >> m_StartId
       >> m_EndId;

    m_CurrentId = m_StartId;
}

void DatImageBatch::GetAttributeList(AttributeList &attributeList)
{
    DatImage::GetAttributeList(attributeList);

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

RC DatImageBatch::GetAttribute(UINT32 aid, void *attr)
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
        rc = DatImage::GetAttribute(aid, attr);
        break;
    }

    return rc;
}

RC DatImageBatch::SetAttribute(UINT32 aid, void *attr)
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
        rc = DatImage::SetAttribute(aid, attr);
        break;
    }

    return rc;
}

IComponent *DatImageBatch::Clone()
{
    DatImageBatch *datImageBatch = new DatImageBatch();
    datImageBatch->m_FilePath = m_FilePath;
    datImageBatch->m_Width = m_Width;
    datImageBatch->m_Height = m_Height;
    datImageBatch->m_Id = m_Id;
    datImageBatch->m_Name = m_Name;
    datImageBatch->m_StartId = m_StartId;
    datImageBatch->m_EndId = m_EndId;
    datImageBatch->m_CurrentId = m_CurrentId;
    return datImageBatch;
}

RC DatImageBatch::Config()
{
    RC rc;

    return rc;
}

RC DatImageBatch::Run()
{
    RC rc;

    wstring filePath = m_FilePath;

    m_FilePath = Utility::InsertNumToFileName(m_FilePath, m_CurrentId);

    rc = DatImage::Run();

    m_FilePath = filePath;

    if (m_CurrentId < m_EndId)
    {
        ++m_CurrentId;
    }

    return rc;
}

DatImageBatch *DatImageBatch::Factory()
{
    DatImageBatch *datImageBatch = new DatImageBatch;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    datImageBatch->m_Name = name;
    ++s_Count;
    return datImageBatch;
}

LPCWSTR DatImageBatch::s_ComponentName = TEXT("批量DAT图像");

UINT32 DatImageBatch::s_Count = 0;
