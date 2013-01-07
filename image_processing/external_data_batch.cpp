/**
* @file
* @brief 外部数据类cpp文件.
* @author ruoxi
*
* 实现了外部数据类.
*/

#include "stdafx.h"

#include "external_data_batch.h"
#include "utility.h"
#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

ExternalDataBatch::ExternalDataBatch()
:
m_StartId(0),
m_EndId(0),
m_CurrentId(0),
ExternalData()
{
}

ExternalDataBatch::~ExternalDataBatch()
{
}

UINT32 ExternalDataBatch::GetTypeId()
{
    return s_ComponentId;
}

void ExternalDataBatch::Save(CArchive &ar)
{
    ar << s_ComponentId;

    ExternalData::Save(ar);

    ar << m_StartId
       << m_EndId;
}

void ExternalDataBatch::Load(CArchive &ar)
{
    UINT32 dummy;
    ar >> dummy;

    ExternalData::Load(ar);

    ar >> m_StartId
       >> m_EndId;

    m_CurrentId = m_StartId;
}

void ExternalDataBatch::GetAttributeList(AttributeList &attributeList)
{
    ExternalData::GetAttributeList(attributeList);

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

RC ExternalDataBatch::GetAttribute(UINT32 aid, void *attr)
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
        rc = ExternalData::GetAttribute(aid, attr);
        break;
    }

    return rc;
}

RC ExternalDataBatch::SetAttribute(UINT32 aid, void *attr)
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
        rc = ExternalData::SetAttribute(aid, attr);
        break;
    }

    return rc;
}

IComponent *ExternalDataBatch::Clone()
{
    ExternalDataBatch *externalDataBatch = new ExternalDataBatch();
    externalDataBatch->m_FilePath = m_FilePath;
    externalDataBatch->m_Width = m_Width;
    externalDataBatch->m_Height = m_Height;
    externalDataBatch->m_Id = m_Id;
    externalDataBatch->m_Name = m_Name;
    externalDataBatch->m_StartId = m_StartId;
    externalDataBatch->m_EndId = m_EndId;
    externalDataBatch->m_CurrentId = m_CurrentId;
    return externalDataBatch;
}

RC ExternalDataBatch::Config()
{
    RC rc;

    return rc;
}

RC ExternalDataBatch::Run(bool input)
{
    RC rc;

    wstring filePath = m_FilePath;

    m_FilePath = Utility::InsertNumToFileName(m_FilePath, m_CurrentId);

    rc = ExternalData::Run();

    m_FilePath = filePath;

    if (m_CurrentId < m_EndId)
    {
        ++m_CurrentId;
    }

    return rc;
}

ExternalDataBatch *ExternalDataBatch::Factory()
{
    ExternalDataBatch *externalDataBatch = new ExternalDataBatch;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    externalDataBatch->m_Name = name;
    ++s_Count;
    return externalDataBatch;
}

LPCWSTR ExternalDataBatch::s_ComponentName = TEXT("批量外部数据");

UINT32 ExternalDataBatch::s_Count = 0;
