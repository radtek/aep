/**
* @file
* @brief 外部数据类cpp文件.
* @author ruoxi
*
* 实现了外部数据类.
*/

#include "stdafx.h"

#include "output_image_batch.h"
#include "utility.h"
#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

OutputImageBatch::OutputImageBatch()
:
m_StartId(0),
m_EndId(0),
m_CurrentId(0),
OutputImage()
{
}

OutputImageBatch::~OutputImageBatch()
{
}

UINT32 OutputImageBatch::GetTypeId()
{
    return s_ComponentId;
}

void OutputImageBatch::Save(CArchive &ar)
{
    ar << s_ComponentId;

    OutputImage::Save(ar);

    ar << m_StartId
       << m_EndId;
}

void OutputImageBatch::Load(CArchive &ar)
{
    UINT32 dummy;
    ar >> dummy;

    OutputImage::Load(ar);

    ar >> m_StartId
       >> m_EndId;
    m_CurrentId = m_StartId;
}

void OutputImageBatch::GetAttributeList(AttributeList &attributeList)
{
    OutputImage::GetAttributeList(attributeList);

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

RC OutputImageBatch::GetAttribute(UINT32 aid, void *attr)
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
        rc = OutputImage::GetAttribute(aid, attr);
        break;
    }

    return rc;
}

RC OutputImageBatch::SetAttribute(UINT32 aid, void *attr)
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
        rc = OutputImage::SetAttribute(aid, attr);
        break;
    }

    return rc;
}

IComponent *OutputImageBatch::Clone()
{
    OutputImageBatch *outputImageBatch = new OutputImageBatch();
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        outputImageBatch->m_OutputId[i] = m_OutputId[i];
        outputImageBatch->m_Width[i] = m_Width[i];
        outputImageBatch->m_Height[i] = m_Height[i];
        outputImageBatch->m_FilePath[i] = m_FilePath[i];
    }
    outputImageBatch->m_Depth = m_Depth;
    outputImageBatch->m_StartId = m_StartId;
    outputImageBatch->m_EndId = m_EndId;
    outputImageBatch->m_CurrentId = m_CurrentId;

    outputImageBatch->m_Id = m_Id;
    outputImageBatch->m_Name = m_Name;

    return outputImageBatch;
}

RC OutputImageBatch::Config()
{
    RC rc;

    return rc;
}

RC OutputImageBatch::Run()
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

    rc = OutputImage::Run();

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

OutputImageBatch *OutputImageBatch::Factory()
{
    OutputImageBatch *outputImageBatch = new OutputImageBatch;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    outputImageBatch->m_Name = name;
    ++s_Count;
    return outputImageBatch;
}

LPCWSTR OutputImageBatch::s_ComponentName = TEXT("批量输出BMP图像");

UINT32 OutputImageBatch::s_Count = 0;
