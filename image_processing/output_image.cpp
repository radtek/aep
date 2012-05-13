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
    m_Input = new IOutputFileInput;
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
        << CString(m_Name.c_str())
        << CString(m_FilePath.c_str())
        << m_Depth;
}

void OutputImage::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> str;
    m_FilePath = str;

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

    attribute.Id = AAID_FILE_PATH;
    attribute.Name = TEXT("图像文件路径");
    attribute.Type = Attribute::TYPE_STRING;
    attributeList.push_back(attribute);

    attribute.Id = AAID_DEPTH;
    attribute.Name = TEXT("位深");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);
}

RC OutputImage::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_FILE_PATH:
        *((wstring *)attr) = m_FilePath;
        break;
    case AAID_DEPTH:
        *((UINT32 *)attr) = m_Depth;
        break;
    }

    return rc;
}

RC OutputImage::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_FILE_PATH:
        m_FilePath = *((wstring *)attr);
        break;
    case AAID_DEPTH:
        m_Depth = *((UINT32 *)attr);
        break;
    }

    return rc;
}

bool OutputImage::Connect(IComponent *component)
{
    return false;
}

IComponent *OutputImage::Clone()
{
    OutputImage *outputImage = new OutputImage();
    outputImage->m_FilePath = m_FilePath;
    outputImage->m_Depth = m_Depth;
    outputImage->m_Id = m_Id;
    outputImage->m_Name = m_Name;
    return outputImage;
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
        m_Input->m_Array = externalDataOutput->m_Array;
        return OK;
    }

    IImageOutput *imageOutput = (IImageOutput *)(input->GetInterface(CLIENT_CIID_IMAGE_OUTPUT));
    if (NULL != imageOutput)
    {
        m_Input->m_Array = imageOutput->m_Array;
        return OK;
    }

    IImageAlgorithmOutput1 *imageAlgorithmOutput1 = (IImageAlgorithmOutput1 *)(input->GetInterface(CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT1));
    if (NULL != imageAlgorithmOutput1)
    {
        m_Input->m_Array = imageAlgorithmOutput1->m_Array;
        return OK;
    }

    IImageAlgorithmOutput2 *imageAlgorithmOutput2 = (IImageAlgorithmOutput2 *)(input->GetInterface(CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT2));
    if (NULL != imageAlgorithmOutput2)
    {
        m_Input->m_Array = imageAlgorithmOutput2->m_Array;
        return OK;
    }

    return RC::COMPONENT_SETINPUT_ERROR;
}

RC OutputImage::Run()
{
    RC rc;

    UINT32 width = mxGetM(m_Input->m_Array) / (m_Depth / 8);
    UINT32 height = mxGetN(m_Input->m_Array);
    UINT32 size = width * height * (m_Depth / 8);
    char *buf = new char[size];
    double *content = mxGetPr(m_Input->m_Array);
    for (UINT32 i = 0; i < size; ++i)
    {
        buf[i] = (char)content[i];
    }

    // Utility::SaveBmpFile(bitmap, m_FilePath.c_str());
    Utility::SaveBmpFile(m_FilePath.c_str(), buf, width, height, m_Depth, NULL);

    return rc;
}

RC OutputImage::GetOutput1(IData *&output)
{
    return RC::COMPONENT_GETOUTPUT_ERROR;
}

RC OutputImage::GetOutput2(IData *&output)
{
    return RC::COMPONENT_GETOUTPUT_ERROR;
}

OutputImage *OutputImage::Factory()
{
    OutputImage *outputImage = new OutputImage;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    outputImage->m_Name = name;
    ++s_Count;
    delete[] name;
    return outputImage;
}

LPCWSTR OutputImage::s_ComponentName = TEXT("输出图像");

UINT32 OutputImage::s_Count = 0;
