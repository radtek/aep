/**
* @file
* @brief ����ⲿ������cpp�ļ�.
* @author ruoxi
*
* ʵ��������ⲿ������.
*/

#include "stdafx.h"

#include "output_image.h"
#include "utility.h"
#include "output_image_dlg.h"
#include "matlab_helper.h"

OutputImage::OutputImage()
:
m_Depth(24)
{
    m_Input = new IOutputFileInput(m_OutputCount);
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        m_OutputId[i] = 0;
        m_Width[i] = 0;
        m_Height[i] = 0;
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
        ar << m_Width[i];
        ar << m_Height[i];
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
        ar >> m_Width[i];
        ar >> m_Height[i];
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

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        attribute.Id = AAID_OUTPUT_ID1 + i;
        CString name = TEXT("�㷨���ID");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_INT;
        attributeList.push_back(attribute);

        attribute.Id = AAID_WIDTH1 + i;
        name = TEXT("������");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_INT;
        attributeList.push_back(attribute);

        attribute.Id = AAID_HEIGHT1 + i;
        name = TEXT("����߶�");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_INT;
        attributeList.push_back(attribute);

        attribute.Id = AAID_FILE_PATH1 + i;
        name = TEXT("���BMPͼ��·��");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_STRING;
        attributeList.push_back(attribute);
    }

    attribute.Id = AAID_DEPTH;
    attribute.Name = TEXT("λ��");
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

    if (aid == AAID_DEPTH)
    {
        m_Depth = *((UINT32 *)attr);
        return rc;
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
        outputImage->m_Width[i] = m_Width[i];
        outputImage->m_Height[i] = m_Height[i];
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

    COutputImageDlg dlg;
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
    dlg.m_Depth = m_Depth;
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
        m_Depth = dlg.m_Depth;
	}

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
        if (!m_Input->m_Array[i] || m_FilePath[i].empty())
        {
            continue;
        }
        UINT32 x = m_Width[i];
        UINT32 m = mxGetM(m_Input->m_Array[i]);
        if (!x)
        {
            UINT32 bpp = m_Depth / 8;
            x = (m + bpp - 1) / bpp;
        }
        UINT32 y = m_Height[i];
        UINT32 n = mxGetN(m_Input->m_Array[i]);
        if (!y)
        {
            y = n;
        }

        UINT32 size = m * n * (m_Depth / 8);
        // char *buf = new char[size];
        double *content = mxGetPr(m_Input->m_Array[i]);
        /*
        for (UINT32 j = 0; j < size; ++j)
        {
            buf[j] = (char)content[j];
        }
        */

        // Utility::SaveBmpFile(bitmap, m_FilePath.c_str());
        CHECK_RC(Utility::SaveBmpFile(m_FilePath[i].c_str(), x, y, content, m, n, 0, 0, m_Depth));
        // delete[] buf;
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

LPCWSTR OutputImage::s_ComponentName = TEXT("���BMPͼ��");

UINT32 OutputImage::s_Count = 0;
