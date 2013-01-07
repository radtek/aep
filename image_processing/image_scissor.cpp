/**
* @file
* @brief 图像窗口类cpp文件.
* @author ruoxi
*
* 实现了图像窗口类.
*/

#include "stdafx.h"

#include "image_scissor.h"
#include "utility.h"
#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

ImageScissor::ImageScissor()
:
m_Width(0),
m_Height(0),
m_CenterX(0),
m_CenterY(0),
m_DeltaX(0),
m_DeltaY(0),
m_FromAlgorithmOutputIndex(4),
m_FirstRun(true)
{
    m_ImageInput = new IImageOutput;
    m_Output = new IImageOutput;
}

ImageScissor::~ImageScissor()
{
    delete m_ImageInput;
    MatLabHelper::DestroyArray(m_Output->m_Array);
    delete m_Output;
}

UINT32 ImageScissor::GetTypeId()
{
    return s_ComponentId;
}

void ImageScissor::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << m_Width
        << m_Height
        << m_CenterX
        << m_CenterY
        << CString(m_OutputFile.c_str())
        << m_FromAlgorithmOutputIndex;
}

void ImageScissor::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    // ar >> m_Width >> m_Height >> m_CenterX >> m_CenterY >> m_FromAlgorithmOutputIndex;
    ar >> m_Width >> m_Height >> m_CenterX >> m_CenterY >> str >> m_FromAlgorithmOutputIndex;
    m_OutputFile = str;
}

void ImageScissor::Destroy()
{
    delete this;
}

void *ImageScissor::GetInterface(UINT32 iid)
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

UINT32 ImageScissor::GetId()
{
    return m_Id;
}

void ImageScissor::SetId(UINT32 id)
{
    m_Id = id;
}

wstring ImageScissor::GetName()
{
    return m_Name;
}

void ImageScissor::SetName(wstring name)
{
    m_Name = name;
}

void ImageScissor::GetAttributeList(AttributeList &attributeList)
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

    attribute.Id = AAID_OUTPUT_FILE;
    attribute.Name = TEXT("输出文件");
    attribute.Type = Attribute::TYPE_STRING;
    attributeList.push_back(attribute);

    attribute.Id = AAID_FROM_ALGORITHM_OUTPUT_INDEX;
    attribute.Name = TEXT("从前一算法获得输入ID");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);
}

RC ImageScissor::GetAttribute(UINT32 aid, void *attr)
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
    case AAID_OUTPUT_FILE:
        *((wstring *)attr) = m_OutputFile;
        break;
    case AAID_FROM_ALGORITHM_OUTPUT_INDEX:
        *((UINT32 *)attr) = m_FromAlgorithmOutputIndex;
        break;
    }

    return rc;
}

RC ImageScissor::SetAttribute(UINT32 aid, void *attr)
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
    case AAID_OUTPUT_FILE:
        m_OutputFile = *((wstring *)attr);
        break;
    case AAID_FROM_ALGORITHM_OUTPUT_INDEX:
        m_FromAlgorithmOutputIndex = *((UINT32 *)attr);
        break;
    }

    return rc;
}

bool ImageScissor::Connect(IComponent *component)
{
    return false;
}

RC ImageScissor::Config()
{
    RC rc;

    return rc;
}

IComponent *ImageScissor::Clone()
{
    ImageScissor *scissor = new ImageScissor();
    scissor->m_Width = m_Width;
    scissor->m_Height = m_Height;
    scissor->m_CenterX = m_CenterX;
    scissor->m_CenterY = m_CenterY;
    scissor->m_DeltaX = m_DeltaX;
    scissor->m_DeltaY = m_DeltaY;
    scissor->m_OutputFile = m_OutputFile;
    scissor->m_FromAlgorithmOutputIndex = m_FromAlgorithmOutputIndex;
    scissor->m_Id = m_Id;
    scissor->m_Name = m_Name;
    scissor->m_FirstRun = m_FirstRun;
    return scissor;
}

void ImageScissor::Reset()
{
    m_ImageInput->m_Array = 0;
    MatLabHelper::DestroyArray(m_Output->m_Array);
    m_Output->m_Array = 0;

    // 不重置偏移
    // m_DeltaX = 0;
    // m_DeltaY = 0;
}

RC ImageScissor::SetInput(IData *input)
{
    if (NULL == input)
    {
        return RC::COMPONENT_SETINPUT_ERROR;
    }

    IImageOutput *imageOutput = (IImageOutput *)(input->GetInterface(CLIENT_CIID_IMAGE_OUTPUT));
    if (NULL != imageOutput)
    {
        m_ImageInput->m_Array = imageOutput->m_Array;
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

RC ImageScissor::Run(bool input)
{
    RC rc;

    INT32 startX = m_CenterX + m_DeltaX - m_Width / 2, startY = m_CenterY + m_DeltaY - m_Height / 2;

    if (!m_OutputFile.empty() && input)
    {
        if (!Utility::FileExists(m_OutputFile.c_str()))
        {
            if (!Utility::CreateFileNested(m_OutputFile.c_str()))
            {
                return RC::FILE_OPEN_ERROR;
            }
        }

        wofstream ofs;
        if (m_FirstRun)
        {
            ofs.open(m_OutputFile.c_str());
            m_FirstRun = false;
        }
        else
        {
            ofs.open(m_OutputFile.c_str(), wofstream::app);
        }
        if (!ofs)
        {
            return RC::FILE_OPEN_ERROR;
        }
        ofs << (m_CenterX + m_DeltaX) << TEXT(" ") << (m_CenterY + m_DeltaY) << endl;
        ofs.close();
    }

    m_Output->m_Array = MatLabHelper::CreateDoubleArray(m_Width, m_Height, mxGetPr(m_ImageInput->m_Array), mxGetM(m_ImageInput->m_Array), mxGetN(m_ImageInput->m_Array), startX, startY);

    return rc;
}

RC ImageScissor::GetOutput(IData *&output)
{
    output = (IData *)(m_Output->GetInterface(CIID_IDATA));
    return OK;
}

ImageScissor *ImageScissor::Factory()
{
    ImageScissor *image = new ImageScissor;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    image->m_Name = name;
    ++s_Count;
    return image;
}

LPCWSTR ImageScissor::s_ComponentName = TEXT("裁剪窗口图像");

UINT32 ImageScissor::s_Count = 0;
