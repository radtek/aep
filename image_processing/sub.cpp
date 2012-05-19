/**
* @file
* @brief 减法类cpp文件.
* @author ruoxi
*
* 实现了减法类.
*/

#include "stdafx.h"

#include "sub.h"
#include "matlab_helper.h"
#include "sub_config_dlg.h"
#include "sub/SubFunc.h"
#include "utility.h"

Sub::Sub()
{
    m_Input1 = new IImageAlgorithmInput1;
    m_Input2 = new IImageAlgorithmInput2;
    m_Output = new IImageAlgorithmOutput(m_OutputCount);
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        m_SubFactor[i] = 0;
    }
}

Sub::~Sub()
{
    delete m_Input1;
    delete m_Input2;
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        MatLabHelper::DestroyArray(m_Output->m_Array[i]);
    }
    delete m_Output;
}

UINT32 Sub::GetTypeId()
{
    return s_ComponentId;
}

void Sub::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str());

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar << m_SubFactor[i];
    }
}

void Sub::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar >> m_SubFactor[i];
    }
}

void Sub::Destroy()
{
    delete this;
}

void *Sub::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CIID_IALGORITHM == iid)
    {
        iface = static_cast<IAlgorithm *>(this);
    }
    else if (CLIENT_CIID_IMAGE_ALGORITHM == iid)
    {
        iface = static_cast<IImageAlgorithm *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 Sub::GetId()
{
    return m_Id;
}

void Sub::SetId(UINT32 id)
{
    m_Id = id;
}

wstring Sub::GetName()
{
    return m_Name;
}

void Sub::SetName(wstring name)
{
    m_Name = name;
}

void Sub::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    for (UINT32 i = AAID_SUB_FACTOR1; i <= AAID_SUB_FACTOR5; ++i)
    {
        attribute.Id = i;
        CString name = TEXT("减法因子");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_DOUBLE;
        attributeList.push_back(attribute);
    }
}

RC Sub::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    for (UINT32 i = AAID_SUB_FACTOR1; i <= AAID_SUB_FACTOR5; ++i)
    {
        if (aid == i)
        {
            *((double *)attr) = m_SubFactor[i];
            return rc;
        }
    }

    return rc;
}

RC Sub::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    for (UINT32 i = AAID_SUB_FACTOR1; i <= AAID_SUB_FACTOR5; ++i)
    {
        if (aid == i)
        {
            m_SubFactor[i] = *((double *)attr);
            return rc;
        }
    }

    return rc;
}

bool Sub::Connect(IComponent *component)
{
    return false;
}

IComponent *Sub::Clone()
{
    Sub *sub = new Sub();
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        sub->m_SubFactor[i] = m_SubFactor[i];
    }
    sub->m_Id = m_Id;
    sub->m_Name = m_Name;
    return sub;
}

void Sub::Reset()
{
    m_Input1->m_Array = 0;
    m_Input2->m_Array = 0;
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        MatLabHelper::DestroyArray(m_Output->m_Array[i]);
    }
    m_Output->Reset();
}

RC Sub::Config()
{
    RC rc;

    CSubConfigDlg dlg;
    dlg.m_SubFactor1 = m_SubFactor[0];
    dlg.m_SubFactor2 = m_SubFactor[1];
    dlg.m_SubFactor3 = m_SubFactor[2];
    dlg.m_SubFactor4 = m_SubFactor[3];
    dlg.m_SubFactor5 = m_SubFactor[4];
    INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
        m_SubFactor[0] = dlg.m_SubFactor1;
        m_SubFactor[1] = dlg.m_SubFactor2;
        m_SubFactor[2] = dlg.m_SubFactor3;
        m_SubFactor[3] = dlg.m_SubFactor4;
        m_SubFactor[4] = dlg.m_SubFactor5;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

    return rc;
}

RC Sub::SetInput(IData *input)
{
    if (NULL == input)
    {
        return RC::COMPONENT_SETINPUT_ERROR;
    }

    IExternalDataOutput *externalDataOutput = (IExternalDataOutput *)(input->GetInterface(CLIENT_CIID_EXTERNAL_DATA_OUTPUT));
    if (NULL != externalDataOutput)
    {
        m_Input1->m_Array = externalDataOutput->m_Array;
        return OK;
    }

    IImageOutput *imageOutput = (IImageOutput *)(input->GetInterface(CLIENT_CIID_IMAGE_OUTPUT));
    if (NULL != imageOutput)
    {
        m_Input2->m_Array = imageOutput->m_Array;
        return OK;
    }

    IImageAlgorithmOutput *imageAlgorithmOutput = (IImageAlgorithmOutput *)(input->GetInterface(CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT));
    if (NULL != imageAlgorithmOutput)
    {
        m_Input2->m_Array = imageAlgorithmOutput->m_Array[0];
        return OK;
    }

    return RC::COMPONENT_SETINPUT_ERROR;
}

RC Sub::GetOutput(IData *&output)
{
    output = (IData *)(m_Output->GetInterface(CIID_IDATA));

    return OK;
}

RC Sub::Run()
{
    RC rc;

    UINT32 x1 = mxGetM(m_Input1->m_Array);
    UINT32 y1 = mxGetN(m_Input1->m_Array);
    UINT32 x2 = mxGetM(m_Input2->m_Array);
    UINT32 y2 = mxGetN(m_Input2->m_Array);

    if (x1 != x2 || y1 != y2)
    {
        return RC::ALGORITHM_INPUT_ERROR;
    }

    if (!SubFuncInitialize())
    {
        return RC::ALGORITHM_RUN_INITIALIZE_ERROR;
    }

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        if (m_Output->m_Array[i] != NULL)
        {
            MatLabHelper::DestroyArray(m_Output->m_Array[i]);
        }
        Array *input3 = MatLabHelper::CreateDoubleArray(1, 1, &m_SubFactor[i]);
        m_Output->m_Array[i] = MatLabHelper::CreateDoubleArray(x1, y1);
        if (!mlfSubFunc(1, &m_Output->m_Array[i], m_Input2->m_Array, m_Input1->m_Array, input3))
        {
            SubFuncPrintStackTrace();
            return RC::ALGORITHM_RUN_ERROR;
        }
        MatLabHelper::DestroyArray(input3);
    }

    // SubFuncTerminate();

    return rc;
}

Sub *Sub::Factory()
{
    Sub *sub = new Sub;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    sub->m_Name = name;
    ++s_Count;
    return sub;
}

LPCWSTR Sub::s_ComponentName = TEXT("减法");

UINT32 Sub::s_Count = 0;
