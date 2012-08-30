/**
* @file
* @brief 图像窗口类cpp文件.
* @author ruoxi
*
* 实现了图像窗口类.
*/

#include "stdafx.h"

#include "external_data_scissor.h"
#include "utility.h"
#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

ExternalDataScissor::ExternalDataScissor()
:
m_Width(0),
m_Height(0),
m_CenterX(0),
m_CenterY(0),
m_DeltaX(0),
m_DeltaY(0),
m_FromAlgorithmOutputIndex(4)
{
    m_ExternalDataInput = new IExternalDataOutput;
    m_Output = new IExternalDataOutput;
}

ExternalDataScissor::~ExternalDataScissor()
{
    delete m_ExternalDataInput;
    MatLabHelper::DestroyArray(m_Output->m_Array);
    delete m_Output;
}

UINT32 ExternalDataScissor::GetTypeId()
{
    return s_ComponentId;
}

void ExternalDataScissor::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << m_Width
        << m_Height
        << m_CenterX
        << m_CenterY
        << m_FromAlgorithmOutputIndex;
}

void ExternalDataScissor::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> m_Width >> m_Height >> m_CenterX >> m_CenterY >> m_FromAlgorithmOutputIndex;
}

void ExternalDataScissor::Destroy()
{
    delete this;
}

void *ExternalDataScissor::GetInterface(UINT32 iid)
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

UINT32 ExternalDataScissor::GetId()
{
    return m_Id;
}

void ExternalDataScissor::SetId(UINT32 id)
{
    m_Id = id;
}

wstring ExternalDataScissor::GetName()
{
    return m_Name;
}

void ExternalDataScissor::SetName(wstring name)
{
    m_Name = name;
}

void ExternalDataScissor::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_WIDTH;
    attribute.Name = TEXT("宽度");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);

    attribute.Id = AAID_HEIGHT;
    attribute.Name = TEXT("高度");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);

    attribute.Id = AAID_CENTER_X;
    attribute.Name = TEXT("窗口中心X");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);

    attribute.Id = AAID_CENTER_Y;
    attribute.Name = TEXT("窗口中心Y");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);

    attribute.Id = AAID_FROM_ALGORITHM_OUTPUT_INDEX;
    attribute.Name = TEXT("从前一算法获得输入ID");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);
}

RC ExternalDataScissor::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_WIDTH:
        *((UINT32 *)attr) = m_Width;
        break;
    case AAID_HEIGHT:
        *((UINT32 *)attr) = m_Height;
        break;
    case AAID_CENTER_X:
        *((UINT32 *)attr) = m_CenterX;
        break;
    case AAID_CENTER_Y:
        *((UINT32 *)attr) = m_CenterY;
        break;
    case AAID_FROM_ALGORITHM_OUTPUT_INDEX:
        *((UINT32 *)attr) = m_FromAlgorithmOutputIndex;
        break;
    }

    return rc;
}

RC ExternalDataScissor::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_WIDTH:
        m_Width = *((UINT32 *)attr);
        break;
    case AAID_HEIGHT:
        m_Height = *((UINT32 *)attr);
        break;
    case AAID_CENTER_X:
        m_CenterX = *((UINT32 *)attr);
        break;
    case AAID_CENTER_Y:
        m_CenterY = *((UINT32 *)attr);
        break;
    case AAID_FROM_ALGORITHM_OUTPUT_INDEX:
        m_FromAlgorithmOutputIndex = *((UINT32 *)attr);
        break;
    }

    return rc;
}

bool ExternalDataScissor::Connect(IComponent *component)
{
    return false;
}

RC ExternalDataScissor::Config()
{
    RC rc;

    return rc;
}

IComponent *ExternalDataScissor::Clone()
{
    ExternalDataScissor *scissor = new ExternalDataScissor();
    scissor->m_Width = m_Width;
    scissor->m_Height = m_Height;
    scissor->m_CenterX = m_CenterX;
    scissor->m_CenterY = m_CenterY;
    scissor->m_DeltaX = m_DeltaX;
    scissor->m_DeltaY = m_DeltaY;
    scissor->m_FromAlgorithmOutputIndex = m_FromAlgorithmOutputIndex;
    scissor->m_Id = m_Id;
    scissor->m_Name = m_Name;
    return scissor;
}

void ExternalDataScissor::Reset()
{
    m_ExternalDataInput->m_Array = 0;
    MatLabHelper::DestroyArray(m_Output->m_Array);
    m_Output->m_Array = 0;

    // 不重置偏移
    // m_DeltaX = 0;
    // m_DeltaY = 0;
}

RC ExternalDataScissor::SetInput(IData *input)
{
    if (NULL == input)
    {
        return RC::COMPONENT_SETINPUT_ERROR;
    }

    IExternalDataOutput *externalDataOutput = (IExternalDataOutput *)(input->GetInterface(CLIENT_CIID_EXTERNAL_DATA_OUTPUT));
    if (NULL != externalDataOutput)
    {
        m_ExternalDataInput->m_Array = externalDataOutput->m_Array;
        return OK;
    }

    IImageAlgorithmOutput *imageAlgorithmOutput = (IImageAlgorithmOutput *)(input->GetInterface(CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT));
    if (NULL != imageAlgorithmOutput)
    {
        if (imageAlgorithmOutput->m_Array[m_FromAlgorithmOutputIndex] != 0)
        {
            double *p = mxGetPr(imageAlgorithmOutput->m_Array[m_FromAlgorithmOutputIndex]);
            m_DeltaX += (INT32)(p[0] + 0.5);
            m_DeltaY += (INT32)(p[1] + 0.5);
        }
        return OK;
    }

    return RC::COMPONENT_SETINPUT_ERROR;
}

RC ExternalDataScissor::Run()
{
    RC rc;

    INT32 startX = m_CenterX + m_DeltaX - m_Width / 2, startY = m_CenterY + m_DeltaY - m_Height / 2;

    m_Output->m_Array = MatLabHelper::CreateDoubleArray(m_Width, m_Height, mxGetPr(m_ExternalDataInput->m_Array), mxGetM(m_ExternalDataInput->m_Array), mxGetN(m_ExternalDataInput->m_Array), startX, startY);

    return rc;
}

RC ExternalDataScissor::GetOutput(IData *&output)
{
    output = (IData *)(m_Output->GetInterface(CIID_IDATA));
    return OK;
}

ExternalDataScissor *ExternalDataScissor::Factory()
{
    ExternalDataScissor *scissor = new ExternalDataScissor;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    scissor->m_Name = name;
    ++s_Count;
    return scissor;
}

LPCWSTR ExternalDataScissor::s_ComponentName = TEXT("裁剪窗口外部数据");

UINT32 ExternalDataScissor::s_Count = 0;
