/**
* @file
* @brief 外部数据类cpp文件.
* @author ruoxi
*
* 实现了外部数据类.
*/

#include "stdafx.h"

#include "output_external_data_batch.h"
#include "utility.h"
#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

OutputExternalDataBatch::OutputExternalDataBatch()
:
m_StartId(0),
m_EndId(0),
m_CurrentId(0),
OutputExternalData()
{
}

OutputExternalDataBatch::~OutputExternalDataBatch()
{
}

UINT32 OutputExternalDataBatch::GetTypeId()
{
    return s_ComponentId;
}

void OutputExternalDataBatch::Save(CArchive &ar)
{
    ar << s_ComponentId;

    OutputExternalData::Save(ar);

    ar << m_StartId
       << m_EndId;
}

void OutputExternalDataBatch::Load(CArchive &ar)
{
    UINT32 dummy;
    ar >> dummy;

    OutputExternalData::Load(ar);

    ar >> m_StartId
       >> m_EndId;
    m_CurrentId = m_StartId;
}

void OutputExternalDataBatch::GetAttributeList(AttributeList &attributeList)
{
    OutputExternalData::GetAttributeList(attributeList);

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

RC OutputExternalDataBatch::GetAttribute(UINT32 aid, void *attr)
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
        rc = OutputExternalData::GetAttribute(aid, attr);
        break;
    }

    return rc;
}

RC OutputExternalDataBatch::SetAttribute(UINT32 aid, void *attr)
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
        rc = OutputExternalData::SetAttribute(aid, attr);
        break;
    }

    return rc;
}

IComponent *OutputExternalDataBatch::Clone()
{
    OutputExternalDataBatch *outputExternalDataBatch = new OutputExternalDataBatch();
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        outputExternalDataBatch->m_OutputId[i] = m_OutputId[i];
        outputExternalDataBatch->m_Width[i] = m_Width[i];
        outputExternalDataBatch->m_Height[i] = m_Height[i];
        outputExternalDataBatch->m_FilePath[i] = m_FilePath[i];
    }
    outputExternalDataBatch->m_StartId = m_StartId;
    outputExternalDataBatch->m_EndId = m_EndId;
    outputExternalDataBatch->m_CurrentId = m_CurrentId;

    outputExternalDataBatch->m_Id = m_Id;
    outputExternalDataBatch->m_Name = m_Name;

    return outputExternalDataBatch;
}

RC OutputExternalDataBatch::Config()
{
    RC rc;

    return rc;
}

RC OutputExternalDataBatch::Run(bool input)
{
    RC rc;

    wstring filePath[m_OutputCount];

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        filePath[i] = m_FilePath[i];
        if (!m_FilePath[i].empty())
        {
            m_FilePath[i] = Utility::InsertNumToFileName(m_FilePath[i], m_CurrentId);
        }
    }

    rc = OutputExternalData::Run();

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        m_FilePath[i] = filePath[i];
    }

    if (m_CurrentId < m_EndId)
    {
        ++m_CurrentId;
    }

    return rc;
}

OutputExternalDataBatch *OutputExternalDataBatch::Factory()
{
    OutputExternalDataBatch *outputExternalDataBatch = new OutputExternalDataBatch;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    outputExternalDataBatch->m_Name = name;
    ++s_Count;
    return outputExternalDataBatch;
}

LPCWSTR OutputExternalDataBatch::s_ComponentName = TEXT("批量输出DAT数据");

UINT32 OutputExternalDataBatch::s_Count = 0;
