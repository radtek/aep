/**
* @file
* @brief 输出外部数据类cpp文件.
* @author ruoxi
*
* 实现了输出外部数据类.
*/

#include "stdafx.h"

#include "output_external_data.h"
#include "utility.h"
#include "matlab_helper.h"

OutputExternalData::OutputExternalData()
{
    m_Input = new IOutputFileInput;
}

OutputExternalData::~OutputExternalData()
{
    delete m_Input;
}

UINT32 OutputExternalData::GetTypeId()
{
    return s_ComponentId;
}

void OutputExternalData::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << CString(m_FilePath.c_str());
}

void OutputExternalData::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> str;
    m_FilePath = str;
}

void OutputExternalData::Destroy()
{
    delete this;
}

void *OutputExternalData::GetInterface(UINT32 iid)
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

UINT32 OutputExternalData::GetId()
{
    return m_Id;
}

void OutputExternalData::SetId(UINT32 id)
{
    m_Id = id;
}

wstring OutputExternalData::GetName()
{
    return m_Name;
}

void OutputExternalData::SetName(wstring name)
{
    m_Name = name;
}

void OutputExternalData::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_FILE_PATH;
    attribute.Name = TEXT("数据文件路径");
    attribute.Type = Attribute::TYPE_STRING;
    attributeList.push_back(attribute);
}

RC OutputExternalData::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_FILE_PATH:
        *((wstring *)attr) = m_FilePath;
        break;
    }

    return rc;
}

RC OutputExternalData::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_FILE_PATH:
        m_FilePath = *((wstring *)attr);
        break;
    }

    return rc;
}

bool OutputExternalData::Connect(IComponent *component)
{
    return false;
}

IComponent *OutputExternalData::Clone()
{
    OutputExternalData *outputExternalData = new OutputExternalData();
    outputExternalData->m_FilePath = m_FilePath;
    outputExternalData->m_Id = m_Id;
    outputExternalData->m_Name = m_Name;
    return outputExternalData;
}

RC OutputExternalData::Config()
{
    RC rc;

    return rc;
}

RC OutputExternalData::SetInput(IData *input)
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

RC OutputExternalData::Run()
{
    RC rc;
    HANDLE file = CreateFile(
        m_FilePath.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (NULL == file)
    {
        return RC::FILE_OPEN_ERROR;
    }
    UINT32 x = mxGetM(m_Input->m_Array);
    UINT32 y = mxGetN(m_Input->m_Array);
    UINT32 length = x * y;
    char *buf = new char[length];
    double *content = mxGetPr(m_Input->m_Array);
    for (UINT32 i = 0; i < length; ++i)
    {
        buf[i] = (char)content[i];
    }
    DWORD written = 0;
    WriteFile(file, buf, length, &written, NULL);
    if (length != written)
    {
        return RC::FILE_WRITE_ERROR;
    }
    delete[] buf;
    CloseHandle(file);
    return rc;
}

RC OutputExternalData::GetOutput1(IData *&output)
{
    return RC::COMPONENT_GETOUTPUT_ERROR;
}

RC OutputExternalData::GetOutput2(IData *&output)
{
    return RC::COMPONENT_GETOUTPUT_ERROR;
}

OutputExternalData *OutputExternalData::Factory()
{
    OutputExternalData *outputExternalData = new OutputExternalData;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    outputExternalData->m_Name = name;
    ++s_Count;
    delete[] name;
    return outputExternalData;
}

LPCWSTR OutputExternalData::s_ComponentName = TEXT("输出外部数据");

UINT32 OutputExternalData::s_Count = 0;
