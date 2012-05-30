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
    m_Input = new IOutputFileInput(m_OutputCount);
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        m_OutputId[i] = 0;
        m_Width[i] = 0;
        m_Height[i] = 0;
    }
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
        << CString(m_Name.c_str());

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar << m_OutputId[i];
        ar << m_Width[i];
        ar << m_Height[i];
        ar << CString(m_FilePath[i].c_str());
    }
}

void OutputExternalData::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar >> m_OutputId[i];
        ar >> m_Width[i];
        ar >> m_Height[i];
        ar >> str;
        m_FilePath[i] = str;
    }
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

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        attribute.Id = AAID_OUTPUT_ID1 + i;
        CString name = TEXT("算法输出ID");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_INT;
        attributeList.push_back(attribute);

        attribute.Id = AAID_WIDTH1 + i;
        name = TEXT("输出宽度");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_INT;
        attributeList.push_back(attribute);

        attribute.Id = AAID_HEIGHT1 + i;
        name = TEXT("输出高度");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_INT;
        attributeList.push_back(attribute);

        attribute.Id = AAID_FILE_PATH1 + i;
        name = TEXT("输出DAT数据文件路径");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_STRING;
        attributeList.push_back(attribute);
    }
}

RC OutputExternalData::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    for (UINT32 i = AAID_OUTPUT_ID1; i <= AAID_OUTPUT_ID5; ++i)
    {
        if (aid == i)
        {
            *((UINT32 *)attr) = m_OutputId[i - AAID_OUTPUT_ID1];
            return rc;
        }
    }

    for (UINT32 i = AAID_WIDTH1; i <= AAID_HEIGHT5; ++i)
    {
        if (aid == i)
        {
            *((UINT32 *)attr) = m_Width[i - AAID_WIDTH1];
            return rc;
        }
    }

    for (UINT32 i = AAID_HEIGHT1; i <= AAID_OUTPUT_ID5; ++i)
    {
        if (aid == i)
        {
            *((UINT32 *)attr) = m_Height[i- AAID_HEIGHT1];
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

    return RC::COMPONENT_GETATTRIBUTE_ERROR;
}

RC OutputExternalData::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    for (UINT32 i = AAID_OUTPUT_ID1; i <= AAID_OUTPUT_ID5; ++i)
    {
        if (aid == i)
        {
            m_OutputId[i - AAID_OUTPUT_ID1] = *((UINT32 *)attr);
            return rc;
        }
    }

    for (UINT32 i = AAID_WIDTH1; i <= AAID_WIDTH5; ++i)
    {
        if (aid == i)
        {
            m_Width[i - AAID_WIDTH1] = *((UINT32 *)attr);
            return rc;
        }
    }

    for (UINT32 i = AAID_HEIGHT1; i <= AAID_HEIGHT5; ++i)
    {
        if (aid == i)
        {
            m_Height[i - AAID_HEIGHT1] = *((UINT32 *)attr);
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

    return RC::COMPONENT_SETATTRIBUTE_ERROR;
}

bool OutputExternalData::Connect(IComponent *component)
{
    return false;
}

IComponent *OutputExternalData::Clone()
{
    OutputExternalData *outputExternalData = new OutputExternalData();
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        outputExternalData->m_OutputId[i] = m_OutputId[i];
        outputExternalData->m_Width[i] = m_Width[i];
        outputExternalData->m_Height[i] = m_Height[i];
        outputExternalData->m_FilePath[i] = m_FilePath[i];
    }
    outputExternalData->m_Id = m_Id;
    outputExternalData->m_Name = m_Name;
    return outputExternalData;
}

void OutputExternalData::Reset()
{
    m_Input->Reset();
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

RC OutputExternalData::Run()
{
    RC rc;

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        if (!m_Input->m_Array[i] ||
            m_FilePath[i].empty())
        {
            continue;
        }
        if (!Utility::FileExists(m_FilePath[i].c_str()))
        {
            if (!Utility::CreateFileNested(m_FilePath[i].c_str()))
            {
                return RC::FILE_OPEN_ERROR;
            }
        }
        HANDLE file = CreateFile(
            m_FilePath[i].c_str(),
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
        UINT32 x = m_Width[i];
        UINT32 m = mxGetM(m_Input->m_Array[i]);
        if (!x)
        {
            x = m;
        }
        UINT32 y = m_Height[i];
        UINT32 n = mxGetN(m_Input->m_Array[i]);
        if (!y)
        {
            y = n;
        }
        UINT32 length = x * y;
        double *buf = new double[length];
        memset(buf, 0, length * sizeof(char));
        double *content = mxGetPr(m_Input->m_Array[i]);
        for (UINT32 yy = 0; yy < min(n, y); ++yy)
        {
            for (UINT32 xx = 0; xx < min(m, x); ++xx)
            {
                buf[yy * x + xx] = content[yy * m + xx];
            }
        }
        DWORD written = 0;
        if (FALSE == WriteFile(file, (char *)buf, length * sizeof(double), &written, NULL))
        {
            delete[] buf;
            return RC::FILE_WRITE_ERROR;
        }
        delete[] buf;
        CloseHandle(file);
    }

    return rc;
}

RC OutputExternalData::GetOutput(IData *&output)
{
    return RC::COMPONENT_GETOUTPUT_ERROR;
}

OutputExternalData *OutputExternalData::Factory()
{
    OutputExternalData *outputExternalData = new OutputExternalData;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    outputExternalData->m_Name = name;
    ++s_Count;
    return outputExternalData;
}

LPCWSTR OutputExternalData::s_ComponentName = TEXT("输出DAT数据");

UINT32 OutputExternalData::s_Count = 0;
