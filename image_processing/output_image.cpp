/**
* @file
* @brief 输出外部数据类cpp文件.
* @author ruoxi
*
* 实现了输出外部数据类.
*/

#include "stdafx.h"

#include "output_image.h"
#include "utility.h"
#include "matlab_helper.h"

OutputImage::OutputImage()
:
m_Depth(24)
{
    m_Input = new IOutputFileInput(m_OutputCount);
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        m_OutputId[i] = 0;
    }
}

OutputImage::~OutputImage()
{
    delete m_Input;
}

UINT32 OutputImage::GetTypeId()
{
    return s_ComponentId;
}

void OutputImage::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str());

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar << m_OutputId[i];
    }

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar << CString(m_FilePath[i].c_str());
    }

    ar << m_Depth;
}

void OutputImage::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar >> m_OutputId[i];
    }

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar >> str;
        m_FilePath[i] = str;
    }

    ar >> m_Depth;
}

void OutputImage::Destroy()
{
    delete this;
}

void *OutputImage::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_OUTPUT_FILE == iid)
    {
        iface = static_cast<IOutputFile *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 OutputImage::GetId()
{
    return m_Id;
}

void OutputImage::SetId(UINT32 id)
{
    m_Id = id;
}

wstring OutputImage::GetName()
{
    return m_Name;
}

void OutputImage::SetName(wstring name)
{
    m_Name = name;
}

void OutputImage::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    for (UINT32 i = AAID_OUTPUT_ID1; i <= AAID_OUTPUT_ID5; ++i)
    {
        attribute.Id = i;
        CString name = TEXT("算法输出ID");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_INT;
        attributeList.push_back(attribute);
    }

    for (UINT32 i = 0; i <= AAID_FILE_PATH5 - AAID_FILE_PATH1; ++i)
    {
        attribute.Id = i + AAID_FILE_PATH1;
        CString name = TEXT("图像文件路径");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_STRING;
        attributeList.push_back(attribute);
    }

    attribute.Id = AAID_DEPTH;
    attribute.Name = TEXT("位深");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);
}

RC OutputImage::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    for (UINT32 i = AAID_OUTPUT_ID1; i <= AAID_OUTPUT_ID5; ++i)
    {
        if (aid == i)
        {
            *((UINT32 *)attr) = m_OutputId[i];
            return rc;
        }
    }

    for (UINT32 i = AAID_FILE_PATH1; i <= AAID_FILE_PATH5; ++i)
    {
        if (aid == i)
        {
            *((wstring *)attr) = m_FilePath[i - AAID_FILE_PATH1];
            return rc;
        }
    }

    if (aid == AAID_DEPTH)
    {
         *((UINT32 *)attr) = m_Depth;
    }

    return RC::COMPONENT_GETATTRIBUTE_ERROR;
}

RC OutputImage::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    for (UINT32 i = AAID_OUTPUT_ID1; i <= AAID_OUTPUT_ID5; ++i)
    {
        if (aid == i)
        {
            m_OutputId[i] = *((UINT32 *)attr);
            return rc;
        }
    }

    for (UINT32 i = AAID_FILE_PATH1; i <= AAID_FILE_PATH5; ++i)
    {
        if (aid == i)
        {
            m_FilePath[i - AAID_FILE_PATH1] = *((wstring *)attr);
            return rc;
        }
    }

    if (aid == AAID_DEPTH)
    {
        m_Depth = *((UINT32 *)attr);
    }

    return RC::COMPONENT_SETATTRIBUTE_ERROR;
}

bool OutputImage::Connect(IComponent *component)
{
    return false;
}

IComponent *OutputImage::Clone()
{
    OutputImage *outputImage = new OutputImage();
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        outputImage->m_OutputId[i] = m_OutputId[i];
        outputImage->m_FilePath[i] = m_FilePath[i];
    }
    outputImage->m_Depth = m_Depth;
    outputImage->m_Id = m_Id;
    outputImage->m_Name = m_Name;
    return outputImage;
}

void OutputImage::Reset()
{
    m_Input->Reset();
}

RC OutputImage::Config()
{
    RC rc;

    return rc;
}

RC OutputImage::SetInput(IData *input)
{
    if (NULL == input)
    {
        return RC::COMPONENT_SETINPUT_ERROR;
    }

    IExternalDataOutput *externalDataOutput = (IExternalDataOutput *)(input->GetInterface(CLIENT_CIID_EXTERNAL_DATA_OUTPUT));
    if (NULL != externalDataOutput)
    {
        m_Input->m_Array[0] = externalDataOutput->m_Array;
        return OK;
    }

    IImageOutput *imageOutput = (IImageOutput *)(input->GetInterface(CLIENT_CIID_IMAGE_OUTPUT));
    if (NULL != imageOutput)
    {
        m_Input->m_Array[0] = imageOutput->m_Array;
        return OK;
    }

    IImageAlgorithmOutput *imageAlgorithmOutput = (IImageAlgorithmOutput *)(input->GetInterface(CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT));
    if (NULL != imageAlgorithmOutput)
    {
        m_Input->m_Array = imageAlgorithmOutput->m_Array;
        for (UINT32 i = 0; i < m_OutputCount; ++i)
        {
            UINT32 outputId = m_OutputId[i];
            if (outputId >= m_OutputCount)
            {
                return RC::COMPONENT_SETINPUT_ERROR;
            }
            m_Input->m_Array[i] = imageAlgorithmOutput->m_Array[outputId];
        }
        return OK;
    }

    return RC::COMPONENT_SETINPUT_ERROR;
}

RC OutputImage::Run()
{
    RC rc;

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        UINT32 width = mxGetM(m_Input->m_Array[i]) / (m_Depth / 8);
        UINT32 height = mxGetN(m_Input->m_Array[i]);
        UINT32 size = width * height * (m_Depth / 8);
        char *buf = new char[size];
        double *content = mxGetPr(m_Input->m_Array[i]);
        for (UINT32 j = 0; j < size; ++j)
        {
            buf[j] = (char)content[j];
        }

        // Utility::SaveBmpFile(bitmap, m_FilePath.c_str());
        Utility::SaveBmpFile(m_FilePath[i].c_str(), buf, width, height, m_Depth, NULL);
        delete buf;
    }

    return rc;
}

RC OutputImage::GetOutput(IData *&output)
{
    return RC::COMPONENT_GETOUTPUT_ERROR;
}

OutputImage *OutputImage::Factory()
{
    OutputImage *outputImage = new OutputImage;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    outputImage->m_Name = name;
    ++s_Count;
    return outputImage;
}

LPCWSTR OutputImage::s_ComponentName = TEXT("输出图像");

UINT32 OutputImage::s_Count = 0;
