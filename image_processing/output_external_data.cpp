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
#include "output_external_data_dlg.h"
#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

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
    m_Output.Reset();
}

RC OutputExternalData::Config()
{
    RC rc;

    COutputExternalDataDlg dlg;
    dlg.m_OutputId1 = m_OutputId[0];
    dlg.m_OutputId2 = m_OutputId[1];
    dlg.m_OutputId3 = m_OutputId[2];
    dlg.m_OutputId4 = m_OutputId[3];
    dlg.m_OutputId5 = m_OutputId[4];
    dlg.m_Width1 = m_Width[0];
    dlg.m_Width2 = m_Width[1];
    dlg.m_Width3 = m_Width[2];
    dlg.m_Width4 = m_Width[3];
    dlg.m_Width5 = m_Width[4];
    dlg.m_Height1 = m_Height[0];
    dlg.m_Height2 = m_Height[1];
    dlg.m_Height3 = m_Height[2];
    dlg.m_Height4 = m_Height[3];
    dlg.m_Height5 = m_Height[4];
    dlg.m_FilePath1 = m_FilePath[0].c_str();
    dlg.m_FilePath2 = m_FilePath[1].c_str();
    dlg.m_FilePath3 = m_FilePath[2].c_str();
    dlg.m_FilePath4 = m_FilePath[3].c_str();
    dlg.m_FilePath5 = m_FilePath[4].c_str();
    INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
        m_OutputId[0] = dlg.m_OutputId1;
        m_OutputId[1] = dlg.m_OutputId2;
        m_OutputId[2] = dlg.m_OutputId3;
        m_OutputId[3] = dlg.m_OutputId4;
        m_OutputId[4] = dlg.m_OutputId5;
        m_Width[0] = dlg.m_Width1;
        m_Width[1] = dlg.m_Width2;
        m_Width[2] = dlg.m_Width3;
        m_Width[3] = dlg.m_Width4;
        m_Width[4] = dlg.m_Width5;
        m_Height[0] = dlg.m_Height1;
        m_Height[1] = dlg.m_Height2;
        m_Height[2] = dlg.m_Height3;
        m_Height[3] = dlg.m_Height4;
        m_Height[4] = dlg.m_Height5;
        m_FilePath[0] = dlg.m_FilePath1;
        m_FilePath[1] = dlg.m_FilePath2;
        m_FilePath[2] = dlg.m_FilePath3;
        m_FilePath[3] = dlg.m_FilePath4;
        m_FilePath[4] = dlg.m_FilePath5;
	}

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
        memcpy(m_Input->m_Array, imageAlgorithmOutput->m_Array, m_OutputCount * sizeof(m_Input->m_Array[0]));
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

RC OutputExternalData::Run(bool input)
{
    RC rc;

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        m_Output.m_Path.push_back(m_FilePath[i]);
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

        wofstream ofs(m_FilePath[i].c_str());
        if (!ofs)
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
        memset(buf, 0, length * sizeof(double));
        double *content = mxGetPr(m_Input->m_Array[i]);
        for (UINT32 yy = 0; yy < min(n, y); ++yy)
        {
            for (UINT32 xx = 0; xx < min(m, x); ++xx)
            {
                buf[yy * x + xx] = content[yy * m + xx];
            }
        }
        ofs << x << endl;
        ofs << y << endl;
        for (UINT32 yy = 0; yy < y; ++yy)
        {
            for (UINT32 xx = 0; xx < x; ++xx)
            {
                ofs << buf[yy * x + xx] << TEXT(' ');
            }
            ofs << endl;
        }
        delete[] buf;
        ofs.close();
    }

    return rc;
}

RC OutputExternalData::GetOutput(IData *&output)
{
    RC rc;

    output = (IData *)(m_Output.GetInterface(CIID_IDATA));

    return rc;
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
